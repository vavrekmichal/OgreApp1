#ifndef __Sound_h_
#define __Sound_h_

#include <irrKlang.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>

class Sound : irrklang::ISoundStopEventReceiver
{
public:
	
	Sound(const char* path, const int width, const int height);
	~Sound(void);
	void playNext(void);
	virtual void OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData);
	void update(void);

	void showVolume(void);
	void increaseVolume(void);
	void decreaseVoleme(void);
	void nextSong(void);
	void actualSong(void);
	void pauseSong(void);

private:
	void setVolume(const int diff);
	static const int overlayDurationConst;
};

#endif // #ifndef __Sound_h_

