#pragma once

#include "sprite.hpp"
#include "text.hpp"
#include "button.hpp"
#include "commandListerItem.hpp"
#include "../commands/commands.h"
#include "../resources.h"
#include "../MenuHandler.hpp"

#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <vector>

#define TOPSCREEN_WIDTH 400
#define BOTTOMSCREEN_WIDTH 320
#define TOPSCREEN_HEIGHT 240
#define BOTTOMSCREEN_HEIGHT 240

#define NUM_TABS 5
#define NUM_COMMANDS_PER_TAB 8

#define SHAPE_INDEX 0
#define COLOR_INDEX 1
#define OBJECT_MANIPULATION 2
#define VAR_STATEMENTS 3
#define CONTROL_STATEMENTS 4

using namespace std;

#define t(x) MenuHandler::AddCommand(x)
#define func(a) []() { t(a); }
#define PAIR(name, command) { name, []() { t(command); }}
#define NULLPAIR PAIR("", nullptr)
#define COLORPAIR(name, r, g, b) PAIR(name, new ColorCommand(name, m3d::Color(r,g,b,255)))

namespace m3dCI 
{
    class CommandLister : public m3d::Drawable
	{
		private:
			pair<string, function<void()>> listOfCommandsByTab[NUM_TABS][NUM_COMMANDS_PER_TAB] =
			{
				{ PAIR("Circle", new CircleCommand()), PAIR("Rectangle", new RectangleCommand()), PAIR("Triangle", nullptr), PAIR("Text", new TextCommand("Empty")), PAIR("Select", new SelectCommand()), PAIR("Delete", new DeleteCommand), NULLPAIR, NULLPAIR },
				{ COLORPAIR("Red", 255, 0, 0), COLORPAIR("Orange", 255, 127, 0), COLORPAIR("Yellow", 255, 255, 0), COLORPAIR("Green", 0, 255, 0), COLORPAIR("Blue", 0, 0, 255), COLORPAIR("Indigo", 75, 0, 130), COLORPAIR("Violet", 148, 0, 211), COLORPAIR("Black", 0, 0, 0) },
				{ PAIR("Up", new UpCommand()), PAIR("Down", new DownCommand()), PAIR("Left", new LeftCommand()), PAIR("Right", new RightCommand()), PAIR("Scale", new ScaleCommand("1","1")), PAIR("Scale_X", new ScaleCommand("1", "-1")), PAIR("Scale_Y", new ScaleCommand("-1", "1")) },
				{ PAIR("Var", new VarCommand()), PAIR("Get_X", new GetXCommand()), PAIR("Get_Y", new GetYCommand()), PAIR("Get_Angle", new GetAngleCommand()), PAIR("Set_Angle", new SetAngleCommand()), PAIR("Get_Scale_X", nullptr), PAIR("Get_Scale_Y", nullptr) },
				{ PAIR("If", new IfCommand()), PAIR("Loop", nullptr), PAIR("While", new WhileCommand()), PAIR("End", new EndCommand()), PAIR("Label", new LabelCommand()), PAIR("goto", new GotoCommand()), NULLPAIR, NULLPAIR }
			};

			m3d::Rectangle *backgroundRectangle = nullptr;
			std::vector<m3dCI::Sprite*> tabs;
			std::vector<std::vector<commandListerItem*>> commands;

			int currentlySelectedTab = -1;
			commandListerItem* currentSelectedCommand = nullptr;

			bool active = false;
			int x, y, w, h;

			std::string getTabSpriteStringID(int index, bool selected);
			m3dCI::Sprite* getTabSprite(int index, bool selected);

			int getCurrentlySelectedTab();

			void CreateTabCommandObjects(int index);

			void SelectTab(int tabIndex);
			void SelectTab(int px, int py);
			void SelectCommandObject(int px, int py);
		public:
			//Create the CodeEditor.
			/*
			 *  @param px X Coordinate
			 *  @param py Y Coordinate
			 *  @param pw Width of Code Editor
			 *  @param ph Height of Code Editor
			 *  @param p_borderWidth Width of Border
			 *  @returns a Code Editor drawable object
			*/
			CommandLister();

			//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
			virtual ~CommandLister();

			void SelectPoint(int px, int py);

			void draw(m3d::RenderContext t_context);

			void SetActive(bool state);
	};
}