#include"gm2.h"

namespace gm
{

	std::string DeleteStrBlank(const char* str)
	{
		std::string tem(str);
		for (auto e=tem.begin();e!=tem.end();)
		{
			if (*e == ' '||*e=='\n')
			{
				e=tem.erase(e);
			}
			else if (*e == '/')
			{
				auto f = e + 1;
				if (f != tem.end())
				{
					if (*f == '/')
					{
						while (*e!='\n')
						{
							e = tem.erase(e);
						}
						e = tem.erase(e);
					}
					else if (*f == '*')
					{
						e = tem.erase(e);
						e = tem.erase(e);
						while (*e != '*'||*(e+1)!='/')
						{
							e = tem.erase(e);
						}
						e = tem.erase(e);
						e = tem.erase(e);
					}
				}
			}
			else
			{
				e++;
			}
			
			

		}
		return tem;
	}
}