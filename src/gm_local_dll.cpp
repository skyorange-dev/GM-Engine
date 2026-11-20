#include"gm2.h"

namespace gm
{
	//1.在initmodule中,工作目录中是否存在C文件夹，如果有则将所有.c文件打包成local.dll,
	//2.在lua端用户可选择LoadLocalDll将本地临时生成的dll加载,并调用对应的函数或传给SetCUpdateData,让C在更新函数时在lua层直接调用C函数进行操作

	//简单一点，只要生成的库文件比所有.c，.cpp和.h都新
	void InitUserAPI(lua_State* L)
	{
		GM_API* user_api = (GM_API*)Malloc(sizeof(GM_API));
		user_api->UserMalloc = Malloc;
		user_api->UserFree= Free;
		lua_pushlightuserdata(L,user_api);
		lua_setglobal(L, "user_capi");
	}

	void CreateDll(std::vector<std::string>& list)
	{
		std::string tem1(work_path + "C/");
		std::string tem("./xclang/bin/clang++ -shared -Wl,--export-all-symbols -O2 -o ");
		tem += tem1;
		tem += "local.dll";
		for (auto& e : list)
		{
			tem +=" ";
			tem += tem1+e;
		}
		tem += " ./gm_c/gm.lib";

		tem += " -I ./gm_c";

		int re=BlockExecuteProcess(tem.c_str());
		printf("退出码: %lu\n", re);
		if (re != 0)
		{
			exit(1);
		}
	}

	void LoadLocalDll(lua_State* L, std::string& path)
	{

		std::vector<std::string>* temp = GetDirectoryFileName(path);
		std::vector<std::string> cfile;
		bool is_dec = false;
		for (auto& e : *temp)
		{
			if (strcmp(GetSuffix(e).c_str(), ".c")==0 || strcmp(GetSuffix(e).c_str(), ".cpp")==0)
			{
				cfile.push_back(e);
			}
			else if (strcmp(e.c_str(), "declaration.lua") == 0)
			{
				is_dec = true;
			}
			
		}

		if (cfile.size() != 0)
		{
			std::string libpath(work_path + "C/local.dll");
			FILE* lib = fopen(libpath.c_str(), "r");
			if (lib == NULL)
			{
				CreateDll(cfile);
			}
			else
			{
				fclose(lib);
				for (auto& e : cfile)
				{
					std::string tem(path + e);
					if (IsNewer(libpath.c_str(), tem.c_str()) == false)
					{
						CreateDll(cfile);
						break;
					}
				}
			}
			lua_pushboolean(L, is_dec);
			lua_setglobal(L, "is_dec");
		}
		
		delete temp;
	

	}

	void CheckLocalDll(lua_State* L)
	{
		std::string tem(work_path);
		std::vector<std::string>* temp = GetDirectoryFileName(tem);
		for (auto& e : *temp)
		{
			if (strcmp(e.c_str(), "C") == 0)
			{
				tem = (tem + e + "/");
				LoadLocalDll(L, tem);
				lua_pushboolean(L, true);
				lua_setglobal(L,"ExistLocalDll");
				break;
			}
		}
		InitUserAPI(L);
		delete temp;
	}
}