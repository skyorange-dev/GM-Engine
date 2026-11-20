#pragma once
#include "gm2.h"

namespace gm
{
#ifdef USER_DEBUG
	size_t image_count = 0;
	size_t text_count = 0;
	size_t audio_count=0;
#endif
	const std::string GetSuffix(const std::string& source,char symbol)
	{
		size_t length=source.find_last_of(symbol);
		if (length == std::string::npos)
		{
			return std::string();
		}
		else
		{
			std::string tem = source.substr(length);
			return tem;
		}
		
	}

	const std::string GetFileName(const std::string& source)
	{
		size_t length = source.find_last_of('/');
		if (length == std::string::npos)
		{
			size_t length = source.find_last_of('\\');
			if (length == std::string::npos)
			{
				return std::string();
			}
			else
			{
				return source.substr(length+1);
			}
		
		}
		else
		{
			return source.substr(length+1);
		}
	}

	//图集
	class Atlas
	{
	public:
		void SetPath(const std::string& path)
		{
			_path = path;
			InitData();
		}

		void InitData()
		{
			std::vector<std::string>* pr = GetDirectoryFileName(_path);
			if (_path.size() == 0)
			{
				std::cerr << "Atlas::InitData,err:未设置图集路径" << std::endl;
				assert(0);
			}

			for (auto& e : *pr)
			{
				if (strcmp(GetSuffix(e).c_str(), ".png")==0|| strcmp(GetSuffix(e).c_str(), ".jpg") == 0)
				{
					_d.insert(make_pair(e, std::make_pair(GM_Texture(),0)));
				}
				
			}
			delete pr;

		}

		GM_Texture DynamicLoad(const std::string& str,SDL_Renderer* render)//需要时进行加载对应资源
		{
			GM_Texture tem;
			SDL_Surface* p = IMG_Load((_path + str).c_str());
			tem._height = p->h;
			tem._width = p->w;
			SDL_Texture* pr = SDL_CreateTextureFromSurface(render, p);
			SDL_FreeSurface(p);
			tem._data = pr;
			return tem;
		}

		GM_Texture Find(const std::string& str, SDL_Renderer* render)//查找资源，如果没有则动态加载
		{
			auto e = _d.find(str);
			if (e == _d.end())
			{
				return GM_Texture();
			}
			else
			{
				if (e->second.first._data == nullptr)
				{
					e->second.first = DynamicLoad(str,render);
#ifdef USER_DEBUG
					image_count++;
#endif
				}
				
				e->second.second++;
				
				return e->second.first;
			}
		}

		void ReleaseTexture(const std::string& str)//释放资源
		{
			auto e = _d.find(str);
			if (e == _d.end())
			{
				return;
			}
			else
			{
				if (e->second.first._data != nullptr)
				{
					e->second.second--;
					if (e->second.second == 0)
					{
						SDL_DestroyTexture(e->second.first._data);
						e->second.first._data = nullptr;
					}

					
#ifdef USER_DEBUG
					image_count--;
#endif
				}
				
			}

		}

		~Atlas()
		{
			for (auto e : _d)
			{
				if (e.second.first._data != nullptr)
				{
					e.second.second = 0;
					SDL_DestroyTexture(e.second.first._data);
				}
#ifdef USER_DEBUG
				image_count = 0;
#endif
			}

		}
	private:
		std::string _path;
	private:
		std::unordered_map<std::string, std::pair<GM_Texture,size_t>,std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, std::pair<GM_Texture,size_t>>>> _d;
	};

	//音频资源管理器
	class Audio_Manager
	{
	public:
		void SetPath(const std::string& path)
		{
			_path = path ;
			InitData();
		}

		void InitData()
		{
			std::vector<std::string>* pr = GetDirectoryFileName(_path);
			if (_path.size() == 0)
			{
				std::cerr << "Audio_Manager::InitData,err:未设置音频资源管理器路径" << std::endl;
				assert(0);
			}

			for (auto& e : *pr)
			{
				if (strcmp(GetSuffix(e).c_str(),".wav")==0|| strcmp(GetSuffix(e).c_str(), ".mp3")==0|| strcmp(GetSuffix(e).c_str(), ".ogg") == 0 || strcmp(GetSuffix(e).c_str(), ".flac"))
				{
					_m.insert(std::make_pair(e,std::make_pair(std::make_pair(nullptr,0),std::make_pair(nullptr,0))));
				}
				
			}
			delete pr;

		}

