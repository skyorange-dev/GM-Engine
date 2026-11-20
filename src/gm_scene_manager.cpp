#pragma once
#include "gm2.h"

namespace gm
{

	SDL_Rect RectCheck(SDL_Rect* pr1,SDL_Rect* pr2)//矩形相交检测函数
	{
		SDL_Rect tem;
		tem.w = 0;
		tem.h = 0;
		int width1 = pr1->w;
		int height1 = pr1->h;
		int box_x1 = pr1->x ;
		int box_y1 = pr1->y;

		int width2 = pr2->w;
		int height2 = pr2->h;
		int box_x2 = pr2->x;
		int box_y2 = pr2->y;

		if (box_x1 + width1 > box_x2)
		{
			//不在2号碰撞箱的左边
			if (box_x1 < box_x2 + width2)
			{
				//不在2号碰撞箱的右边
				if (box_y1 + height1 > box_y2)
				{
					//不在2号碰撞箱的上边
					if (box_y1 < box_y2 + height2)
					{
						//不在2号碰撞箱的下边
						//综上，只存在相交,或包含的可能
						if (box_x1<=box_x2 && box_x1 + width1>=box_x2 + width2&& box_y1 <= box_y2 && box_y1 + height1 >= box_y2 + height2)//box1与box2包含
						{
							//box2被box1包含
							tem.x = box_x2;
							tem.y = box_y2;
							tem.w = width2;
							tem.h = height2;
						}
						else if (box_x2 <= box_x1 && box_x2+ width2 >= box_x1 + width1 && box_y2 <= box_y1 && box_y2 + height2 >= box_y1 + height1)
						{
							//box1被box2包含
							tem.x = box_x1;
							tem.y = box_y1;
							tem.w = width1;
							tem.h = height1;
						}
						else
						{

							//box1与box2相交

							if (box_x2 < box_x1)
							{
								tem.x = box_x1;
								if (width1 < box_x2 + width2 - box_x1)
								{
									tem.w = width1;
								}
								else
								{
									tem.w = box_x2 + width2 - box_x1;
								}
							}
							else if (box_x2 >= box_x1 && box_x2 <= box_x1 + width1)
							{
								tem.x = box_x2;
								if (width2< width1 - (box_x2 - box_x1))
								{
									tem.w = width2;
								}
								else
								{
									tem.w = width1 - (box_x2 - box_x1);
								}
								
							}

							if (box_y2 < box_y1)
							{
								tem.y = box_y1;
								if (height1 < box_y2 + height2 - box_y1)
								{
									tem.h = height1;
								}
								else
								{
									tem.h = box_y2 + height2 - box_y1;
								}
								
							}
							else if (box_y2 >= box_y1 && box_y2 <= box_y1 + height1)
							{
								tem.y = box_y2;
								if (height2<height1 - (box_y2 - box_y1))
								{
									tem.h = height2;
								}
								else
								{
									tem.h = height1 - (box_y2 - box_y1);
								}

							}

							
							


						}
					}
						
					
				}
			}
		}
		
		return tem;
	}

