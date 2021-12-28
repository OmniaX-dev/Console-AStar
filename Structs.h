#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

enum ENUM_REALLOCATION_STRATEGY{
	REALLOCATION_STRATEGY_DOUBLE,
	REALLOCATION_STRATEGY_TRIPLE,
	REALLOCATION_STRATEGY_ADD_ONE,
	REALLOCATION_STRATEGY_ADD_TWO,
	REALLOCATION_STRATEGY_TIMES_TEN
};

template<class ITEM_TYPE>
struct ArrayList{
	ITEM_TYPE **list;
	int item_count;
	int item_size;
	int block_size;

	ENUM_REALLOCATION_STRATEGY realloc_strat;

	int _cur_iter;

	ArrayList()
	{
		__constructor(1, REALLOCATION_STRATEGY_DOUBLE);
	}

	ArrayList(int default_size)
	{
		__constructor(default_size, REALLOCATION_STRATEGY_DOUBLE);
	}

	ArrayList(int default_size, ENUM_REALLOCATION_STRATEGY reallocation_strategy)
	{
		__constructor(default_size, reallocation_strategy);
	}

	void __constructor(int block, ENUM_REALLOCATION_STRATEGY reallocation_strategy)
	{
		realloc_strat = reallocation_strategy;
		block_size = block;
		item_size = sizeof(ITEM_TYPE);
		list = (ITEM_TYPE**)malloc(item_size * block_size);
		item_count = 0;
		reset_iteration();
	}

	void push(ITEM_TYPE *i)
	{
		if (item_count == block_size)
		{
			switch(realloc_strat)
			{
			case REALLOCATION_STRATEGY_ADD_ONE:
				block_size += 1;
				break;
			case REALLOCATION_STRATEGY_ADD_TWO:
				block_size += 2;
				break;
			case REALLOCATION_STRATEGY_DOUBLE:
				block_size *= 2;
				break;
			case REALLOCATION_STRATEGY_TRIPLE:
				block_size *= 3;
				break;
			case REALLOCATION_STRATEGY_TIMES_TEN:
				block_size *= 10;
				break;
			default:
				block_size *= 2;
				break;
			}
			list = (ITEM_TYPE**)realloc(list, block_size * item_size);
		}
		list[item_count] = i;
		item_count++;
	}

	ITEM_TYPE *pop()
	{
		if (item_count > 0)
		{
			item_count--;
			return list[item_count];
		}
		return NULL;
	}

	ITEM_TYPE *get(int i)
	{
		if (i < 0 || i >= item_count)
			return NULL;
		return list[i];
	}

	void set(ITEM_TYPE *o, int i)
	{
		if (i < item_count)
			list[i] = o;
	}

	bool remove(ITEM_TYPE *o)
	{
		for (int i = 0; i < item_count; i++)
		{
			if (list[i] == o)
			{
				list[i] = NULL;
				compact_list();
				return true;
			}
		}
		return false;
	}
	
	bool contains(ITEM_TYPE *o)
	{
		for (int i = 0; i < item_count; i++)
		{
			if (list[i] == o)
				return true;
		}
		return false;
	}

	void clear(void)
	{
		item_count = 0;
	}

	void compact_list()
	{
		for (int i = 0; i < item_count; i++)
		{
			if (list[i] == NULL)
			{
				for (int j = i + 1; j < item_count; j++)
				{
					list[j - 1] = list[j];
				}
				item_count--;
				i--;
			}
		}
	}

	bool put(ITEM_TYPE *o, int i)
	{
		if (i < 0 || i >= item_count)
			return false;
		push(NULL);
		for (int j = item_count - 1; j > i; j--)
			list[j] = list[j - 1];
		list[i] = o;
		return true;
	}

	ITEM_TYPE *get_next()
	{
		if (_cur_iter >= item_count)
		{
			reset_iteration();
			return NULL;
		}
		return list[_cur_iter++];
	}

	void reset_iteration()
	{
		_cur_iter = 0;
	}
};

struct SpriteFormatter{
	int up_row;
	int down_row;
	int left_row;
	int right_row;

	SpriteFormatter()
	{
		up_row = 3;
		down_row = 0;
		left_row = 1;
		right_row = 2;
	}

	SpriteFormatter(int u, int d, int l, int r)
	{
		up_row = u;
		down_row = d;
		left_row = l;
		right_row = r;
	}
};

struct Coord{
	Coord()
	{
		x = y = 0;
	}
	Coord(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
	int x;
	int y;
};

#endif