		Mix_Chunk* DynamicLoadChunk(const std::string& str)//需要时进行加载对应资源
		{
			Mix_Chunk* music = Mix_LoadWAV((_path+str).c_str());
			return music;
		}

		Mix_Music* DynamicLoadMusic(const std::string& str)//需要时进行加载对应资源
		{

			Mix_Music* music = Mix_LoadMUS((_path+str).c_str());
			return music;
		}

		void* Find(const std::string& str,int flag)//查找资源，如果没有则动态加载
		{
			auto e = _m.find(str);
			if (e == _m.end())
			{
				return nullptr;
			}
			else
			{
				if (flag == 0)//音效
				{
					if (e->second.first.first == nullptr)
					{
						e->second.first.first = DynamicLoadChunk(str);
					
#ifdef USER_DEBUG
						audio_count++;
#endif

					}
					e->second.first.second++;
					return e->second.first.first;
				}
				else
				{
					if (e->second.second.first == nullptr)
					{
						e->second.second.first= DynamicLoadMusic(str);
						
#ifdef USER_DEBUG
						audio_count++;
#endif
					}
					e->second.second.second++;
					return e->second.second.first;
				}


			}
	
		}

		void ReleaseAudio(const std::string& str)//释放资源
		{
				auto e = _m.find(str);
				if (e == _m.end())
				{
					return;
				}
				else
				{
					if (e->second.first.first != nullptr) 
					{
						e->second.first.second--;
						if (e->second.first.second == 0)
						{
							Mix_FreeChunk(e->second.first.first);
							e->second.first.first = nullptr;
						}
						
						
#ifdef USER_DEBUG
						audio_count--;
#endif
					}

					if (e->second.second.first != nullptr)
					{
						e->second.second.second--;
						if (e->second.second.second == 0)
						{
							Mix_FreeMusic(e->second.second.first);
							e->second.second.first = nullptr;
						}
						
						
#ifdef USER_DEBUG
						audio_count--;
#endif
					}
					
					
				}
			
			

		}

		~Audio_Manager()
		{

			for (auto e : _m)
			{
				if (e.second.first.first != nullptr)
				{
					e.second.first.second = 0;
					Mix_FreeChunk(e.second.first.first);
				}

				if (e.second.second.first != nullptr)
				{
					e.second.second.second = 0;
					Mix_FreeMusic(e.second.second.first);
				}
			}
#ifdef USER_DEBUG
			audio_count = 0;
#endif

		}

	private:
		std::string _path;
	private:
		std::unordered_map<std::string, std::pair<std::pair<Mix_Chunk*,size_t> ,std::pair<Mix_Music*,size_t>>, std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, std::pair<std::pair<Mix_Chunk*,size_t>,std::pair<Mix_Music*,size_t>>>>> _m;
		
		
	};

	//字体资源管理器
	class Font_Manager
	{
	public:
		void SetPath(const std::string& path)
		{
			_path = path;
			InitData();
		}

		void InitData()
		{
			std::vector<std::string>* pr = GetDirectoryFileName(_path);
			if (_path.size() == 0)
			{
				std::cerr << "Font_Manager::InitData, err:未设置字体管理器路径" << std::endl;
				assert(0);
			}

			for (auto& e : *pr)
			{
				_td.insert(make_pair(e, std::map<int, TTF_Font*,std::less<int>,STL_Allocator<std::pair<int, TTF_Font*>>>()));
			}
			delete pr;

		}

		TTF_Font* DynamicLoad(const std::string& str,int size)//需要时进行加载对应资源
		{
			TTF_Font* font = TTF_OpenFont((_path+str).c_str(), size);
		
			return font;
		}

		TTF_Font* FontFind(const std::string& str,int size)//查找资源，如果没有则动态加载
		{
			auto e = _td.find(str);
			if (e == _td.end())
			{
				return nullptr;
			}
			else
			{
				auto re = (e->second).find(size);
				if (re == (e->second).end())
				{
					auto rev=(e->second).insert(std::make_pair(size,DynamicLoad(str, size)));
					return rev.first->second;
				}
				

				return re->second;
			}
		}

