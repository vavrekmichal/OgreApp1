#ifndef __Mission_h_
#define __Mission_h_

#include "Target.h"
#include <string>
#include <vector>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>


class Mission
{
public:
	Mission(Ogre::SceneManager* mSceneManager, const std::string& missionName, Ogre::SceneNode *playerNode, Ogre::RenderWindow *window);
	~Mission(void);
	void update(void);

protected:
	void inicialization(Ogre::SceneManager *mSceneMgr, Ogre::RenderWindow *mWindow);

	std::string name; //name of mission
	std::vector<std::shared_ptr<Target>> targetVector; //List of targets to complete this mission
	Ogre::SceneNode *player; // Players SceneNode. In this case is Ninja
	Ogre::RenderWindow *mWindow; //RenderWindow instance for making overlays
	float mTimer; //float as timer to determine of duration overlay
private:
	Ogre::Overlay* remainOverlay;
	Ogre::TextAreaOverlayElement* remainTextArea;
	int duration;
    bool remainIsShowed;
	static const int overlayDurationConst;
};

#endif // #ifndef __Mission_h_
