#include "WallLine.h"
#include <sstream>

//-------------------------------------------------------------------------------------
///Create given number of wall in given direction
WallLine::WallLine(Ogre::SceneManager* manager, int x, int y, const Ogre::Vector2& v, const MyDirection& m):blockLength(300)
{
	int a = 0;
	int b = 0;
	float c = blockLength / 2.0f;
		
	bool isHorizontal = false;
	if(m ==Left || m == Right){
		isHorizontal= true;
	}

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			switch (m) {
				case Left:
					a += -blockLength;
					break;
				case Right:
					a += blockLength;
					break;
				case Front:
					b += -blockLength;
					break;
				case Back:
					b += blockLength;
					break;
				default:
					break;
			}
			Ogre::Real posX= v.x + a;
			Ogre::Real posZ= v.y + b;

			Ogre::Vector3 posVec = Ogre::Vector3(posX, c, posZ);
			std::stringstream ss;
			ss<<"wall" << a << b << c << genRandom(5);
			std::shared_ptr<Wall> helpWall = (std::shared_ptr<Wall>) new Wall(
				manager, 
				ss.str(), 
				posVec,
				isHorizontal);
			wallVector.push_back(helpWall);
					
		}
		a = 0; b = 0;
		c += blockLength;
	}
}
//-------------------------------------------------------------------------------------
///using random string like prevention of collision in entity and sceneNode register
std::string WallLine::genRandom( size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str;
    str.resize( length );
    std::generate_n( str.begin(), length, randchar );
    return str;
}
//-------------------------------------------------------------------------------------
WallLine::~WallLine(void)
{
}
//-------------------------------------------------------------------------------------