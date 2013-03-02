#include "OgreApp1.h"
#include "DieException.h"

bool OgreApp1::gameRunning (true);

Ogre::Real mRotate;          // The rotate constant
Ogre::Real mMove;            // The movement constant
 
Ogre::Vector3 mDirection;     // Value to move in the correct direction

static bool castOverlay(false);
Ogre::OverlayContainer* endPanel;
Ogre::TextAreaOverlayElement* endTextArea;
Ogre::Overlay* endOverlay;
//-------------------------------------------------------------------------------------
OgreApp1::OgreApp1(void):
    goingForward(false),
	goingBack(false),
    goingRight(false),
    goingLeft(false),
    goingUp(false),
    goingDown(false),
    fastMove(false),
	rotate(.15),
	move(150)
{
}
//-------------------------------------------------------------------------------------
OgreApp1::~OgreApp1(void)
{

}

//-------------------------------------------------------------------------------------
void OgreApp1::createCamera(void)
{
	// create the camera
    mCamera = mSceneMgr->createCamera("MyUpperCam");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(0,500,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    // set the near clip distance
    mCamera->setNearClipDistance(5);
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}
 
//-------------------------------------------------------------------------------------
void OgreApp1::createViewports(void)
{
	// Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));  
}
//-------------------------------------------------------------------------------------
void OgreApp1::createScene(void)
{
	Ogre::ResourceManager::ResourceMapIterator font = Ogre::FontManager::getSingleton().getResourceIterator();

    while( font.hasMoreElements() )
    {
        font.getNext()->load();
    }
	
	setLights();
	setGround();
	setSky();
	setFog();
	createWalls();

	ninjaPlayer = (std::shared_ptr<Player>)new Player(mSceneMgr,"ninja.mesh","Ninja",Ogre::Vector3(0,0,0));
	mission = (std::shared_ptr<Mission>) new Mission(mSceneMgr,"MyMission",ninjaPlayer->getSceneNode(), mWindow);
	soundPlayer = (std::shared_ptr<Sound>) new Sound("../../media/song", mWindow->getWidth(), mWindow->getHeight());

	createGuards();
}

//-------------------------------------------------------------------------------------

void OgreApp1::createFrameListener(void)
{
	BaseApplication::createFrameListener();
 
	// set the rotation and move speed
	mRotate = rotate;
	mMove = move;
	mDirection = Ogre::Vector3::ZERO;
}
//-------------------------------------------------------------------------------------
bool OgreApp1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if (mWindow->isClosed()) return false;
    if (mShutDown) return false;
	mKeyboard->capture();
	mMouse->capture();
	mTrayMgr->frameRenderingQueued(evt);
	if(gameRunning){
		updateCamera(evt.timeSinceLastFrame);
		mission->update();
		ninjaPlayer->update(evt.timeSinceLastFrame);
		soundPlayer->update();
		try{
			for(std::vector<std::shared_ptr<GuardGroup>>::iterator it=guardGroups.begin();
				it!=guardGroups.end();
				++it){
					(*it)->update(evt.timeSinceLastFrame);
			}
		}catch(const DieException & d){
			lose(d.exceptionReason);
			
			ninjaPlayer->die();
		}
	}
	return true;	
}
//-------------------------------------------------------------------------------------
///OIS::KeyListener
bool OgreApp1::keyPressed( const OIS::KeyEvent& evt ){
	
	if(evt.key==OIS::KC_ESCAPE){
		//Ogre::OverlayManager::getSingleton().destroy("LoseBox");
		mShutDown = true;
		return true;
	}
	if(evt.key==OIS::KC_LSHIFT){
		fastMove=true;
	}
	if(evt.key==OIS::KC_UP||evt.key==OIS::KC_W){
		goingForward=true;
	}
	if(evt.key==OIS::KC_DOWN||evt.key==OIS::KC_S){
		goingBack=true;
	}
	if(evt.key==OIS::KC_LEFT||evt.key==OIS::KC_A){
		goingLeft=true;
	}
	if(evt.key==OIS::KC_RIGHT||evt.key==OIS::KC_D){
		goingRight=true;;
	}
	if(evt.key==OIS::KC_PGDOWN||evt.key==OIS::KC_E){
		goingUp=true;
	}
	if(evt.key==OIS::KC_PGUP||evt.key==OIS::KC_Q){
		goingDown=true;
	}
	
	
    return true;
}
//-------------------------------------------------------------------------------------
bool OgreApp1::keyReleased( const OIS::KeyEvent& evt ){

	if(evt.key==OIS::KC_F){
		soundPlayer->showVolume();
	}

	if(evt.key==OIS::KC_I){
		soundPlayer->increaseVolume();
	}

	if(evt.key==OIS::KC_K){
		soundPlayer->decreaseVoleme();
	}
	
	if(evt.key==OIS::KC_M){
		soundPlayer->nextSong();
	}

	if(evt.key==OIS::KC_N){
		soundPlayer->actualSong();
	}

	if(evt.key==OIS::KC_B){
			soundPlayer->pauseSong();
	}

	if(evt.key==OIS::KC_LSHIFT){
		fastMove=false;
	}
	if(evt.key==OIS::KC_UP||evt.key==OIS::KC_W){
		goingForward=false;
	}
	if(evt.key==OIS::KC_DOWN||evt.key==OIS::KC_S){
		goingBack=false;
	}
	if(evt.key==OIS::KC_LEFT||evt.key==OIS::KC_A){
		goingLeft=false;
	}
	if(evt.key==OIS::KC_RIGHT||evt.key==OIS::KC_D){
		goingRight=false;
	}
	if(evt.key==OIS::KC_PGDOWN||evt.key==OIS::KC_E){
		goingUp=false;
	}
	if(evt.key==OIS::KC_PGUP||evt.key==OIS::KC_Q){
		goingDown=false;
	}
	return true;
}
//-------------------------------------------------------------------------------------
///OIS::MouseListener
bool OgreApp1::mouseMoved( const OIS::MouseEvent& evt ){

	if(evt.state.buttonDown(OIS::MB_Middle) ){
		mSceneMgr->getCamera("MyUpperCam")->yaw(Ogre::Degree(-mRotate * evt.state.X.rel));
	}else{
		mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(-mRotate * evt.state.X.rel), Ogre::Node::TS_WORLD);
	}

	return true;
}
//-------------------------------------------------------------------------------------
bool OgreApp1::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id ){
	Ogre::SceneNode* ninjaNode = mSceneMgr->getSceneNode("NinjaNode");
	Ogre::Vector3 ninjaMove = Ogre::Vector3(0,0,0);
	
	if(id==OIS::MB_Left){
		ninjaPlayer->goingForward=true;
	}
	if(id==OIS::MB_Right){
		ninjaPlayer->goingBack=true;
	}
	return true;
}
//-------------------------------------------------------------------------------------
bool OgreApp1::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id ){
	Ogre::SceneNode* ninjaNode = mSceneMgr->getSceneNode("NinjaNode");
	if(id==OIS::MB_Left){
		ninjaPlayer->goingForward=false;
	}
	if(id==OIS::MB_Right){
		ninjaPlayer->goingBack=false;
	}
	return true;
}

