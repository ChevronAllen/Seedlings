#pragma once
#include "../commands/commandObject.hpp"

class ScaleCommand : public CommandObject
{

public:
    // TODO: Design such that x or y = -1, maintains that scale.
    ScaleCommand(std::string t_x , std::string t_y , bool t_lockEdit=false,bool t_lockAdd=false): CommandObject(t_lockEdit, t_lockAdd)
    {
        m_name="scale";
		setParam(0, t_x);
		setParam(1, t_y);
    }

    ~ScaleCommand();

    std::vector<std::string> getParamNames() {return {"x scale", "y scale"};}

    std::string convertToLua()
    {
        return "scale_object(" + m_params[0] + "," + m_params[0] + ")\n"; 
    }

};


