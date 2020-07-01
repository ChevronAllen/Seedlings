#include "minigameTemplateMenu.hpp"

MinigameTemplateMenu::MinigameTemplateMenu(m3d::Screen* screen) :
	Menu(screen)
{
	int margin = 5;

	codeEditor = om->CreateCodeEditor(margin, (BOTTOMSCREEN_WIDTH * 0.75) - (margin * 2), 1);

	codeEditor->SetActive(true);

	int buttonWidth = BOTTOMSCREEN_WIDTH * 0.25 - (margin * 2);
	int buttonHeight = (BOTTOMSCREEN_HEIGHT - buttonWidth - (margin * 2)) / 3;

	AddButton = om->CreateButton(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin, buttonWidth, buttonHeight, m3d::Color(255,255,255), m3d::Color(0, 0, 0), 1);
	AddButton->SetText("ADD");
	AddButton->OnRelease = [this]() { this->AddButton_OnClick(); };

	EditButton = om->CreateButton(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	EditButton->SetText("EDIT");
	EditButton->OnRelease = [this]() { this->EditButton_OnClick(); };

	RemoveButton = om->CreateButton(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight * 2, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	RemoveButton->SetText("DEL");
	RemoveButton->OnRelease = [this]() { this->DeleteButton_OnClick(); };

	closeButton = om->CreateButton(48 + BOTTOMSCREEN_WIDTH * 0.5, 0, new m3dCI::Sprite(*ResourceManager::getSprite("tabClose.png")));
	closeButton->OnRelease = [this]() { this->CloseButton_OnClick(); };
	closeButton->SetEnabledState(false);
	
	submitButton = om->CreateButton(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight * 3, buttonWidth, buttonWidth, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	submitButton->SetText("Run");
	submitButton->OnRelease = [this]() { this->SubmitButton_OnClick(); };

	commandLister = om->CreateCommandLister();
}

void MinigameTemplateMenu::OnUpdate()
{
	if (util->IsConsoleDrawn())
		return;

	if (commandEditor != nullptr && showCommandEditor)
	{
		if (commandEditor->getComplete())
		{
			showCommandEditor = false;

			om->DeleteCommandEditor(commandEditor);

			commandLister->SetActive(false);
			codeEditor->SetActive(true);
			AddButton->SetEnabledState(true);
			EditButton->SetEnabledState(true);
			RemoveButton->SetEnabledState(true);
			submitButton->SetEnabledState(true);
		}
		else
		{
			scr->drawBottom(*commandEditor);

			if (closeButton != nullptr)
			{
				closeButton->setPosition(BOTTOMSCREEN_WIDTH - 37, 0);
				scr->drawBottom(*closeButton);
			}
		}
	}

	if (codeEditor != nullptr)
	{
		if(showCommandLister)
			scr->drawTop(*codeEditor);
		else if (!showCommandEditor)
		{
			scr->drawBottom(*codeEditor);
			AddButton->SetEnabledState(codeEditor->canAdd());
			EditButton->SetEnabledState(codeEditor->canEdit());
			RemoveButton->SetEnabledState(codeEditor->canRemove());
		}
	}

	if (commandLister != nullptr && showCommandLister)
	{
		scr->drawBottom(*commandLister);

		if (closeButton != nullptr)
		{
			closeButton->setPosition(48 + BOTTOMSCREEN_WIDTH * 0.5, 0);
			scr->drawBottom(*closeButton);
		}
	}

	if (!showCommandEditor)
	{
		if (AddButton != nullptr)
			scr->drawBottom(*AddButton);

		if (EditButton != nullptr)
			scr->drawBottom(*EditButton);

		if (RemoveButton != nullptr)
			scr->drawBottom(*RemoveButton);

		if (submitButton != nullptr)
			scr->drawBottom(*submitButton);
	}
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
MinigameTemplateMenu::~MinigameTemplateMenu()
{
	om->DeleteCodeEditor(codeEditor);
	om->DeleteCommandLister(commandLister);
	om->DeleteButton(AddButton);
	om->DeleteButton(EditButton);
	om->DeleteButton(RemoveButton);
	om->DeleteButton(closeButton);
	om->DeleteButton(submitButton);
}

void MinigameTemplateMenu::AddButton_OnClick()
{
	showCommandLister = true;
	commandLister->SetActive(true);
	codeEditor->SetActive(false);
	AddButton->SetEnabledState(false);
	EditButton->SetEnabledState(false);
	RemoveButton->SetEnabledState(false);
	closeButton->SetEnabledState(true);
	submitButton->SetEnabledState(false);

	codeEditor->ShiftToTop();
}

void MinigameTemplateMenu::SubmitButton_OnClick()
{
	if (submitFunction != nullptr)
		submitFunction(codeEditor->GetCommands());
}

void MinigameTemplateMenu::EditButton_OnClick()
{
	if (codeEditor == nullptr || codeEditor->getSelectedObject() == nullptr)
		return;

	commandEditor = om->CreateCommandEditor(codeEditor->getSelectedObject());

	commandLister->SetActive(false);
	codeEditor->SetActive(false);
	AddButton->SetEnabledState(false);
	EditButton->SetEnabledState(false);
	RemoveButton->SetEnabledState(false);
	closeButton->SetEnabledState(true);
	submitButton->SetEnabledState(false);

	showCommandEditor = true;
}

void MinigameTemplateMenu::DeleteButton_OnClick()
{
	codeEditor->removeCommand();
}

void MinigameTemplateMenu::CloseButton_OnClick()
{
	commandLister->SetActive(false);
	codeEditor->SetActive(true);
	codeEditor->ShiftToBottom();
	AddButton->SetEnabledState(true);
	EditButton->SetEnabledState(true);
	RemoveButton->SetEnabledState(true);
	closeButton->SetEnabledState(false);
	submitButton->SetEnabledState(true);

	scr->clear();

	if (showCommandEditor)
	{
		om->DeleteCommandEditor(commandEditor);
		showCommandEditor = false;
	}
	showCommandLister = false;
}

void MinigameTemplateMenu::AddStartCommands(std::vector<CommandObject*> commands)
{
	for (unsigned int i = 0; i < commands.size(); i++)
		codeEditor->addCommand(commands[i]);
}

void MinigameTemplateMenu::AddCommand(CommandObject* command)
{
	codeEditor->addCommand(command);
	commandLister->SetActive(false);
	codeEditor->SetActive(true);
	codeEditor->ShiftToBottom();
	AddButton->SetEnabledState(true);
	EditButton->SetEnabledState(true);
	RemoveButton->SetEnabledState(true);
	closeButton->SetEnabledState(false);
	submitButton->SetEnabledState(true);

	scr->clear();

	showCommandLister = false;
}

void MinigameTemplateMenu::ClearCommands()
{
	codeEditor->ClearCommands();
}

void MinigameTemplateMenu::SetSubmitFunction(std::function<void(std::vector<CommandObject*>)> callbackFunction)
{
	submitFunction = callbackFunction;
}