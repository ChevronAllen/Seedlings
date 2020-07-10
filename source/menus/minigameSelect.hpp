#pragma once

#include "menu.hpp"
#include "../sceneManager.hpp"
#include "MinigameDescriptor.hpp"

#define MINIGAME_COUNT 6

class MinigameSelect : public Menu
{
	private:
		enum MINIGAME_LIST
		{
			MAZE = 0,
			PONG = 1
		};

		//std::vector<MinigameDescriptor
		MinigameDescriptor minigames[MINIGAME_COUNT] =
		{
			MinigameDescriptor("Maze", "Navigate through a maze.\n\n\n\nAims to teach: Object Movement", "mazeSmall.png", "mazeLarge.png"),
			MinigameDescriptor("Pong", "Don't let the ball bounce\ninto your base!\n\n\nAims to teach: Conditionals", "pongSmall.png", "pongLarge.png"),
			MinigameDescriptor("Tic-Tac-Toe", "Get three X's in a row!\n\n\n\nAims to teach: Object Creation", "TTTSmall.png", "TTTLarge.png"),
			MinigameDescriptor(),
			MinigameDescriptor(),
			MinigameDescriptor()
		};
		
		int selectedMinigame = -1;
		
		m3d::Rectangle* whiteBackground;

		m3dCI::Sprite *selectedMinigameLargeSprite = nullptr;
		m3dCI::Text *MinigameSelectTopText = nullptr, *MinigameDescription = nullptr, *MinigameName = nullptr;
		m3dCI::Button* minigameOptions[MINIGAME_COUNT];
	public:
		MinigameSelect(m3d::Screen* screen);
		virtual ~MinigameSelect();

		void SelectMinigame(int index);
		
		void OnUpdate();
};