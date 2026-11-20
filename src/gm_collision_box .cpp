#include "gm2.h"

namespace gm
{
#define Judge_Mask(index,mask_ptr) ((1<<(index%64))&(mask_ptr[index/64]))



	Collision_Box* NewCollision_Box(int width,int height,int type,int _typeid,int buffer_size,bool IsRigidity)
	{
		Collision_Box* pr = (Collision_Box*)Malloc(sizeof(Collision_Box));
		pr->_height = width;
		pr->_width = height;
		pr->_type = type;
		pr->_IsCheck = 1;
		pr->_cap = buffer_size;
		pr->_typeid = _typeid;
		memset(&(pr->_mask), 0, 4 * sizeof(size_t));
		memset(&(pr->_maskid), 0, 4 * sizeof(size_t));
		pr->_IsRigidity = IsRigidity;
		if (IsRigidity == false)
		{
			pr->_ptr = Malloc(1 +buffer_size * sizeof(Entity*));
			*((unsigned char*)pr->_ptr) = 0;
		}
		else
		{
			pr->_ptr = NULL;
		}
		
		return pr;
	}
	void DeleteCollision_Box(Collision_Box* pr)
	{
		if (pr->_IsRigidity == false)
		{
			Free(pr->_ptr);
		}
		
		Free(pr);
	}

	void WriteBuffer(Entity* temp,Entity* pr)
	{
		Collision_Box* ptr = (pr->_b_ptr);
		size_t size = *((unsigned char*)(ptr->_ptr));
		if (ptr->_cap != size)
		{
			Entity** buffer = (Entity**)((unsigned char*)(ptr->_ptr) + 1);
			buffer[size] = temp;
			*((unsigned char*)(ptr->_ptr)) = size + 1;
		}
		

	}

	//Entity* EntityCollisionCheck(Entity* pr,Renderer_Task* rt_ptr)
	//{
	//	Collision_Box* tem_pr = ((Collision_Box*)(pr->_b_ptr));
	//	size_t* mask_ptr = &((tem_pr->_mask)[0]);
	//	int width1 = tem_pr->_width;
	//	int height1 = tem_pr->_height;
	//	int box_x1 = pr->_dest.x +(pr->_dest.w - width1)/2;
	//	int box_y1 = pr->_dest.y + (pr->_dest.h - height1) / 2;
	//	Entity* rid = nullptr;
	//	for (auto& e:(rt_ptr->_t))
	//	{
	//		Collision_Box* temp_pr = ((Collision_Box*)(e.second->_b_ptr));
	//		if (e.second != pr && e.second->_b_ptr != NULL &&Judge_Mask(temp_pr->_type, mask_ptr)==0)
	//		{
	//			if (temp_pr->_IsRigidity == false)
	//			{
	//				if ( temp_pr->_IsCheck == 1)
	//				{
	//					int width2 = ((Collision_Box*)(e.second->_b_ptr))->_width;
	//					int height2 = ((Collision_Box*)(e.second->_b_ptr))->_height;
	//					int box_x2 = e.second->_dest.x + (e.second->_dest.w - width2) / 2;
	//					int box_y2 = e.second->_dest.y + (e.second->_dest.h - height2) / 2;

	//					if (box_x1 + width1 > box_x2)
	//					{
	//						//不在2号碰撞箱的左边
	//						if (box_x1 < box_x2 + width2)
	//						{
	//							//不在2号碰撞箱的右边
	//							if (box_y1 + height1 > box_y2)
	//							{
	//								//不在2号碰撞箱的上边
	//								if (box_y1 < box_y2 + height2)
	//								{
	//									//不在2号碰撞箱的下边
	//									//综上，只存在相交的可能
	//									if (tem_pr->_IsRigidity == true)
	//									{
	//										WriteBuffer(tem_pr, e.second);
	//										rid = e.second;
	//									}
	//									else
	//									{
	//										return e.second;
	//									}

	//								}
	//							}
	//						}
	//					}

