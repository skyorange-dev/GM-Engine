SDL_Texture={}

function SDL_Texture.new(render,width,height)
    return C_NewTexture(render,width,height);
end

Entity={}

function Entity.new(scene_name,tex_num,IsDraw)
	local t={};
	if IsDraw == nil then
		local scene_name=scene_name;
		local value;
		local OwnedCollison=false;
		if tex_num ==nil then
			value=C_NewEntity(1);
		else
			value=C_NewEntity(tex_num);
		end
			
		local auto_ptr=ffi.cast("Entity*",value);
		local function Delete()
			if t.UnBindWindow~=nil then
				t.UnBindWindow(t)
			end
			if t.dptr._b_ptr~=ffi.NULL then
				C_DeleteCollision_Box(t.value);
			end
			if t.data_value~=nil then
				if t.data_delete~= nil then
					t.data_delete(t.data_value);
				end
				local ptr=ffi.cast("GM_API*",user_capi);
				ptr.UserFree(t.data_value);
			end
			C_DeleteEntity(value);
		end
	
		t.value=value
		t.dptr=auto_ptr
		t.Delete=Delete
	else
		local scene_name=scene_name;
		local value;
		local OwnedCollison=false;
		if tex_num ==nil then
			value=C_NewEntity(1);
		else
			value=C_NewEntity(tex_num);
		end
			
		local auto_ptr=ffi.cast("Entity*",value);
		local function Delete()
			if t.UnBindWindow~=nil then
				t.UnBindWindow(t)
			end
			if t.dptr._b_ptr~=ffi.NULL then
				C_DeleteCollision_Box(t.value);
			end
			if t.data_value~=nil then
				if t.data_delete~= nil then
					t.data_delete(t.data_value);
				end
				local ptr=ffi.cast("GM_API*",user_capi);
				ptr.UserFree(t.data_value);
			end
			C_DeleteDEntity(value,t.bsize);
		end
	
		t.value=value
		t.dptr=auto_ptr
		t.Delete=Delete
	end
	
			
	return t;
	
end

Image={}

function Image.new(scene_table,tex_num)
	local v;
	local scene_name=scene_table.scene_name;
	local gmanager=scene_table.gmanager;
	if tex_num==nil then
		tex_num=1;
	end
	v=Entity.new(scene_name,tex_num);
	grmanager.scene.RegisterGRTable(scene_name,v.value,v);

	local function InitTextureBuffer(str,render,buffer_index)
		local tem=gmanager.GetImage(str,render);
		C_WritePtr(v.value,tem.value,buffer_index);
		return tem.dptr._width,tem.dptr._height;
	end

	local function InitImage(str,render)
		local tem=gmanager.GetImage(str,render);
		v.dptr._data[0]=tem.dptr._data;
		v.dptr._source.w = tem.dptr._width;
		v.dptr._source.h = tem.dptr._height;
		v.dptr._dest.w = tem.dptr._width;
		v.dptr._dest.h = tem.dptr._height;
		v.dptr._source.x =0;
		v.dptr._source.y =0;
		v.dptr._dest.x =0;
		v.dptr._dest.y =0;
		return tem.dptr._width,tem.dptr._height;
	end

	local function SetUpdateData(update_fname,func,init_func,auto_open)
		if auto_open ~=false then
			v.dptr._IsUpdate=1;
		end

		if init_func ~=nil then
			init_func(v)
		end
	
		for i,j in ipairs(GM_Update_Func[3]) do
			if j==update_fname then
				C_SetUpdateData(v.value,i);
				return;
			end
		end
		
		local func_count=GM_Update_Func[4];
		func_count=func_count+1;
		GM_Update_Func[3][func_count]=update_fname;
		GM_Update_Func[1][func_count]=func;
		GM_Update_Func[4]=func_count;
		C_SetUpdateData(v.value,func_count);
	
	end

	local function NewCData(ctype,delete,init,...)
		local ptr=ffi.cast("GM_API*",user_capi);
		v.data_value=ptr.UserMalloc(ffi.sizeof(ctype));
		v.data_dptr=ffi.cast(ctype.."*",v.data_value);
		if init~= nil then
			init(v.data_value,...);
		end
		if delete ~= nil then
			v.data_delete=delete;
		end
	end


	v.InitTextureBuffer=InitTextureBuffer;
	v.InitImage=InitImage;
	v.SetUpdateData= SetUpdateData;
	v.NewCData=NewCData;
	v.aplayer=scene_table.aplayer;

	return v;
