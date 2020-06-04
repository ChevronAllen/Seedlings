//#include "gameObject.hpp"
#include "sceneObject.hpp"

void gameObject::moveGameObject(int dir)
{
	//if(xpos >= 0 && xpos <= 400)
	//	xpos = xpos + xdir;  
	//ypos = ypos + ydir; 

	if(dir == 1)
		if(ypos > 0)
			ypos--;
	if(dir == 2)
		if(ypos < 230)
			ypos++;
	if(dir == 3)
		if(xpos > 0)
			xpos--;
	if(dir == 4)
		if(xpos < 390)
			xpos++;


	gamObj->setYPosition(ypos);
	gamObj->setXPosition(xpos);
	
	//screen->drawTop(*gamObj);
}
