#pragma once

#include "menu.hpp"

class MainMenu : public Menu
{
	private:
		m3d::Rectangle* whiteBackground;

		m3dCI::Text* StartupText;
		m3dCI::Button* ClickHereToContinue;
		m3dCI::Sprite* apple;
	public:
		MainMenu(m3d::Screen* screen);
		virtual ~MainMenu();
		
		void OnUpdate();
};