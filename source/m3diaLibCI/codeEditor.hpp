#pragma once

#include "sprite.hpp"
#include "text.hpp"
#include "../commands/commands.h"

#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <vector>
#include <m3dia.hpp>

namespace m3dCI 
{
    class CodeEditor: public m3d::Drawable
	{
		private:
			m3d::Rectangle *borderRectangle,
				*innerRectangle;
			std::vector<CommandObject*> commands;

			CommandObject* currentSelectedCommand = nullptr;
			int x, xShift = 0, y, borderWidth, w, h;

			double scrollY = 0;
			double thisScrollChange = 0;
			bool active = false;
			
			void refreshCommandList();

			int GetSelectedCommandIndex();

			void SelectCommand(int index);
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
			CodeEditor(int px, int pw, int p_borderWidth);

			//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
			virtual ~CodeEditor();
			
			//need a way to insert at specified line
			void addCommand(CommandObject* command, int position = -1);
			void SelectCommand(int px, int py);
			void removeCommand(int position = -1);
			void ClearCommands();

			bool canAdd();
			bool canEdit();
			bool canRemove();
			std::vector<CommandObject*> GetCommands();
			CommandObject* getSelectedObject();

			bool IsBlankCommandSelected();

			void draw(m3d::RenderContext t_context);

			bool isPointInside(int px, int py);

			bool GetActive();
			void SetActive(bool state);

			void DoDrag(m3d::Vector2f dragVector);
			void DragComplete();

			void ShiftToTop();
			void ShiftToBottom();
	};
}