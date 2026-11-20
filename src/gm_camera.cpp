#include "gm2.h"

namespace gm
{
	void SetTrack(void* pr, lua_State* L, const char* str)
	{
		Camera* ptr = (Camera*)pr;
		auto e = _ref_data->find(str);
		if (e == _ref_data->end())
		{
			ptr->_track = luaL_ref(L, LUA_REGISTRYINDEX);
			_ref_data->insert(std::make_pair(str, ptr->_track));
		}
		else
		{
			lua_pop(L, 1);
			ptr->_track = e->second;
		}

	}

	void InitCamera(Camera* c, int window_lwidth, int window_lheight)//初始化
	{
		c->_cvalue.w = window_lwidth;
		c->_cvalue.h = window_lheight;
		c->_cvalue.x = 0;
		c->_cvalue.y = 0;
		c->_last_value.x = 0;
		c->_last_value.y = 0;
		c->_last_value.w = 0;
		c->_last_value.w = 0;
		c->_pr = NULL;
		c->_track = track_ref;
		c->_last_cvalue.w = c->_cvalue.w;
		c->_last_cvalue.h = c->_cvalue.h;
		c->_last_cvalue.x = c->_cvalue.x;
		c->_last_cvalue.y = c->_cvalue.y;
		c->_coffset.x = 0;
		c->_coffset.y = 0;
		c->_priority = 100;
		c->_ipr = NULL;
		c->_IsRender = 1;
		c->_IsUpdate = 0;
	}

	void DefaultTrack(Camera* c, Entity* pr)
	{
		int e_center_x = pr->_dest.x + pr->_dest.w / 2;
		int e_center_y = pr->_dest.y + pr->_dest.h / 2;
		int c_center_x = c->_cvalue.x + c->_cvalue.w / 2;
		int c_center_y = c->_cvalue.y + c->_cvalue.h / 2;
		c->_cvalue.x += e_center_x - c_center_x;
		c->_cvalue.y+= e_center_y - c_center_y;
	}

	void SetDynamicCamera(lua_State* L, Camera* c,Entity* pr)
	{
		c->_pr = pr;
		TrackEntityStatus(L,c, pr);
	}


	void TrackEntityStatus(lua_State* L,Camera* c, Entity* pr)
	{
		static bool IsUpdate = false;
		if (pr->_dest.x != c->_last_value.x)
		{
			IsUpdate = true;
		}
		else if (pr->_dest.y != c->_last_value.y)
		{
			IsUpdate = true;
		}
		else if (pr->_dest.w != c->_last_value.w)
		{
			IsUpdate = true;
		}
		else if (pr->_dest.h != c->_last_value.h)
		{
			IsUpdate = true;
		}
		if (IsUpdate = true)
		{
		
			int e_center_x = pr->_dest.x + pr->_dest.w / 2;
			int e_center_y = pr->_dest.y + pr->_dest.h / 2;
			int c_center_x = c->_cvalue.x + c->_cvalue.w / 2;
			int c_center_y = c->_cvalue.y + c->_cvalue.h / 2;
			c->_cvalue.x += e_center_x - c_center_x;
			c->_cvalue.y+= e_center_y - c_center_y;
			c->_last_value.x = pr->_dest.x;
			c->_last_value.y = pr->_dest.y;
			c->_last_value.w = pr->_dest.w;
			c->_last_value.h = pr->_dest.h;
			IsUpdate = false;
		}
	}


}