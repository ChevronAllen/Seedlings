#include "mainMenu.hpp"

MainMenu::MainMenu(m3d::Screen* screen) :
	Menu(screen)
{
	StartupText = new m3dCI::Text("Seedlings");
	StartupText->setFontSize(2);
	StartupText->setFontWeight(2);
	StartupText->setColor(m3d::Color(0, 0, 0));
	StartupText->setOpacity(0);

	int width = StartupText->getWidth();
	int height = StartupText->getHeight();
	
	int topScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = screen->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = screen->getScreenHeight();

	StartupText->setPosition((topScreenWidth / 2) - (width / 2) + 25, (screenHeight / 2) - (height / 2));

	whiteBackground = new m3d::Rectangle(0, 0, 1000, 1000, m3d::Color(255, 255, 255));

	int clickHereToContinueX = ((bottomScreenWidth)-(bottomScreenWidth*0.8)) / 2;
	int clickHereToContinueY = ((screenHeight)-(screenHeight*0.3));
	
	ClickHereToContinue = om->CreateButton(clickHereToContinueX, clickHereToContinueY, (bottomScreenWidth*0.8), (screenHeight*0.2), m3d::Color(255, 255, 255), m3d::Color(0, 0, 0), 3);
	ClickHereToContinue->SetText("Press start to Play!");
	ClickHereToContinue->OnRelease = [this]() { MenuHandler::getInstance()->TransitionTo(MenuHandler::MenuState::MinigameSelect); };
	ClickHereToContinue->SetEnabledState(false);

	apple = new m3dCI::Sprite(*ResourceManager::getSprite("apple.png"));
	apple->setCenter(apple->m_sprite.params.pos.w / 2, apple->m_sprite.params.pos.h / 2);
	apple->setPosition(topScreenWidth * 0.75 + 25, -(apple->m_sprite.params.pos.h / 2));
	apple->setScale(0.35f, 0.35f);

}

void MainMenu::OnUpdate()
{
	if (util->IsConsoleDrawn())
		return;

	int topScreenWidth = scr->getScreenWidth(m3d::RenderContext::ScreenTarget::Top);
	int bottomScreenWidth = scr->getScreenWidth(m3d::RenderContext::ScreenTarget::Bottom);
	int screenHeight = scr->getScreenHeight();

	if (m3d::buttons::buttonReleased(m3d::buttons::Button::Start)
		|| m3d::buttons::buttonReleased(m3d::buttons::Button::A)
		|| Input::btnReleased(m3d::buttons::Touch))
	{
		if (!ClickHereToContinue->GetEnabledState())
		{
			apple->setXPosition(topScreenWidth * 0.1 + 25);
			apple->setYPosition((screenHeight / 2) - 10);
			apple->setRotation(0);
			StartupText->setOpacity(255);
		}
		else
		{
			if (m3d::buttons::buttonReleased(m3d::buttons::Button::Start))
				MenuHandler::getInstance()->TransitionTo(MenuHandler::MenuState::MinigameSelect);
		}
	}

	scr->drawTop(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawBottom(*whiteBackground, RenderContext::Mode::Flat);
	scr->drawTop(*StartupText, RenderContext::Mode::Flat);
	if (apple->getYPosition() < (screenHeight / 2 - 10))
	{
		apple->setYPosition(apple->getYPosition() + 4);
	}
	else
	{
		if (apple->getXPosition() > topScreenWidth * 0.1 + 25)
		{
			apple->setXPosition(apple->getXPosition() - 3);
			apple->rotate(-8.25f);
		}
		else if (StartupText->getOpacity() < 255)
		{
			apple->setRotation(0.0f);
			StartupText->setOpacity(std::min((int)StartupText->getOpacity() + 3, 255));
		}
		else
		{
			ClickHereToContinue->SetEnabledState(true);
			scr->drawBottom(*ClickHereToContinue, RenderContext::Mode::Flat);
		}
	}
	scr->drawTop(*apple);
}

//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
MainMenu::~MainMenu()
{
	delete(StartupText);
	//The following commented out object don't have deletion support. They *should* be grabbed by the garbage collector. 
	//Ideally, we would change these objects to support a default virtual deconstructor
	//delete(whiteBackground);
	//delete(whiteBottomBackground);
	delete(apple);
	om->DeleteButton(ClickHereToContinue);
}