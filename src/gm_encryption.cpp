#include"gm2.h"

#define OFFSET 

namespace gm
{

	// 自定义结构，用于在writer回调中收集字节码数据
	typedef struct 
	{
		char* data;
		size_t len;
	} BytecodeBuffer;


	int my_writer(lua_State* L, const void* p, size_t sz, void* ud) 
	{
		BytecodeBuffer* buf = (BytecodeBuffer*)ud;
		// 为新的数据块重新分配内存
		char* new_data = (char*)realloc(buf->data, buf->len + sz);
		if (!new_data)
		{
			return 1; // 内存分配失败
		}	
		// 拷贝数据块
		memcpy(new_data + buf->len, p, sz);
		buf->data = new_data;
		buf->len += sz;
		return 0; // 成功
	}

	void encryption(const char* spath, const char* dpath, lua_State* L)
	{
		std::vector<std::string>* pr=FGetDirectoryFileName(spath);
		for (auto& e : *pr)
		{
			if (strcmp(GetSuffix(e).c_str(),".lua") == 0)
			{
				if (luaL_loadfile(L, e.c_str()) != LUA_OK) 
				{
					// 处理加载错误...
					std::cout << "加密" << e <<"时发生错误"<< std::endl;
					exit(1);
				}

				BytecodeBuffer buf = { NULL, 0 };
				if (lua_dump(L, my_writer, &buf) != 0) 
				{
					std::cout << "加密" << e << "时发生错误" << std::endl;
					// 处理编译错误...
					exit(1);
				}

				buf.data = (char*)realloc(buf.data, buf.len + 1);
				*(buf.data + buf.len) = 1;
				buf.len += 1;
				std::string tem = e;
				tem.pop_back();
				tem.pop_back();
				tem.pop_back();
				tem += "gm";
				tem.erase(0, strlen(spath));
				std::string tem1 = dpath + tem;
				CreateDirectoryRecursive(tem1.c_str());
				WriteNewFile(tem1.c_str(),buf.data,buf.len);
				free(buf.data);
			}
		}
		delete pr;
	}

	void decryption(std::string& sname, lua_State* L)
	{
		if (run_mode == 0)
		{
			//源码执行
			if (luaL_dofile(L, sname.c_str()) != LUA_OK)
			{
				const char* error_msg = lua_tostring(L, -1);
				printf("执行 Lua 文件出错: %s\n", error_msg);
				lua_pop(L, 1); // 弹出错误信息
				lua_close(L);
				exit(1);
			}
		}
		else 
		{
			//解密执行
			sname.pop_back();
			sname.pop_back();
			sname.pop_back();
			sname += "gm";
			void* buffer = nullptr;
			size_t size = ReadFile(sname.c_str(), &buffer);
			if (luaL_loadbuffer(L, (const char*)buffer, size-1,sname.c_str()) == LUA_OK)
			{
				// 加载成功，函数对象被压入Lua栈顶
				lua_pcall(L, 0, 0, 0); // 执行它
			}
			else
			{
				printf("执行 Lua 文件出错: %s\n", sname.c_str());
				lua_close(L);
				exit(1);
			}
		}
	}
	
}