		GM_Texture Find(const std::string& str, int size, const std::string& data, SDL_Renderer* render)//查找资源，如果没有则动态加载
		{
			//color默认白色
			std::string tem(data + str + std::to_string(size));
			auto e = _d.find(tem);
			if (e == _d.end())
			{
				TTF_Font* pr=FontFind(str, size);
				if (pr == nullptr)
				{
					std::cerr << "Font_Manager::Find,err:不存在该字体" << std::endl;
					assert(0);
				}
				SDL_Color t_color = { 255,255,255,255 };
				SDL_Surface* sur_text = TTF_RenderUTF8_Blended(pr,data.c_str(), t_color);
				GM_Texture temp;
				temp._height = sur_text->h;
				temp._width = sur_text->w;
				SDL_Texture* tex_text = SDL_CreateTextureFromSurface(render, sur_text);
				SDL_FreeSurface(sur_text);
				temp._data = tex_text;
				_d.insert(std::make_pair(move(tem),std::make_pair(temp,1)));
#ifdef USER_DEBUG
				text_count++;
#endif
				return temp;
			}
			e->second.second++;
			return e->second.first;
			
		}


		void ReleaseTexture(const std::string& str, int size, const std::string& data)//释放资源
		{
			std::string tem(data + str + std::to_string(size));
			auto e = _d.find(tem);
			if (e == _d.end())
			{
				return;
			}
			else
			{
				e->second.second--;
				if (e->second.second == 0)
				{
					SDL_DestroyTexture(e->second.first._data);
					e->second.first._data = nullptr;
					_d.erase(e);
				}
				
			
#ifdef USER_DEBUG
				text_count--;
#endif
			}

		}

		~Font_Manager()
		{
			for (auto& e : _d)
			{
				if (e.second.first._data != nullptr)
				{
					e.second.second = 0;
					SDL_DestroyTexture(e.second.first._data);
				}
			}

			for (auto& e : _td)
			{
				for (auto& j : e.second)
				{
					TTF_CloseFont(j.second);
				}
	
			}
#ifdef USER_DEBUG
			text_count=0;
#endif

		}
	private:
		std::string _path;
	private:
		std::unordered_map<std::string, std::map<int,TTF_Font*, std::less<int>, STL_Allocator<std::pair<int, TTF_Font*>>>, std::hash<std::string>, std::equal_to<std::string>,STL_Allocator<std::pair<std::string, std::map<int, TTF_Font*, std::less<int>, STL_Allocator<std::pair<int, TTF_Font*>>>>>> _td;
		std::unordered_map<std::string, std::pair<GM_Texture,size_t>, std::hash<std::string>, std::equal_to<std::string>,STL_Allocator<std::pair<std::string, std::pair<GM_Texture,size_t>>>> _d;
	};


	class TTexture_Manager
	{
	public:

		void NewTextureNode(const char* name, TTexture_Node tem)
		{
			auto re=_d.insert(std::make_pair(name, std::make_pair(tem, 0)));
			if (re.second == false)
			{
				std::printf("存在同名TextureNode\n");
				exit(1);
			}

		}

