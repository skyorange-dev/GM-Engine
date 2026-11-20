MoveDirection={}--根据移动方位返回0到8等数字

function MoveDirection.new(up_key,down_key,left_key,right_key)
	local up=up_key;
	local up_switch=false;
	local down=down_key;
	local down_switch=false;
	local left=left_key;
	local left_switch=false;
	local right=right_key;
	local right_switch=false;

	local function CheckDirection()
		local key_char,type=event.GetKeyBoardMessage()
		if key_char==up then
			if type==1 then
				up_switch=true;
			else
				up_switch=false;
			end

		elseif key_char==down then
			if type==1 then
				down_switch=true;
			else
				down_switch=false;
			end

		elseif key_char==left then
			if type==1 then
				left_switch=true;
			else
				left_switch=false;
			end

		elseif key_char==right then
			if type==1 then
				right_switch=true;
			else
				right_switch=false;
			end
		end

		if up_switch ==true and down_switch==false then
			if left_switch ==true and right_switch==false then
				return 0;
			elseif right_switch ==true and left_switch==false then
				return 2;
			else
				return 1;
			end
		elseif down_switch ==true and up_switch==false then
			if left_switch ==true and right_switch==false then
				return 6;
			elseif right_switch ==true and left_switch==false then
				return 8;
			else
				return 7;
			end
		else
			if left_switch ==true and right_switch==false then
				return 3;
			elseif right_switch ==true and left_switch==false then
				return 5;
			else
				return 4;
			end
		end



	end

	return {
		CheckDirection=CheckDirection
	}
	
end

--通过速度判断方位

function JudgeDirection(speed_x,speed_y)
	if speed_x>0 then
		if speed_y>0 then
			return 8;
		elseif speed_y<0 then
			return 2;
		else
			return 5;
		end
	elseif speed_x<0 then
		if speed_y>0 then
			return 6;
		elseif speed_y<0 then
			return 0;
		else
			return 3;
		end
	else
		if speed_y>0 then
			return 7;
		elseif speed_y<0 then
			return 1;
		else
			return 4;
		end
	end
end