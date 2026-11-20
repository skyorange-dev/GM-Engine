Scene={}

function Scene.new(scene_name)
    local scene_table={}
    local aplayer=Audio_Player.new();
    local gmanager=Graphics_Manager.new();
    local srmanager=Scene_Resource_Manager.new();
    local auto_ptr=ffi.new("int*");
    local is_delete=false;
    grmanager.scene.RegisterSTable(scene_name,scene_table);
    local tem=grmanager.scene.SearchSTable(scene_name);
    ffi.gc(auto_ptr,function(val)
        if scene_table.is_delete==false then
              grmanager.scene.DeleteSTable(scene_table.scene_name);
        end
    end)
    scene_table.aplayer=aplayer;
    scene_table.gmanager=gmanager;
    scene_table.srmanager=srmanager;
    scene_table.scene_name=scene_name;
    scene_table.is_delete=is_delete;
    scene_table.auto_ptr=auto_ptr;
    return scene_table;
end