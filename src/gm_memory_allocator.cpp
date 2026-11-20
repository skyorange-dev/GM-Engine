#pragma once
#include"gm2.h"

//GM的内存分配器
namespace gm
{
	void* lua_alloc(void* ud, void* ptr, size_t osize, size_t nsize)
	{
		// 1. 释放内存
		if (nsize == 0) {
			if (ptr) {
				Free(ptr);
			}
			return NULL;
		}

		// 2. 分配新内存
		if (ptr == NULL)
		{
			return Malloc(nsize);;
		}

		// 3. 重分配内存
		void* pr = Malloc(nsize);
		if (pr)
		{
			memcpy(pr, ptr, (nsize > osize) ? osize : nsize);
			Free(ptr);
		}
		return pr;
	}


	void json_init() 
	{
		cJSON_Hooks hooks;
		hooks.malloc_fn = Malloc;
		hooks.free_fn =Free;

		cJSON_InitHooks(&hooks);
	}

	void* sdl_malloc(size_t size) 
	{
		intptr_t pr= (intptr_t)SDLMalloc(16+size);
		void* ptr = NULL;
		size_t tem = pr / 16;
		if (tem * 16 != pr)
		{
			size_t offset = ((tem + 1) * 16) - pr;
			ptr = (void*)((tem + 1) * 16);
			*((unsigned char*)ptr - 1) = offset;
		}
		else
		{
			ptr = (void*)((char*)pr+16);
			*((unsigned char*)ptr - 1) = 16;

		}

		return ptr;
	}

	void* sdl_calloc(size_t nmemb, size_t size) 
	{
		void* ptr = sdl_malloc(nmemb * size);
		if (ptr)
		{
			memset(ptr, 0, nmemb * size);
		}
		return ptr;
	}

	
	void* sdl_realloc(void* ptr, size_t size) 
	{
		void* pr = NULL;
		if (size != 0)
		{
			pr = sdl_malloc(size);
			if (pr)
			{
				if (ptr != NULL)
				{
					void* pr0 = ((char*)ptr-(*((unsigned char*)ptr - 1)));
					unsigned int* pr1 = (unsigned int*)((char*)pr0 - 4);
					memcpy(pr, ptr, (size > *pr1) ? *pr1 : size);
					sdl_free(ptr);
				}

			}
		}
		else
		{
			
			if (ptr != NULL)
			{
				sdl_free(ptr);
			}

			
		}
	
		
		return pr;
	}

	void sdl_free(void* ptr) 
	{
		size_t offset = *((unsigned char*)ptr - 1);
		SDLFree((char*)ptr-offset);
	}

}

