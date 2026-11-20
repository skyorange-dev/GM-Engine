#include "gm2.h"

namespace gm
{
	int C_SetImagePath(lua_State* L)
	{
		const char* p1 = lua_tostring(L, -1);
		SetImagePath(p1);
		lua_pop(L, 1);
		return 0;
	}
	int C_SetAudioPath(lua_State* L)
	{
		const char* p1 = lua_tostring(L, -1);
		SetAudioPath(p1);
		lua_pop(L, 1);
		return 0;
	}
	int C_SetFontPath(lua_State* L)
	{
		const char* p1 = lua_tostring(L, -1);
		SetFontPath(p1);
		lua_pop(L, 1);
		return 0;
	}

	int C_GetImage(lua_State* L/*,const std::string& str, SDL_Renderer* render*/)
	{
		const char* str = lua_tostring(L, -2);
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		SDL_Renderer* render = (SDL_Renderer*)p1;
		GM_Texture* pr = (GM_Texture*)Malloc(sizeof(GM_Texture));
		*pr=GetImage(str, render);
		lua_pop(L, 2);
		lua_pushlightuserdata(L, pr);
		return 1;
	}
	int C_GetAudio(lua_State* L)
	{
		const char* p1 = lua_tostring(L, -2);
		int flag = lua_tonumber(L, -1);
		lua_pop(L, 2);
		lua_pushlightuserdata(L,GetAudio(p1,flag));
		return 1;
	}
	int C_GetText(lua_State* L)
	{
		std::string str = lua_tostring(L, -4);
		int size = lua_tonumber(L, -3);
		std::string data= lua_tostring(L, -2);
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		SDL_Renderer* render = (SDL_Renderer*)p1;
		GM_Texture* pr = (GM_Texture*)Malloc(sizeof(GM_Texture));
		*pr = GetText(str, size,data,render);
		lua_pop(L, 4);
		lua_pushlightuserdata(L, pr);
		return 1;
	}
	int C_DeleteImage(lua_State* L)
	{
		const char* p1 = lua_tostring(L, -1);
		DeleteImage(p1);
		lua_pop(L, 1);
		return 0;
	}
	int C_DeleteGM_Texture(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -1);
		Free((void*)p1);
		lua_pop(L, 1);
		return 0;
	}
	int C_DeleteAudio(lua_State* L)
	{
		const char* p1 = lua_tostring(L, -1);
		DeleteAudio(p1);
		lua_pop(L, 1);
		return 0;
	}
	int C_DeleteText(lua_State* L)
	{
		std::string str = lua_tostring(L, -3);
		int size = lua_tonumber(L, -2);
		std::string data = lua_tostring(L, -1);
		DeleteText(str, size, data);
		lua_pop(L, 3);
		return 0;
	}

	int C_PlayChunk(lua_State* L)
	{
		int channel = lua_tonumber(L, -4);
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		int loops = lua_tonumber(L, -2);
		int time= lua_tonumber(L, -1);
		lua_pop(L, 4);
		Mix_PlayChannelTimed(channel,(Mix_Chunk*)p1,loops,time);
		return 0;
	}

	int C_PlayMusic(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		int loops = lua_tonumber(L, -1);
		lua_pop(L, 2);
		Mix_PlayMusic((Mix_Music*)p1, loops);
		return 0;
	}

	int C_PauseChunk(lua_State* L)
	{
		int channel = lua_tonumber(L, -1);
		lua_pop(L, 1);
		Mix_Pause(channel);
		return 0;
	}

	int C_PauseMusic(lua_State* L)
	{
		Mix_PauseMusic();
		return 0;
	}

	int C_ResumeChunk(lua_State* L)
	{
		int channel = lua_tonumber(L, -1);
		lua_pop(L, 1);
		Mix_Resume(channel);
		return 0;
	}

	int C_ResumeMusic(lua_State* L)
	{
		Mix_ResumeMusic();
		return 0;
	}

	int C_FadeInChunk(lua_State* L)
	{
		int channel = lua_tonumber(L, -4);
		intptr_t p1 = (intptr_t)lua_touserdata(L, -3);
		int loops = lua_tonumber(L, -2);
		int ms = lua_tonumber(L, -1);;
		lua_pop(L, 4);
		Mix_FadeInChannel(channel,(Mix_Chunk*)p1,loops,ms);
		return 0;
	}

	int C_FadeOutChunk(lua_State* L)
	{
		
		int which = lua_tonumber(L, -2);
		int ms = lua_tonumber(L, -1);;
		lua_pop(L, 2);
		Mix_FadeOutChannel(which, ms);
		return 0;
	}

	int C_FadeInMusic(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -4);
		int loops = lua_tonumber(L, -3);
		int ms = lua_tonumber(L, -2);
		double position= lua_tonumber(L, -1);
		lua_pop(L, 4);
		Mix_FadeInMusicPos((Mix_Music*)p1, loops, ms,position);
		return 0;
	}

	int C_FadeOutMusic(lua_State* L)
	{
		int ms = lua_tonumber(L, -1);;
		lua_pop(L, 1);
		Mix_FadeOutMusic(ms);
		return 0;
	}

	int C_StopChunk(lua_State* L)
	{
		int channel = lua_tonumber(L, -2);
		int ticks = lua_tonumber(L, -1);;
		lua_pop(L, 2);
		if (channel == -1)
		{
			Mix_HaltChannel(-1);
		}
		else
		{
			Mix_ExpireChannel(channel,ticks);
		}
	
		return 0;
	}

	int C_StopMusic(lua_State* L)
	{
		Mix_HaltMusic();
		return 0;
	}

	int C_RewindMusic(lua_State* L)
	{
		Mix_RewindMusic();
		return 0;
	}

	int C_VolumeMusic(lua_State* L)
	{
		int volume = lua_tonumber(L, -1);
		lua_pop(L,1);
		Mix_VolumeMusic(volume);
		return 0;
	}

	int C_VolumeChunk(lua_State* L)
	{
		int channel = lua_tonumber(L, -2);;
		int volume = lua_tonumber(L, -1);
		lua_pop(L, 2);
		Mix_Volume(channel,volume);
		return 0;
	}

	int C_VolumeChunkData(lua_State* L)
	{
		intptr_t p1 = (intptr_t)lua_touserdata(L, -2);
		int volume = lua_tonumber(L, -1);
		lua_pop(L, 2);
		Mix_VolumeChunk((Mix_Chunk*)p1, volume);
		return 0;
	}

	int C_SetMusicPosition(lua_State* L)
	{
		double position = lua_tonumber(L, -1);
		lua_pop(L, 1);
		Mix_SetMusicPosition(position);
		return 0;
	}

	int C_SetChunkPanning(lua_State* L)
	{
		int channel = lua_tonumber(L, -3);;
		Uint8 left = lua_tonumber(L, -2);
		Uint8 right= lua_tonumber(L, -1);
		lua_pop(L, 3);
		Mix_SetPanning(channel,left,right);
		return 0;
	}

	int C_SetChannelDistance(lua_State* L)
	{
		int channel = lua_tonumber(L, -2);;
		Uint8 distance = lua_tonumber(L, -1);
		lua_pop(L, 2);
		Mix_SetDistance(channel, distance);
		return 0;
	}

	int C_SetChannelPosition(lua_State* L)
	{
		int channel = lua_tonumber(L, -3);;
		Sint16 angle = lua_tonumber(L, -2);
		Uint8 distance = lua_tonumber(L, -1);
		lua_pop(L, 3);
		Mix_SetPosition(channel, angle, distance);
		return 0;
	}

	int C_NewTextureNode(lua_State* L/*const char* name, TTexture_Node tem*/)
	{
		const char* str = lua_tostring(L, -5);
		intptr_t p1 = (intptr_t)lua_touserdata(L, -4);
		SDL_Renderer* render = (SDL_Renderer*)p1;
		int width = lua_tonumber(L, -3);
		int height = lua_tonumber(L, -2);
		TTexture_Node tem;
		tem._data = nullptr;
		tem._width = width;
		tem._height = height;
		tem._L = L;
		tem._render = render;
		int re=luaL_ref(L, LUA_REGISTRYINDEX);
		tem._func = re;
		NewTextureNode(str,tem);
		lua_pop(L, 4);
		return 0;
	}

	int C_FindTexture(lua_State* L/*const char* name*/)
	{
		const char* str = lua_tostring(L, -1);
		void* re=FindTexture(str);
		lua_pop(L, 1);
		lua_pushlightuserdata(L, re);
		return 1;
	}

	int C_DeleteTexture(lua_State* L)
	{
		const char* str = lua_tostring(L, -1);
		DeleteTexture(str);
		lua_pop(L, 1);
		return 0;
	}

	void InitResource_Manager(lua_State* L)
	{
		lua_register(L, "C_SetImagePath", C_SetImagePath);
		lua_register(L, "C_SetAudioPath", C_SetAudioPath);
		lua_register(L, "C_SetFontPath", C_SetFontPath);
		lua_register(L, "C_GetImage", C_GetImage);
		lua_register(L, "C_GetAudio", C_GetAudio);
		lua_register(L, "C_GetText", C_GetText);
		lua_register(L, "C_DeleteImage", C_DeleteImage);
		lua_register(L, "C_DeleteAudio", C_DeleteAudio);
		lua_register(L, "C_DeleteText", C_DeleteText);
		lua_register(L, "C_DeleteGM_Texture", C_DeleteGM_Texture);
		lua_register(L, "C_PlayChunk", C_PlayChunk);
		lua_register(L, "C_PlayMusic", C_PlayMusic);
		lua_register(L, "C_PauseChunk", C_PauseChunk);
		lua_register(L, "C_PauseMusic", C_PauseMusic);
		lua_register(L, "C_ResumeChunk", C_ResumeChunk);
		lua_register(L, "C_ResumeMusic", C_ResumeMusic);
		lua_register(L, "C_FadeInChunk", C_FadeInChunk);
		lua_register(L, "C_FadeOutChunk", C_FadeOutChunk);
		lua_register(L, "C_FadeInMusic", C_FadeInMusic);
		lua_register(L, "C_FadeOutMusic", C_FadeOutMusic);
		lua_register(L, "C_StopChunk", C_StopChunk);
		lua_register(L, "C_StopMusic", C_StopMusic);
		lua_register(L, "C_RewindMusic", C_RewindMusic);
		lua_register(L, "C_VolumeMusic", C_VolumeMusic);
		lua_register(L, "C_VolumeChunk", C_VolumeChunk);
		lua_register(L, "C_VolumeChunkData", C_VolumeChunkData);
		lua_register(L, "C_SetMusicPosition", C_SetMusicPosition);
		lua_register(L, "C_SetChunkPanning", C_SetChunkPanning);
		lua_register(L, "C_SetChannelDistance", C_SetChannelDistance);
		lua_register(L, "C_SetChannelPosition", C_SetChannelPosition);
		lua_register(L, "C_NewTextureNode", C_NewTextureNode);
		lua_register(L, "C_FindTexture", C_FindTexture);
		lua_register(L, "C_DeleteTexture", C_DeleteTexture);
	}
}