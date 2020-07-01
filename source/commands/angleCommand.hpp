#pragma once
#include "../commands/commandObject.hpp"

class GetAngleCommand : public CommandObject
{

public:
    GetAngleCommand(bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="get angle";
    }

    ~GetAngleCommand();

    std::vector<std::string> getParamNames() {return {};}

    std::string convertToLua()
    {
        return "get_angle()\n"; 
    }

};


class SetAngleCommand : public CommandObject
{

public:
    SetAngleCommand(std::string t_value ="0",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="set angle";
		setParam(0, t_value);
    }

    ~SetAngleCommand();

    std::vector<std::string> getParamNames() {return {"value"};}

    std::string convertToLua()
    {
        return "set_angle(" + m_params[0] +")\n"; 
    }

};