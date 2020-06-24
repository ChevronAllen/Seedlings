#pragma once
#include "../commands/commandObject.hpp"

class LabelCommand : public CommandObject
{

public:
    LabelCommand(std::string t_param = "marker", bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        name="label";
        m_params[0] = t_param;
    }

    ~LabelCommand();

    std::vector<std::string> getParamNames() {return {"label"};}

    std::string convertToLua()
    {
        return "::" + m_params[0] + "::\n"; 
    }

};