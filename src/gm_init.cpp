#include"gm2.h"

//gm初始化接口
namespace gm
{
	std::unordered_map<std::string, bool,std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string,bool>>>* plugin_list;

	int GM_Update_Func=0;

	int GM_Update=0;

	void LoadConfig()
	{
		std::vector<std::string>* tem = GetDirectoryFileName("./gm_config/");
		if (tem == nullptr)
		{
			std::cout << "找不到gm_config文件夹" << std::endl;
			delete tem;
			exit(1);
		}
		for (auto& e : *tem)
		{
			if (strcmp(e.c_str(), "config.json") == 0)
			{
				std::ifstream file("./gm_config/config.json");
				if (!file.good())
				{
					std::cout << "config.json文件加载失败" << std::endl;
					exit(1);
				}
				std::stringstream str_stream;
				str_stream << file.rdbuf();
				file.close();
				cJSON* json_root = cJSON_Parse(str_stream.str().c_str());
				cJSON* json_path = cJSON_GetObjectItem(json_root, "work_path");
				if (strlen(json_path->valuestring) != 0)
				{
					work_path = json_path->valuestring;
				}
				delete tem;
				cJSON_Delete(json_root);
				return;
			}
		}
		

	}

	void LoadPluginFile(lua_State* L,std::string& path)
	{

		std::vector<std::string>* temp = GetDirectoryFileName(path);
		for (auto& e : *temp)
		{
			std::string tem(path+e+"/");
			std::ifstream file(tem+"plugin.json");
			if (!file.good())
			{
				std::cout << tem + "plugin.json"<<"文件加载失败" << std::endl;
				delete temp;
				exit(1);
			}
			std::stringstream str;
			str << file.rdbuf();
			file.close();
			cJSON* root = cJSON_Parse(str.str().c_str());
			cJSON* json_path = cJSON_GetObjectItem(root, "plugin_name");
			cJSON* json_author = cJSON_GetObjectItem(root, "author");
			std::string tem_find(std::string(json_path->valuestring)+ "-" + json_author->valuestring);
			if (plugin_list->find(tem_find) == plugin_list->end())
			{
				(*plugin_list)[tem_find] = true;
				cJSON* json_declaration = cJSON_GetObjectItem(root, "declaration");
				if (luaL_dofile(L, std::string(tem + json_declaration->valuestring).c_str()) != LUA_OK)
				{
					const char* error_msg = lua_tostring(L, -1);
					printf("执行 Lua 文件出错: %s\n", error_msg);
					lua_pop(L, 1); // 弹出错误信息
					lua_close(L);
					cJSON_Delete(root);
					delete temp;
					exit(1);
				}
				cJSON* json_dynamiclibrary = cJSON_GetObjectItem(root, "dynamiclibrary");
				if (luaL_dofile(L, std::string(tem+json_dynamiclibrary->valuestring).c_str()) != LUA_OK)
				{
					const char* error_msg = lua_tostring(L, -1);
					printf("执行 Lua 文件出错: %s\n", error_msg);
					lua_pop(L, 1); // 弹出错误信息
					cJSON_Delete(root);
					lua_close(L);
					delete temp;
					exit(1);
				}
				cJSON* json_lua = cJSON_GetObjectItem(root, "lua");
				if (strcmp(GetSuffix(json_lua->valuestring).c_str(), std::string().c_str()) != 0)
				{
					if (luaL_dofile(L, std::string(tem + json_dynamiclibrary->valuestring).c_str()) != LUA_OK)
					{
						const char* error_msg = lua_tostring(L, -1);
						printf("执行 Lua 文件出错: %s\n", error_msg);
						lua_pop(L, 1); // 弹出错误信息
						cJSON_Delete(root);
						lua_close(L);
						delete temp;
						exit(1);
					}
				}
			}
			cJSON_Delete(root);

		}
		delete temp;
	}

	void LoadPlugins(lua_State* L)
	{
		std::string tem(work_path);
		std::vector<std::string>* temp = GetDirectoryFileName(tem);
		for (auto& e : *temp)
		{
			if (strcmp(e.c_str(), "plugin") == 0)
			{
				tem = (tem + e + "/");
				LoadPluginFile(L,tem);
			}
		}
		delete temp;
	}

