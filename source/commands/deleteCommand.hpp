#pragma once
#include "../commands/commandObject.hpp"

class DeleteCommand : public CommandObject
{

public:
    DeleteCommand(std::string t_param = "name",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="delete";
		setParam(0, t_param);
        m_background = m3dCI::Sprite( *ResourceManager::getSprite("command_background_delete.png"));
        m_background.setTint(COM_LOCK_TINT);
    }

    ~DeleteCommand();

    std::vector<std::string> getParamNames() {return {"Object Name"};} 

    std::string convertToLua()
    {
        return "delete(" + m_params[0] + ")\n"; 
    }

};