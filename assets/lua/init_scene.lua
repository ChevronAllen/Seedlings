name_table = {}
current_object = nil
_lock = false;

function select_gameobject(name)
    current_object = name_table[name]
end
function delete(name)
    name_table[name] = nil
end
