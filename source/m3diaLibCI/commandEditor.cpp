#include "commandEditor.hpp"

#define XStart 15
#define YStart 6
#define CELL_WIDTH 274
#define CELL_HEIGHT 57

namespace m3dCI
{
	CommandEditor::CommandEditor(CommandObject* pcommand)
		: m3d::Drawable()
	{
		command = pcommand;
		std::vector<std::string> commandDefs = command->getParamNames();
		int numParams = command->getParamNames().size();

		background = new m3dCI::Sprite(*ResourceManager::getSprite("commandEditPopup.png"));

		name = new m3dCI::Text(command->getName());
		name->setPosition(XStart, YStart + 19);

		name->setColor(COM_TEXT_COLOR);
		name->setFontWeight(1.0f);
		name->setFontSize(1.0f);
		
		for (int i = 0; i < numParams; i++)
		{
			params[i] = new m3dCI::Text(command->getParamNames()[i] + ": " + command->getParams()[i]);
			params[i]->setPosition(XStart, YStart + 19 + (CELL_HEIGHT * (i + 1)));

			params[i]->setColor(COM_TEXT_COLOR);
			params[i]->setFontWeight(1.0f);
			params[i]->setFontSize(1.0f);
		}

		Util::PrintLine("Created");
	}

	CommandEditor::~CommandEditor()
	{
		delete(background);
		delete(name);

		for (int i = 0; i < MAX_PARAMS; i++)
			if (params[i] != nullptr)
				delete(params[i]);
	}

	void CommandEditor::draw(m3d::RenderContext t_context)
	{
		if (background != nullptr)
			background->draw(t_context);

		if (name != nullptr)
			name->draw(t_context);

		for (int i = 0; i < MAX_PARAMS; i++)
			if (params[i] != nullptr)
				params[i]->draw(t_context);
	}

	void CommandEditor::HandleClick(int x, int y)
	{
		if (x >= XStart && x <= XStart + CELL_WIDTH && y >= YStart && y <= YStart + (CELL_HEIGHT * (command->getParamNames().size() + 1)))
		{
			int selected = (y - YStart) / CELL_HEIGHT;

			if (selected > 0)
			{
				m3d::SoftwareKeyboard sk;

				sk.darkenTop(false);
				sk.allowBlank(false);
				sk.allowEmpty(false);
				sk.allowHome(false);
				sk.setInitialText(command->getParams()[selected - 1]);
				sk.display();

				if (sk.getLastButton() != m3d::SoftwareKeyboard::Button::Right)
				{
					Util::PrintLine("Keyboard Canceled");
					return;
				}
				else
				{
					command->setParam(selected - 1, sk.getLastInput());

					isComplete = true;
				}
			}
			else
			{

			}
		}
	}
}
