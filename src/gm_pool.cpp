#include"gm2.h"
#include <gperftools/malloc_extension.h>

namespace gm
{
	size_t GetMemoryUsed()
	{
		size_t size;
		MallocExtension::instance()->GetNumericProperty("generic.current_allocated_bytes", &size);
		return size;
	}

	void* Malloc(size_t num)
	{
		return tc_malloc(num);
	}


	void Free(void* ptr)
	{
		return tc_free(ptr);
	}


	void* SDLMalloc(size_t num)
	{
		if (num + 5 > 128)
		{
			unsigned char* j = (unsigned char*)malloc(num + 5);
			*j = 0;
			unsigned int* tem = (unsigned int*)(j + 1);
			*tem = num;
			return (tem + 1);
		}
		else
		{
			unsigned int* tem;
			unsigned char* j = (unsigned char*)Malloc(num + 5);

			if (j == nullptr)
			{
				j = (unsigned char*)malloc(num + 5);
				*j = 0;
			}
			else
			{
				*j = 1;
			}
			tem = (unsigned int*)(j + 1);
			*tem = num;
			return(tem + 1);

		}

	}


	void SDLFree(void* ptr)
	{
		unsigned char* pr = ((unsigned char*)ptr - 5);
		if (*pr != 0)
		{
			unsigned int* tem = (unsigned int*)(pr + 1);
			Free(pr);
		}
		else
		{
			free(pr);
		}

	}

//#ifdef USER_DEBUG
//	size_t GetPoolCapacity()
//	{
//		return _tcpool.GetPoolCapacity();
//	}
//#endif


}



	