	void InitLuaTool(lua_State* L)
	{
		std::vector<std::string>* tem = GetDirectoryFileName("./gm_lua/");
		if (tem == nullptr)
		{
			delete tem;
			std::cout << "找不到gm_lua文件夹" << std::endl;
			exit(1);
		}
		std::string temp ;
		for (auto& e : *tem)
		{
			if (strcmp(e.c_str(), "gm_init.lua") == 0 || strcmp(e.c_str(), "gm_init.gm") == 0)
			{
				temp = e;
				continue;
			}
			if (strcmp(GetSuffix(e.c_str()).c_str(), ".lua") == 0)
			{
				if (luaL_dofile(L, ("./gm_lua/" + e).c_str()) != LUA_OK)
				{
					const char* pr = lua_tostring(L, -1);
					printf("执行 Lua 文件出错: %s\n", pr);
					lua_pop(L, 1);
					exit(1);
				}
			}
			else
			{
				run_mode = 1;
				std::string temp(e);
				temp.pop_back();
				temp.pop_back();
				temp += "lua";
				temp = "./gm_lua/" + temp;
				decryption(temp, L);
			}

			
			
		}
		
		if (strcmp(GetSuffix(temp.c_str()).c_str(), ".lua") == 0)
		{
			if (luaL_dofile(L, ("./gm_lua/" + temp).c_str()) != LUA_OK)
			{
				const char* pr = lua_tostring(L, -1);
				printf("执行 Lua 文件出错: %s\n", pr);
				lua_pop(L, 1);
				exit(1);
			}
		}
		else
		{
			run_mode = 1;
			std::string tem(temp);
			tem.pop_back();
			tem.pop_back();
			tem += "lua";
			tem = "./gm_lua/" + tem;
			decryption(tem, L);
		}
		run_mode = 0;
		delete tem;
		

	}

	void InitValuePlugin_List()
	{
		static std::unordered_map<std::string, bool, std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, bool>>> _plugin_list;
		plugin_list = &_plugin_list;
	}

	void InitValue(lua_State* L)
	{
		char buffer[1024];
		GetFullPath(work_path, buffer);
		size_t size = strlen(buffer);
		for (int i = 0; i < size; i++)
		{
			if (buffer[i] == '\\')
			{
				buffer[i] = '/';
			}
		}
		std::string tem(buffer);
		lua_pushstring(L, tem.c_str());
		lua_setglobal(L,"work_path");
		lua_pushnumber(L, SDL_QUIT);
		lua_setglobal(L, "SDL_QUIT");
		lua_pushnumber(L, SDL_WINDOW_HIDDEN);
		lua_setglobal(L, "WINDOW_UNRESIZEABLE");
		lua_pushstring(L, "./gm_sl/gm_sl_");
		lua_setglobal(L, "stl_path");
		lua_newtable(L);
		lua_pushnumber(L, 0);
		lua_rawseti(L, -2, 4);//func_count
		lua_pushnumber(L, 0);
		lua_rawseti(L, -2, 5);//value_count
		lua_newtable(L);
		lua_rawseti(L, -2, 1);
		lua_newtable(L);
		lua_rawseti(L, -2, 2);
		lua_newtable(L);
		lua_rawseti(L, -2, 3);
		lua_setglobal(L,"GM_Update_Func");
		lua_getglobal(L, "GM_Update_Func");
		GM_Update_Func=luaL_ref(L, LUA_REGISTRYINDEX);
		

		
	}
	

	void InitMoudule(lua_State* L)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);//支持.png,.jpg
		Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);//支持mp3,ogg,flac,wav
		TTF_Init();
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); //绕过d3d9.dll崩溃问题

		//设置lua端全局变量
		InitValue(L);
		InitGraphic(L);
		//初始化全局对象
		InitValueResource_Manager();
		InitValuePlugin_List();
		InitValueModuleData();
		InitValueRefData();
		InitValueCollison_Manager();
		//初始化事件变量
		InitEventValue();

		//初始化entity的默认函数
		InitDefaultFunc(L);

		//将C函数与数据加载到lua端
		InitWindow(L);
		InitEncryption(L);
		InitResource_Manager(L);
		InitEntity(L);
		InitEvent(L);
		InitCollision_Box(L);
		InitFFI(L);
		InitModule(L);
		InitCamera(L);
		InitMemory(L);
		
		//检查是否需要加载外部dll
		CheckLocalDll(L);
		//初始化lua组件
		InitLuaTool(L);

		//加载外部插件
		LoadPlugins(L);

		//初始化ref
		InitRef(L);
		

	}
}