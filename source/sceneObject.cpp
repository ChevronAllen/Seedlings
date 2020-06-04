#include "sceneObject.hpp"

void sceneObject::setToggle(bool toggle, m3d::Screen *screen)
{
            //m3d::Screen screen;
    gameObject *printme ;
    m3d::Rectangle *gamObj;
    if(toggle == true)
    {
        screen->drawTop(*back);
        screen->drawTop(*wall1);
        
        screen->drawTop(*wall2);
        screen->drawTop(*wall3);
        screen->drawTop(*wall4);
        screen->drawTop(*wall5);
        screen->drawTop(*wall6);
        screen->drawTop(*wall7);
        screen->drawTop(*wall8);
        screen->drawTop(*wall9);
        screen->drawTop(*wall10);
        screen->drawTop(*wall11);
        screen->drawTop(*wall12);
        screen->drawTop(*wall13);
        screen->drawTop(*wall14);
        screen->drawTop(*wall15);
        screen->drawTop(*wall16);
        screen->drawTop(*wall17);
        screen->drawTop(*wall18);
        screen->drawTop(*wall19);
        screen->drawTop(*wall20);
        screen->drawTop(*wall21);
        screen->drawTop(*wall22);
        screen->drawTop(*wall23);
        screen->drawTop(*wall24);
        screen->drawTop(*wall25);
        screen->drawTop(*wall26);
        screen->drawTop(*wall27);
        screen->drawTop(*wall28);
        screen->drawTop(*wall29);
        screen->drawTop(*wall30);
        screen->drawTop(*wall31);
        screen->drawTop(*wall32);
        screen->drawTop(*wall33);
        screen->drawTop(*wall34);
        
    	list<gameObject*>::iterator i;
		for( i = golist->begin(); i != golist->end(); ++i){
        	printme = *i;
        	gamObj = printme->gamObj;
        	screen->drawTop(*gamObj);
    	}
	}
}
void sceneObject::addtolist(gameObject *gobj){
    golist->insert(golist->end(),1, gobj);
}
void sceneObject::deletefromlist(gameObject *gobj)
{
	gameObject* remove;
	remove = gobj;
	golist->remove(gobj);
	delete remove; 
}
