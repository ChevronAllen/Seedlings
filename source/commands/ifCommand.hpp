#pragma once
#include "../commands/commandObject.hpp"

class IfCommand : public CommandObject
{

public:
    IfCommand(std::string t_param = "true" ,bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        name="if";
        m_params[0] = t_param;
    }

    ~IfCommand();

    std::vector<std::string> getParamNames() {return {"Condition"};}


    std::string convertToLua()
    {
        return "if (" + m_params[0] + ") then\n"; 
    }

};