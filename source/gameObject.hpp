#include <m3dia.hpp>
//#include "sceneObject.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;

class gameObject{
	public:
		int xpos;
		int ypos;
		m3d::Color *colorRec; 
    	m3d::Rectangle *gamObj;

		gameObject(){
			xpos = 5;
			ypos = 5;
			colorRec = new m3d::Color(150,0,0); 
	    	gamObj = new m3d::Rectangle(xpos,ypos,10,10,*colorRec);
		}
		void moveGameObject(int dir);
};
/*void gameObject::moveGameObject(int xdir, int ydir)
{
	xpos = xpos + xdir;  
	ypos = ypos + ydir; 
	gamObj->setYPosition(ypos);
	gamObj->setXPosition(xpos);
	
	//screen->drawTop(*gamObj);
}*/