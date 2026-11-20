Camera={}

function Camera.new(window_v,scene_table,value)
       local t={};
       local scene_name=scene_table.scene_name;
       local window_v=window_v;
       t.value= value;
       t.dptr=ffi.cast("Camera*",t.value);
       grmanager.scene.RegisterGRTable(scene_name,t.value,t);
       local function SetTrack(func_name,func,init_func)
            if init_func ~=nil then
			    init_func(t)
		    end
            C_SetTrack(t.value,func_name,func);
       end

       local function UnBindCamera(entity_t)
            t.dptr._pr=NULL;
            t.dptr._IsUpdate=0;
            entity_t.UnBindCamera=nil;
            entity_t.TrackCeneter=nil;
       end

      local function TrackCenter(center_x,center_y)
		    local c_center_x = t.dptr._cvalue.x + t.dptr._cvalue.w / 2;
		    local c_center_y = t.dptr._cvalue.y + t.dptr._cvalue.h / 2;
		    t.dptr._cvalue.x =  t.dptr._cvalue.x+(center_x - c_center_x);
		    t.dptr._cvalue.y =  t.dptr._cvalue.y+(center_y - c_center_y);
          
       end


       local function BindEntity(entity_t)
            entity_t.UnBindCamera=UnBindCamera;
            t.dptr._IsUpdate=1;
            C_SetDynamicCamera(t.value,entity_t.value);
       end

       local function Delete()
            C_DeleteCamera(window_v,t.value);
       end

       t.SetTrack=SetTrack;
       t.BindEntity=BindEntity;
       t.Delete=Delete;
       t.TrackCenter=TrackCenter;
      return t;
end