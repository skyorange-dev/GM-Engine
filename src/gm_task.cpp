#include"gm2.h"

namespace gm
{
	void LoadDebug(lua_State* L, std::string& path)
	{
#ifdef USER_DEBUG
		std::thread pipe(pipe_connect);
		pipe.detach();
#endif
		if (luaL_dofile(L, path.c_str()) != LUA_OK)
		{
			const char* error_msg = lua_tostring(L, -1);
			printf("执行 Lua 文件出错: %s\n", error_msg);
			lua_pop(L, 1); // 弹出错误信息
			lua_close(L);
			exit(1);
		}

	}

	void Game(bool flags,bool is_debug,char* pr)
	{
		lua_State* L = InitMemory();
		luaL_openlibs(L);
		if (flags == true)
		{
			LoadConfig();
		}
		InitMoudule(L);
		if (is_debug == true)
		{
			std::string tem(pr);
			LoadDebug(L,tem);
		}
		bool try_loading = false;
		while (1)
		{
			FILE* file = fopen((work_path + "main.lua").c_str(), "r");
			if (file == NULL)
			{
				file = fopen((work_path + "main.gm").c_str(), "r");
				if (file == NULL)
				{
					if (try_loading == false)
					{
						std::vector<std::string>*  pr=GetDirectoryFileName("./");
						bool isfound = false;
						for (auto& e : *pr)
						{
							if (strcmp(GetSuffix(e,'_').c_str(), "_gm") == 0)
							{
								work_path = "./"+e+"/";
								try_loading = true;
								isfound = true;
								break;
							}
						}
						delete pr;
						if (isfound == true)
						{
							continue;
						}
						
					}
					std::cout << "main文件不存在" << std::endl;
					exit(1);
				}
				run_mode = 1;
			
			}
			fclose(file);
			break;
		}
		
		std::string tem = work_path + "main.lua";
		decryption(tem, L);
		lua_close(L);
		SDL_Quit();
			
	}

	void Encryption(int args, char* argv[])
	{
		lua_State* L = InitMemory();
		if (args == 4)
		{
			//加密
			encryption(argv[2], argv[3], L);
		}
		else
		{
			std::cout << "usage:gm -e spath dpath" << std::endl;
		}
	}

	void AddStartPath(int args, char* argv[])
	{
		lua_State* L = InitMemory();
		if (args == 3)
		{
			if (strcmp(GetSuffix(argv[2],'_').c_str(), "_gm") != 0)
			{
				std::cout << "所执行的文件夹要求以_gm结尾" << std::endl;
				exit(1);
			}
			//设置默认启动游戏文件夹
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
			cJSON* json_string = cJSON_GetObjectItem(json_root, "work_path");
			cJSON* new_path = cJSON_CreateString(argv[2]);
			cJSON_ReplaceItemInObject(json_root, "work_path", new_path);
			if (json_string == nullptr)
			{
				std::cout << "设置默认启动文件夹失败" << std::endl;
				exit(1);
			}
			char* json_str = cJSON_Print(json_root);
			if (json_str == NULL)
			{
				std::cout << "设置默认启动文件夹失败" << std::endl;
				exit(1);
			}
			FILE* f = fopen("./gm_config/config.json", "w");
			if (f == NULL)
			{
				std::cout << "设置默认启动文件夹失败" << std::endl;
				exit(1);
			}
			else
			{
				fputs(json_str, f);
				fclose(f);
			}
			free(json_str);
			cJSON_Delete(json_root);
			delete new_path;
		}
		else
		{
			std::cout << "usage:gm -s start_path" << std::endl;
		}
	}

	void ResetStartPath(int args, char* argv[])
	{
		lua_State* L = InitMemory();
		if (args == 2)
		{
			//重置默认加载文件夹选项
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
			cJSON* json_string = cJSON_GetObjectItem(json_root, "work_path");
			cJSON* new_path = cJSON_CreateString(std::string().c_str());
			cJSON_ReplaceItemInObject(json_root, "work_path", new_path);
			if (json_string == nullptr)
			{
				std::cout << "重置默认加载文件夹选项失败" << std::endl;
				exit(1);
			}
			char* json_str = cJSON_Print(json_root);
			if (json_str == NULL)
			{
				std::cout << "重置默认加载文件夹选项失败" << std::endl;
				exit(1);
			}
			FILE* f = fopen("./gm_config/config.json", "w");
			if (f == NULL)
			{
				std::cout << "重置默认加载文件夹选项失败" << std::endl;
				exit(1);
			}
			else
			{
				fputs(json_str, f);
				fclose(f);
			}
			free(json_str);
			cJSON_Delete(json_root);
			delete new_path;
		}
		else
		{
			std::cout << "usage:gm -rs" << std::endl;
		}
	}

