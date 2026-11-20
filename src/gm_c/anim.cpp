#include "gm.h"

AltlasAnimPlayer::AltlasAnimPlayer(Entity* entity_pr,int s,Event* eptr, int start)
	:_pr(entity_pr)
	,_size(s)
	,_epr(eptr)
	,_start_index(start)
{
	_interval=45;
	_image_interval=entity_pr->_dest.w;
	_image_height=entity_pr->_dest.h;
	_timer=0;
	_n_index=start;
}
	
void AltlasAnimPlayer::Run()
{
	if(_epr->_time-_timer>_interval)
	{
		_timer=_epr->_time;
		if(_n_index+1!=_size+_start_index)
		{
			_n_index=_n_index+1;
			_pr->_source.x=_n_index*_image_interval;
		}
		else
		{
			_n_index=_start_index;
			_pr->_source.x=_n_index*_image_interval;
		}
	}
			
}
	
void AltlasAnimPlayer::SetIndex(int index)
{
	_pr->_source.x=(index+_start_index)*_image_interval;
}
	
int AltlasAnimPlayer::GetIndex()
{
	return (_pr->_source.x-_start_index*_image_interval)/_image_interval;
}
	
void AltlasAnimPlayer::SetInterval(int interval)
{
	_interval=interval;
}
		
