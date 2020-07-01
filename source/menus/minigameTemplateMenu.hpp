#pragma once

#include "menu.hpp"

class MinigameTemplateMenu : public Menu
{
	private:
		m3dCI::Button *AddButton = nullptr,
			*EditButton = nullptr,
			*RemoveButton = nullptr,
			*closeButton = nullptr,
			*submitButton = nullptr;
		m3dCI::CodeEditor* codeEditor = nullptr;
		m3dCI::CommandLister* commandLister = nullptr;
		m3dCI::CommandEditor* commandEditor = nullptr;

		std::function<void(std::vector<CommandObject*>)> submitFunction = nullptr;

		bool showCommandLister = false, showCommandEditor = false;
	public:
		MinigameTemplateMenu(m3d::Screen* screen);
		virtual ~MinigameTemplateMenu();

		void AddCommand(CommandObject* command);
		void AddStartCommands(std::vector<CommandObject*> obj);
		void ClearCommands();

		void SetSubmitFunction(std::function<void(std::vector<CommandObject*>)> callbackFunction);

		void AddButton_OnClick();
		void EditButton_OnClick();
		void DeleteButton_OnClick();
		void SubmitButton_OnClick();
		void CloseButton_OnClick();
		
		void OnUpdate();
};