end

Text={}

function Text.new(scene_table,tex_num)
	local scene_name=scene_table.scene_name;
	local gmanager=scene_table.gmanager;
	local v;
	if tex_num==nil then
		tex_num=1;
	end
	v=Entity.new(scene_name,tex_num);
	grmanager.scene.RegisterGRTable(scene_name,v.value,v);
	local function InitTextureBuffer(font_name,text_size,text_str,render,buffer_index)
		local tem=gmanager.GetText(font_name,text_size,text_str,render);
		C_WritePtr(v.value,tem.value,buffer_index);
		return tem.dptr._width,tem.dptr._height;
	end

	local function InitText(font_name,text_size,text_str,render)
		local tem=gmanager.GetText(font_name,text_size,text_str,render);
		v.dptr._data[0]=tem.dptr._data;
		v.dptr._source.w = tem.dptr._width;
		v.dptr._source.h = tem.dptr._height;
		v.dptr._dest.w = tem.dptr._width;
		v.dptr._dest.h = tem.dptr._height;
		v.dptr._source.x =0;
		v.dptr._source.y =0;
		v.dptr._dest.x =0;
		v.dptr._dest.y =0;
		return tem.dptr._width,tem.dptr._height;
	end

	local function SetUpdateData(update_fname,func,init_func,auto_open)
		if auto_open ~=false then
			v.dptr._IsUpdate=1;
		end

		if init_func ~=nil then
			init_func(v)
		end
			for i,j in ipairs(GM_Update_Func[3]) do
			if j==update_fname then
				C_SetUpdateData(v.value,i);
				return;
			end
		end
		
		local func_count=GM_Update_Func[4];
		func_count=func_count+1;
		GM_Update_Func[3][func_count]=update_fname;
		GM_Update_Func[1][func_count]=func;
		GM_Update_Func[4]=func_count;
		C_SetUpdateData(v.value,func_count);
	end

	
	local function NewCData(ctype,delete,init,...)
		local ptr=ffi.cast("GM_API*",user_capi);
		v.data_value=ptr.UserMalloc(ffi.sizeof(ctype));
		v.data_dptr=ffi.cast(ctype.."*",v.data_value);
		if init~= nil then
			init(v.data_value,...);
		end
		if delete ~= nil then
			v.data_delete=delete;
		end
	end



	v.InitTextureBuffer=InitTextureBuffer;
	v.InitText=InitText;
	v.SetUpdateData= SetUpdateData;
	v.NewCData=NewCData;

	return v;
end

Draw={}

function Draw.new(scene_table,tex_num)
	local v;
	if tex_num== nil then
		tex_num=1;
	end
	v=Entity.new(scene_name,tex_num,true);
	v.dptr._type=1;
	local scene_name=scene_table.scene_name;
	local gmanager=scene_table.gmanager;
	--local size=0;
	local size_ptr=ffi.cast("size_t*",v.dptr._data);

	grmanager.scene.RegisterGRTable(scene_name,v.value,v);

	local function InitDraw(width,height,render,func)
		local tem0=C_NewTexture(render,width,height);
		local tem=ffi.cast("SDL_Texture*",tem0);
		v.dptr._data[v.bsize]=tem;
		v.bsize=v.bsize+1;
		v.dptr._source.w = width;
		v.dptr._source.h = height;
		v.dptr._dest.w = width;
		v.dptr._dest.h = height;
		v.dptr._source.x =0;
		v.dptr._source.y =0;
		v.dptr._dest.x =0;
		v.dptr._dest.y =0;
		if func~= nil then
			 C_InitTexture(render,tem0,func);
		end
		return v.bsize;
	end

	local function InitTextureBuffer(width,height,render,func)
		local tem0=C_NewTexture(render,width,height);
		local tem=ffi.cast("SDL_Texture*",tem0);
		v.dptr._data[v.bsize]=tem;
		v.bsize=v.bsize+1;
		if func~= nil then
			 C_InitTexture(render,tem0,func);
		end
		return v.bsize;
	end

	local function SetUpdateData(update_fname,func,init_func,auto_open)
		if auto_open ~=false then
			v.dptr._IsUpdate=1;
		end

		if init_func ~=nil then
			init_func(v)
		end
	
		for i,j in ipairs(GM_Update_Func[3]) do
			if j==update_fname then
				C_SetUpdateData(v.value,i);
				return;
			end
		end
		
		local func_count=GM_Update_Func[4];
		func_count=func_count+1;
		GM_Update_Func[3][func_count]=update_fname;
		GM_Update_Func[1][func_count]=func;
		GM_Update_Func[4]=func_count;
		C_SetUpdateData(v.value,func_count);
	end

	
	local function SetRender(render_fname,func)
		C_SetRender(v.value,render_fname,func);
	end

	local function NewCData(ctype,delete,init,...)
		local ptr=ffi.cast("GM_API*",user_capi);
		v.data_value=ptr.UserMalloc(ffi.sizeof(ctype));
		v.data_dptr=ffi.cast(ctype.."*",v.data_value);
		if init~= nil then
			init(v.data_value,...);
		end
		if delete ~= nil then
			v.data_delete=delete;
		end
	end


	v.SetUpdateData= SetUpdateData;
	v.InitTextureBuffer=InitTextureBuffer;
	v.SetRender= SetRender;
	v.NewCData=NewCData;
	v.InitDraw=InitDraw;
	v.bsize=0;

	return v;
