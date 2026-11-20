#include"gm2.h"

namespace gm
{
	int C_DeleteStrBlank(lua_State* L)
	{
		std::string str = DeleteStrBlank(lua_tostring(L, -1));
		lua_pop(L, 1);
		lua_pushstring(L, str.c_str());
		return 1;
	}

	int C_GetFileNameSuffix(lua_State* L)
	{
		std::string tem=lua_tostring(L, -1);
		std::string str1;
		str1 = GetFileName(tem);
		if (strcmp(str1.c_str(), std::string().c_str()) == 0)
		{
			str1 = tem;
		}
		
		lua_pop(L, 1);
		lua_pushstring(L, str1.c_str());
		return 1;
	}

	int C_WritePtr(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		Entity* tem = (Entity*)p1;
		intptr_t p2 = (intptr_t)lua_touserdata(L, -2);
		GM_Texture* temp = (GM_Texture*)p2;
		int index = lua_tonumber(L, -1);
		(tem->_data)[index] = temp->_data;
		lua_pop(L, 3);
		return 0;
	}

	void InitFFI(lua_State* L)
	{
		lua_register(L, "C_DeleteStrBlank", C_DeleteStrBlank);
		lua_register(L, "C_GetFileNameSuffix", C_GetFileNameSuffix);
		lua_register(L, "C_WritePtr", C_WritePtr);
	}
}