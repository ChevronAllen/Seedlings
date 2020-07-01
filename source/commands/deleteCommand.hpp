#pragma once
#include "../commands/commandObject.hpp"

class DeleteCommand : public CommandObject
{

public:
    DeleteCommand(std::string t_param = "name",bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="delete";
		setParam(0, t_param);
    }

    ~DeleteCommand();

    std::vector<std::string> getParamNames() {return {"Object Name"};} 

    std::string convertToLua()
    {
        return "delete(" + m_params[0] + ")\n"; 
    }

};