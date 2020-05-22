#include <m3dia.hpp>
//#include "sceneObject.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;

class sceneObject{
	public:
		m3d::Color *colorRec; 
    	m3d::Rectangle *wall34;	
    	//bool toggle;
	    sceneObject(){ 
	    	colorRec = new m3d::Color(150,0,0); 
	    	wall34 = new m3d::Rectangle(0,225,400,1,*colorRec);
	    }

    	void setToggle(bool toggle , m3d::Screen *screen);
};
void sceneObject::setToggle(bool toggle, m3d::Screen *screen)
{
	        //m3d::Screen screen;
	if(toggle == true)
	{
	   	screen->drawTop(*wall34);
    }
}
int main() {
	m3d::Applet app;
	m3d::Screen screen;
	//m3d::Screen *screen1 = &screen;
	sceneObject *test = new sceneObject();
	while(app.isRunning())
	{
        if (m3d::buttons::buttonPressed(m3d::buttons::B)) {
            app.exit();
        }
        
        //if (m3d::buttons::buttonPressed(m3d::buttons::A)) {
        test->setToggle(true, &screen);
       //}
        screen.render();
	}
	return(0);
}