#include"gm2.h"

//实体
namespace gm
{
	int	C_SetRender(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		const char* p2 = lua_tostring(L, -2);
		SetRender((void*)p1, L, p2);
		lua_pop(L, 2);
		return 0;
	}

	int	C_SetUpdateData(lua_State* L)
	{
		if (GM_Update == 0)
		{
			lua_getglobal(L, "GM_Update");
			GM_Update = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Entity* pr = (Entity*)p1;
		int index = lua_tonumber(L, -1);
		//SetUpdateData((void*)p1, L, index);
		pr->_update = index;
		lua_pop(L, 2);
		return 0;
	}

	int C_NewEntity(lua_State* L)
	{
		int num = lua_tonumber(L, -1);
		lua_pop(L, 1);
		lua_pushlightuserdata(L,NewEntity(L,num));
		return 1;
	}


	int C_DeleteEntity(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Entity* pr = (Entity*)p1;
		lua_pop(L, 1);
		DeleteEntity(pr);
		return 0;
	}

	int C_DeleteDEntity(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Entity* pr = (Entity*)p1;
		int count = lua_tonumber(L, -1);
		lua_pop(L, 2);
		DeleteDEntity(pr,count);
		return 0;
	}

	int C_NewTexture(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		SDL_Renderer* render = (SDL_Renderer*)p1;
		int width = lua_tonumber(L, -2);
		int height = lua_tonumber(L, -1);
		void* pr = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
		SDL_SetTextureBlendMode((SDL_Texture*)pr, SDL_BLENDMODE_BLEND);
		lua_pushlightuserdata(L, pr);
		return 1;
	}

	int C_InitTexture(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		SDL_Renderer* render = (SDL_Renderer*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -2);
		SDL_Texture* tex = (SDL_Texture*)p2;
		RenderTexture(L, tex, render);
		lua_pop(L, 2);
		return 0;
	}

}

namespace gm
{
	void InitEntity(lua_State* L)
	{
		lua_register(L, "C_NewEntity", C_NewEntity);
		lua_register(L, "C_DeleteEntity", C_DeleteEntity);
		lua_register(L, "C_SetRender", C_SetRender);
		lua_register(L, "C_SetUpdateData", C_SetUpdateData);
		lua_register(L, "C_InitTexture", C_InitTexture);
		lua_register(L, "C_NewTexture", C_NewTexture);
		lua_register(L, "C_DeleteDEntity",C_DeleteDEntity);
	}
}