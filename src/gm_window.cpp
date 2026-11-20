#pragma once
#include"gm2.h"

namespace gm
{
	void Window::UpdateViewport()
	{
		if (_IsLinear == true)
		{
			int windowW, windowH;
			SDL_GetWindowSize(_pr, &windowW, &windowH);
			if (windowW == 0 || windowH == 0) return;

			SDL_RenderSetLogicalSize(_render, _lwidth, _lheight);
		}
		else
		{
			int windowW, windowH;
			SDL_GetWindowSize(_pr, &windowW, &windowH);
			if (windowW == 0 || windowH == 0) return;

			// 计算整数倍缩放
			int scaleX = windowW / _lwidth;
			int scaleY = windowH / _lheight;
			int scale = (scaleX < scaleY) ? scaleX : scaleY;
			if (scale < 1) scale = 1;  // 至少 1 倍

			// 计算缩放后的渲染区域
			int renderW = _lwidth * scale;
			int renderH = _lheight * scale;

			// 居中显示，留黑边
			SDL_Rect viewport;
			viewport.w = renderW;
			viewport.h = renderH;
			viewport.x = (windowW - renderW) / 2;
			viewport.y = (windowH - renderH) / 2;

			// 设置视口
			SDL_RenderSetViewport(_render, &viewport);
		}
		

	}

	Window::Window(lua_State* L,const char* title, int lwidth, int lheight, Uint32 flags1,Uint32 flags2,bool flags3)
	{
		_L = L;
		_IsLinear = flags3;
		if (flags3 == true)
		{
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"); // 1 = 线性过滤
		}
		if (flags2 == -1)
		{
			_pr = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, lwidth, lheight, SDL_WINDOW_HIDDEN);
		}
		else
		{
			_pr = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, lwidth, lheight, flags2| SDL_WINDOW_HIDDEN);
		}
		_lwidth = lwidth;
		_lheight = lheight;
		_nwidth = lwidth;
		_nheight = lheight;
		_render = SDL_CreateRenderer(_pr, -1, flags1);
		_frequency = SDL_GetPerformanceFrequency();
		SDL_SetRenderDrawBlendMode(_render, (SDL_BlendMode)1);
		SetMaxFps();
	}

	void Window::CheckWindow()
	{
		int windowW, windowH;
		SDL_GetWindowSize(_pr, &windowW, &windowH);
		if (windowW != _nwidth|| windowH != _nheight)
		{
			UpdateViewport();
		}
	}


	void Window::FullScreen()
	{
		SDL_SetWindowFullscreen(_pr, SDL_WINDOW_FULLSCREEN_DESKTOP);
		UpdateViewport();
	}

	void Window::WindowScreen()
	{
		SDL_SetWindowFullscreen(_pr, 0);
		UpdateViewport();
	}

	void Window::ShowWindow()
	{
		SDL_ShowWindow(_pr);
	}

	void Window::SetNextScene(const std::string& data)
	{
		_m.SetNextScene(data);
	}
#ifdef USER_DEBUG
	double u_interval = 0;
	size_t u_tem_interval = 0;
#endif

	int Window::UpdateData()
	{
#ifdef USER_DEBUG
		u_tem_interval = SDL_GetPerformanceCounter();
#endif
		int re= _m.UpdateData();
#ifdef USER_DEBUG
		u_interval = ((double)(SDL_GetPerformanceCounter() - u_tem_interval) / _frequency) * 1000;
#endif
		return re;
	}

#ifdef USER_DEBUG
	double r_interval = 0;
	size_t r_tem_interval = 0;
#endif
	void Window::Render()
	{
		
#ifdef USER_DEBUG
		r_tem_interval = SDL_GetPerformanceCounter();
#endif
		_m.Render(_render);//渲染实体;
		SDL_RenderPresent(_render);
#ifdef USER_DEBUG
		r_interval = ((double)(SDL_GetPerformanceCounter() - r_tem_interval) / _frequency) * 1000;
#endif
	}

	void Window::SetMaxFps(int fps)//设置最大帧数
	{
		_max_fps = fps;
	}

#ifdef USER_DEBUG
	double interval =0;
	size_t tem_interval=0;
#endif

	void Window::DynamicDelay(int n)
	{
		//当参数为0代表只是更新一下计数器
		if (n == 0)
		{
			_last_counter = SDL_GetPerformanceCounter();
#ifdef USER_DEBUG
			tem_interval = SDL_GetPerformanceCounter();
#endif
		}
		else
		{
			size_t now_counter = SDL_GetPerformanceCounter();
			size_t delta = ((double)(now_counter - _last_counter) / _frequency) * 1000;
			if (delta  < 1000 / _max_fps)
			{
				SDL_Delay(1000 / _max_fps - delta);
			}
			_last_counter = SDL_GetPerformanceCounter();
			
#ifdef USER_DEBUG
			interval = ((double)(now_counter - tem_interval) / _frequency) * 1000;
			tem_interval = SDL_GetPerformanceCounter();
#endif
		}
	}

#ifdef USER_DEBUG
	double GetInterval()
	{
		return interval;
	}
	double GetUInterval()
	{
		return u_interval;
	}
	double GetRInterval()
	{
		return r_interval;
	}
#endif


	void Window::RenderClear()
	{
		SDL_SetRenderDrawColor(_render, 0,0,0, 255);//清空屏幕
		SDL_RenderClear(_render);
	}
	void routinue(char* pr)
	{
		while (1)
		{
			std::cout << pr << std::endl;
			SDL_Delay(1000);
		}
	}
	Camera* Window::InsertScene(const std::string& sname,int scene_width,int scene_height)
	{
		
		Renderer_Task tem;
		tem._scene_width = scene_width;
		tem._scene_height = scene_height;
		tem._stexture= SDL_CreateTexture(
			_render,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,  // 关键：声明为渲染目标
			scene_width, scene_height
		);
		std::string temp(sname);
		tem._L = _L;
		return _m.InsertScene(std::make_pair(temp,tem),_lwidth,_lheight);
	}

	Camera* Window::CreateCamera(const std::string& sname, int lwidth, int lheight)
	{
		return _m.CreateCamera(sname,lwidth,lheight);
	}

	void Window::DeleteCamera(Camera* pr)
	{
		std::string sname(*((char**)((char*)pr -sizeof(void*))));
		_m.DeleteCamera(pr, sname);
	}

	void Window::EraseScene(const std::string& sname)
	{
		_m.EraseScene(sname);

	}

	void Window::InsertEntity(const std::string& sname, Entity* pr,int distance)
	{
		char** ptr = (char**)((char*)pr - sizeof(void*));
		size_t size = sname.size();
		*ptr = (char*)Malloc(size+ 1);
		memcpy(*ptr, sname.c_str(), size);
		(*ptr)[size] = '\0';
		_m.InsertEntity(sname, pr,distance);
	}

	void Window::EraseEntity(Entity* pr)
	{
		std::string sname(*((char**)((char*)pr - sizeof(void*))));
		_m.EraseEntity(sname, pr);
	}

	SDL_Renderer* Window::GetRenderer()
	{
		return _render;
	}

	Window::~Window()
	{
		Free(_pr);
	}

	Window* CreateWindow(lua_State* L,const char* title, int lwidth, int lheight, Uint32 flags1,Uint32 flags2,bool flags3)
	{
		Window* pr = (Window*)Malloc(sizeof(Window));
		new (pr) Window(L,title, lwidth, lheight, flags1,flags2,flags3);
		return pr;
	}
}