	void Renderer_Task::Render(SDL_Renderer* render)
	{
		Entity* pr = nullptr;

		for (auto& e : _t)
		{
			
			pr = e.second;
			
			if (pr->_IsWRender == 0)//未开启窗口渲染模式
			{
				int camera_count = _camera.size();
				int c_count = 0;
				for (auto& f : _camera)
				{
					c_count++;
					if (f.second->_IsRender == 0)
					{
						continue;
					}
					SDL_Rect dest_tem = RectCheck(&(pr->_dest), &(f.second->_cvalue));
					if (dest_tem.w != 0 && dest_tem.h != 0)
					{
						SDL_Rect source_tem(pr->_source);
						source_tem.w = dest_tem.w;
						source_tem.h = dest_tem.h;
						if (dest_tem.x == pr->_dest.x)
						{
							source_tem.x = pr->_source.x;

						}
						else
						{
							source_tem.x = pr->_source.x + dest_tem.x - pr->_dest.x;
						}
						if (dest_tem.y == pr->_dest.y)
						{
							source_tem.y = pr->_source.y;
						}
						else
						{
							source_tem.y = pr->_source.y + dest_tem.y - pr->_dest.y;
						}

						dest_tem.x -= f.second->_cvalue.x - f.second->_coffset.x;
						dest_tem.y -= f.second->_cvalue.y - f.second->_coffset.y;
					
						if (pr->_IsVisible == 1)
						{
							if (pr->_render == render_ref)
							{

								SDL_RenderCopy(render, (pr->_data)[pr->_rindex], &source_tem, &dest_tem);
							}
							else
							{
								//绘图
								if (pr->_IsSDraw == 0)
								{
									SDL_SetRenderTarget(render, pr->_data[pr->_rindex]);
									SDL_SetRenderDrawColor(render, 128, 128, 128, 0);
									SDL_RenderClear(render);
									lua_rawgeti(_L, LUA_REGISTRYINDEX, pr->_render);
									lua_pushlightuserdata(_L, pr);
									lua_pushlightuserdata(_L, render);
									int re = lua_pcall(_L, 2, 0, 0);
									if (re != 0)
									{
										const char* err = lua_tostring(_L, -1);
										printf("Lua 错误: %s\n", err);
										lua_pop(_L, 1);
										exit(1);
									}
									SDL_SetRenderTarget(render, NULL);

								}
								SDL_RenderCopy(render, (pr->_data)[pr->_rindex], &source_tem, &dest_tem);

							}

						}

						
					}


				}
			}
			else
			{
				SDL_Rect dest_tem(pr->_dest);
				SDL_Rect source_tem(pr->_source);
				if (dest_tem.w != 0 && dest_tem.h != 0)
				{
					if (pr->_IsVisible == 1)
					{
						if (pr->_render == render_ref)
						{

							SDL_RenderCopy(render, (pr->_data)[pr->_rindex], &source_tem, &dest_tem);
						}
						else
						{
							//绘图
							if (pr->_IsSDraw == 0)
							{

								SDL_SetRenderTarget(render, pr->_data[pr->_rindex]);
								SDL_SetRenderDrawColor(render, 128, 128, 128, 0);
								SDL_RenderClear(render);
								lua_rawgeti(_L, LUA_REGISTRYINDEX, pr->_render);
								lua_pushlightuserdata(_L, pr);
								lua_pushlightuserdata(_L, render);
								int re = lua_pcall(_L, 2, 0, 0);
								if (re != 0)
								{
									const char* err = lua_tostring(_L, -1);
									printf("Lua 错误: %s\n", err);
									lua_pop(_L, 1);
									exit(1);
								}
								SDL_SetRenderTarget(render, NULL);
							}
							SDL_RenderCopy(render, (pr->_data)[pr->_rindex], &source_tem, &dest_tem);


						}

					}

				}
			}
			
			
		}

	
	
	
			
	}



