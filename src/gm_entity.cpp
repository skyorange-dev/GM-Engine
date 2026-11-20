#include "gm2.h"

//实体
namespace gm
{
#ifdef USER_DEBUG
	size_t entity_count = 0;
#endif
	
	std::unordered_map<std::string, int, std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, int>>>* _ref_data;

	int update_count = 1;

	void InitValueRefData()
	{
		static std::unordered_map<std::string, int, std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, int>>> ref_data;
		_ref_data = &ref_data;
	}

	void SetRender(void* pr, lua_State* L, const char* str)
	{
		Entity* ptr = (Entity*)pr;
		auto e = _ref_data->find(str);
		if ( e== _ref_data->end())
		{
			ptr->_render = luaL_ref(L, LUA_REGISTRYINDEX);
			_ref_data->insert(std::make_pair(str, ptr->_render));
		}
		else
		{
			lua_pop(L, 1);
			ptr->_render = e->second;
		}
		
		
	}

	void RenderTexture(lua_State* L, SDL_Texture* tex, SDL_Renderer* render)
	{

		SDL_SetRenderTarget(render, tex);
		SDL_SetRenderDrawColor(render, 128, 128, 128, 0);
		SDL_RenderClear(render);
		lua_pushlightuserdata(L, render);
		int re = lua_pcall(L, 1, 0, 0);
		if (re != 0)
		{
			const char* err = lua_tostring(L, -1);
			printf("Lua 错误: %s\n", err);
			lua_pop(L, 1);
			exit(1);
		}
		SDL_SetRenderTarget(render, NULL);

	}

	void* NewEntity(lua_State* L, int num)
	{
#ifdef USER_DEBUG
		entity_count++;
#endif
		void* ptr = (Entity*)Malloc(sizeof(void*)+sizeof(Entity));
		Entity*  pr = (Entity*)((char*)ptr + sizeof(void*));
		pr->_IsVisible = 1;
		pr->_IsUpdate = 0;
		pr->_b_ptr = NULL;
		pr->_update = 0;
		pr->_rindex = 0;
		pr->_IsWRender = 0;
		pr->_IsSDraw = 0;
		pr->_b_ptr = 0;
		pr->_type = 0;
		if (num != 0)
		{
			pr->_data = (SDL_Texture**)Malloc(sizeof(SDL_Texture*) * num);
		}
		else
		{
			pr->_data = NULL;
		}
		pr->_render = render_ref;
		pr->_ipr = NULL;
		*((void**)ptr) = NULL;
		return pr;
	}

	void DeleteEntity(Entity* pr)
	{
#ifdef USER_DEBUG
		entity_count--;
#endif
		char* sname = (char*)((char*)pr - sizeof(void*));
		if (pr->_ipr != NULL)
		{
			Free(pr->_ipr);
			Free(*((char**)sname));
		}
		if (pr->_data != NULL)
		{
			Free(pr->_data);
		}
		Free(sname);
	}

	void DeleteDEntity(Entity* pr,int count)
	{
#ifdef USER_DEBUG
		entity_count--;
#endif
		char* sname = (char*)((char*)pr - sizeof(void*));
		if (pr->_ipr != NULL)
		{
			Free(pr->_ipr);
			Free(*((char**)sname));
		}
		if (pr->_data != NULL)
		{
			for (int i = 0; i < count; i++)
			{
				SDL_DestroyTexture(pr->_data[i]);
			}

		}

		Free(sname);
	}
}

