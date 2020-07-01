#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m3dia.hpp>
#include "scene.hpp"


class Minigame : public Scene
{
	
	private:
		static bool winCond;
		static Scene* m_currentScene;

	public:
		virtual bool checkWinCond() = 0;

		void toggleWinCond()
		{
			winCond = !winCond; 
		}


		virtual void loadScene() = 0;
		virtual void loadWinScr() = 0;
		virtual void loadLoseScr() = 0;
		
		

		virtual void closeGame() = 0;
	//from scene
		virtual void initialize()=0;
		virtual void load()=0;
		virtual void unload()=0;
		virtual void update()=0;
		virtual void draw()=0;

		virtual void onEnter()=0;

		virtual void onExit()=0;

	
	

};





