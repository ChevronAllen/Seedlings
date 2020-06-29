#pragma once
#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "../MenuHandler.hpp"
#include "../scene.hpp"
#include "../resources.h"
#include "../minigame.hpp"
#include "../gameObjects/mazePlayer.hpp"

class MazeScene : public Minigame
{
	private:
		m3dCI::Sprite *wallpaper;
		m3dCI::Sprite *texture;
        m3dCI::Sprite* popup;
		m3dCI::Sprite* dummy;
		m3dCI::Button *retryBtn, *exitBtn;
		ObjectManager* om;
		m3d::Rectangle *winScreen;
        m3d::Rectangle *loseScreen;
		m3d::Color *colorRec;
		m3d::Color *colorText;
		m3d::Text *prompt;
		m3dCI::Text* popupText;
        TerminalObject *runner;
		int x, y, runnerID;
        bool walls[24][40] ={ { 1, 0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
            { 1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1},
            { 1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1},
            { 1, 0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1},
            { 1, 1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1},
            { 1, 0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1},
            { 1, 0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1},
            { 1, 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
            { 1, 0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1},
            { 1, 0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1},
            { 1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  1},
            { 1, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  0,  0,  1},
            { 1, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1}};
            //2d array acting as map of array
        bool (*wallHolder)[24][40] = &walls;
		//wallHolder = &walls;

		enum MazeState
		{
			TutorialMessage,
			Requesting,
			Execute,
			Win,
			Lose
		};
		MazeState currentState;
	public:
		MazeScene()
		{
            //array traversers
            x = 1.0;
			y = 0.0;
			om = ObjectManager::getInstance();
		}

		void initialize(){
            sandbox = new LuaSandbox();
			sandbox->executeFile("lua/init_scene.lua");

        //loads and gets maze texture
			//texture = new m3dCI::Sprite(*(ResourceManager::getSprite("wall.png")));
            //sprite* spr = new m3d::Sprite();

       //initialize playable character
            runner = new TerminalObject(wallHolder);

			runnerID = addObject(runner);
            runner->initialize();
			setObjectName("runner", runnerID);
			//addObject(runner);

       //Load text and bottom screen background color
			colorRec = new m3d::Color(150,150,150);
			colorText = new m3d::Color(0,0,0);

       //initializes text and bottom screen background
			winScreen = new m3d::Rectangle(0,0,320,240,*colorRec);
			prompt = new m3d::Text("Maze",*colorText);
			prompt->setPosition(160,120);
			wallpaper   = new m3dCI::Sprite(*(ResourceManager::getSprite("maze.png")));
            //  Initialize popup BG
            popup       = new m3dCI::Sprite(*(ResourceManager::getSprite("menu_popup.png")));
            popup->setPosition(80,20);
		    //wallpaper->setTexture(*texture);
		    wallpaper->setCenter(0,0);
		    wallpaper->setScale(10,10);



			currentState = MazeState::TutorialMessage;

			// TODO:
			// - add functionality to buttons in popup menu
			// - add line by line text in popup menu 
			// - calculate terminal object's new position based on commands

			dummy = new m3dCI::Sprite(*(ResourceManager::getSprite("retry.png")));
			dummy->setPosition(80, 20);
			
			retryBtn = om->CreateButton(100, 150, 85, 50, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);
			retryBtn->SetText("RETRY");

			exitBtn = om->CreateButton(200, 150, 85, 50, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);
			exitBtn->SetText("EXIT");


			popupText = new m3dCI::Text("Use the commands!");
			popupText->setFontSize(.7);
			popupText->setFontWeight(.7);
			popupText->setColor(m3d::Color(0, 0, 0));	
			popupText->setPosition(100,50);
		}

		void draw(){
			m3d::Screen * screen = GameManager::getScreen();

		    wallpaper->setPosition(0,0);
            screen->drawTop(*wallpaper);
			//ObjectManager* om = ObjectManager::getInstance();

            if(currentState == MazeState::TutorialMessage)
            {   
				
				
                screen->drawTop(*popup);
				screen->drawTop(*popupText, RenderContext::Mode::Flat);
				screen->drawTop(*retryBtn, RenderContext::Mode::Flat);
				screen->drawTop(*exitBtn, RenderContext::Mode::Flat);
				
				
				
            }

			//screen->drawBottom(*bwallpaper);
			//screen->drawBottom(*prompt);

            runner->draw();

			/*
			if (runner->getPosition().u >= 370 || runner->getPosition().v >= 220)
			{
				//loseScreen = new m3d::Rectangle(300, 300, 50, 50, m3d::Color(0, 0, 100));
				//screen->drawTop(*loseScreen);
				screen->drawTop(*popup);
				m3d::Text* loseMsg = new m3d::Text("You lose ...", m3d::Color(0, 0, 0));
				loseMsg->setPosition(140, 120);
				
				screen->drawTop(*loseMsg);
				//screen->drawTop(*dummy);
			}
			*/
		

		}

        void load(){}; //any data files
        
        void unload(){};
        
        void update(){

			switch (currentState)
			{
				case MazeState::TutorialMessage:

					if (buttons::buttonDown(buttons::Start))
					{
						currentState = MazeState::Requesting;

						std::vector<CommandObject*> startingCommands =
						{
							new SelectCommand("runner",true,false),
							new DownCommand("5",false,true),
							new RightCommand("15")
						};

						MenuHandler::RequestUserCode(startingCommands, [&](std::vector<CommandObject*> commands) { SubmitMazeCode(commands); });
					}
					break;
				case MazeState::Execute:
					break;
				case MazeState::Win:
					break;
				case MazeState::Lose:
					break;
				case MazeState::Requesting:
					break;
			}
        };

		void SubmitMazeCode(std::vector<CommandObject*> luaCode)
		{
			std::string str = CommandObject::ConvertBulk(luaCode);

			Util::getInstance()->PrintLine(str);

			sandbox->executeString(str);
			currentState = MazeState::Execute;
		}

        void onEnter(){};
        void onExit(){};
        bool checkWinCond(){return true;};
        void loadScene(){};
        
		void loadLoseScr()
		{
			
		}


        void loadWinScr(){};
        void requestUI(){};
        void closeGame(){};
};
