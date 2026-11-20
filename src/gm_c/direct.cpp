#include "gm.h"
int JudgeDirection(double speed_x,double speed_y)
{
	if(speed_x>0) 
	{
		if(speed_y>0)
		{
			return 8;
		}
		else if(speed_y<0)
		{
			return 2;
		}	
		else
		{
			return 5;
		}
	}
	else if(speed_x<0) 
	{
		if(speed_y>0)
		{
			return 6;
		}
		else if(speed_y<0)
		{
			return 0;
		}
		else
		{
			return 3;
		}
	}
	else
	{
		if(speed_y>0)
		{
			return 7;
		}
		else if(speed_y<0)
		{
			return 1;
		}
		else
		{
			return 4;
		}
	}
}