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
	
	Sound(const char* path, int width, int height);
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
	void setVolume(int diff);
	int volume;
	const int volumeDiff;
	static const int overlayDurationConst;

	irrklang::ISoundEngine* engine;
	Ogre::Overlay* overlay;
	std::vector<std::string> songNames;
	irrklang::ISound* song;
	int actualSongNumber;
	int durationOverlay;
	bool overlayIsShowed;
	Ogre::TextAreaOverlayElement* musicTextArea;
};

#endif // #ifndef __Sound_h_