	std::vector<UpdateNode> update_manager;
//#ifdef USER_DEBUG
//	double _interval = 0;
//	size_t _tem_interval = 0;
//	size_t _frequency = SDL_GetPerformanceFrequency();
//#endif
	int Renderer_Task::UpdateData()
	{
//#ifdef USER_DEBUG
//		_tem_interval = SDL_GetPerformanceCounter();
//#endif
		int code = 0;
		Entity* pr = nullptr;
		lua_rawgeti(_L, LUA_REGISTRYINDEX, GM_Update_Func);
		lua_rawgeti(_L, -1, 2);
		int count = 0;
		UpdateNode temp;
		for (auto& e : _t)
		{
			pr = e.second;
			if (pr->_IsUpdate == 1)
			{
			/*	lua_rawgeti(_L, LUA_REGISTRYINDEX, pr->_update);*/
				//lua_rawgeti(_L, -1, 2);
				count++;
				/*lua_pushlightuserdata(_L,pr);
				lua_rawseti(_L,-2,count);*/
				temp._entity = pr;
				if (pr->_b_ptr == NULL)
				{	
					
					/*lua_pushnumber(_L,0);*/
					temp._check = NULL;
				
				}
				else
				{
					if (((Collision_Box*)(pr->_b_ptr))->_IsCheck == 0)
					{
						/*lua_pushnumber(_L, 0);*/
						temp._check = NULL;
					}
					else
					{
						void* tem = CollisionCheck(pr);
						if (tem == nullptr)
						{
							/*lua_pushnumber(_L, 0);*/
							temp._check = NULL;
						}
						else
						{
							/*lua_pushlightuserdata(_L, tem);*/
							temp._check = tem;
						}
			
					}

	

				}
				if (pr->_update > 0)
				{
				/*	count++;*/
					/*lua_rawseti(_L, -2, count);*/
					/*lua_pushnumber(_L, pr->_update);*/
					temp._index= pr->_update;
					update_manager.push_back(temp);
					/*count++;
					lua_rawseti(_L, -2, count);*/
					/*int re = lua_pcall(_L, 2, 1, 0);
					if (re != 0)
					{
						const char* err = lua_tostring(_L, -1);
						printf("Lua 错误: %s\n", err);
						lua_pop(_L, 1);
					}*/
				
				}
				
				
				/*code = lua_tonumber(_L, -1);
				lua_pop(_L, 1);
				if (code != 0)
				{
					return code;
				}*/

			}
			
		}
		lua_pushlightuserdata(_L, update_manager.data());
		lua_rawseti(_L, -2,1); 
		lua_pop(_L, 1);
		lua_pushnumber(_L, count);
		lua_rawseti(_L, -2, 5);
		lua_pop(_L, 1);
		lua_rawgeti(_L, LUA_REGISTRYINDEX, GM_Update);
//#ifdef USER_DEBUG
//		_interval = ((double)(SDL_GetPerformanceCounter() - _tem_interval) / _frequency) * 1000;
//		/*_tem_interval = SDL_GetPerformanceCounter();*/
//		printf("interval(ms):%.2f\n", _interval);
//#endif
		int re=lua_pcall(_L, 0, 1,0);
		update_manager.clear();
		if (re != 0)
		{
			const char* err = lua_tostring(_L, -1);
			printf("Lua 错误: %s\n", err);
			lua_pop(_L, 1);
			exit(1);
		}
		code = lua_tonumber(_L, -1);
		lua_pop(_L, 1);
		if (code != 0)
		{
			return code;
		}
		for (auto& e : _camera)
		{
			if (e.second->_IsUpdate == 1)
			{
				if (e.second->_track==track_ref)
				{
					TrackEntityStatus(_L, e.second, (Entity*)(e.second->_pr));
				}
				else
				{
					lua_rawgeti(_L, LUA_REGISTRYINDEX, e.second->_track);
					lua_pushlightuserdata(_L, (e.second));
					if (e.second->_pr != NULL)
					{
						lua_pushlightuserdata(_L, (e.second->_pr));
						lua_pcall(_L, 2, 0, 0);
						Camera* c = e.second;
						Entity* entity = (Entity*)(e.second->_pr);
						c->_last_value.x = entity->_dest.x;
						c->_last_value.y = entity->_dest.y;
						c->_last_value.w = entity->_dest.w;
						c->_last_value.h = entity->_dest.h;
					}
					else
					{
						lua_pushnil(_L);
						lua_pcall(_L, 2, 0, 0);
					}
				
				}
			}
			
		}
		return code;
	}


	void Scene_Manager::SetNextScene(const std::string& data)//设置下一个场景
	{
		auto e = _m.find(data);
		if (e == _m.end())
		{
			std::cerr << "Scene_Manager::SetNextScene,err:该场景不存在" << std::endl;
			assert(0);
		}
		else
		{
			_nscene = &(e->second);
		}
	}

	void Scene_Manager::Render(SDL_Renderer* render)//渲染该场景的所有实体
	{
		if (_nscene == nullptr)
		{
			std::cerr << "Scene_Manager::Render,err:场景指针为空" << std::endl;
			assert(0);
		}
		else
		{
			_nscene->Render(render);
		}
	}

