#include "gm2.h"

//namespace gm
//{
	//基于场景的实体存档系统(同时可以考虑作为网络同步的数据来传输只不过不是保存在文件里)
	//grmanager.scene.CreateSave(目标地址(包含文件名),实体对应的C指针，构建函数名，实体数据名称(可选))
	//grmanager.scene.LoadSave(目标地址(包含文件名)，场景表，窗口表,具体字段(可选))(调用这个函数会根据操作函数名试图从场景全局数据表中获取函数对象调用，然后覆盖数据等操作，最后返回操作的实体表，如果已经遍历结束或搜索不到键值返回nil)
	//1.实体相关的函数
	/*
	{
		"create_name",//实体构建函数，构建函数名(包含实体的对象创建，Texture缓存区创建，更新函数设置，碰撞箱绑定，窗口绑定，掩码设置等)
		"track_name",//摄像机跟踪函数
		...
	}
	*/

	//2.实体字段
	/*
	{
		"source"=[],//图像截取的矩形[x,y,w,h]
		"dest"=[],//输出到逻辑窗口的位置和大小[x,y,w,h]
		"rindex"=,//下次渲染的索引
		"IsVisible"=,//是否可见
		"IsUpdate"=,//是否需要更新数据
		"IsWRender"=,//是否是窗口渲染模式
		"IsSDraw"=//当实体为Draw类型时为是否静态渲染
	}
	*/
	 
	//3.碰撞箱数据
	/*
	{
		"mask"=[],//碰撞类型屏蔽
		"maskid"=[],//碰撞子类型屏蔽
		"width"=,
		"height"=,
		"type"=,//实体的碰撞类型
		"typeid"=,//实体子类型id
		"IsCheck"=//是否需要碰撞检测
	}
	*/

	//4.摄像机数据
	/*
	{
		SDL_Rect _cvalue;//摄像机的坐标以及大小
		SDL_Point _coffset;//摄像机偏移量位置
		void* _pr;//绑定的实体
		void* _ipr;//绑定的迭代器
		Track _track;//跟踪方法
		int _priority;//放映画面的优先级
		unsigned char _IsUpdate;//是否需要更新
		unsigned char _IsRender;//是否需要把该摄像机的画面进行渲染
	}
	*/

	//5.实体数据目录(实体数据编号,实体数据编号,碰撞箱数据编号(如果没有则为-1))
	/*
	{
		//地图实体
		"map1"=[[1,1,-1]],
		"map2"=[[1,2，-1]],
		...
		//实体敌人
		"entity"=[[2,3,1]]，
		...
	}
	*/

	//具体结构
	/*
	{
		"func_name"=[],
		"entity_data"=[],
		"cbox_data"=[],
		"camera_data"=[],
		"data_directory"={}
	}
	*/

	//1.保存的是可选的，保存存档在底层只是负责把数据保存进存档，读取存档时则只是把存档文件翻译成Save结构体里的数据
	//2.保存在上层分为保存entity和保存camera,保存entity是把对应的构建函数名和entity的地址传入底层API，保存camera是把对应绑定的实体标识符和camera的地址传进去
	//3.加载在上层是加载entity和加载camera,加载entity会创建新的enity表然后用save中的数据覆盖新创建的表最后把entity表返回给用户
	//同时写入新创建表的指针
	//加载camera会创建新的camera表然后用save中的数据覆盖新创建的表然后绑定对应标识符的entity最后把camera的表返回给用户
