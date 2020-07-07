#include "MenuHandler.hpp"

#include "menus/menu.hpp"
#include "menus/mainMenu.hpp"
#include "menus/minigameSelect.hpp"
#include "menus/minigameTemplateMenu.hpp"

using namespace m3d;

//Set default instance of this class to 0, to notify that the instance hasn't been created
MenuHandler *MenuHandler::instance = 0;

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of this instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
MenuHandler* MenuHandler::createInstance(Screen* screen)
{
	if (instance == 0)
	{
		instance = new MenuHandler(screen);
	}
	
	return instance;
}

/*
	This Class is a singleton. 
	Meaning, only one instance of this class may ever exist.
	This allows for all classes to access this object through the use of this instance value.
	An initial instantiation must occur with proper values passed into createInstance
	All further attempts to accesss this class can use dummy values for all parameters of getInstance
*/
MenuHandler* MenuHandler::getInstance()
{
	if (instance == 0)
	{
		return nullptr;
	}
	
	return instance;
}

//Initialize the Util class.
//Only ever called once.
MenuHandler::MenuHandler(Screen* screen)
{
	currentMenu = nullptr;
	scr = screen;

	TransitionTo(MenuState::MainMenu);

	util = Util::getInstance();
}

MenuHandler::~MenuHandler()
{
	delete(currentMenu);
}

//The function which is called on every game frame.
void MenuHandler::OnUpdate()
{
	if (transition != MenuState::NotTransitioning)
	{
		TransitionTo(transition);
	}
	else
	{
		if (currentMenu != nullptr)
			currentMenu->OnUpdate();
	}
}

void MenuHandler::TransitionTo(MenuState state)
{
	//This adds a frame buffer between menu changes. Allowing for objects in the menu to interact with other menu pieces
	if (transition == MenuState::NotTransitioning)
	{
		transition = state;
		return;
	}

	transition = MenuState::NotTransitioning;

	scr->clear();//Causes screen to blink. Otherwise, the screen buffers dont get cleared between scenes. 

	switch (state)
	{
		//This could be written much more efficiently. I had a different idea in mind when originally developing this.
		case MenuState::MainMenu:
		{
			//theres no way to convert from enum to string in C++... uggh
			util->PrintLine("Attempting transition to: MainMenu");

			MainMenu* menu = new MainMenu(scr);

			if (currentMenu != nullptr)
				delete(currentMenu);

			currentMenu = menu;
			currentState = state;
			break;
		}
		case MenuState::MinigameSelect:
		{
			util->PrintLine("Attempting transition to: MinigameSelect");
			MinigameSelect* menu = new MinigameSelect(scr);

			if (currentMenu != nullptr)
				delete(currentMenu);

			currentMenu = menu;
			currentState = state;
			break;
		}
		case MenuState::MinigameTemplateMenu:
		{
			//need to figure out which minigame to switch to and tell it so here
			util->PrintLine("Attempting transition to: MinigameTemplateMenu");
			MinigameTemplateMenu* menu = new MinigameTemplateMenu(scr);

			if (currentMenu != nullptr)
				delete(currentMenu);

			currentMenu = menu;
			currentState = state;
			break;
		}
		default:
		{
			util->PrintLine("Attempting to transition to menu state which has not been defined.");
			break;
		}
	}
}

MenuHandler::MenuState MenuHandler::GetTransitionState()
{
	if (instance == 0)
		instance = MenuHandler::getInstance();

	return instance->transition;
}

void MenuHandler::AddCommand(CommandObject *com)
{
	if (com == nullptr)
		return;

	MenuHandler* mh = getInstance();

	if (mh == 0)
		return;

	if (mh->currentState != MenuState::MinigameTemplateMenu)
		return;

	MinigameTemplateMenu* menu = ((MinigameTemplateMenu*)mh->currentMenu);

	menu->AddCommand(com);
}

void MenuHandler::RequestUserCode(std::vector<CommandObject*> commands, std::function<void(std::vector<CommandObject*>)> callbackFunction)
{
	MenuHandler* mh = getInstance();

	if (mh == 0)
		return;

	if (mh->currentState != MenuState::MinigameTemplateMenu)
		return;

	MinigameTemplateMenu* menu = ((MinigameTemplateMenu*)mh->currentMenu);

	menu->ClearCommands();

	menu->AddStartCommands(commands);

	menu->SetSubmitFunction(callbackFunction);
}