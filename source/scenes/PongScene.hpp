#pragma once
#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "../MenuHandler.hpp"
#include "../scene.hpp"
#include "../resources.h"
#include "../gameObjects/pongBall.hpp"


class PongScene : public Minigame
{

	private:
		m3dCI::Sprite* wallpaper;
		m3dCI::Sprite* popup;
		PongBall* ball;

		enum PongState
		{
			TutorialMessage,
			Requesting,
			Execute,
			Win,
			Lose
		};

		PongState currentState;
	public:
		PongScene() : Minigame()
		{
			
		}

		void initialize()
		{
			
			wallpaper = new m3dCI::Sprite(*(ResourceManager::getSprite("pong1.png")));
			//  Initialize popup BG
			popup = new m3dCI::Sprite(*(ResourceManager::getSprite("menu_popup.png")));
			popup->setPosition(80, 20);
			//wallpaper->setTexture(*texture);
			wallpaper->setCenter(0, 0);
			wallpaper->setScale(1, 1);


			//runnerID = addObject(runner);
			
			//setObjectName("runner", runnerID);
			ball = new PongBall();
			ball->initialize();

		}

		void draw()
		{
			m3d::Screen* screen = GameManager::getScreen();

			wallpaper->setPosition(0, 0);
			screen->drawTop(*wallpaper);

			ball->draw();
			ball->update();
			

		
		}

		void load() {}; //any data files

		void unload() {};

		void update()
		{
			
			
		}


		void onEnter() {};
		void onExit() {};
		bool checkWinCond() { return true; }
		void loadScene() {};
		void loadWinScr() {};
		void loadLoseScr() {};
		void requestUI() {};
		void closeGame() {};



};
