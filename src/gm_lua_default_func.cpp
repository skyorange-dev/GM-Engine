#include"gm2.h"

namespace gm
{
	int render_ref;//默认渲染函数标识符

	int track_ref;//默认相机跟踪函数标识符

	void InitRef(lua_State* L)
	{
		lua_getglobal(L, "C_DefaultRender");
		render_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		lua_getglobal(L, "C_DefaultTrack");
		track_ref = luaL_ref(L, LUA_REGISTRYINDEX);
	}


	//默认渲染函数
	int C_DefaultRender(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Entity* pr = (Entity*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -1);
		SDL_Renderer* render = (SDL_Renderer*)p2;
		lua_pop(L, 2);
		lua_pushnumber(L, (intptr_t)((pr->_data)[0]));
		return 1;
	}

	//默认相机跟踪函数
	int C_DefaultTrack(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Camera* pr = (Camera*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -1);
		Entity* entity = (Entity*)p2;
		lua_pop(L, 2);
		DefaultTrack(pr,entity);
		return 0;
	}
	
}

namespace gm
{
	void InitDefaultFunc(lua_State* L)
	{
		lua_register(L, "C_DefaultRender", C_DefaultRender);
		lua_register(L, "C_DefaultTrack", C_DefaultTrack);
	}
}