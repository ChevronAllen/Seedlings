#include "../gameObject.hpp"
#include "../gameManager.hpp"
#include "../resources.h"


class PongBall : public GameObject
{

private:
    m3dCI::Sprite *texture;
    m3dCI::Sprite *sprite;
	int dirX = 1, dirY = 1; 
	

public:
	PongBall()
    {
        x = 180;
        y = 110;
        xScale = 1;
        yScale = 1;
        angle = 0;
    }

    ~PongBall()
    {
        texture = NULL;
    }

    void initialize()
    {
        sprite = new m3dCI::Sprite(*(ResourceManager::getSprite("ball.png")));
        sprite->setScale(xScale,yScale);
        sprite->setPosition(x,y);
    }

    void update() {

		//TODO: 
		// - control ball movement w/ respect to paddles
		// - refactor window bounds with variables 
		// - reset the ball 

		moveTo(2 * dirX, 2 * dirY);

		if (x <= 0 || x >= 400)
		{
			dirX *= -1;
		}
		
		if (y >= 240 || y <= 0)
		{
			dirY *= -1;
			//reset();
		}
		
    };

	void reset()
	{
		x = 180;
		y = 110;
	}

    void draw()
    {
        m3d::Screen * screen = GameManager::getScreen();

		sprite->setPosition(x, y);
        screen->drawTop(*sprite);


    }


    void destroy(){ this->~PongBall(); }
    void moveTo(double _x,double _y)
    {
		y += _y;
		x += _x;
  
    };
    void Rotate(double deg){};
  
};
