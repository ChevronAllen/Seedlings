#pragma once

#include "sprite.hpp"
#include "text.hpp"
#include "commandObject.hpp"

#include <citro2d.h>
#include <string>
#include <3ds.h>
#include <m3dia.hpp>
#include <cmath>
#include <vector>

#define CELL_HEIGHT 20

namespace m3dCI 
{
    class CodeEditor: public m3d::Drawable
	{
		private:
			m3d::Rectangle *borderRectangle,
				*innerRectangle;
			std::vector<CommandObject*> commands;

			CommandObject* currentSelectedCommand = nullptr;
			int x, y, borderWidth, w, h, cellsTall;
			
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
			CodeEditor(int px, int py, int pw, int ph, int p_borderWidth);

			//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
			virtual ~CodeEditor();
			
			//need a way to insert at specified line
			void addCommand(std::string command, int position = -1);

			void SelectCommand(int px, int py);
			void removeCommand(int position = -1);

			void draw(m3d::RenderContext t_context);

			bool isPointInside(int px, int py);
	};
}