#include "minigameSelect.hpp"
#include "../scenes/MazeScene.hpp"
#include "../scenes/PongScene.hpp"

#define xScale 1.3f
#define yScale 1.3f

MinigameSelect::MinigameSelect(m3d::Screen* screen) :
	Menu(screen)
{
	MinigameSelectTopText = new m3dCI::Text("Select a minigame");
	MinigameSelectTopText->setFontSize(1);
	MinigameSelectTopText->setFontWeight(1);
	MinigameSelectTopText->setColor(m3d::Color(0, 0, 0));

	int width = MinigameSelectTopText->getWidth();
	int height = MinigameSelectTopText->getHeight();
	
	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();

	MinigameSelectTopText->setPosition((topScreenWidth / 2) - (width / 2), (screenHeight / 2) - (height / 2));
	
	MinigameName = new m3dCI::Text("[SELECTED MINIGAME]");
	MinigameName->setFontSize(0.9);
	MinigameName->setFontWeight(0.9);
	MinigameName->setColor(m3d::Color(0, 0, 0));
	MinigameName->setPosition(20 + 100, 45);

	MinigameDescription = new m3dCI::Text("If you see this then\n I made a mistake..");
	MinigameDescription->setFontSize(0.6);
	MinigameDescription->setFontWeight(0.6);
	MinigameDescription->setColor(m3d::Color(0, 0, 0));
	MinigameDescription->setPosition(20+100, 90);

	whiteBackground = new m3d::Rectangle(0, 0, 1000, 1000, m3d::Color(255, 255, 255));

	int ButtonWidth = 50;
	int ButtonHeight = 50;

	int Rows = MINIGAME_COUNT / 3;
	int Columns = MINIGAME_COUNT / 2;

	int rowPadding = ((screenHeight * 0.25) * Rows - (ButtonHeight * Rows)) / (Rows - 1);
	int columnPadding = ((bottomScreenWidth * 0.25) * Columns - (ButtonWidth * Columns)) / (Columns - 1);//45

	for (int i = 0; i < MINIGAME_COUNT; i++)
	{
		int column = i % Columns;
		int row = i / 3;

		int x = (bottomScreenWidth * 0.25) / 2 + (columnPadding * column) + (ButtonWidth * column),
			y = (screenHeight * 0.25) + (rowPadding * row) + (ButtonHeight * row),
			w = ButtonWidth,
			h = ButtonHeight;

		m3dCI::Button* newButton;
		if (minigames[i].getSmallSpriteLocation() != "NULL")
			newButton = om->CreateButton(x, y, new m3dCI::Sprite(*ResourceManager::getSprite(minigames[i].getSmallSpriteLocation())));
		else
			newButton = om->CreateButton(x, y, w, h, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);

		newButton->OnRelease = [&, i]()
		{
			//second touch
			if (selectedMinigame == i)
			{
				if (i == MINIGAME_LIST::MAZE)
					SceneManager::transitionTo(new MazeScene());
				if (i == MINIGAME_LIST::PONG)
					SceneManager::transitionTo(new PongScene());

				MenuHandler::getInstance()->TransitionTo(MenuHandler::MenuState::MinigameTemplateMenu);
			}
			else
			{
				SelectMinigame(i);
			}
		};

		minigameOptions[column + (row * Columns)] = newButton;
	}

	OnUpdate();
}

void MinigameSelect::OnUpdate()
{
	if (util->IsConsoleDrawn())
		return;

	if (Input::btnReleased(m3d::buttons::DPadRight))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame + 1);
	else if (Input::btnReleased(m3d::buttons::DPadLeft))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame - 1);
	else if (Input::btnReleased(m3d::buttons::DPadDown))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame + 3);
	else if (Input::btnReleased(m3d::buttons::DPadUp))
		SelectMinigame(selectedMinigame == -1 ? 0 : selectedMinigame - 3);

	if (Input::btnReleased(m3d::buttons::B))
	{
		if (selectedMinigame != -1)
		{
			int addedWidth = minigameOptions[selectedMinigame]->getWidth() * xScale - minigameOptions[selectedMinigame]->getWidth();
			int x = minigameOptions[selectedMinigame]->getXPosition() + (addedWidth / 2);
			int addedHeight = minigameOptions[selectedMinigame]->getHeight() * yScale - minigameOptions[selectedMinigame]->getHeight();
			int y = minigameOptions[selectedMinigame]->getYPosition() + (addedHeight / 2);

			minigameOptions[selectedMinigame]->setScale(1.0f, 1.0f);
			minigameOptions[selectedMinigame]->setPosition(x, y);

			selectedMinigame = -1;
		}
		else
		{
			mh->TransitionTo(MenuHandler::MenuState::MainMenu);
			return;
		}
	}

	scr->drawTop(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawBottom(*whiteBackground, RenderContext::Mode::Flat);

	if(selectedMinigame == -1)
		scr->drawTop(*MinigameSelectTopText, RenderContext::Mode::Flat);
	else
	{
		scr->drawTop(*MinigameName, RenderContext::Mode::Flat);
		scr->drawTop(*MinigameDescription, RenderContext::Mode::Flat);
		scr->drawTop(*selectedMinigameLargeSprite, RenderContext::Mode::Flat);
	}

	for(int i = 0; i < MINIGAME_COUNT; i++)
		scr->drawBottom(*minigameOptions[i], RenderContext::Mode::Flat);

	if (Input::btnReleased(m3d::buttons::A) && selectedMinigame != -1)
		minigameOptions[selectedMinigame]->OnRelease();
}

MinigameSelect::~MinigameSelect()
{
	for (int i = 0; i < MINIGAME_COUNT; i++)
		om->DeleteButton(minigameOptions[i]);

	delete(whiteBackground);
	delete(MinigameSelectTopText);
	delete(MinigameName);
	delete(MinigameDescription);
	delete(selectedMinigameLargeSprite);
}

void MinigameSelect::SelectMinigame(int index)
{
	index = (index < 0?MINIGAME_COUNT + index : index) % MINIGAME_COUNT;

	if (index < 0 || index >= MINIGAME_COUNT)
		return;

	if (selectedMinigame != -1)
	{
		int addedWidth = minigameOptions[selectedMinigame]->getWidth() * xScale - minigameOptions[selectedMinigame]->getWidth();
		int x = minigameOptions[selectedMinigame]->getXPosition() + (addedWidth / 2);
		int addedHeight = minigameOptions[selectedMinigame]->getHeight() * yScale - minigameOptions[selectedMinigame]->getHeight();
		int y = minigameOptions[selectedMinigame]->getYPosition() + (addedHeight / 2);

		minigameOptions[selectedMinigame]->setScale(1.0f, 1.0f);
		minigameOptions[selectedMinigame]->setPosition(x, y);
	}

	selectedMinigame = index;

	selectedMinigameLargeSprite = new m3dCI::Sprite(*ResourceManager::getSprite(minigames[index].getLargeSpriteLocation()));
	selectedMinigameLargeSprite->setPosition(10, 45);

	int addedWidth = minigameOptions[index]->getWidth() * xScale - minigameOptions[index]->getWidth();
	int x = minigameOptions[index]->getXPosition() - (addedWidth / 2);
	int addedHeight = minigameOptions[index]->getHeight() * yScale - minigameOptions[index]->getHeight();
	int y = minigameOptions[index]->getYPosition() - (addedHeight / 2);

	minigameOptions[index]->setScale(xScale, yScale);
	minigameOptions[index]->setPosition(x, y);

	MinigameName->setText(minigames[index].getName());
	MinigameDescription->setText(minigames[index].getDescription());
}