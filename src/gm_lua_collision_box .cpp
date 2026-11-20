#include "gm2.h"

namespace gm
{
#define Set_Mask(index,mask_ptr) (mask_ptr[index/64]=((1<<(index%64))|(mask_ptr[index/64])))
#define ReSet_Mask(index,mask_ptr) (mask_ptr[index/64]=((~(1<<(index%64)))&(mask_ptr[index/64])))

	int C_NewCollision_Box(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -7);
		Entity* entity = (Entity*)p1;
		int width = lua_tonumber(L,-6);
		int height = lua_tonumber(L, -5);
		int type = lua_tonumber(L, -4);
		int _typeid= lua_tonumber(L, -3);
		int buffer_size = lua_tonumber(L, -2);
		bool IsRigidity = lua_toboolean(L, -1);
		lua_pop(L, 7);
		Collision_Box* pr = NewCollision_Box(width,height,type,_typeid,buffer_size,IsRigidity);
		entity->_b_ptr = pr;
		Insert(entity);
		lua_pushlightuserdata(L, pr);
		if (pr->_ptr == NULL)
		{
			lua_pushnil(L);
			lua_pushnil(L);
		}
		else
		{
			lua_pushlightuserdata(L, ((unsigned char*)(pr->_ptr)));
			lua_pushlightuserdata(L,((unsigned char*)(pr->_ptr) + 1));
			//std::cout << (size_t)((unsigned char*)(pr->_ptr) + 1) << std::endl;
		}

		return 3;
	}

	int C_DeleteCollision_Box(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Entity* entity = (Entity*)p1;
		Erase(entity);
		DeleteCollision_Box(entity->_b_ptr);
		lua_pop(L, 1);
		return 0;
	}
	
	int C_SetMask(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		Collision_Box* box = (Collision_Box*)p1;
		int index = lua_tonumber(L, -2);
		int flag = lua_tonumber(L, -1);
		lua_pop(L, 3);
		if (flag == 0)
		{
			Set_Mask(index, (&(box->_mask[0])));
		}
		else
		{
			Set_Mask(index, (&(box->_maskid[0])));
		}
		return 0;
	}

	int C_ReSetMask(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Collision_Box* box = (Collision_Box*)p1;
		int index = lua_tonumber(L, -2);
		int flag = lua_tonumber(L, -1);
		lua_pop(L, 3);
		if (flag == 0)
		{
			ReSet_Mask(index, (&(box->_mask[0])));
		}
		else
		{
			ReSet_Mask(index, (&(box->_maskid[0])));
		}
		
		return 0;
	}

	void InitCollision_Box(lua_State* L)
	{
		lua_register(L, "C_NewCollision_Box", C_NewCollision_Box);
		lua_register(L, "C_DeleteCollision_Box", C_DeleteCollision_Box);
		lua_register(L, "C_SetMask", C_SetMask);
		lua_register(L, "C_ReSetMask", C_ReSetMask);
	}
}