	void AddSearchPath(int args, char* argv[])
	{
		lua_State* L = InitMemory();
		if (args == 3)
		{
			//添加默认搜索路径
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
			cJSON* json_path = cJSON_GetObjectItem(json_root, "search_path");
			cJSON* new_path = cJSON_CreateString(argv[2]);
			cJSON_AddItemToArray(json_path,new_path);
			if (json_path == nullptr)
			{
				std::cout << "添加默认搜索路径失败" << std::endl;
				exit(1);
			}
			char* json_str = cJSON_Print(json_root);
			if (json_str == NULL)
			{
				std::cout << "添加默认搜索路径失败" << std::endl;
				exit(1);
			}
			FILE* f = fopen("./gm_config/config.json", "w");
			if (f == NULL)
			{
				std::cout << "添加默认搜索路径失败" << std::endl;
				exit(1);
			}
			else
			{
				fputs(json_str, f);
				fclose(f);
			}
			free(json_str);
			cJSON_Delete(json_root);
			delete new_path;
		}
		else
		{
			std::cout << "usage:gm -ap start_path" << std::endl;
		}
	}

	void DeleteSearchPath(int args, char* argv[])
	{
		lua_State* L = InitMemory();
		if (args == 3)
		{
			//删除默认搜索路径
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
			cJSON* json_string = cJSON_GetObjectItem(json_root, "search_path");
			cJSON* json_item = nullptr;
			bool isdeleted = false;
			int index = 0;
			cJSON_ArrayForEach(json_item, json_string)
			{
				if (strcmp(json_item->valuestring, argv[2]) == 0)
				{
					isdeleted = true;
					cJSON_DeleteItemFromArray(json_string, index);
					break;
				}
				index++;
			}
			if (isdeleted == false)
			{
				return;
			}
			if (json_string == nullptr)
			{
				std::cout << "删除默认搜索路径失败" << std::endl;
				exit(1);
			}
			char* json_str = cJSON_Print(json_root);
			if (json_str == NULL)
			{
				std::cout << "删除默认搜索路径失败" << std::endl;
				exit(1);
			}
			FILE* f = fopen("./gm_config/config.json", "w");
			if (f == NULL)
			{
				std::cout << "删除默认搜索路径失败" << std::endl;
				exit(1);
			}
			else
			{
				fputs(json_str, f);
				fclose(f);
			}
			free(json_str);
			cJSON_Delete(json_root);
		}
		else
		{
			std::cout << "usage:gm -ap start_path" << std::endl;
		}
	}

