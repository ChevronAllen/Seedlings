#pragma once
#include "../commands/commandObject.hpp"

class SelectCommand : public CommandObject
{

public:
    SelectCommand(std::string t_param = "object",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        name="select";
        m_params[0] = t_param;
    }

    ~SelectCommand();

    std::vector<std::string> getParamNames() {return {"Object Name"};}

    std::string convertToLua()
    {
        return "select_gameobject(" + m_params[0] + ")\n"; 
    }

};