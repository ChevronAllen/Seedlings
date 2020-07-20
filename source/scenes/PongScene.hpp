#pragma once
#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "../resources.h"
#include "../gameObjects/pongPaddle.hpp"
#include "../scenes/scene.hpp"
#include "../scenes/MainMenuScene.hpp"
#include <array>

#ifdef DEBUG
//#define DEBUG_MAZE
#endif


class PongScene : public Minigame
{
	private:
		//TextMenuItem *prompt, *winPrompt;
		SpriteMenuItem *popup, *wallpaper, *wPopup;
		PongBall *ball;
		PongPaddle *leftPaddle, *rightPaddle;
		array<int, 2> points; 
		int matchPoint; 
		
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
		PongScene();
		~PongScene();

		void initialize();

		void draw();
		
		void load();
        
		void unload();
        
		void update();

		void SubmitPongCode(std::vector<CommandObject*> luaCode);

		void onEnter();
		void onExit();
		bool checkWinCond();
		void loadScene();
		void loadWinScr();
		void loadLoseScr();
		void requestUI();
		void closeGame();
};
