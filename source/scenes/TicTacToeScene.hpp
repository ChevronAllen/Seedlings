#pragma once
#include "../gameManager.hpp"
#include "../sceneManager.hpp"
#include "../resources.h"
#include "../scenes/scene.hpp"
#include "../scenes/MainMenuScene.hpp"

class TicTacToeScene : public Minigame 
{
    private: 
        SpriteMenuItem *wallpaper, *popup;
        m3d::Color *colorRec, *colorText;
        TextMenuItem *prompt, *winPrompt;

        enum TTTState 
        {
            TutorialMessage,
            Requesting,
            Execute,
            EnemyTurn,
            Win,
            Lose
        };

        TTTState currentState;

        enum BoardState
        {
            VACANT,
            X,
            O
        };

        BoardState currentBoardState[3][3];
    public:
        TicTacToeScene();
        ~TicTacToeScene();

        void initialize();

        void draw();

        void load();

        void unload();
        
        void update();

        void SubmitTTTCode(std::vector<CommandObject*> luaCode);

        void onEnter();
		void onExit();
		bool checkWinCond();
		void loadScene();
		void loadWinScr();
		void loadLoseScr();
		void requestUI();
		void closeGame();

};