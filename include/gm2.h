#pragma once
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<SDL2_gfxPrimitives.h>
#include <gperftools/tcmalloc.h>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cJSON.h>
#include<vector>
#include<unordered_map>
#include<map>
#include <stdlib.h>
#include<math.h>
#include<assert.h>
#include<stack>
#include<cstdio>
#include<direct.h>
#include<unordered_set>
#include<queue>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>
#include<algorithm>
#include<set>
#include<cstring>
#include<thread>
#include <mutex>
#include <atomic>
#include "json.hpp"
#pragma warning(disable : 4996)

extern "C"
{
#include <lua.h> 
#include "lualib.h"
#include "lauxlib.h"
}

//#define POOL_DEBUG

#define USER_DEBUG

extern std::string work_path;//工作目录

extern int run_mode;//运行方式

namespace gm
{
	class Resource_Manager;

	extern 	Resource_Manager* _rm;//资源管理器

	extern int render_ref;//默认渲染函数

	extern int track_ref;//默认相机跟踪函数标识符

	struct Entity;

	union GM_Ptr
	{
		Entity* _lua_ptr;
		intptr_t _c_ptr;
	};
}


//camera
namespace gm
{
	struct Entity;

	typedef int Track;

	struct Camera
	{
		SDL_Rect _last_value;//实体的上一次更新所记录的值
		SDL_Rect _last_cvalue;//摄像机的上一次更新所记录的值
		SDL_Rect _cvalue;//摄像机的坐标以及大小
		SDL_Point _coffset;//摄像机偏移量位置
		void* _pr;//绑定的实体
		void* _ipr;//绑定的迭代器
		Track _track;//跟踪方法
		int _priority;//放映画面的优先级
		unsigned char _IsUpdate;//是否需要更新
		unsigned char _IsRender;//是否需要把该摄像机的画面进行渲染
	};

	void DefaultTrack(Camera* c, Entity* pr);

	void SetDynamicCamera(lua_State* L, Camera* c, Entity* pr);

	void TrackEntityStatus(lua_State* L, Camera* c, Entity* pr);

	void SetTrack(void* pr, lua_State* L, const char* str);

	void InitCamera(lua_State* L);

	void InitCamera(Camera* c, int window_lwidth, int window_lheight);//初始化

}

//default_func
namespace gm
{
	void InitRef(lua_State* L);

	void InitDefaultFunc(lua_State* L);
}

//ffi
namespace gm
{
	std::string DeleteStrBlank(const char* str);

	void InitFFI(lua_State* L);
}

//encryption
namespace gm
{
	void encryption(const char* spath, const char* dpath, lua_State* L);//生成加密文件

	void decryption(std::string& sname, lua_State* L);//根据run_mode的值做出不同行为:1.如果是0,则源码执行2.如果是非0，则解密执行

	void InitEncryption(lua_State* L);
}

//graphic
namespace gm
{
	void InitGraphic(lua_State* L);
}

//event
namespace gm
{
	struct Event
	{
		//鼠标信息
		SDL_Point _mouse_position;//鼠标位置
		Uint32 _mouse_message ;//鼠标事件
		Uint8 _mouse_buttondown ;//鼠标被按下的键
		Sint32 _mouse_wheel;//鼠标滚轮滚动
		//键盘信息
		Uint32 _keyboard_message ;//键盘事件
		Uint8 _IsRepeated;//是否重复按下
		SDL_Scancode _keyboard_down;//键盘按下的键

		//窗口信息
		Uint32 _window_message;//窗口事件

		//时间
		size_t _frequency;
		size_t _time;
		size_t _ntime;

	};

	extern Event e;

	void UpdateEvent();

	void InitEventValue();

	void InitEvent(lua_State* L);
}

//默认内存管理函数
namespace gm
{
#ifdef POOL_DEBUG
	void SetToCheck(void* pr);
#endif
	void* Malloc(size_t num);

	void Free(void* ptr);

	//void* UserMalloc(size_t num);//提供给用户用来引擎用来申请内存的接口

	//void UserFree(void* ptr);//提供给用户用来引擎用来释放内存的接口

	void* SDLMalloc(size_t num);

	void SDLFree(void* ptr);

