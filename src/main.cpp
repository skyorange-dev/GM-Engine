//#include"tool.h"
//int main()
//{
//	lua_State* L = luaL_newstate();
//    Used_L = L;
//	luaL_openlibs(L);
//	InitTool(L);
//	SDL_AddEventWatch(MyEventWatcher, NULL);
//	LoadLuaFile(L,".\\lua\\minidayz.lua");
//	ReleaseResource();
//	return 0;
//}

#include"gm2.h"

using namespace gm;

std::string work_path("./");

int run_mode=0;

int main(int args,char* argv[])
{
#ifdef _WIN32
	SetConsole();
#endif
	if (args > 1)
	{
		while (1)
		{
			if (strcmp(argv[1], "-e") == 0)
			{
				Encryption(args, argv);
				break;
			}

			if (strcmp(argv[1], "-cl") == 0)
			{
				CreateLibrary();
				break;
			}


			if (strcmp(argv[1], "-s") == 0)
			{
				AddStartPath(args, argv);
				break;

			}

			if (strcmp(argv[1], "-rs") == 0)
			{
				ResetStartPath(args, argv);
				break;
			}

			if (strcmp(argv[1], "-ap") == 0)
			{
				AddSearchPath(args, argv);
				break;
			}

			if (strcmp(argv[1], "-dp") == 0)
			{
				DeleteSearchPath(args, argv);
				break;
			}

			if (args == 4)
			{
				if (strcmp(argv[3], "-g") == 0)
				{
					GameInPath(args, argv,true);
					break;
				}
			}


			GameInPath(args, argv);
			break;
			
		}
		
	}
	else
	{
		Game();
	}

	
	
	//Window* window = CreateWindow(u8"你好，世界",1280,720);
	//SetFontPath(".");
	//SetImagePath(".");
	//SGL_Texture re0=GetText("ipix.ttf", 32, u8"你好，世界",window->GetRenderer());
	//SGL_Texture re=GetImage("avatar.jpg",window->GetRenderer());
	//SDL_Rect rect_img;
	//SDL_Rect rect_text;
	//Mix_Music* music = (Mix_Music*)GetAudio("music.mp3");
	//Mix_FadeInMusic(music, -1, 1500);
	//rect_img.w = re._width;
	//rect_img.h = re._height;
	//rect_text.w = re0._width;
	//rect_text.h = re0._height;
	//Image tem;
	//rect_img.x = 0;
	//rect_img.y = 0;
	//rect_text.x = 0;
	//rect_text.y = 0;
	//tem._source = rect_img;
	//tem._dest = rect_img;
	//tem._data = re._data;
	//window->InsertScene("测试");
	//window->SetNextScene("测试");
	//window->InsertEntity("测试",&tem);
	////window->InsertEntity("测试");

	//window->DynamicDelay(0);
	//while (1)
	//{
	//	window->UpdateData();

	//	window->RenderClear();
	//	window->Render();

	//	window->DynamicDelay();
	//}


	return 0;
}
