#include"gm2.h"

namespace gm
{
	int C_GetPoolMemoryUsed(lua_State* L)
	{
		lua_pushnumber(L,GetMemoryUsed());
		return 1;
	}

	void InitMemory(lua_State* L)
	{
		lua_register(L, "C_GetPoolMemoryUsed", C_GetPoolMemoryUsed);
	}
}