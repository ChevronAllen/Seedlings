#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"

class TerminalObject : public GameObject
{

private:
    m3dCI::Sprite *texture;
    m3dCI::Sprite *sprite;
    bool (*wall)[12][20];
    int counter;
    //pointer to maze array 

public:
    TerminalObject(bool (*walls)[12][20])
    {
        wall =  walls;
        x = 20;
        y = 20;
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
        int i;
        int xc = (x/20);
        int yc = (y/20);
         /*

        
        if( (x + _x) < 0 || (y + _y) < 0 || (x + _x) >= 40 || (y + _y) >= 24)
            return;
        
        if((*wall)[(int)(x + _x)][(int)(y + _y)]==0)
        {
            x += (_x * 10);
	        y += (_y * 10);
        }*/
        //if( (xc + _x) < 0 || (yc + _y) < 0 || (xc + _x) >= 20 || (yc + _y) >= 12)
            //return;
        if(_y == 0)
        {
            if(_x > 0)
            {
                _x += xc;
                for( i = xc; i < (int)_x; i++)
                {
                    if((*wall)[yc][i + 1] == 1)
                    {
                        break;
                    }
                        
                    x = x + 20;
                }
            }
            if(_x < 0)
            {
                _x += xc;
                for(i = xc; i > (int)_x; i--)
                {
                    if((*wall)[yc][i - 1] == 1)
                        break;
                    x -= 20;
                }
            }
            
        }
        if(_x==0)
        {
            if(_y > 0)
            {
                _y += yc;
                for(i = yc; i < (int)_y; i++)
                {
                    if((*wall)[i+1][xc] == 1)
                        break;
                    y += 20;
                }
            }
            if(_y < 0)
            {
                _y += yc;
                for( i = yc; i > (int)_y; i--)
                {
                    if((*wall)[i - 1][xc] == 1)
                        break;
                    y -= 20;
                }
            }
        }
        
    };
    void Rotate(double deg){};
};
