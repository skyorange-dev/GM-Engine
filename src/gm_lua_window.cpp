#include"gm2.h"

namespace gm
{
	int C_FullScreen(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		pr->FullScreen();
		lua_pop(L, 1);
		return 0;
	}

	int C_WindowScreen(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		pr->WindowScreen();
		lua_pop(L, 1);
		return 0;
	}

	int C_SetNextScene(lua_State* L/*const std::string& data*/)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Window* pr = (Window*)p1;
		std::string str = lua_tostring(L, -1);
		pr->SetNextScene(str);
		lua_pop(L, 2);
		return 0;
	}

	int C_UpdateData(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		lua_pop(L, 1);
		lua_pushnumber(L,pr->UpdateData());
		return 1;
	}

	int C_Render(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		lua_pop(L, 1);
		pr->Render();
		return 0;
	}

	int C_DynamicDelay(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Window* pr = (Window*)p1;
		int v = lua_tonumber(L, -1);
		lua_pop(L, 2);
		pr->DynamicDelay(v);
		return 0;
	}

	int C_RenderClear(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		pr->RenderClear();
		lua_pop(L, 1);
		return 0;
	}

	int C_SetMaxFps(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Window* pr = (Window*)p1;
		int v = lua_tonumber(L, -1);
		pr->SetMaxFps(v);
		lua_pop(L, 2);
		return 0;
	}

	int C_InsertScene(lua_State* L/*const std::string& data*/)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -4);
		Window* pr = (Window*)p1;
		std::string str = lua_tostring(L, -3);
		int width = lua_tonumber(L, -2);
		int height = lua_tonumber(L, -1);
		lua_pop(L, 4);
		lua_pushlightuserdata(L,pr->InsertScene(str,width,height));
	
		return 1;
	}

	int C_CreateCamera(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -4);
		Window* pr = (Window*)p1;
		std::string str = lua_tostring(L, -3);
		int lwidth = lua_tonumber(L, -2);
		int lheight = lua_tonumber(L, -1);
		lua_pop(L, 4);
		lua_pushlightuserdata(L, pr->CreateCamera(str,lwidth,lheight));
		return 1;
	}

	int C_DeleteCamera(lua_State* L/*const std::string& data, Entity* pr*/)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Window* pr = (Window*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -1);
		Camera* pr2 = (Camera*)p2;
		pr->DeleteCamera(pr2);
		lua_pop(L, 2);
		return 0;
	}

	int C_EraseScene(lua_State* L/*const std::string& data*/)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Window* pr = (Window*)p1;
		std::string str = lua_tostring(L, -1);
		pr->EraseScene(str);
		lua_pop(L, 2);
		return 0;
	}

	int C_InsertEntity(lua_State* L/*const std::string& data, Entity* pr*/)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -4);
		Window* pr = (Window*)p1;
		std::string str = lua_tostring(L, -3);
		intptr_t p2 = (intptr_t)lua_touserdata(L, -2);
		Entity* pr2 = (Entity*)p2;
		int distance = lua_tonumber(L, -1);
		pr->InsertEntity(str,pr2,distance);
		lua_pop(L, 4);
		return 0;
	}

	int C_EraseEntity(lua_State* L/*const std::string& data, Entity* pr*/)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Window* pr = (Window*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -1);
		Entity* pr2 = (Entity*)p2;
		pr->EraseEntity(pr2);
		lua_pop(L, 2);
		return 0;
	}

	int C_GetRenderer(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		lua_pop(L, 1);
		lua_pushlightuserdata(L,pr->GetRenderer());
		return 1;
	}

	int C_CreateWindow(lua_State* L)
	{
		const char* title = lua_tostring(L,-6);
		int lwidth = lua_tonumber(L,-5);
		int lheight = lua_tonumber(L,-4);
		Uint32 flags1 = lua_tonumber(L,-3);
		Uint32 flags2 = lua_tonumber(L, -2);
		bool flags3 = lua_toboolean(L, -1);
		printf("%d\n", flags2);
		lua_pop(L, 6);
		lua_pushlightuserdata(L, CreateWindow(L,title,lwidth,lheight,flags1,flags2,flags3));
		return 1;
	}

	int C_DeleteWindow(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		Free(pr);
		lua_pop(L,1);
		return 0;
	}

	int C_ShowWindow(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Window* pr = (Window*)p1;
		pr->ShowWindow();
		lua_pop(L, 1);
		return 0;
	}

	void InitWindow(lua_State* L)
	{
		lua_register(L, "C_FullScreen", C_FullScreen);
		lua_register(L, "C_WindowScreen",C_WindowScreen);
		lua_register(L, "C_SetNextScene", C_SetNextScene);
		lua_register(L, "C_UpdateData", C_UpdateData);
		lua_register(L, "C_Render", C_Render);
		lua_register(L, "C_DynamicDelay", C_DynamicDelay);
		lua_register(L, "C_RenderClear", C_RenderClear);
		lua_register(L, "C_SetMaxFps", C_SetMaxFps);
		lua_register(L, "C_InsertScene", C_InsertScene);
		lua_register(L, "C_EraseScene", C_EraseScene);
		lua_register(L, "C_InsertEntity", C_InsertEntity);
		lua_register(L, "C_EraseEntity", C_EraseEntity);
		lua_register(L, "C_GetRenderer", C_GetRenderer);
		lua_register(L, "C_CreateWindow", C_CreateWindow);
		lua_register(L, "C_DeleteWindow", C_DeleteWindow);
		lua_register(L, "C_ShowWindow", C_ShowWindow);
		lua_register(L, "C_CreateCamera", C_CreateCamera);
		lua_register(L, "C_DeleteCamera", C_DeleteCamera);
		
	}
}