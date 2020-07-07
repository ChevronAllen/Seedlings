#pragma once

#include "util.hpp"

#include <3ds.h>
#include <vector>
#include <m3dia.hpp>

#include "commands/commands.h"
#include "m3diaLibCI/button.hpp"

using namespace m3d;

class Menu;
class MainMenu;
class MinigameSelect;
class MinigameTemplateMenu;

class MenuHandler
{
	public:
		enum class MenuState
		{
			MainMenu,
			MinigameSelect,
			MinigameTemplateMenu,
			NotTransitioning
		};

		MenuState transition = MenuState::NotTransitioning;

		static MenuHandler* getInstance();
		static MenuHandler* createInstance(Screen* screen);
		
		//The function which is called on every game frame.
		void OnUpdate();

		void TransitionTo(MenuState state);
		virtual ~MenuHandler();

		static MenuState GetTransitionState();
		static void AddCommand(CommandObject *command);
		static void RequestUserCode(std::vector<CommandObject*> commands, std::function<void(std::vector<CommandObject*>)> callbackFunction);
	private:
		MenuState currentState;

		//The active Screen object
		Screen* scr;
		//The Utility manager
		Util* util;

		Menu* currentMenu;

		/*
			This Class is a singleton.
			Meaning, only one instance of this class may ever exist.
			This allows for all classes to access this object through the use of this instance value.
			An initial instantiation must occur with proper vaules passed into getInstance
			All further attempts to accesss this class can use dummy values for all parameters of getInstance
		*/
		static MenuHandler *instance;

		MenuHandler(Screen* screen);
};