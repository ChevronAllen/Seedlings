#include <m3dia.hpp> 
#include "sandbox.h"
#include "userAPI.h"

class Minigame {
    public:
    //SceneObject *scene (I dont have the SceneObject files yet so I'll leave this be for a second).
    LuaSandbox *sandbox;

    void initialize();
    void OnUpdate();
    void destroy();
};