//	struct DataNode
//	{
//		char* _key;
//		int _func;
//		int _edata;
//		int _box;
//	};
//
//	struct Save
//	{
//		char** _func_name;
//		Entity* _entity_data;
//		Collision_Box* _cbox_data;
//		Camera* _camera_data;
//		DataNode* _data_directory;
//		size_t _dsize;
//	};
//
//	bool bitset_getvalue(size_t* bitset, size_t index)
//	{
//		size_t index1 = index / 64;
//		size_t index2 = index % 64;
//		if (bitset[index1] & (1 << (64 - index2 - 1)))
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//
//	}
//
//	int InsertCBoxData(ejson::jstream& temp, Entity* entity)
//	{
//		if (entity->_b_ptr != NULL)
//		{
//			Collision_Box* box = entity->_b_ptr;
//			ejson::jvalue root = temp.GetRootValue();
//			ejson::jvalue t = root["cbox_data"];
//			std::string bdata(R"({
//		"mask" = [)");
//
//			//mask
//			int count1 = 0;
//			for (int i = 0; i < 4 * 8 * 8; i++)
//			{
//				if (bitset_getvalue(box->_mask, i))
//				{
//					bdata += i;
//					bdata += ',';
//					count1++;
//				}
//			}
//			if (count1 != 0)
//			{
//				bdata.pop_back();
//			}
//
//			bdata += R"(],"maskid"=[)";
//
//			//maskid
//			int count2 = 0;
//			for (int i = 0; i < 4 * 8 * 8; i++)
//			{
//				if (bitset_getvalue(box->_maskid, i))
//				{
//					bdata += i;
//					bdata += ',';
//					count2++;
//				}
//			}
//			if (count2 != 0)
//			{
//				bdata.pop_back();
//			}
//
//
//			bdata += R"(],"width"=)";
//
//			//width
//			bdata += box->_width;
//
//			bdata += R"(,"height"=)";
//
//			//height
//			bdata += box->_height;
//
//			bdata += R"(,"type"=)";
//
//			//type
//			bdata += box->_type;
//
//			bdata += R"(,"typeid"=)";
//
//			//typeid
//			bdata += box->_typeid;
//
//			bdata += R"(,"IsCheck"=)";
//
//			//IsCheck
//			bdata += box->_IsCheck ? 1 : 0;
//
//			bdata += '}';
//
//			t << ejson::NIPAIR << JSTRING(bdata.c_str());
//
//			return t.GetArraySize();
//		}
//		else
//		{
//			return -1;
//		}
//
//	}
//
//	std::pair<int, int> InsertEData(ejson::jstream& temp, Entity* entity)
//	{
//		ejson::jvalue root = temp.GetRootValue();
//		ejson::jvalue t = root["entity_data"];
//		std::string edata(R"({
//		"source" = [)");
//
//		//source
//		edata += entity->_source.x;
//		edata += ',';
//		edata += entity->_source.y;
//		edata += ',';
//		edata += entity->_source.w;
//		edata += ',';
//		edata += entity->_source.h;
//
//		edata += R"(],"dest"=[)";
//
//		//dest
//		edata += entity->_dest.x;
//		edata += ',';
//		edata += entity->_dest.y;
//		edata += ',';
//		edata += entity->_dest.w;
//		edata += ',';
//		edata += entity->_dest.h;
//
//		edata += R"(],"rindex"=)";
//
//		//rindex
//		edata += entity->_rindex;
//
//		edata += R"(,"IsVisible"=)";
//
//		//IsVisible
//		edata += entity->_IsVisible ? 1 : 0;
//
//		edata += R"(,"IsUpdate"=)";
//
//		//IsUpdate
//		edata += entity->_IsUpdate ? 1 : 0;
//
//		edata += R"(,"IsWRender"=)";
//
//		//IsWRender
//		edata += entity->_IsWRender ? 1 : 0;
//
//		edata += R"(,"IsSDraw"=)";
//
//		//IsSDraw
//		edata += entity->_IsSDraw ? 1 : 0;
//
//		edata += '}';
//
//		t << ejson::NIPAIR << JSTRING(edata.c_str());
//
//		size_t index1 = t.GetArraySize();
//
//		size_t index2 = InsertCBoxData(temp, entity);
//
//		return std::make_pair(index1, index2);
//
//	}
//
//	Save LoadJson(const char* path,const char* dest="entity")
//	{
//		ejson::jstream temp(path);
//		ejson::jvalue root = temp.GetRootValue();
//		ejson::jvalue d = root["data_directory"];
//		size_t size = d.GetObjectSize();
//		Save tem;
//		/*tem._funcname =(char**)Malloc(size*sizeof(char*)) ;*/
//		for (int i = 0; i < size; i++)
//		{
//
//		}
//	}
//
//
//	void CreateJson(const char* path)
//	{
//		ejson::jstream tem(path);
//		tem.Clear();
//		ejson::jvalue root=tem.GetRootValue();
//		root << JSTRING(R"({"create_func"=[],
//		"entity_data"=[],
//		"cbox_data"=[],
//		"data_directory"={"entity"=[]}})");
//	}
//
//	void DeleteEntityData(const char* path, const char* dest)
//	{
//		ejson::jstream temp(path);
//		ejson::jvalue root = temp.GetRootValue();
//		ejson::jvalue d = root["data_directory"];
//		auto ret = d.TryAccess(dest);
//
//		if (ret.first == true)
//		{
//			ret.second << ejson::DEL;
//		}
//
//	}
//
//	void InsertEntityData(const char* path,std::string func_name,Entity* entity,const char* dest="entity")
//	{
//		ejson::jstream temp(path);
//		ejson::jvalue root=temp.GetRootValue();
//		ejson::jvalue t = root["create_func"];
//		t << ejson::NIPAIR << func_name.c_str();
//
//		size_t index1 = t.GetArraySize();
//
//		auto re=InsertEData(temp,entity);
//
//		ejson::jvalue d = root["data_directory"];
//
//		std::string tem("[");
//		tem += index1;
//		tem += ',';
//		tem += re.first;
//		tem += ',';
//		tem += re.second;
//		tem += "]";
//
//		auto ret=d.TryAccess(dest);
//
//		if (ret.first == true)
//		{
//			ret.second << ejson::NIPAIR << JSTRING(tem.c_str());
//		}
//		else
//		{
//			d << NPAIR(dest)<<ejson::EARRAY<<ejson::NIPAIR<<JSTRING(tem.c_str());
//		}
//
//	}
//
//
//}