	//				}
	//			}
	//		
	//		}
	//		
	//		
	//	}
	//	return rid;
	//}

	class Collison_Manager
	{
	public:
		void Insert(Entity* ptr)
		{
			Collision_Box* pr = ptr->_b_ptr;
			int index1 = pr->_type;
			int index2 = pr->_typeid;
			if (_d.size() <= index1)
			{
				for (int i = _d.size(); i < index1 + 1; i++)
				{
					_d.push_back(std::vector<std::set<Entity*, std::less<Entity*>, STL_Allocator<Entity*>>>());
				}
			}
			if (_d[index1].size() <= index2)
			{
				for (int i = _d[index1].size(); i < index2 + 1; i++)
				{
					_d[index1].push_back(std::set<Entity*, std::less<Entity*>, STL_Allocator<Entity*>>());
				}
			}
			_d[index1][index2].insert(ptr);
		}

		void Erase(Entity* ptr)
		{
			Collision_Box* pr = ptr->_b_ptr;
			int index1 = pr->_type;
			int index2 = pr->_typeid;
			_d[index1][index2].erase(ptr);
		}

		Entity* CollisionCheck(Entity* pr)
		{
			Collision_Box* tem_pr = ((Collision_Box*)(pr->_b_ptr));
			size_t* mask_ptr = &((tem_pr->_mask)[0]);
			size_t* maskid_ptr = &((tem_pr->_maskid)[0]);
			int width1 = tem_pr->_width;
			int height1 = tem_pr->_height;
			int box_x1 = pr->_dest.x + (pr->_dest.w - width1) / 2;
			int box_y1 = pr->_dest.y + (pr->_dest.h - height1) / 2;
			Entity* rid = nullptr;

			for (int i=0;i<_d.size();i++)
			{
				if (Judge_Mask(i, mask_ptr) == 0)//没被屏蔽
				{
			
					for (int j = 0; j < _d[i].size(); j++)
					{
						if (Judge_Mask(j, maskid_ptr) == 0)//没被屏蔽
						{
							std::set<Entity*, std::less<Entity*>, STL_Allocator<Entity*>>& tem = _d[i][j];
							for (auto& e : tem)
							{
								Collision_Box* temp_pr = e->_b_ptr;
								if (temp_pr->_IsRigidity == false)
								{
									if (temp_pr->_IsCheck == 1)
									{
										int width2 = ((Collision_Box*)(e->_b_ptr))->_width;
										int height2 = ((Collision_Box*)(e->_b_ptr))->_height;
										int box_x2 = e->_dest.x + (e->_dest.w - width2) / 2;
										int box_y2 = e->_dest.y + (e->_dest.h - height2) / 2;

										if (box_x1 + width1 > box_x2)
										{
											//不在2号碰撞箱的左边
											if (box_x1 < box_x2 + width2)
											{
												//不在2号碰撞箱的右边
												if (box_y1 + height1 > box_y2)
												{
													//不在2号碰撞箱的上边
													if (box_y1 < box_y2 + height2)
													{
														//不在2号碰撞箱的下边
														//综上，只存在相交的可能
														if (tem_pr->_IsRigidity == true)
														{
															WriteBuffer(pr, e);
															rid = e;
														}
														else
														{
															return e;
														}

													}
												}
											}
										}

									}
								}
									

								
							}
						}
					}
				}
			}
			return rid;
		}

	private:
		std::vector<std::vector<std::set<Entity*,std::less<Entity*>,STL_Allocator<Entity*>>>> _d;
	};

	Collison_Manager* _cm;

	void InitValueCollison_Manager()
	{
		static Collison_Manager cm;
		_cm = &cm;
		
	}

	void Insert(Entity* ptr)
	{
		_cm->Insert(ptr);
	}

	void Erase(Entity* ptr)
	{
		_cm->Erase(ptr);
	}

	Entity* CollisionCheck(Entity* pr)
	{
		return _cm->CollisionCheck(pr);
	}

}