//-------------------------------------------------------------------------------------
///Setters
void OgreApp1::setFog(void){
	Ogre::ColourValue fadeColour(0.9, 0.9, 0.9);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 10, 2000);
	mWindow->getViewport(0)->setBackgroundColour(fadeColour);
}
//-------------------------------------------------------------------------------------
void OgreApp1::setSky(void){
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
}
//-------------------------------------------------------------------------------------
void OgreApp1::setGround(void){
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 150000, 150000, 200, 200, true, 1, 500, 500, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
 
    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(true);
}
//-------------------------------------------------------------------------------------
void OgreApp1::setLights(void){
	 mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
	 mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);

 
    Ogre::Light* directionalLight = mSceneMgr->createLight("directionalLight");
    directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(Ogre::ColourValue(.2,.2,.2));
    directionalLight->setSpecularColour(Ogre::ColourValue(.25,.25, 0));
 
    directionalLight->setDirection(Ogre::Vector3( 0, -5, -1 )); 

    Ogre::Light* spotLight = mSceneMgr->createLight("spotLight");
    spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(1, 1, 1);
    spotLight->setSpecularColour(1.0, 1.0, 1.0);
 
    spotLight->setDirection(0, -1, -3);
    spotLight->setPosition(Ogre::Vector3(0, 5000, 15000));
 
    spotLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(90));

}
//-------------------------------------------------------------------------------------
///Creaters
void OgreApp1::createWalls(void){
	std::ifstream myfile;
	myfile.open("../../media/mission/missionSetter.ogre");
	
	while(myfile.good())
	{
		std::string st;
		std::getline(myfile,st);
		std::istringstream istr(st);
		if(st!=""){
			int height,width,x,y;
			std::string stringType;
			MyDirection type;
			istr>>height;
			istr>>width;
			istr>>x;
			istr>>y;
			istr>>stringType;
			if(stringType=="Front"){
				type=Front;
			}else{
				if(stringType=="Back"){
					type=Back;
				}else{
					if(stringType=="Left"){
						type=Left;
					}else{
						if(stringType=="Right"){
							type=Right;
						}else{

						}
					}
				}
			}
			
			walls.push_back((std::shared_ptr<WallLine>)new WallLine(mSceneMgr, height, width, Ogre::Vector2(x, y), type));
		}
	}
}
//-------------------------------------------------------------------------------------
void OgreApp1::createGuards(void){
	
	std::deque<Ogre::Vector3> positions;

	positions.push_back( Ogre::Vector3(-8300, 0, 500));
	positions.push_back( Ogre::Vector3(-400, 0, 500));
	positions.push_back( Ogre::Vector3(-4000, 0, 0));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr,"robot1.mesh", "Protector", 2, positions, Cyclic));

	//second group up --2
	positions.clear();
	positions.push_back( Ogre::Vector3(-8300, 0, -3000));
	positions.push_back( Ogre::Vector3(-400, 0, -3000));
	positions.push_back( Ogre::Vector3(-4000, 0, -2500));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr,"robot1.mesh", "Protector of God", 2, positions, Cyclic));
	
	//3rd group up-down1 --2
	positions.clear();
	positions.push_back( Ogre::Vector3(-400, 0, -200));
	positions.push_back( Ogre::Vector3(-350, 0, -200));
	positions.push_back( Ogre::Vector3(-350, 0, -3000));
	positions.push_back( Ogre::Vector3(-400, 0, -3000));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Hell", 2, positions, Cyclic));
	
	//4th group up-down1 --2
	positions.clear();
	positions.push_back( Ogre::Vector3(-8250, 0, -200));
	positions.push_back( Ogre::Vector3(-8200, 0, -200));
	positions.push_back( Ogre::Vector3(-8200, 0, -3000));
	positions.push_back( Ogre::Vector3(-8250, 0, -3000));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Sky", 2, positions, Cyclic));
	
	//5th group middle-box --3
	positions.clear();
	positions.push_back( Ogre::Vector3(-4300, 0, -1650));
	positions.push_back( Ogre::Vector3(-4300, 0, 0));
	positions.push_back( Ogre::Vector3(-4700, 0, -1650));
	positions.push_back( Ogre::Vector3(-4700, 0, 0));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Sea", 3, positions, Cyclic));

	//6th group under-box-line --5
	positions.clear();
	positions.push_back( Ogre::Vector3(-8000, 0, -350));
	positions.push_back( Ogre::Vector3(-700, 0, -100));
	positions.push_back( Ogre::Vector3(-8000, 0, -500));
	positions.push_back( Ogre::Vector3(-4700, 0, -350));
	positions.push_back( Ogre::Vector3(-700, 0, -350));
	positions.push_back( Ogre::Vector3(-4700, 0, -100));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Heaven", 5, positions, Cyclic));

	//7th group upper-box-line --3
	positions.clear();
	positions.push_back( Ogre::Vector3(-4500, 0, -2700));
	positions.push_back( Ogre::Vector3(-6300, 0, -2400));
	positions.push_back( Ogre::Vector3(-2400, 0, -2400));
	positions.push_back( Ogre::Vector3(-4500, 0, -2000));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Darkness", 3, positions, Cyclic));


	//8th group left-box-line --3
	positions.clear();
	positions.push_back( Ogre::Vector3(-7000, 0, 0));
	positions.push_back( Ogre::Vector3(-7000, 0, -2700));		
	positions.push_back( Ogre::Vector3(-7500, 0, -1350));
	positions.push_back( Ogre::Vector3(-6500, 0, -1350));
	positions.push_back( Ogre::Vector3(-7000, 0, -1350));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Pain", 3, positions, Cyclic));

	//9th group right-box-line --3
	positions.clear();
	positions.push_back( Ogre::Vector3(-1500, 0, 0));
	positions.push_back( Ogre::Vector3(-1500, 0, -2700));
	positions.push_back( Ogre::Vector3(-2100, 0, -1350));
	positions.push_back( Ogre::Vector3(-1000, 0, -1350));
	positions.push_back( Ogre::Vector3(-1500, 0, -1350));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Himself", 3, positions, Cyclic));

	//Random Guards --2
	positions.clear();
	positions.push_back( Ogre::Vector3(-8000, 0, -3000));
	positions.push_back( Ogre::Vector3(  500, 0,   500));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Chaos", 1, positions, Random));

	positions.clear();
	positions.push_back( Ogre::Vector3(-4000, 0, -1000));
	positions.push_back( Ogre::Vector3(  0, 0,   0));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Heart", 1, positions, Random));

	//Line Guards --3
	positions.clear();
	positions.push_back( Ogre::Vector3(300, 0, -2800));
	positions.push_back( Ogre::Vector3(300, 0,   0));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Fear", 1, positions, Line));

	positions.clear();
	positions.push_back( Ogre::Vector3(-100, 0, -2800));
	positions.push_back( Ogre::Vector3(-100, 0,   0));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Terror", 1, positions, Line));

	positions.clear();
	positions.push_back( Ogre::Vector3(100, 0, -2700));
	positions.push_back( Ogre::Vector3(100, 0, -1800));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Begin", 1, positions, Line));

	//Follow Guards --2
	positions.clear();
	positions.push_back( Ogre::Vector3(-1000, 0, -2800));
	positions.push_back( Ogre::Vector3(-1000, 0,  -100));
	guardGroups.push_back((std::shared_ptr<GuardGroup>)new GuardGroup(mSceneMgr, "robot1.mesh", "Protector of Your Path", 2, positions, Follower));
}
//-------------------------------------------------------------------------------------
///Others
void OgreApp1::updateCamera(const float f){
	mDirection=Ogre::Vector3(0,0,0);

	float realSpeed = mMove;

	if(fastMove){
		realSpeed *=3; 
	}

	if(goingForward){
		mDirection.z = -realSpeed;
		mDirection.y = realSpeed;
	}

	if(goingBack){
		mDirection.z = realSpeed;
		mDirection.y = -realSpeed;
	}

	if(goingLeft){
		mDirection.x = -realSpeed;
	}

	if(goingRight){
		mDirection.x = realSpeed;
	}

	if(goingUp){
		mDirection.y = -realSpeed;
	}

	if(goingDown){
		mDirection.y = realSpeed;
	}
	mCamera->moveRelative(mDirection * f);
}

