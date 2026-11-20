#include"gm2.h"

namespace gm
{

	int	C_SetTrack(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		const char* p2 = lua_tostring(L, -2);
		SetTrack((void*)p1, L, p2);
		lua_pop(L, 2);
		return 0;
	}

	int	C_SetDynamicCamera(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		Camera* pr1 = (Camera*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -1);
		Entity* pr2 = (Entity*)p2;
		lua_pop(L, 2);
		SetDynamicCamera(L,pr1,pr2);
		return 0;
	}

}

namespace gm
{
	void InitCamera(lua_State* L)
	{
		lua_register(L, "C_SetDynamicCamera", C_SetDynamicCamera);
		lua_register(L, "C_SetTrack", C_SetTrack);
	}
}