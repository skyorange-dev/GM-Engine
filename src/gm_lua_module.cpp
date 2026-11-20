#include"gm2.h"

namespace gm
{
	int C_LoadModuleList(lua_State* L)
	{
		lua_pushlightuserdata(L,LoadMoudules(L));
		lua_pushnumber(L, _data->size());
		return 2;
	}

	int C_DeleteModuleList(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Free((Module*)p1);
		lua_pop(L, 1);
		for (auto& e : *_data)
		{
			cJSON_Delete(e);
		}
		return 0;
	}

	void InitModule(lua_State* L)
	{
		lua_register(L, "C_LoadModuleList", C_LoadModuleList);
		lua_register(L, "C_DeleteModuleList", C_DeleteModuleList);
	}
}