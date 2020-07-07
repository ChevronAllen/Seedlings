#include "userAPI.hpp"
#include "util.hpp"
#include "sandbox.h"

/*
    Comparison oparations for the memBlock object.
    all comparisons are dependent on == and <
*/

/// The array of lua accessible user API functions, paired with their lua global name
std::pair<std::string, lua_CFunction> enabledFunctions[] = {
    std::make_pair( "println" , UserAPI::print_line),
    std::make_pair( "print" , UserAPI::print),
    std::make_pair( "rectangle" , UserAPI::make_rectangle),
    std::make_pair( "circle" , UserAPI::make_circle),
    std::make_pair( "triangle" , UserAPI::make_rectangle),
    std::make_pair( "move" , UserAPI::move_object),
    std::make_pair( "position" , UserAPI::set_position),
    std::make_pair( "get_x" , UserAPI::get_x_position),
    std::make_pair( "get_y" , UserAPI::get_y_position),
    std::make_pair( "rotate" , UserAPI::rotate),
    std::make_pair( "set_angle" , UserAPI::set_angle),
    std::make_pair( "get_angle" , UserAPI::get_angle),
    std::make_pair( "set_scale" , UserAPI::set_scale),
    std::make_pair( "set_color" , UserAPI::set_color),
    std::make_pair( "delete" , UserAPI::delete_object)



};

/*
    Operator overloading for memBlock.
*/

bool operator ==  (LuaSandbox::memBlock a, LuaSandbox::memBlock b)
{
    return (a.head == b.head) && (a.size == b.size);
}
bool operator !=  (LuaSandbox::memBlock a, LuaSandbox::memBlock b)
{
    return !(a == b);
}
bool operator <   (LuaSandbox::memBlock a, LuaSandbox::memBlock b)
{
    return a.head < b.head;
}
bool operator >   (LuaSandbox::memBlock a, LuaSandbox::memBlock b)
{
    return b < a;
}
bool operator <=  (LuaSandbox::memBlock a, LuaSandbox::memBlock b)
{
    return !(a>b);
}
bool operator >=  (LuaSandbox::memBlock a, LuaSandbox::memBlock b)
{
    return !(a<b);
}

void* LuaSandbox::allocator(void *ud, void *ptr, size_t osize, size_t nsize)
{
    memBlock * mem = NULL;

    // Free
    if(nsize == 0)
    {
        // search for the memory block
        for (unsigned int i = 0; i < blockList.size(); i++)
        {
            // block is found
            if(blockList.at(i)->head == ptr)
            {
                // erase block
                blockList.erase(blockList.begin() + i);
                break;
            }
        }

        return NULL;
    }

    //  Allocate
    if( osize == 0)
    {//  No space allocated, create a new memory block
        mem = new memBlock(malloc(nsize),nsize);
    } else 
    {// Adjust an existing memory block
        // sum 
        size_t memTotal = getTotalMemoryUsed();

        if( memTotal < (nsize - osize) && 
            memTotal + (nsize - osize) < SANDBOX_MEM_CAPACITY)
        {
            mem = searchBlockList(ptr);
            if(mem == NULL){
                mem = new memBlock(ptr,nsize);
            }
            mem->head = realloc(ptr,nsize);
            mem->size = nsize;
        }
        
    }

    return mem;
}

LuaSandbox::memBlock* LuaSandbox::searchBlockList(void* ptr)
{
    //  If ptr is null skip the search and return null
    if(ptr == NULL){return NULL;}

    // for each block test if  head == ptr
    for (unsigned int i = 0; i <blockList.size(); ++i)
    {
        LuaSandbox::memBlock* m = blockList.at(i);
        if(m->head == ptr)
        {
            return m;
        }
    }
    return NULL;
}

size_t LuaSandbox::getTotalMemoryUsed()
{
    size_t size = 0;
    for (unsigned int i = 0; i <blockList.size(); ++i)
    {
        size += blockList.at(i)->size;
    }
    return size;
}


void LuaSandbox::executeString(std::string text)
{
//  TODO: Needs a more thorough test
    // Temporary implementation, unprotected
    const char* temp = text.c_str();
    //Util::getInstance()->PrintLine(temp);
    luaL_dostring(state,temp);
    return;
}

void LuaSandbox::executeFile(std::string path)
{
    //  TODO: Needs a more thorough test
    // Temporary implementation, unprotected
    
    size_t length;
    char* buffer;
    std::string fullPath = "romfs:/";
    fullPath = fullPath.append(path);
    
    FILE* fp = fopen(fullPath.c_str(), "r");
    if(fp == NULL)
    {
        std::cerr << "Error: couldnt open file at '" << fullPath << "'" << std::endl;
        return;
    }

    fseek(fp,0L, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    buffer = (char*)calloc(size, sizeof(char));
    fread(buffer,sizeof(char),size,fp);

    fclose(fp);
    
    luaL_dostring(state,buffer);
    return;
}

double LuaSandbox::tryGetDouble(std::string id)
{
    //  convert sting to const char*
    const char* n = id.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(state,n);

    //  convert value on the stack to a double 
    double value = lua_tonumber(state,-1);
    
    // value no longer needed, remove from the stack
    lua_remove(state,1);

    // throw an error if the type is wrong
    if(ltype != LUA_TNUMBER){
        throw ;
    }
    
    return value;
}

// TODO: test 
bool LuaSandbox::tryGetBool(std::string id)
{
    //  convert sting to const char*
    const char* n = id.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(state,n);

    //  convert value on the stack to a double 
    bool value = lua_toboolean(state,-1);
    
    // value no longer needed, remove from the stack
    lua_remove(state,1);

    // throw an error if the type is wrong
    if(ltype != LUA_TBOOLEAN){
        throw ;
    }
    
    return value;
}

// TODO: test 
std::string LuaSandbox::tryGetString(std::string id)
{
    //  convert sting to const char*
    const char* n = id.c_str();

    //  push value unto the stack
    int ltype = lua_getglobal(state,n);

    //  convert value on the stack to a double 
    std::string value = std::string( lua_tostring(state,-1));
    
    // value no longer needed, remove from the stack
    lua_remove(state,1);

    // throw an error if the type is wrong
    if(ltype != LUA_TBOOLEAN){
        throw ;
    }
    
    return value;
}

void LuaSandbox::bindAPI()
{
    
    for(std::pair<std::string, lua_CFunction> func : enabledFunctions)
    {
        lua_pushcfunction(state, func.second);
        lua_setglobal(state, func.first.c_str());
    }
    return;
}

void LuaSandbox::close()
{
    lua_close(state);
    return;
}