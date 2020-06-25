#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <m3dia.hpp>

using namespace m3d;

class Minigame
{
	// TODO: add appropiate parameters to methods
	private:
		m3d::Screen* scr;
		m3d::Applet* app;
		bool winState;
		//need description and title
		//small sprite icon
		//large sprite to display next to icon
		//constructor that take title and description
		//Scrapped below:
		//get name
		//get description
		//get sprite
		//stat virtual name; <-might be static virtual function

	public:
		virtual void start() = 0;
		virtual void update() = 0;
		virtual bool checkWinState() = 0;
		virtual void loadSetting() = 0;
		virtual void loadWinScreen() = 0; //
		virtual void loadLoseScreen() = 0; //
		virtual void requestUserInput() = 0; //loads keyboard
		virtual void closeGame() = 0;



};
