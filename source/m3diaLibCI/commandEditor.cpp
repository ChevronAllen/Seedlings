#include "commandEditor.hpp"

#include "../commands/commands.h"

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
}
