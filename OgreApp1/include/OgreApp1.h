#ifndef __OgreApp1_h_
#define __OgreApp1_h_

#include "Sound.h" 
#include "BaseApplication.h"
#include "Player.h"
#include "WallLine.h"


#include "Mission.h"
#include "GuardGroup.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


class OgreApp1 : public BaseApplication
{
public:
    OgreApp1(void);
    virtual ~OgreApp1(void);
	static void endGame(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	// OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent& evt );
    virtual bool keyReleased( const OIS::KeyEvent& evt );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent& evt );
    virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
	
 
    Ogre::Real mRotate;          // The rotate constant
    Ogre::Real mMove;            // The movement constant
    Ogre::SceneNode *mCamNode;   // The SceneNode the camera is currently attached to
    Ogre::Vector3 mDirection;    // Value to move in the correct direction
	std::shared_ptr<Player> ninjaPlayer;


	std::shared_ptr<Mission> mission;
	std::shared_ptr<Sound> soundPlayer;
	std::vector<std::shared_ptr<WallLine>> walls;
	std::vector<std::shared_ptr<GuardGroup>> guardGroups;

private:
	void setLights(void);
	void setGround(void);
	void setSky(void);
	void setFog(void);
	void createWalls(void);
	void createGuards(void);
	void lose(const std::string reason);

	void updateCamera(const float f);
	bool goingForward;
    bool goingBack;
    bool goingRight;
    bool goingLeft;
    bool goingUp;
    bool goingDown;
    bool fastMove;
	static bool gameRunning;

};

#endif // #ifndef __OgreApp1_h_
