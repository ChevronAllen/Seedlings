#include "minigame.hpp"


void Minigame::toggleWinCond()
{
	winCond = !winCond;
}

Minigame::Minigame()
{
	m3d::Screen * screen = GameManager::getScreen();
    m_sandbox = new LuaSandbox( [this](){onExecutionBegin();},
                                [this](){onExecutionEnd();});
	   

	int margin = 5;

	codeEditor = new CodeEditorMenuItem(margin, (BOTTOMSCREEN_WIDTH * 0.75) - (margin * 2), 1);
	menu->AddItem(codeEditor);
	codeEditor->SetActive(true);

	int buttonWidth = BOTTOMSCREEN_WIDTH * 0.25 - (margin * 2);
	int buttonHeight = (BOTTOMSCREEN_HEIGHT - buttonWidth - (margin * 2)) / 3;

	AddButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	AddButton->SetText("ADD");
	AddButton->SetOnRelease([this](int x, int y) { this->AddButton_OnClick(); });

	EditButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	EditButton->SetText("EDIT");
	EditButton->SetOnRelease([this](int x, int y) { this->EditButton_OnClick(); });

	RemoveButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight * 2, buttonWidth, buttonHeight, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	RemoveButton->SetText("DEL");
	RemoveButton->SetOnRelease([this](int x, int y) { this->DeleteButton_OnClick(); });

	closeButton = new ButtonMenuItem(48 + BOTTOMSCREEN_WIDTH * 0.5, 0, new m3dCI::Sprite(*ResourceManager::getSprite("tabClose.png")));
	closeButton->SetOnRelease([this](int x, int y) { this->CloseButton_OnClick(); });
	closeButton->SetActive(false);

	submitButton = new ButtonMenuItem(BOTTOMSCREEN_WIDTH * 0.75 + margin, margin + buttonHeight * 3, buttonWidth, buttonWidth, m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 1);
	submitButton->SetText("Run");
	submitButton->SetOnRelease([this](int x, int y) { this->SubmitButton_OnClick(); });

	menu->AddItem(submitButton);
	menu->AddItem(closeButton);
	menu->AddItem(EditButton);
	menu->AddItem(RemoveButton);
	menu->AddItem(AddButton);

	commandLister = new CommandListerMenuItem(this);
	commandLister->SetActive(false);
	menu->AddItem(commandLister);
}

Minigame::~Minigame()
{
	m_sandbox->close();
}

void Minigame::initialize()
{
    m_gridOverlay = new m3dCI::Sprite( *ResourceManager::getSprite("minigame_grid.png"));
    m_gridOverlay->setOpacity(50);
}

