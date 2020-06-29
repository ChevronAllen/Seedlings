#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"

class TerminalObject : public GameObject
{

private:
    m3dCI::Sprite *texture;
    m3dCI::Sprite *sprite;
    bool (*wall)[24][40];
    //pointer to maze array 

public:
    TerminalObject(bool (*walls)[24][40])
    {
        wall =  walls;
        x = 370;
        y = 220;
        xScale = 1;
        yScale = 1;
        angle = 0;
    }

    ~TerminalObject()
    {
        texture = NULL;
    }

    void initialize()
    {
        sprite = new m3dCI::Sprite(*(ResourceManager::getSprite("terminal.png")));
        sprite->setScale(xScale,yScale);
        sprite->setPosition(x,y);
    }

    void update() {
        
    };

    void draw()
    {
        m3d::Screen * screen = GameManager::getScreen();

		sprite->setPosition(x, y);
        screen->drawTop(*sprite);
    }


    void destroy(){ this->~TerminalObject(); }
    void moveTo(double _x,double _y)
    {
        if( (x + _x) < 0 || (y + _y) < 0 || (x + _x) >= 40 || (y + _y) >= 24)
            return;
        if((*wall)[(int)(x + _x)][(int)(y + _y)]==0)
        {
            x += (_x * 10);
	        y += (_y * 10);
        }
    };
    void Rotate(double deg){};
};
