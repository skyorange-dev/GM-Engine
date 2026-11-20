#include "gm2.h"

namespace gm
{
	std::vector<cJSON*, STL_Allocator<cJSON*>>* _data;

	void InitValueModuleData()
	{
		static std::vector<cJSON*, STL_Allocator<cJSON*>> data;
		_data = &data;
	}

	Module* LoadModulesFile(lua_State* L, std::string& path)
	{
	
		std::vector<std::string>* temp = GetDirectoryFileName(path);
		int size = temp->size();
		Module* pr = (Module*)Malloc(size*sizeof(Module));
		int count = 0;
		for (auto& e : *temp)
		{
			std::string tem(path + "/" + e + "/");
			std::ifstream file(tem + "module.json");
			if (!file.good())
			{
				std::cout << tem + "module.json" << "文件加载失败" << std::endl;
				delete temp;
				exit(1);
			}
			std::stringstream str;
			str << file.rdbuf();
			file.close();
			cJSON* root = cJSON_Parse(str.str().c_str());
			_data->push_back(root);
			cJSON* json_name = cJSON_GetObjectItem(root, "name");
			cJSON* json_author = cJSON_GetObjectItem(root, "author");
			cJSON* json_description = cJSON_GetObjectItem(root, "description");
			cJSON* json_version = cJSON_GetObjectItem(root, "version");
			cJSON* json_execute = cJSON_GetObjectItem(root, "execute");
			pr[count]._name = json_name->valuestring;
			pr[count]._author = json_author->valuestring;
			pr[count]._description = json_description->valuestring;
			pr[count]._version = json_version->valuestring;
			pr[count]._execute = json_execute->valuestring;
			count++;
		}
		delete temp;
		return pr;
	}

	Module* LoadMoudules(lua_State* L)
	{
		std::string tem(work_path);
		std::vector<std::string>* temp = GetDirectoryFileName(tem);
		Module* pr = nullptr;
		for (auto& e : *temp)
		{
			if (strcmp(e.c_str(), "module") == 0)
			{
				tem = (tem + e+"/");
				pr=LoadModulesFile(L, tem);
			}
		}
		delete temp;
		return pr;
	}

}