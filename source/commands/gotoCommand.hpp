#pragma once
#include "../commands/commandObject.hpp"

class GotoCommand : public CommandObject
{

public:
    GotoCommand(std::string t_param = "marker", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        name="goto";
        m_params[0] = t_param;
    }

    ~GotoCommand();

    std::vector<std::string> getParamNames() {return {"label"};}

    std::string convertToLua()
    {
        return "goto " + m_params[0] + "\n"; 
    }

};