		void DynamicLoad(TTexture_Node& node)
		{
			void* pr = SDL_CreateTexture(node._render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, node._width, node._height);
			SDL_SetTextureBlendMode((SDL_Texture*)pr, SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(node._render, (SDL_Texture*)pr);
			SDL_SetRenderDrawColor(node._render, 128, 128, 128, 0);
			SDL_RenderClear(node._render);
			lua_rawgeti(node._L, LUA_REGISTRYINDEX, node._func);
			lua_pushlightuserdata(node._L, node._render);
			int re = lua_pcall(node._L, 1, 0, 0);
			if (re != 0)
			{
				const char* err = lua_tostring(node._L, -1);
				printf("Lua 错误: %s\n", err);
				lua_pop(node._L, 1);
				exit(1);
			}
			SDL_SetRenderTarget(node._render, NULL);
			node._data = (SDL_Texture*)pr;
		}

		void DeleteTexture(const char* name)
		{
			auto re = _d.find(name);
			if (re != _d.end())
			{
				if (re->second.second == 1)
				{
					SDL_DestroyTexture(re->second.first._data);
					re->second.first._data = nullptr;
					re->second.second = 0;
				}
				else
				{
					re->second.second -= 1;
				}
			
			}
		}

		TTexture_Node* FindTexture(const char* name)
		{
			auto re = _d.find(name);
			if (re == _d.end())
			{
				//std::printf("不存在对应的TextureNode\n");
				return nullptr;
			}
			else
			{
				if ((re->second).first._data == nullptr)
				{
					DynamicLoad((re->second).first);
				}
				(re->second).second+=1;
				return &((re->second).first);
			}
		}

		~TTexture_Manager()
		{
			for (auto& e : _d)
			{
				if (e.second.first._data != nullptr)
				{
					SDL_DestroyTexture(e.second.first._data);
				}
				
			}
		}

	private:
		std::unordered_map<std::string, std::pair<TTexture_Node, size_t>, std::hash<std::string>, std::equal_to<std::string>, STL_Allocator<std::pair<std::string, std::pair<TTexture_Node, size_t>>>> _d;
	};

	class Resource_Manager
	{
	public:
		void SetImagePath(const std::string& path)
		{
			_g.SetPath(path);
		}
		void SetAudioPath(const std::string& path)
		{
			_a.SetPath(path);
		}
		void SetFontPath(const std::string& path)
		{
			_f.SetPath(path);
		}

		GM_Texture GetImage(const std::string& str,SDL_Renderer* render)
		{
			return _g.Find(str,render);
		}
		void* GetAudio(const std::string& str,int flag)
		{
			return _a.Find(str,flag);
		}
		GM_Texture GetText(const std::string& str, int size, const std::string& data, SDL_Renderer* render)
		{
			return _f.Find(str, size,data,render);
		}
		void DeleteImage(const std::string& str)
		{
			return _g.ReleaseTexture(str);
		}
		void DeleteAudio(const std::string& str)
		{
			return _a.ReleaseAudio(str);
		}
		void DeleteText(const std::string& str, int size, const std::string& data)
		{
			return _f.ReleaseTexture(str, size, data);
		}
		void NewTextureNode(const char* name, TTexture_Node tem)
		{
			return _tt.NewTextureNode(name, tem);
		}

		void DeleteTexture(const char* name)
		{
			_tt.DeleteTexture(name);
		}

		TTexture_Node* FindTexture(const char* name)
		{
			return _tt.FindTexture(name);
		}
	private:
		Atlas _g;
		Audio_Manager _a;
		Font_Manager _f;
		TTexture_Manager _tt;
	};

	Resource_Manager* _rm;

	void InitValueResource_Manager()
	{
		static Resource_Manager rm;
		_rm = &rm;
	}

	void SetImagePath(const std::string& path)
	{
		_rm->SetImagePath(path);
	}
	void SetAudioPath(const std::string& path)
	{
		_rm->SetAudioPath(path);
	}
	void SetFontPath(const std::string& path)
	{
		_rm->SetFontPath(path);
	}

	GM_Texture GetImage(const std::string& str, SDL_Renderer* render)
	{
		return _rm->GetImage(str, render);
	}
	void* GetAudio(const std::string& str,int flag)
	{
		return _rm->GetAudio(str,flag);
	}
	GM_Texture GetText(const std::string& str, int size, const std::string& data, SDL_Renderer* render)
	{
		return _rm->GetText(str, size, data, render);
	}
	void DeleteImage(const std::string& str)
	{
		return _rm->DeleteImage(str);
	}
	void DeleteAudio(const std::string& str)
	{
		return _rm->DeleteAudio(str);
	}
	void DeleteText(const std::string& str, int size, const std::string& data)
	{
		return _rm->DeleteText(str, size, data);
	}

	void NewTextureNode(const char* name, TTexture_Node tem)
	{
		return _rm->NewTextureNode(name, tem);
	}

	void DeleteTexture(const char* name)
	{
		_rm->DeleteTexture(name);
	}

	TTexture_Node* FindTexture(const char* name)
	{
		return _rm->FindTexture(name);
	}

}