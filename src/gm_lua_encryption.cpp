#include"gm2.h"

namespace gm
{
	int C_RunLuaFile(lua_State* L)
	{
		std::string str = lua_tostring(L, -1);
		decryption(str, L);
		lua_pop(L, 1);
		return 0;
	}

	void InitEncryption(lua_State* L)
	{
		lua_register(L, "C_RunLuaFile", C_RunLuaFile);
	}
}