end

StaticDraw={}

function StaticDraw.new(scene_table,tex_num)
	local v;
	local gmanager=scene_table.gmanager;
	if tex_num== nil then
		tex_num=1;
	end
	v=Entity.new(scene_name,tex_num,true);
	v.dptr._type=1;
	v.dptr._IsSDraw=1;
	local scene_name=scene_table.scene_name;
	local gmanager=scene_table.gmanager;
	--local size=0;
	local size_ptr=ffi.cast("size_t*",v.dptr._data);

	grmanager.scene.RegisterGRTable(scene_name,v.value,v);

	local function InitStaticDraw(tex_name)
		local tem0=gmanager.GetTTexture(tex_name);
		local tem1=ffi.cast("TTexture_Node*",tem0);
		local tem=ffi.cast("SDL_Texture*",tem1._data);
		v.dptr._data[v.bsize]=tem;
		v.bsize=v.bsize+1;
		v.dptr._source.w = tem1._width;
		v.dptr._source.h = tem1._height;
		v.dptr._dest.w = tem1._width;
		v.dptr._dest.h = tem1._height;
		v.dptr._source.x =0;
		v.dptr._source.y =0;
		v.dptr._dest.x =0;
		v.dptr._dest.y =0;
	
		return v.bsize;
	end

	local function InitTextureBuffer(tex_name)
		local tem0=gmanager.GetTTexture(tex_name);
		local tem1=ffi.cast("TTexture_Node*",tem0);
		local tem=ffi.cast("SDL_Texture*",tem1._data);
		v.dptr._data[v.bsize]=tem;
		v.bsize=v.bsize+1;
		return v.bsize;
	end

	local function SetUpdateData(update_fname,func,init_func,auto_open)
		if auto_open ~=false then
			v.dptr._IsUpdate=1;
		end

		if init_func ~=nil then
			init_func(v)
		end
	
		for i,j in ipairs(GM_Update_Func[3]) do
			if j==update_fname then
				C_SetUpdateData(v.value,i);
				return;
			end
		end
		
		local func_count=GM_Update_Func[4];
		func_count=func_count+1;
		GM_Update_Func[3][func_count]=update_fname;
		GM_Update_Func[1][func_count]=func;
		GM_Update_Func[4]=func_count;
		C_SetUpdateData(v.value,func_count);
	end

	local function NewCData(ctype,delete,init,...)
		local ptr=ffi.cast("GM_API*",user_capi);
		v.data_value=ptr.UserMalloc(ffi.sizeof(ctype));
		v.data_dptr=ffi.cast(ctype.."*",v.data_value);
		if init~= nil then
			init(v.data_value,...);
		end
		if delete ~= nil then
			v.data_delete=delete;
		end
	end


	v.SetUpdateData= SetUpdateData;
	v.InitTextureBuffer=InitTextureBuffer;
	v.NewCData=NewCData;
	v.InitStaticDraw=InitStaticDraw;
	v.NewCTDataNode=NewCTDataNode;
	v.bsize=0;

	return v;
end