	//void Reserve(double num, double judge1=0.75, size_t judge2=1000);

	size_t GetMemoryUsed();

	void* lua_alloc(void* ud, void* ptr, size_t osize, size_t nsize);

	void json_init();

	void* sdl_malloc(size_t size);

	void* sdl_calloc(size_t nmemb, size_t size);

	void* sdl_realloc(void* ptr, size_t size);

	void sdl_free(void* ptr);

	void InitMemory(lua_State* L);

	//接入STL容器的分配器
	template<class T>
	struct STL_Allocator
	{
		using value_type = T;


		STL_Allocator() = default;


		STL_Allocator(const STL_Allocator<T>&) noexcept {}


		template<typename U>
		STL_Allocator(const STL_Allocator<U>&) noexcept {}


		template<typename U>
		struct rebind {
			using other = STL_Allocator<U>;
		};


		T* allocate(std::size_t n) {
			return (T*)Malloc(n * sizeof(T));
		}


		void deallocate(T* ptr, std::size_t n) noexcept {
			Free(ptr);
		}
	};

//#ifdef USER_DEBUG
//	size_t GetPoolCapacity();
//#endif

}

namespace gm
{
	typedef int	(*lua_func)(lua_State* L);

	extern std::vector<cJSON*, STL_Allocator<cJSON*>>* _data;//模组数据

	extern std::unordered_map<std::string, int, std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, int>>>* _ref_data;

}

//module
namespace gm
{
	struct Module
	{
		const char* _name;
		const char* _author;
		const char* _description;
		const char* _version;
		const char* _execute;
	};

	Module* LoadMoudules(lua_State* L);

	void InitModule(lua_State* L);

	void InitValueModuleData();
}

//collision_box
namespace gm
{
	struct Entity;

	struct Renderer_Task;

	//返回对应C端指针然后查表即可
	struct Collision_Box
	{
		size_t _mask[4];//碰撞类型屏蔽
		size_t _maskid[4];//碰撞子类型屏蔽
		void* _ptr;//刚性碰撞箱的缓冲区
		int _width;
		int _height;
		unsigned char _typeid;//实体子类型id
		unsigned char _cap;//刚性碰撞箱缓冲区大小
		unsigned char _type;//实体的碰撞类型
		unsigned char _IsCheck;//是否需要碰撞检测
		unsigned char _IsRigidity;//是否为刚性碰撞箱
	};

	Collision_Box* NewCollision_Box(int width,int height,int type,int _typeid,int buffer_size,bool IsRigidity);

	void DeleteCollision_Box(Collision_Box* pr);

	void InitCollision_Box(lua_State* L);

	void InitValueCollison_Manager();

	void Insert(Entity* ptr);

	void Erase(Entity* ptr);

	Entity* CollisionCheck(Entity* pr);

}

//enitity
namespace gm
{
	//用C的方式:定义实体抽象类，等用户具体实现重写Render等方法，又或者使用库自带实现的重写了Render等方法的各种类

	struct Entity;

	typedef std::multimap<int, Entity*, std::greater<int>, STL_Allocator<std::pair<int, Entity*>>>::iterator iterator;

	typedef std::multimap<int, Camera*, std::greater<int>, STL_Allocator<std::pair<int, Camera*>>>::iterator c_iterator;

	/*typedef  void (*Render)(void* pr,SDL_Renderer* render);

	typedef  int (*Update)(void* pr);*/

	typedef  int Render;

	typedef  int Update;

	//用C的方式实现继承与多态，每个具体的实体都要有以下字段
	struct Entity
	{
		SDL_Rect _source;//图像截取的矩形
		SDL_Rect _dest;//输出到逻辑窗口的位置和大小
		SDL_Texture** _data;
		unsigned short _rindex;//下次渲染的索引
		unsigned char _IsVisible;//是否可见
		unsigned char _IsUpdate;//是否需要更新数据
		unsigned char _IsWRender;//是否是窗口渲染模式
		unsigned char _IsSDraw;//当实体为Draw类型时为是否静态渲染
		////////////////////////////////////////////////
		void* _ipr;//绑定的迭代器
		Collision_Box* _b_ptr;//与哪个碰撞箱绑定
		Render _render; //执行该实体的渲染逻辑
		Update _update;//执行该实体的数据更新逻辑
		unsigned char _type;//实体类型
	};
	
