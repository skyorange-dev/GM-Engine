Collision_Box={}

function Collision_Box.Init(entity_t,width,height,_type,typeid,buffer_size,is_ragidity)
       if is_ragidity~= true then
           local entity_value=entity_t.value;
           local value;
           local buffer1_ptr;
           local buffer_size1_ptr;
           if width== nil then
                width=0;
           end
           if height== nil then
                height=0;
           end
           if buffer_size==nil then
                buffer_size=2;
           end
           if is_ragidity==nil then
                is_ragidity=false;
           end
           if _type ==nil then
                _type=0;
           end
           if typeid ==nil then
                typeid=0;
           end
        
           value,buffer_size1_ptr,buffer1_ptr=C_NewCollision_Box(entity_value,width,height,_type,typeid,buffer_size,is_ragidity);
           buffer_size1_ptr=ffi.cast("unsigned char*",buffer_size1_ptr);
           buffer1_ptr=ffi.cast("Entity**",buffer1_ptr);
           local auto_ptr=ffi.cast("Collision_Box*",value);
           auto_ptr._type=_type;
       
           local function EntityCollisionCheck(entity_value)
                  local tem_type,tem_value=C_EntityCollisionCheck(_lwidth,_lheight,entity_value);
                  if tem_value==0 then--返回第一个碰撞的实体的指针，如果没发生碰撞就返回nil
                        return nil;
                  else
                        return tem_type,tem_value;
                  end
           end  

           local function MouseCollisionCheck(entity_dptr)
                if  event_dptr._mouse_position.x>entity_dptr._dest.x and event_dptr._mouse_position.x<entity_dptr._dest.x+auto_ptr._width then
                     if  event_dptr._mouse_position.y>entity_dptr._dest.y and event_dptr._mouse_position.y<entity_dptr._dest.y+auto_ptr._height then
                           if _last_mouse_status==-1 then
                                return true;--鼠标处于该实体碰撞箱内
                           end
                    end
                end
                return false;--表示该实体碰撞箱未与鼠标接触
           end  

           function CheckCollBuffer()
                local size1=buffer_size1_ptr[0];
                return size1;
           end
           function ReadCollBuffer()
                local size1=buffer_size1_ptr[0];
                local tem_t={};
                for i=1,size1 do
         
                    tem_t[i]=ffi.cast("void*",buffer1_ptr[i-1]);
                 
                end
        
                buffer_size1_ptr[0]=0;
            
                return size1,tem_t;
           end

           local function SetMask(index,str)
                if str=="typeid" then
                    str=1;
                else
                    str=0;
                end
                C_SetMask(value,index,str);
           end

           local function ReSetMask(index,str)
                 if str=="typeid" then
                    str=1;
                else
                    str=0;
                end
                C_ReSetMask(value,index,str);
           end

           entity_t.b_value=value;
           entity_t.b_dptr=auto_ptr;
           entity_t.EntityCollisionCheck=EntityCollisionCheck;
           entity_t.MouseCollisionCheck=MouseCollisionCheck;
           entity_t.ReadCollBuffer=ReadCollBuffer;
           entity_t.SetMask=SetMask;
           entity_t.ReSetMask=ReSetMask;
           entity_t.CheckCollBuffer=CheckCollBuffer;
     
       else
           local entity_value=entity_t.value;
           local value;
           local buffer_size1_ptr;
           local buffer1_ptr;
           if width== nil then
                width=0;
           end
           if height== nil then
                height=0;
           end
           if buffer_size==nil then
                buffer_size=2;
           end
  
           if _type ==nil then
                _type=0;
           end
           if typeid ==nil then
                typeid=0;
           end
           value,buffer_size1_ptr,buffer1_ptr=C_NewCollision_Box(entity_value,width,height,_type,typeid,buffer_size,is_ragidity);
           buffer_size1_ptr=nil;
           buffer1_ptr=nil;
       
     
           local auto_ptr=ffi.cast("Collision_Box*",value);
           auto_ptr._type=_type;
       
           local function EntityCollisionCheck(entity_value)
                  local tem_type,tem_value=C_EntityCollisionCheck(_lwidth,_lheight,entity_value);
                  if tem_value==0 then--返回第一个碰撞的实体的指针，如果没发生碰撞就返回nil
                        return nil;
                  else
                        return tem_type,tem_value;
                  end
           end  

           local function MouseCollisionCheck(entity_dptr)
                if  event_dptr._mouse_position.x>entity_dptr._dest.x and event_dptr._mouse_position.x<entity_dptr._dest.x+auto_ptr._width then
                     if  event_dptr._mouse_position.y>entity_dptr._dest.y and event_dptr._mouse_position.y<entity_dptr._dest.y+auto_ptr._height then
                           if _last_mouse_status==-1 then
                                return true;--鼠标处于该实体碰撞箱内
                           end
                    end
                end
                return false;--表示该实体碰撞箱未与鼠标接触
           end  

    

           local function SetMask(index,str)
                if str=="typeid" then
                    str=1;
                else
                    str=0;
                end
                C_SetMask(value,index,str);
           end

           local function ReSetMask(index,str)
                 if str=="typeid" then
                    str=1;
                else
                    str=0;
                end
                C_ReSetMask(value,index,str);
           end

           entity_t.b_value=value;
           entity_t.b_dptr=auto_ptr;
           entity_t.EntityCollisionCheck=EntityCollisionCheck;
           entity_t.MouseCollisionCheck=MouseCollisionCheck;
           entity_t.SetMask=SetMask;
           entity_t.ReSetMask=ReSetMask;

       end
      
end