void Minigame::update()
{
    #ifdef DEBUG_MINIGAME
	if (buttons::buttonPressed(buttons::X))
	{
		if(m_sandbox->getThreadState() == THREAD_HALT)
		{
            Util::PrintLine("Thread Running");
			m_sandbox->setThreadState(THREAD_RUNNING);
		}else
        {
            Util::PrintLine("Thread Halted");
            m_sandbox->setThreadState(THREAD_HALT);
        }
	}
	if (buttons::buttonPressed(buttons::Y))
	{
        Util::PrintLine("Thread Queue Clear");
		m_sandbox->setThreadState(THREAD_CLEAR);

	}
    #endif
    
	m3d::Screen * scr = GameManager::getScreen();
	
	if (commandEditor != nullptr && showCommandEditor)
	{
		scr->drawBottom(*commandEditor);

		if (commandEditor->getComplete())
		{
			AddButton->SetActive(true);
		}

		if (closeButton != nullptr)
		{
			closeButton->setPosition(BOTTOMSCREEN_WIDTH - 37, 0);
			scr->drawBottom(*closeButton);
		}
	}

	if (codeEditor != nullptr)
	{
		if (showCommandLister)
			scr->drawTop(*codeEditor);
		else if (!showCommandEditor && !editCommandFromCommandEditor)
		{
			scr->drawBottom(*codeEditor);
			AddButton->SetActive(codeEditor->canAdd());
			EditButton->SetActive(codeEditor->canEdit());
			RemoveButton->SetActive(codeEditor->canRemove());
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

	menu->OnUpdate();
}

void Minigame::AddButton_OnClick()
{
	showCommandLister = true;
	commandLister->SetActive(true);
	codeEditor->SetActive(false);
	AddButton->SetActive(false);
	EditButton->SetActive(false);
	RemoveButton->SetActive(false);
	closeButton->SetActive(true);
	submitButton->SetActive(false);

	codeEditor->ShiftToTop();
}

void Minigame::SubmitButton_OnClick()
{
    if(m_sandbox->getThreadState() != THREAD_CLOSE)
    {
        if (submitFunction != nullptr)
        {
            submitFunction(codeEditor->GetCommands());
        }
    }
    #ifdef DEBUG
    else
    {
        Util::PrintLine("warning: thread closed");
    }
    #endif

	submitButton->SetActive(false);
}

void Minigame::EditButton_OnClick()
{
	if (codeEditor == nullptr || codeEditor->getSelectedObject() == nullptr)
		return;

	commandEditor = new CommandEditorMenuItem(codeEditor->getSelectedObject());
	commandEditor->SetEditFunction
	(
		[&]()
		{
		editCommandFromCommandEditor = true;

		CloseButton_OnClick();
		AddButton_OnClick();
		}
	);

	menu->AddItem(commandEditor);

	commandLister->SetActive(false);
	codeEditor->SetActive(false);
	AddButton->SetActive(false);
	EditButton->SetActive(false);
	RemoveButton->SetActive(false);
	closeButton->SetActive(true);
	submitButton->SetActive(false);

	showCommandEditor = true;
}

void Minigame::DeleteButton_OnClick()
{
	codeEditor->removeCommand();
}

void Minigame::CloseButton_OnClick()
{
	m3d::Screen * scr = GameManager::getScreen();
	if (showCommandEditor)
	{
		showCommandEditor = false;
		showCommandLister = false;

		menu->RemoveItem(commandEditor);

		codeEditor->SetActive(true);
		commandLister->SetActive(false);

		AddButton->SetActive(false);
		EditButton->SetActive(true);
		RemoveButton->SetActive(true);
		submitButton->SetActive(true);

		commandEditor->ForceComplete();
	}
	else
	{
		showCommandLister = false;

		commandLister->SetActive(false);

		if (editCommandFromCommandEditor)
		{
			editCommandFromCommandEditor = false;
			codeEditor->SetActive(true);
			EditButton_OnClick();
		}
		else
		{
			codeEditor->SetActive(true);
			AddButton->SetActive(true);
			EditButton->SetActive(true);
			RemoveButton->SetActive(true);
			submitButton->SetActive(true);

		}

		codeEditor->ShiftToBottom();
	}
}

void Minigame::AddStartCommands(std::vector<CommandObject*> commands)
{
	for (unsigned int i = 0; i < commands.size(); i++)
		codeEditor->addCommand(commands[i]);
}

void Minigame::AddCommand(CommandObject* command)
{
	m3d::Screen * scr = GameManager::getScreen();

	if (editCommandFromCommandEditor)
		codeEditor->replaceCommand(codeEditor->getSelectedObject(), command);
	else
		codeEditor->addCommand(command);

	commandLister->SetActive(false);
	codeEditor->SetActive(true);
	codeEditor->ShiftToBottom();
	AddButton->SetActive(true);
	EditButton->SetActive(true);
	RemoveButton->SetActive(true);
	closeButton->SetActive(false);
	submitButton->SetActive(true);

	if (editCommandFromCommandEditor)
	{
		editCommandFromCommandEditor = false;
		EditButton_OnClick();
	}


	showCommandLister = false;
}

void Minigame::ClearCommands()
{
	codeEditor->ClearCommands();
}

void Minigame::SetSubmitFunction(std::function<void(std::vector<CommandObject*>)> callbackFunction)
{
	submitFunction = callbackFunction;
}

void Minigame::onExecutionEnd()
{
	//Until a hault option is made here. We don't want the execution to run twice.
	submitButton->SetActive(true);
}

void Minigame::draw()
{
    Scene::draw();
    
    if(m_gridOverlay != nullptr)
    {
        GameManager::getScreen()->drawTop(*m_gridOverlay, m3d::RenderContext::Mode::Flat, 1);
    }
};