	int Scene_Manager::UpdateData()
	{
		if (_nscene == nullptr)
		{
			std::cerr << "Scene_Manager::Render,err:场景指针为空" << std::endl;
			assert(0);
		}
		else
		{
			return _nscene->UpdateData();
		}
	}

	Camera* Scene_Manager::InsertScene(const std::pair<std::string, Renderer_Task>& sname,int w_lwidth, int w_lheight)//插入新场景
	{
		auto re=_m.insert(sname);
		Renderer_Task* ptr = &(re.first->second);
		const std::string& str = (re.first->first);
		char* p = (char*)Malloc(sizeof(void*) + sizeof(Camera));
		char** spr = (char**)(p);
		size_t size = str.size();
		char* temp_ptr = (char*)Malloc(size + 1);
		*spr = temp_ptr;
		memcpy(*spr, str.c_str(), size);
		(*spr)[size] = '\0';
		Camera* camera = (Camera*)(p + sizeof(void*));
		InitCamera(camera,w_lwidth,w_lheight);
		auto e = ptr->_camera.insert(std::make_pair(camera->_priority, camera));
		c_iterator* pr = (c_iterator*)Malloc(sizeof(c_iterator));
		//SetToCheck(pr);
		memcpy(pr, &e, sizeof(c_iterator));
		camera->_ipr = pr;
		return camera;
		
	}


	void Scene_Manager::EraseScene(const std::string& sname)//删除场景
	{
		auto tem=_m.find(sname);
		if (tem!= _m.end())
		{
			for (auto& e : tem->second._camera)
			{
				Free(e.second->_ipr);
				char* pr = (char*)((char*)e.second);
				Free(pr);
				Free(pr);
			}
			SDL_DestroyTexture(tem->second._stexture);
			_m.erase(tem);
		}
	
	}

	Camera* Scene_Manager::CreateCamera(const std::string& sname,int lwidth,int lheight)
	{
		auto e = _m.find(sname);
		if (e != _m.end())
		{
			char* p = (char*)Malloc(sizeof(void*) + sizeof(Camera));
			char** spr = (char**)p;
			size_t size = sname.size() ;
			*spr = (char*)Malloc(size+1);
			memcpy(*spr, sname.c_str(), size);
			(*spr)[size] = '\0';
			Camera* camera = (Camera*)(p + sizeof(void*));
			InitCamera(camera, lwidth, lheight);
			auto re=(e->second._camera.insert(std::make_pair(camera->_priority,camera)));
			camera->_ipr = Malloc(sizeof(c_iterator));
			memcpy(camera->_ipr, &re, sizeof(c_iterator));
			return camera;
		}
	}

	void Scene_Manager::DeleteCamera(Camera* pr, std::string& sname)
	{
		auto e = _m.find(sname);
		if (e == _m.end())
		{
			std::cerr << "Scene_Manager::DeleteCamera,err:该场景不存在" << std::endl;
			assert(0);
		}
		else
		{
			char* ptr = (char*)((char*)pr - sizeof(void*));
			Free(*((char**)ptr));
			e->second._camera.erase(*((c_iterator*)(pr->_ipr)));
			Free(pr->_ipr);
			Free(ptr);
		}
	}

	void Scene_Manager::InsertEntity(const std::string& sname, void* ptr,int distance)
	{
		Entity* pr = (Entity*)ptr;
		auto e = _m.find(sname);
		if (e == _m.end())
		{
			std::cerr << "Scene_Manager::InsertEntity,err:该场景不存在" << std::endl;
			assert(0);
		}
		else
		{
			auto re = e->second._t.insert(std::make_pair(distance, pr));
			pr->_ipr= Malloc(sizeof(iterator));
			memcpy(pr->_ipr ,&re,sizeof(iterator));
		}
	}

	void Scene_Manager::EraseEntity(const std::string& sname, void* ptr)
	{
		Entity* pr = (Entity*)ptr;
		auto e = _m.find(sname);
		if (e == _m.end())
		{
			std::cerr << "Scene_Manager::EraseEntity,err:该场景不存在" << std::endl;
			assert(0);
		}
		else
		{
			e->second._t.erase(*((iterator*)(pr->_ipr)));

		}

	}




}

