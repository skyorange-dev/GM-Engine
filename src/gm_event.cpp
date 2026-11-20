#include"gm2.h"

namespace gm
{
    SDL_Event event;

    Event e;

    void InitEventValue()
    {
        e._mouse_message = -1;
        e._mouse_buttondown = -1;
        e._mouse_wheel = -1;
        e._keyboard_message = -1;//键盘事件
        e._IsRepeated = -1;//是否重复按下
        e._keyboard_down;//键盘按下的键
        e._window_message = -1;//窗口事件
        e._frequency = SDL_GetPerformanceFrequency();
        e._time= ((double)SDL_GetPerformanceCounter() / e._frequency)*1000;
        e._ntime = ((double)SDL_GetPerformanceCounter() / e._frequency) * 1000 * 1000*1000;
    }
  
  

	void UpdateEvent()
	{
		int re=SDL_PollEvent(&event);
        size_t count = SDL_GetPerformanceCounter();
        e._time = ((double)count/ e._frequency)*1000;
        e._ntime = ((double)count/ e._frequency) * 1000 * 1000*1000;
		if (re == 0)
		{
            e._mouse_message = -1;
            e._keyboard_message = -1;
            e._window_message = -1;
			return;
		}
		else
		{
            switch (event.type)
            {
             //鼠标事件
            case SDL_MOUSEMOTION:
                e._mouse_position.x = event.motion.x;
                e._mouse_position.y = event.motion.y;
                e._mouse_message = SDL_MOUSEMOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                e._mouse_position.x = event.button.x;
                e._mouse_position.y = event.button.y;
                e._mouse_buttondown = event.button.button;
                e._mouse_message = SDL_MOUSEBUTTONDOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                e._mouse_position.x = event.button.x;
                e._mouse_position.y = event.button.y;
                e._mouse_message = SDL_MOUSEBUTTONUP;
                break;
            case SDL_MOUSEWHEEL:
                e._mouse_wheel= event.wheel.y;
                e._mouse_message = SDL_MOUSEWHEEL;
             //键盘事件
            case SDL_KEYDOWN:
                e._keyboard_down = event.key.keysym.scancode;
                e._IsRepeated = event.key.repeat;
                e._keyboard_message = SDL_KEYDOWN;
                break;
            case SDL_KEYUP:
                e._keyboard_down = event.key.keysym.scancode;
                e._IsRepeated = -1;
                e._keyboard_message = SDL_KEYUP;
                break;
             //窗口事件
            case SDL_QUIT:
                e._window_message = SDL_QUIT;
                break;
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    e._window_message = SDL_WINDOWEVENT_CLOSE;
                    break;
                default:
                    break;
                }
            }
            default:
                break;
            }
           
		}
	}

}