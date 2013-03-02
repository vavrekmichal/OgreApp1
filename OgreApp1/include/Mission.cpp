#include "Mission.h"
#include "OgreApp1.h"

 #ifdef _DEBUG
    const int Mission::overlayDurationConst (50);
#else
    const int Mission::overlayDurationConst (500);
#endif
//-------------------------------------------------------------------------------------
Mission::Mission(Ogre::SceneManager* mSceneManager, const std::string& missionName, Ogre::SceneNode *playerNode, Ogre::RenderWindow *window):
	name(missionName),player(playerNode),mWindow(window),duration(0),remainIsShowed(false)
{
	inicialization(mSceneManager,window);
}
//-------------------------------------------------------------------------------------
Mission::~Mission(void)
{
	Ogre::OverlayManager::getSingleton().destroy("RemainingBox");
}
//-------------------------------------------------------------------------------------
///The function initializes all mission targets and mission overlay
void Mission::inicialization(Ogre::SceneManager* mSceneManager, Ogre::RenderWindow *window){

	//mission loader
	std::ifstream myfile;
	myfile.open("../../media/mission/missionTargets.ogre");
	
	while(myfile.good())
	{
		std::string st;
		std::getline(myfile,st);
		std::istringstream istr(st);
		if(st!=""){
			std::string name;
			int x,y,z;
			istr>>name;
			istr>>x;
			istr>>y;
			istr>>z;
			targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, name, Ogre::Vector3(x, y, z), player));
		}
	}

	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton(); 

    //Create a panel 
    Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "MyPanel")); 
    panel->setMetricsMode(Ogre::GMM_PIXELS); 
	panel->setDimensions(350, 75);
 
	panel->setLeft((window->getWidth() - panel->getWidth()) / 2);
	panel->setTop((window->getHeight() - panel->getHeight()) / 2);    
    panel->setMaterialName("Core/StatsBlockCenter"); // Optional background material 
   
    // Create a text area 
    remainTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "Output")); 
    remainTextArea->setMetricsMode(Ogre::GMM_PIXELS); 
	remainTextArea->setDimensions(300, 50);
	remainTextArea->setLeft((panel->getWidth() - remainTextArea->getWidth()) / 2);
	remainTextArea->setTop((panel->getHeight() - remainTextArea->getHeight()) / 2);
	remainTextArea->setCharHeight(14);    
    remainTextArea->setFontName("StarWars"); 

	// Add the text area to the panel 
    panel->addChild(remainTextArea); 

    // Create an overlay, and add the panel 
    remainOverlay = overlayManager.create("RemainingBox"); 
    remainOverlay->add2D((panel)); 
		
}
//-------------------------------------------------------------------------------------
///Mission update controls visibility of overlays and calls update on targets. Also if 
///count of targets is 0 -> mission is complere
void Mission::update(void){
	if(remainIsShowed){
		if(duration<1){
			remainOverlay->hide(); 
			remainIsShowed=false;
		}else{
			--duration;
		}
	}

	std::vector<std::shared_ptr<Target>>::iterator it = targetVector.begin();
	for (; it != targetVector.end(); ) {
		(*it)->update();
		if ((*it)->checkDistanceFromCollector()){
			it = targetVector.erase(it);
			if(targetVector.size()==0){
				remainTextArea->setCaption(std::string("\nBlahopreji, vyhral jsi!\nPro ukonceni stiskni ESC"));
				remainOverlay->show();
				OgreApp1::endGame();
			}else{
				// Show the overlay 
				std::stringstream ss;//create a stringstream
				ss << targetVector.size();//add number to the stream
			 
				remainTextArea->setCaption(std::string("\nZbyva ti jeste sebrat ")+ss.str()+" hlav");
				remainOverlay->show();
				remainIsShowed=true;
				duration=overlayDurationConst;
			}
		}
		else
			++it;
	}	
}
//-------------------------------------------------------------------------------------