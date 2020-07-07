#pragma once

#include "sprite.hpp"
#include "text.hpp"
#include "button.hpp"
#include "../resources.h"
#include "../commands/commands.h"

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

using namespace std;

namespace m3dCI 
{
    class CommandEditor : public m3d::Drawable
	{
		private:

			m3dCI::Sprite* background = nullptr;
			CommandObject* command;

			m3dCI::Text *name = nullptr;
			m3dCI::Text *params[MAX_PARAMS] = { nullptr, nullptr, nullptr };
		public:
			
			CommandEditor(CommandObject* command);

			//Destructor: Objects that must be deleted when this object is deleted. Delete(nullptr) is fail-safe.
			virtual ~CommandEditor();

			void draw(m3d::RenderContext t_context);

			void HandleClick(int x, int y);
	};
}