//-------------------------------------------------------------------------------------
void OgreApp1::endGame(void){

	gameRunning=false;
}

//-------------------------------------------------------------------------------------
void OgreApp1::lose( const std::string reason){
	if(!castOverlay){
		castOverlay=true;
		Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton(); 

		//Create a panel 
		endPanel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "LosePanel")); 
		endPanel->setMetricsMode(Ogre::GMM_PIXELS); 
		endPanel->setDimensions(350, 75);
 
		endPanel->setLeft((mWindow->getWidth() - endPanel->getWidth()) / 2);
		endPanel->setTop((mWindow->getHeight() - endPanel->getHeight()) / 2);    
		endPanel->setMaterialName("Core/StatsBlockCenter"); // Optional background material 
   
		// Create a text area 
		endTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "LoseOutput")); 
		endTextArea->setMetricsMode(Ogre::GMM_PIXELS); 
		endTextArea->setDimensions(300, 50);
		endTextArea->setCaption("Lituji ale prohral jsi protoze\n"+reason);
		endTextArea->setLeft((endPanel->getWidth() - endTextArea->getWidth()) / 2);
		endTextArea->setTop((endPanel->getHeight() - endTextArea->getHeight()) / 2);
		endTextArea->setCharHeight(14);    
		endTextArea->setFontName("StarWars"); 

		// Add the text area to the panel 
		endPanel->addChild(endTextArea); 

		// Create an overlay, and add the panel 
		endOverlay = overlayManager.create("LoseBox"); 
		endOverlay->add2D((endPanel)); 
		endOverlay->show();
	}
}
//-------------------------------------------------------------------------------------





#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        OgreApp1 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