	void SetRender(void* pr, lua_State* L, const char* str);//设置Render方法

	void SetCRender(void* pr, lua_func func, const char* str);

	void SetUpdateData(void* pr, lua_State* L, const char* str);//设置UpdateData方法

	void SetCUpdateData(void* pr, lua_func func, const char* str);

	void* NewEntity(lua_State* L, int num);//创建实体

	void DeleteEntity(Entity* pr);//删除实体	

	void DeleteDEntity(Entity* pr, int count);
	
	void InitEntity(lua_State* L);

	void InitValueRefData();

	void RenderTexture(lua_State* L, SDL_Texture* tex, SDL_Renderer* render);

#ifdef USER_DEBUG
	extern size_t entity_count;
#endif
	
}

//scene_manager
namespace gm
{
	struct UpdateNode
	{
		void* _entity;
		void* _check;
		size_t _index;
	};

	class Scene_Manager;

	struct Renderer_Task
	{
		void Render(SDL_Renderer* render);

		int UpdateData();

		std::multimap<int, Entity*, std::greater<int>, STL_Allocator<std::pair<int, Entity*>>> _t;
		std::multimap<int, Camera*, std::greater<int>, STL_Allocator<std::pair<int, Camera*>>> _camera;
		SDL_Texture* _stexture;
		lua_State* _L;
		int _scene_width;
		int _scene_height;
	};

	class Scene_Manager
	{
	public:
		friend Entity* EntityCollisionCheck(Entity* pr, Renderer_Task* rt_ptr);
	public:

		void SetNextScene(const std::string& data);

		void Render(SDL_Renderer* render);

		Camera* CreateCamera(const std::string& sname, int lwidth, int lheight);

		int UpdateData();

		Camera* InsertScene(const std::pair<std::string, Renderer_Task>& sname,int w_lwidth, int w_lheight);

		void EraseScene(const std::string& sname);

		void InsertEntity(const std::string& sname, void* ptr, int distance);

		void EraseEntity(const std::string& sname, void* ptr);

		void DeleteCamera(Camera* pr, std::string& sname);

	private:
		std::unordered_map<std::string, Renderer_Task,std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair< std::string, Renderer_Task>>> _m;
		Renderer_Task* _nscene = nullptr;
	};

}

//local_dll
namespace gm
{
	//GM提供给外部dll所能使用的接口
	struct GM_API
	{
		void* (*UserMalloc)(size_t num);
		void (*UserFree)(void* ptr);
	};

	void CheckLocalDll(lua_State* L);
}
//os
namespace gm
{

#ifdef _WIN32

	void SetConsole();//让windows控制台正确处理lua端字符的函数

	std::vector<std::string>* GetDirectoryFileName(std::string path);//获得对应文件夹的所有文件名

	std::vector<std::string>* FGetDirectoryFileName(std::string path);//递归式获得对应文件夹的所有文件名(不包含文件夹)

	void WriteNewFile(const char* name, void* buffer, size_t size);//创建新文件，并写入

	size_t ReadFile(const char* name, void** buf);//读取文件

	void CreateDirectoryRecursive(const std::string& fullPath);	//逐级创建目录

	void pipe_connect();

	bool isDirectory(const std::string& path);

	void GetFullPath(std::string& sname, char* buffer);

	bool IsNewer(const char* file1, const char* file2);

	int BlockExecuteProcess(const char* path);

	void deletefile(const char* path);
#endif

}

//resource_manager
namespace gm
{
	struct GM_Texture
	{
		SDL_Texture* _data=nullptr;
		int _width;
		int _height;
	};

	struct TTexture_Node
	{
		SDL_Renderer* _render;//对应的render指针
		lua_State* _L;//对应的lua栈
		SDL_Texture* _data;//纹理指针
		int _width;//所创建的纹理宽度
		int _height;//所创建的纹理高度
		int _func;//创建纹理的方法
	};

	const std::string GetSuffix(const std::string& source, char symbol = '.');

	const std::string GetFileName(const std::string& source);

