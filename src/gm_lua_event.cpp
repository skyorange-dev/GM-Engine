#include"gm2.h"

namespace gm
{
	int C_GetEventDptr(lua_State* L)
	{
		lua_pushlightuserdata(L, & e);
		return 1;
	}

	int C_UpdateEvent(lua_State* L)
	{
		UpdateEvent();
		return 0;
	}

	void InitEvent(lua_State* L)
	{
		lua_register(L, "C_UpdateEvent", C_UpdateEvent);
		lua_register(L, "C_GetEventDptr", C_GetEventDptr);
	
	}
}