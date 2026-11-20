Scene_Resource_Manager={}

function Scene_Resource_Manager.new()
    local value_manager={};

    local function NewValue(str,value)
        value_manager[str]=value;
    end

    local function GetValue(str)
        return value_manager[str];
    end

    local function DeleteValue(str)
        value_manager[str]=nil;
    end

    return{
        NewValue=NewValue,
        GetValue=GetValue,
        DeleteValue=DeleteValue
    
    }
end

Global_Resource_Manager={}

function Global_Resource_Manager.new()
    local t={};
    local stable_manager={};
    local etable_manager={};

    local function NewValue(scene_name,str,value)
        stable_manager[scene_name].srmanager.NewValue(str,value);
    end

    local function GetValue(scene_name,str)
        return  stable_manager[scene_name].srmanager.GetValue(str);
    end

    local function DeleteValue(scene_name,str)
        stable_manager[scene_name].srmanager.DeleteValue(str);
    end

    local function RegisterGRTable(scene_name,value,entity_table)
        entity_table.grm_scene_name=scene_name;
        local key=ffi.cast("uintptr_t",value);
        if key<9007199254740992ULL then
            local number=tonumber(key)
             etable_manager[number]=entity_table;
        else
             local number=tostring(key)
             etable_manager[number]=entity_table;
        end
      
        --print("注册了",key,etable_manager[key])
    end

     local function SearchGRTable(value)
         local key=ffi.cast("uintptr_t",value);
          
         if key<9007199254740992ULL then
            local number=tonumber(key)
            return  etable_manager[number];
        else
             local number=tostring(key)
            return etable_manager[number];
        end
        --print("查询",key,etable_manager[key])
 
    end

    local function DeleteGRTable(value)
        local key=ffi.cast("uintptr_t",value);
         if key<9007199254740992ULL then
            local number=tonumber(key)
            local tem=etable_manager[number];
            tem.Delete();
            etable_manager[number]=nil;
        else
            local number=tostring(key)
            local tem=etable_manager[number];
            tem.Delete();
            etable_manager[number]=nil;
        end
        --print("删除了",key,tem)
     
    end

    local function RegisterSTable(scene_name,scene_table)
        stable_manager[scene_name]=scene_table;
    end
     
    local function DeleteSTable(scene_name)

        local count=1;
        local tem={}
        for k, v in pairs(etable_manager) do
            if v.grm_scene_name==scene_name then
                  v.Delete();
                  tem[count]=k;
                  count=count+1;
            end 
        end
        for k,v in ipairs(tem) do
            --print("删除了",k,v)
            etable_manager[v]=nil;
        end
        
         local scene_table=stable_manager[scene_name];
         scene_table.aplayer.Delete();
         scene_table.gmanager.Delete();
         stable_manager[scene_name]=nil;
           
    end

    local function SearchSTable(scene_name)
        return stable_manager[scene_name];
    end

    --管理场景所独有的资源
    t.scene={
        NewValue=NewValue,
        GetValue=GetValue,
        DeleteValue=DeleteValue,
        RegisterGRTable=RegisterGRTable,
        SearchGRTable=SearchGRTable,
        DeleteGRTable=DeleteGRTable,
        RegisterSTable=RegisterSTable,
        DeleteSTable=DeleteSTable,
        SearchSTable=SearchSTable
 
    }

    local shared={};

    local function NewValue(str,value)
        shared[str]=value;
    end

    local function GetValue(str)
        return shared[str];
    end

    local function DeleteValue(str)
        shared[str]=nil;
    end

    --管理所有场景所共享的资源
     t.shared={
         NewValue=NewValue,
         GetValue=GetValue,
         DeleteValue=DeleteValue
    
     }
     return t;
    

end

grmanager=Global_Resource_Manager.new();







