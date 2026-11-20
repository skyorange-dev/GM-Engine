AnimPlayer={}

function AnimPlayer.new(entity_pr,s,start)
	local dptr1=event.dptr;
	local dptr2=entity_pr;
	local start_index;
	local size=s;
	local _interval=45;
	local _timer=0;
	if start==nil then
		start_index=0;
	else
		start_index=start;
	end
	local function Run()
		if dptr1._time-_timer>_interval then
			_timer=dptr1._time;
			if dptr2._rindex+1~=size+start_index then
				dptr2._rindex=dptr2._rindex+1;
			else
				dptr2._rindex=start_index;
			end
		end
	end

	local function SetIndex(index)
		dptr2._rindex=index+start_index;
	end

	local function GetIndex()
		
		return dptr2._rindex-start_index;
	end

	local function SetInterval(interval)
		_interval=interval;
	end

	return {
		Run=Run,
		SetIndex=SetIndex,
		GetIndex=GetIndex,
		SetInterval= SetInterval
	}
	
end

AtlasAnimPlayer={}

function AtlasAnimPlayer.new(entity_pr,s,start)
	local dptr1=event.dptr;
	local dptr2=entity_pr;
	local start_index;
	local size=s;
	local _interval=45;
	local image_interval=dptr2._dest.w;
	local image_height=dptr2._dest.h;
	local _timer=0;
	if start==nil then
		start_index=0;
	else
		start_index=start;
	end
	local n_index=start_index;
	local function Run()
		if dptr1._time-_timer>_interval then
			_timer=dptr1._time;
			if n_index+1~=size+start_index then
				n_index=n_index+1;
				dptr2._source.x=n_index*image_interval;
			else
				n_index=start_index;
				dptr2._source.x=n_index*image_interval;
			end
		end
	end

	local function SetIndex(index)
		dptr2._source.x=(index+start_index)*image_interval;
	end

	local function GetIndex()
		
		return (dptr2._source.x-start_index*image_interval)/image_interval;
	end

	local function SetInterval(interval)
		_interval=interval;
	end

	return {
		Run=Run,
		SetIndex=SetIndex,
		GetIndex=GetIndex,
		SetInterval= SetInterval
	}
	
end








