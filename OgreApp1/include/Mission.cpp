#include "Mission.h"
#include "OgreApp1.h"

 #ifdef _DEBUG
    const int Mission::overlayDurationConst = 50;
#else
    const int Mission::overlayDurationConst = 500;
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

	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target1", Ogre::Vector3(100, 100, -3000), player)); //on highway
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target2", Ogre::Vector3(100, 100, -1500), player)); //on highway
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target3", Ogre::Vector3(100, 100, -500), player)); //on highway
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target4", Ogre::Vector3(-4500, 100, -1700), player)); //in box
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target5", Ogre::Vector3(-700, 100, -100), player)); //right-down corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target6", Ogre::Vector3(-8000, 100, -2700), player)); //left-up corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target7", Ogre::Vector3(-4500, 100, -2700), player)); //center-up corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target8", Ogre::Vector3(-4500, 100, 100), player)); //center-down corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target9", Ogre::Vector3(-8200, 100, 100), player)); //left-down corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target10", Ogre::Vector3(-8000, 100, -100), player)); //left-down corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target11", Ogre::Vector3(-1000, 100, -1500), player)); //center-down corner
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target12", Ogre::Vector3(-3000, 100, -1500), player)); //center-right 
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target13", Ogre::Vector3(-6000, 100, -1500), player)); //center-left 
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target14", Ogre::Vector3(-2700, 100, -1500), player)); //center-right 
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target15", Ogre::Vector3(-6300, 100, -1500), player)); //center-left 
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target16", Ogre::Vector3(-3300, 100, -1500), player)); //center-right 
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target17", Ogre::Vector3(-6700, 100, -1500), player)); //center-left 
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target18", Ogre::Vector3(-8300, 100, -1500), player)); //left-center
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target19", Ogre::Vector3(-7300, 100, -2000), player)); //left-up
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target20", Ogre::Vector3(-7300, 100, -1000), player)); //left-down
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target21", Ogre::Vector3(-1400, 100, -2000), player)); //right-up
	targetVector.push_back((std::shared_ptr<Target>)new Target(mSceneManager, "target22", Ogre::Vector3(-1400, 100, -1000), player)); //right-down

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
			

	//Create a panel 
    Ogre::OverlayContainer* winPanel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "WinPanel")); 
    winPanel->setMetricsMode(Ogre::GMM_PIXELS); 
	winPanel->setDimensions(350, 75);
 
	winPanel->setLeft((window->getWidth() - winPanel->getWidth()) / 2);
	winPanel->setTop((window->getHeight() - winPanel->getHeight()) / 2);    
    winPanel->setMaterialName("Core/StatsBlockCenter"); // Optional background material 
   
    // Create a text area 
    Ogre::TextAreaOverlayElement* winText = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "WinText")); 
    winText->setMetricsMode(Ogre::GMM_PIXELS); 
	winText->setDimensions(300, 50);
	winText->setLeft((panel->getWidth() - winText->getWidth()) / 2);
	winText->setTop((panel->getHeight() - winText->getHeight()) / 2);
	winText->setCharHeight(14);    
	winText->setCaption("\nBlahopreji, vyhral jsi!\nPro ukonceni stiskni ESC");
    winText->setFontName("StarWars"); 

	// Add the text area to the panel 
    winPanel->addChild(winText); 

    // Create an overlay, and add the panel 
    winOverlay = overlayManager.create("WinBox"); 
    winOverlay->add2D(winPanel); 
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
				winOverlay->show();
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