Window={}

function Window.new(str,lwidth,lheight,flag1,flag2,flag3)
	local value;--C端所使用的指针
	if flag1==nil then 
		if flag2==nil then
			if flag3==nil then
				value=C_CreateWindow(str,lwidth,lheight,32,-1,true);
			else
				value=C_CreateWindow(str,lwidth,lheight,32,-1,flag3);
			end
			
		else
			if flag3==nil then
				value=C_CreateWindow(str,lwidth,lheight,32,flag2,true);
			else
				value=C_CreateWindow(str,lwidth,lheight,32,flag2,flag3);
			end
		end
	else
		if flag2==nil then
			if flag3==nil then
				value=C_CreateWindow(str,lwidth,lheight,flag1,-1,true);
			else
				value=C_CreateWindow(str,lwidth,lheight,flag1,-1,flag3);
			end
			
		else
			if flag3==nil then
				value=C_CreateWindow(str,lwidth,lheight,flag1,flag2,true);
			else
				value=C_CreateWindow(str,lwidth,lheight,flag1,flags2,flag3);
			end
		end
	end

	local auto_ptr=ffi.cast("void*",value);--lua端所使用的指针
	ffi.gc(auto_ptr, function(val)--注意，C端指针被ffi转换成Lua端指针后就无法转回去了
        C_DeleteWindow(value);
    end);

	local function FullScreen()
		C_FullScreen(value);
	end

	local function WindowScreen()
		C_WindowScreen(value);
	end

	local function ShowWindow()
		C_ShowWindow(value);
	end

	local function SetNextScene(str)
		C_SetNextScene(value,str);
	end

	local function UpdateData()
		return C_UpdateData(value);
	end

	local function Render()
		C_Render(value);
	end

	local function DynamicDelay(flag)
		if flag==nil then
			C_DynamicDelay(value,1);
		else
			C_DynamicDelay(value,flag);
		end
	end

	local function RenderClear()
		C_RenderClear(value);
	end

	local function SetMaxFps(maxfps)
		C_SetMaxFps(value,maxfps);
	end

	local function InsertScene(scene_table,width,height)
	    if width ==nil then
			width=1920;
		end
		if height ==nil then
			height=1080;
		end
	    scene_table.is_delete=true;
		return Camera.new(value,scene_table,C_InsertScene(value,scene_table.scene_name,width,height));
	end

	local function DeleteCamera(camera_t)--删除摄像机
		C_DeleteCamera(value,camera_t.value);
		camera_t.DeleteCamera=nil;
	end

	local function CreateCamera(scene_table,lwidth,lheight)
		local camera_t= Camera.new(value,scene_table,C_CreateCamera(value,scene_table.scene_name,lwidth,lheight));
		camera_t.DeleteCamera= DeleteCamera;
		return camera_t;
	end

	local function EraseScene(scene_name)
		grmanager.scene.DeleteSTable(scene_name);
		C_EraseScene(value,scene_name);
	end

	local function UnBindWindow(entity_t)--解绑实体
		C_EraseEntity(value,entity_t.value);
		entity_t.UnBindWindow=nil;
	end

	local function BindEntity(scene_name,entity_t,distance)
		if distance ==nil then
			distance=100;
		end
		entity_t.UnBindWindow=UnBindWindow;
		C_InsertEntity(value,scene_name,entity_t.value,distance);
	end

	local function GetRenderer()
		return C_GetRenderer(value);
	end

	local function NewCTDataNode(tex_name,width,height,func)
         C_NewTextureNode(tex_name,C_GetRenderer(value),width,height,func);
    end
		
		
	return{
		value=value,
		ptr=auto_ptr,
		ShowWindow=ShowWindow,
		FullScreen=FullScreen,
		WindowScreen=WindowScreen,
		SetNextScene=SetNextScene,
		UpdateData=UpdateData,
		Render=Render,
		DynamicDelay=DynamicDelay,
		RenderClear=RenderClear,
		SetMaxFps=SetMaxFps,
		InsertScene=InsertScene,
		EraseScene=EraseScene,
		BindEntity=BindEntity,
		EraseScene=EraseScene,
		GetRenderer=GetRenderer,
		CreateCamera= CreateCamera,
		NewCTDataNode= NewCTDataNode
	};

end