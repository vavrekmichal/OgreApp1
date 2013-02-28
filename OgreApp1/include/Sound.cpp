#include "Sound.h"


#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

irrklang::ISoundEngine* engine;
std::vector<std::string> songNames;
irrklang::ISound* song;
int actualSongNumber = 0;
Ogre::Overlay* overlay;
int durationOverlay = 0;
bool overlayIsShowed = false;
Ogre::TextAreaOverlayElement* musicTextArea;

//volume 
int volume = 5;


#ifdef _DEBUG
    const int Sound::overlayDurationConst = 50;
#else
    const int Sound::overlayDurationConst = 500;
#endif
//-------------------------------------------------------------------------------------
///Load all songs, initializes overlay and play first
Sound::Sound(const char* path, int width, int height)
{
	engine = irrklang::createIrrKlangDevice();
	
	struct dirent *entry;
	DIR *dp;

	dp = opendir(path);
	std::string stringName;

	if (dp == NULL) {
		perror("opendir: Path does not exist or could not be read.");
	}else{
		while ((entry = readdir(dp))){
			stringName = entry->d_name;
			if(!(!strcmp(".", stringName.c_str())||!strcmp("..",stringName.c_str()))){
				songNames.push_back(std::string(path)+ '/'+ entry->d_name);	
			}
		}
	}
	song = engine->play2D(songNames[0].c_str(), false, false, true);
	song->setVolume(volume);

	closedir(dp);
	
	//Event Listener
	song->setSoundStopEventReceiver(this);
	
	//overlay
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton(); 

    //Create a panel 
    Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(overlayManager.createOverlayElement("Panel", "MusicPanel")); 
    panel->setMetricsMode(Ogre::GMM_PIXELS); 
	panel->setDimensions(width*9/10, 50);
 
	panel->setLeft((width - panel->getWidth()) / 2);   
    panel->setMaterialName("Core/StatsBlockCenter"); // Optional background material 
   
    // Create a text area 
    musicTextArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "MusicTextArea")); 
    musicTextArea->setMetricsMode(Ogre::GMM_PIXELS); 
	musicTextArea->setTop(5);
	musicTextArea->setLeft((( panel->getWidth())) / 4);
	musicTextArea->setCharHeight(14);   
    musicTextArea->setFontName("StarWars"); 

	// Add the text area to the panel 
    panel->addChild(musicTextArea); 

    // Create an overlay, and add the panel 
    overlay = overlayManager.create("MusicBox"); 
    overlay->add2D((panel)); 

	actualSong();
}

//-------------------------------------------------------------------------------------
Sound::~Sound(void)
{
	engine->drop();
}
//-------------------------------------------------------------------------------------
///Get random next song and play it (not same)
void Sound::playNext(void){
	int i= rand() % songNames.size();
	while(i == actualSongNumber) {i = rand() % songNames.size();}
	song = engine->play2D(songNames[i].c_str(), false, false, true);
	setVolume(0);
	//Event Listener
	song->setSoundStopEventReceiver(this);
	actualSongNumber=i;
	actualSong();
}
//-------------------------------------------------------------------------------------
///implements onSoundStopped for cyclic play
void Sound::OnSoundStopped (irrklang::ISound* isound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData){
	
	if(reason==irrklang::ESEC_SOUND_FINISHED_PLAYING||reason==irrklang::ESEC_SOUND_STOPPED_BY_USER){
		playNext();
	}
	
}
//-------------------------------------------------------------------------------------
///print actual song into overlay
void Sound::actualSong(void){
	musicTextArea->setCaption("\nNiny hraje " + std::string(songNames[actualSongNumber]).substr(16,songNames[actualSongNumber].size()-1));
	overlay->show();
	overlayIsShowed = true;
	durationOverlay = overlayDurationConst;
}
//-------------------------------------------------------------------------------------
///controls visibility of overlay
void Sound::update(void){
	if(overlayIsShowed){
		if(durationOverlay==0){
			overlayIsShowed=false;
			overlay->hide();
		}else{
			--durationOverlay;
		}
	}
}
//-------------------------------------------------------------------------------------
///shows overlay with actual volume
void Sound::showVolume(void){
	std::stringstream ss;//create a stringstream
	ss << volume *10<<" procent";
	musicTextArea->setCaption(std::string("\nHlasitost je ") + ss.str() );
	overlay->show();
	overlayIsShowed = true;
	durationOverlay = overlayDurationConst;
}
//-------------------------------------------------------------------------------------
///set given volume
void Sound::setVolume(int diff){
	volume +=diff; 
	if(volume<0)volume = 0;
	if(volume>10)volume = 10;
	song->setVolume((float)volume/10);
	showVolume();
}
//-------------------------------------------------------------------------------------
void Sound::increaseVolume(void){
	setVolume(1);
}
//-------------------------------------------------------------------------------------
void Sound::decreaseVoleme(void){
	setVolume(-1);
}
//-------------------------------------------------------------------------------------
void Sound::nextSong(void){
	song->stop();
}
//-------------------------------------------------------------------------------------
///paused or unpaused actual playing sound
void Sound::pauseSong(void){
	if(song->getIsPaused()){
		song->setIsPaused(false);
		actualSong();
	}else{
		song->setIsPaused(true);
		musicTextArea->setCaption(std::string("\nHudba je pozastavena." ));
		overlay->show();
		overlayIsShowed = true;
		durationOverlay = overlayDurationConst;
	}
}
//-------------------------------------------------------------------------------------