	void SetImagePath(const std::string& path);//设置图片资源所在目录

	void SetAudioPath(const std::string& path);//设置音频资源所在目录

	void SetFontPath(const std::string& path);//设置字体资源所在目录

	GM_Texture GetImage(const std::string& str, SDL_Renderer* render);//获取对应图像的纹理

	void* GetAudio(const std::string& str,int flag);//获取对应音频数据的地址，根据需要自行强制类型转换

	GM_Texture GetText(const std::string& str, int size, const std::string& data, SDL_Renderer* render);//获取对应文本的纹理

	void DeleteImage(const std::string& str);//删除对应图像的纹理

	void DeleteAudio(const std::string& str);//删除对应音频数据

	void DeleteText(const std::string& str, int size, const std::string& data);//删除对应文本的纹理

	void InitValueResource_Manager();//创建资源管理器

	void InitResource_Manager(lua_State* L);

	void NewTextureNode(const char* name, TTexture_Node tem);

	void DeleteTexture(const char* name);

	TTexture_Node* FindTexture(const char* name);
	

#ifdef USER_DEBUG
	extern size_t image_count;
	extern size_t text_count;
	extern size_t audio_count;
#endif

}

//window
namespace gm
{
	extern size_t time;

	class Window
	{
	private:
		void UpdateViewport();
		
		void CheckWindow();
	public:
		Window(lua_State* L, const char* title, int lwidth, int lheight, Uint32 flags1, Uint32 flags2, bool flags3);

		void FullScreen();//全屏

		void WindowScreen();//窗口化

		void ShowWindow();//显示窗口
		
		void SetNextScene(const std::string& data);//设置下一个场景

		int UpdateData();//更新实体数据

		void Render();//渲染实体

		void DynamicDelay(int n = 1);//动态延时

		void RenderClear();//清空画面

		void SetMaxFps(int fps=60);//设置最大帧数

		Camera* CreateCamera(const std::string& sname, int lwidth, int lheight);//给场景额外创建摄像机

		void DeleteCamera(Camera* pr);

		Camera* InsertScene(const std::string& sname, int scene_width, int scene_height);//创建新场景

		void EraseScene(const std::string& data);//删除场景

		void InsertEntity(const std::string& data, Entity* pr,int distance);//往场景里插入实体指针

		void EraseEntity(Entity* pr);

		SDL_Renderer* GetRenderer();//获取渲染器

		~Window();
		
	private:
		Scene_Manager _m;
		lua_State* _L;
		SDL_Window* _pr;
		SDL_Renderer* _render;
		size_t _last_counter;
		size_t _frequency;
		int _lwidth;//逻辑宽度
		int _lheight;//逻辑高度
		int _nwidth;//实际宽度
		int _nheight;//实际高度
		int  _max_fps;//最大帧数
		bool _IsLinear;
	};

	Window* CreateWindow(lua_State* L,const char* title, int lwidth, int lheight, Uint32 flags1,Uint32 flags2 , bool flags3);//创建一个窗口，参数为逻辑分辨率的宽与高，始终保持宽高比渲染
	
	void InitWindow(lua_State* L);


#ifdef USER_DEBUG
	double GetInterval();

	double GetUInterval();

	double GetRInterval();

#endif
}



//gm初始化接口
namespace gm
{
	void LoadConfig();

	void InitMoudule(lua_State* L);

	extern int GM_Update_Func;

	extern int GM_Update;
	
}

//gm根据不同的命令行参数执行不同任务
namespace gm
{
	lua_State* InitMemory();//初始化内存分配器

	void Game(bool flags=true, bool is_debug=false, char* pr=nullptr);//运行游戏

	void Encryption(int args, char* argv[]);//加密代码

	void AddStartPath(int args, char* argv[]);//添加默认加载游戏文件夹

	void ResetStartPath(int args, char* argv[]);//重置默认加载文件夹选项

	void AddSearchPath(int args, char* argv[]);//添加默认搜索路径

	void DeleteSearchPath(int args, char* argv[]);//删除默认搜索路径

	void GameInPath(int args, char* argv[], bool is_debug = false);//指定游戏文件夹运行游戏

	void CreateLibrary();//构建静态库

}
