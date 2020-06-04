#include <m3dia.hpp>
#include <time.h>
#include "gameObject.hpp"
#include <stdlib.h>
#include <list> 
#include <iterator>

using namespace std;

class sceneObject{
    public:
        m3d::Color *colorRec;
        m3d::Color *colorBack;

        m3d::Rectangle *wall1; 
        m3d::Rectangle *wall2; 
        m3d::Rectangle *wall3; 
        m3d::Rectangle *wall4; 
        m3d::Rectangle *wall5; 
        m3d::Rectangle *wall6; 
        m3d::Rectangle *wall7; 
        m3d::Rectangle *wall8; 
        m3d::Rectangle *wall9; 
        m3d::Rectangle *wall10; 
        m3d::Rectangle *wall11; 
        m3d::Rectangle *wall12; 
        m3d::Rectangle *wall13; 
        m3d::Rectangle *wall14; 
        m3d::Rectangle *wall15; 
        m3d::Rectangle *wall16; 
        m3d::Rectangle *wall17; 
        
        m3d::Rectangle *wall18; 
        m3d::Rectangle *wall19; 
        m3d::Rectangle *wall20; 
        m3d::Rectangle *wall21;
        m3d::Rectangle *wall22; 
        m3d::Rectangle *wall23; 
        m3d::Rectangle *wall24; 
        m3d::Rectangle *wall25; 
        m3d::Rectangle *wall26; 
        m3d::Rectangle *wall27; 
        m3d::Rectangle *wall28; 
        m3d::Rectangle *wall29; 
        m3d::Rectangle *wall30; 
        m3d::Rectangle *wall31; 
        m3d::Rectangle *wall32; 
        m3d::Rectangle *wall33; 
        m3d::Rectangle *wall34;
        m3d::Rectangle *back;
        list <gameObject*> *golist;
        
        sceneObject(){ 
            colorRec = new m3d::Color(0,0,0); 
            colorBack = new m3d::Color(200,200,200);
            wall1 = new m3d::Rectangle(0,0,400,1,*colorRec);
            wall2 = new m3d::Rectangle(0,238,400,1,*colorRec);
            wall3 = new m3d::Rectangle(0,119,400,1,*colorRec);
            wall4 = new m3d::Rectangle(0,59,400,1,*colorRec);
            wall5 = new m3d::Rectangle(0,179,400,1,*colorRec);
            wall6 = new m3d::Rectangle(0,15,400,1,*colorRec);
            wall7 = new m3d::Rectangle(0,30,400,1,*colorRec);
            wall8 = new m3d::Rectangle(0,45,400,1,*colorRec);
            wall9 = new m3d::Rectangle(0,75,400,1,*colorRec);
            wall10 = new m3d::Rectangle(0,90,400,1,*colorRec);
            wall11 = new m3d::Rectangle(0,105,400,1,*colorRec);
            wall12 = new m3d::Rectangle(0,135,400,1,*colorRec);
            wall13 = new m3d::Rectangle(0,150,400,1,*colorRec);
            wall14 = new m3d::Rectangle(0,165,400,1,*colorRec);
            wall15 = new m3d::Rectangle(0,195,400,1,*colorRec);
            wall16 = new m3d::Rectangle(0,210,400,1,*colorRec);
            wall17 = new m3d::Rectangle(0,225,400,1,*colorRec);
            
            wall18 = new m3d::Rectangle(398,0,1,300,*colorRec);
            wall19 = new m3d::Rectangle(0,0,1,300,*colorRec);
            wall21 = new m3d::Rectangle(199,0,1,300,*colorRec);
            wall22 = new m3d::Rectangle(99,0,1,300,*colorRec);
            wall23 = new m3d::Rectangle(299,0,1,300,*colorRec);
            wall24 = new m3d::Rectangle(50,0,1,300,*colorRec);
            wall25 = new m3d::Rectangle(150,0,1,300,*colorRec);
            wall26 = new m3d::Rectangle(250,0,1,300,*colorRec);
            wall27 = new m3d::Rectangle(350,0,1,300,*colorRec);
            wall28 = new m3d::Rectangle(25,0,1,300,*colorRec);
            wall29 = new m3d::Rectangle(75,0,1,300,*colorRec);
            wall30 = new m3d::Rectangle(125,0,1,300,*colorRec);
            wall31 = new m3d::Rectangle(175,0,1,300,*colorRec);
            wall32 = new m3d::Rectangle(225,0,1,300,*colorRec);
            wall33 = new m3d::Rectangle(275,0,1,300,*colorRec);
            wall34 = new m3d::Rectangle(325,0,1,300,*colorRec);
            wall20 = new m3d::Rectangle(375,0,1,300,*colorRec);
            back = new m3d::Rectangle(0,0,400,300,*colorBack);
            
            golist = new list<gameObject*>;
        }

        void setToggle(bool toggle , m3d::Screen *screen);

        void addtolist(gameObject *gobj); 
        void deletefromlist(gameObject *gobj);
};