	void GameInPath(int args, char* argv[],bool is_debug)
	{
		if (args == 2||is_debug==true)
		{
			//指定执行哪个目录下的游戏文件
			if (strcmp(GetSuffix(argv[1], '/').c_str(), std::string().c_str()) != 0|| strcmp(GetSuffix(argv[1], '\\').c_str(), std::string().c_str()) != 0)
			{
				if (strcmp(GetSuffix(argv[1], '_').c_str(), "_gm") != 0)
				{
					if (strcmp(GetSuffix(argv[1], '.').c_str(), ".gm") == 0)
					{
						std::string tem(argv[1]);
						size_t size = GetSuffix(argv[1], '/').size();
						if (size == 0)
						{
							size = GetSuffix(argv[1], '\\').size();
						}
						for (int i = 0; i < size - 1; i++)
						{
							tem.pop_back();
						}
						work_path = tem;
			
						if (is_debug == true)
						{
							Game(false, is_debug, argv[2]);
						}
						else
						{
							Game(false);
						}

						return;
					}

					if (strcmp(GetSuffix(argv[1], '.').c_str(), ".lua") == 0)
					{
						std::string tem(argv[1]);
						size_t size = GetSuffix(argv[1], '/').size();
						if (size == 0)
						{
							size = GetSuffix(argv[1], '\\').size();
						}
						for (int i = 0; i < size - 1; i++)
						{
							tem.pop_back();
						}
						work_path = tem;
					
						if (is_debug == true)
						{
							Game(false, is_debug, argv[2]);
						}
						else
						{
							Game(false);
						}
						return;
					}
					std::cout << "gm可执行文件要以.lua文件或.gm文件结尾，gm可执行文件夹要求以_gm结尾" << std::endl;
					exit(1);
				}
				else
				{
					std::string tem(argv[1]);		
					if (isDirectory(tem)==false)
					{
						std::cout << "不存在" << argv[1] << "所对应的文件夹" << std::endl;
						exit(1);
					}

					std::ifstream file1(tem + "/main.lua");
					if (file1.good() == true)
					{
						file1.close();
						work_path = tem + "/";
						if (is_debug == true)
						{
							Game(false, is_debug, argv[2]);
						}
						else
						{
							Game(false);
						}
						return;
					}
					file1.close();
					std::ifstream file2(tem + "/main.gm");
					if (file2.good() == true)
					{
						file2.close();
						work_path = tem + "/";
						lua_State* L = InitMemory();
						if (is_debug == true)
						{
							Game(false, is_debug, argv[2]);
						}
						else
						{
							Game(false);
						}
						return;
					}
					else
					{
						file2.close();
						std::cout << argv[1] << "所对应的文件夹" << "不存在main文件" << std::endl;
						exit(1);
					}
				}
			}
			
			
			bool isfound = false;
			std::vector<std::string>* pr = GetDirectoryFileName("./");
			for (auto& e : *pr)
			{
				if (strcmp(e.c_str(), argv[1]) == 0)
				{
					isfound = true;
					work_path = std::string("./") + argv[1]+ std::string("/");
					break;
				}
			}
			if (isfound != true)
			{
				if (GetSuffix(argv[1], '/').size() == 0 && GetSuffix(argv[1], '\\').size() == 0)
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
					cJSON* json_string = cJSON_GetObjectItem(json_root, "search_path");
					cJSON* json_item = nullptr;


					cJSON_ArrayForEach(json_item, json_string)
					{
						std::vector<std::string>* pr = GetDirectoryFileName(json_item->valuestring);
						for (auto& e : *pr)
						{
							if (strcmp(e.c_str(), argv[1]) == 0)
							{
								isfound = true;
								work_path = std::string(json_item->valuestring) + "/" + argv[1]+"/";
								delete pr;
								break;
							}
						}
						if (isfound == true)
						{
							break;
						}

					}
					if (isfound == false)
					{
						std::cout << "找不到对应的路径" << std::endl;
						exit(1);
					}
				}
			}
			lua_State* L = InitMemory();
		
			if (is_debug == true)
			{
				Game(false, is_debug, argv[2]);
			}
			else
			{
				Game(false);
			}
		}
		
	}

	lua_State* InitMemory()
	{
		std::string tem(work_path);
		/*FILE* pr = fopen((tem + "pool.config").c_str(), "r");
		if (pr != NULL)
		{
			int n;
			fscanf(pr, "%d", &n);
			Reserve(n);
			fclose(pr);
		}*/
		
		if (SDL_SetMemoryFunctions(sdl_malloc, sdl_calloc, sdl_realloc, sdl_free) != 0)
		{
			exit(-1);
		}

		//自定义json内存分配器
		json_init();

		lua_State* L = lua_newstate(lua_alloc, NULL);
		return L;
	}

	void CreateLibrary()
	{
		std::string path("./gm_c/");
		std::vector<std::string>* temp = GetDirectoryFileName("./gm_c/");
		std::vector<std::string> cfile;
		for (auto& e : *temp)
		{
			if (strcmp(GetSuffix(e).c_str(), ".c") == 0)
			{
				std::string tem("./xclang/bin/clang++ --target=x86_64-w64-mingw32 -c -O2 -o ");
				std::string tem1(e);
				tem1.pop_back();
				tem1.push_back('o');
				tem += path;
				tem += tem1;
				tem += " ";
				tem += path;
				tem += e;
				int re = BlockExecuteProcess(tem.c_str());
				if (re != 0)
				{
					printf("程序在编译目标文件时发生错误,进程退出码为%lu", re);
					exit(1);
				}
				cfile.push_back(tem1);
			}
			if (strcmp(GetSuffix(e).c_str(), ".cpp") == 0)
			{
				std::string tem("./xclang/bin/clang++ --target=x86_64-w64-mingw32 -c -O2 -o ");
				std::string tem1(e);
				tem1.pop_back();
				tem1.pop_back();
				tem1.pop_back();
				tem1.push_back('o');
				tem += path;
				tem += tem1;
				tem += " ";
				tem += path;
				tem += e;
				int re = BlockExecuteProcess(tem.c_str());
				if (re != 0)
				{
					printf("程序在编译目标文件时发生错误,进程退出码为%lu", re);
					exit(1);
				}
				cfile.push_back(tem1);
			}

		}

		std::string tem("./xclang/bin/llvm-ar rcs ");
		tem += path;
		tem += "gm.lib";
		for (auto& e : cfile)
		{
			tem += " ";
			tem += path;
			tem +=  e;
		}

		int re = BlockExecuteProcess(tem.c_str());
		delete temp;
		if (re != 0)
		{
			printf("程序在打包目标文件时发生错误,进程退出码为%lu", re);
			exit(1);
		}
		else
		{
			for(auto& e:cfile)
			{ 
				deletefile((path+e).c_str());
			}
		}

	}



}