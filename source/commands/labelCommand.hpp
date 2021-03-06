#pragma once
#include "../commands/commandObject.hpp"

class LabelCommand : public CommandObject
{

public:
    LabelCommand(std::string t_param = "marker", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="label";
		setParam(0, t_param);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_branching.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~LabelCommand();

    std::vector<std::string> getParamNames() {return {"label"};}

    std::string convertToLua()
    {
        return "::" + m_params[0] + "::\n"; 
    }

};