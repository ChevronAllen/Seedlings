#pragma once
#include <stdlib.h>
#include <string>
#include <vector>

#include <m3dia.hpp>
#include "../m3diaLibCI/sprite.hpp"
#include "../resources.h"
#include "../gameManager.hpp"

#define MAX_PARAMS 3
#define COM_PADDING 3
#define COM_SPACING 5
#define COM_TEXT_COLOR  m3d::Color(0,0,0)
#define COM_LOCK_TINT   m3d::Color(100,100,100,100)
#define COM_CLEAR_TINT  m3d::Color(255,255,255)

class CommandObject //: public Drawable 
{

protected:
    std::string m_name;
    bool m_isEditLocked;
    bool m_isAddLocked;
    std::string m_params[MAX_PARAMS];
    m3dCI::Sprite m_background;
	m3dCI::Text* m_text[MAX_PARAMS + 1] = { nullptr, nullptr, nullptr, nullptr };
    m3dCI::Sprite m_lockIcon;

public:
    CommandObject(bool t_lockEdit = false,bool t_lockAdd = false)
    {
        m_name="";
        m_isEditLocked = t_lockEdit;
        m_isAddLocked = t_lockAdd;
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background.png"));
        m_background.setTint(COM_LOCK_TINT);
        m_text[0] = new m3dCI::Text(m_name);
        m_lockIcon = m3dCI::Sprite( *ResourceManager::getSprite("command_lock.png"));
        m_lockIcon.setCenter(-108,7);
    }

    ~CommandObject(){}

    virtual std::vector<std::string> getParamNames() 
    { 
        return  {"error"};
    }

	std::string* getParams()
	{
		return m_params;
	}


	std::string getName()
	{
		return m_name;
	}
	
	void setParam(int index, std::string str)
	{
		if (str == "")
			return;

		m_params[index] = str;

		if (m_text[index + 1] == nullptr)
		{
			m_text[index + 1] = new m3dCI::Text(str);

			m_text[index + 1]->setColor(COM_TEXT_COLOR);
			m_text[index + 1]->setFontWeight(0.6f);
			m_text[index + 1]->setFontSize(0.6f);
		}

		m_text[index + 1]->setText(str);
	}
    
    void setParams(std::string t_params[MAX_PARAMS])
    {
		for (int i = 0; i < MAX_PARAMS; i++)
		{
			m_params[i] = t_params[i];

			if (m_text[i + 1] == nullptr)
			{
				m_text[i + 1] = new m3dCI::Text(t_params[i]);

				m_text[i + 1]->setColor(COM_TEXT_COLOR);
				m_text[i + 1]->setFontWeight(0.6f);
				m_text[i + 1]->setFontSize(0.6f);
			}

			m_text[i + 1]->setText(t_params[i]);
        }
    }

    virtual std::string convertToLua()
    {
        return "";
    }

    static std::string ConvertBulk(std::vector<CommandObject*> t_list)
    {
        std::string chunk;
        for (CommandObject* cmd : t_list)
        {
            chunk.append(cmd->convertToLua());
        }
        return chunk;
    }

    virtual void draw(double t_x, double t_y, m3d::RenderContext t_context)
    {
        m3d::Screen* scr = GameManager::getScreen();
        unsigned short int paramCount = getParamNames().size();

		m_background.setPosition(t_x, t_y);
        m_lockIcon.setPosition(t_x, t_y);
        if(m_isEditLocked)
        {
            m_background.setBlend(0.5f);
        }else
        {
            m_background.setBlend(0.f);
        }
        m_background.draw(t_context);
		

        if(m_isAddLocked)
        {
            m_lockIcon.draw(t_context); 
        }


        m_text[0]->setText(m_name);
        m_text[0]->setColor(COM_TEXT_COLOR);
        m_text[0]->setFontWeight(0.6f);
		m_text[0]->setFontSize(0.6f);

		int t_yCursor = t_y + COM_PADDING - 3;
		int t_xCursor = COM_PADDING + 12;

		m_text[0]->setPosition(t_xCursor, t_yCursor);
		m_text[0]->draw(t_context);

		t_xCursor += m_text[0]->getWidth() + (2 * COM_SPACING);

        int t_paramStartX = t_xCursor - COM_SPACING;

        for (unsigned int i = 1; i < paramCount + 1; i++)
        {
            if(m_text[i] != nullptr)
            {
				m_text[i]->setPosition(t_xCursor, t_yCursor);
                m_text[i]->draw(t_context);
                t_xCursor += m_text[i - 1]->getWidth() + COM_SPACING;
            }
        }

        
    }

	bool IsEditLocked()
	{
		return m_isEditLocked;
	}

	bool IsAddlocked()
	{
		return m_isAddLocked;
	}
};

