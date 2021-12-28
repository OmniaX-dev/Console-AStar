#include "Pathfinding.h"
#include "utilities.h"
#include <stdlib.h>
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
#   define NO_ANSI_ESCAPE_SEQUENCES
#endif

#if defined(__CYGWIN__)
#   undef __STRICT_ANSI__
#   include <iostream>
#   include <sstream>
#   define __STRICT_ANSI__
#else
#   include <iostream>
#   include <sstream>
#endif
#include "TermColor.hpp"

Pathfinding::Pathfinding(void)
{
	width = 0;
	height = 0;
	matrix = NULL;
	start = NULL;
	end = NULL;
}

Pathfinding::Pathfinding(int w, int h)
{
	width = w;
	height = h;
	matrix = alloc_2d_array<Node*>(width, height);
	clear();
	open_list = ArrayList<Node>(100);
	closed_list = ArrayList<Node>(100);
	start = NULL;
	end = NULL;
	distance_type = MANHATTAN;
	save_analyze = false;
}

void Pathfinding::print_matrix(void)
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			char c = (char)matrix[i][j]->value;
			if (c == ' ')
				std::cout << termcolor::on_bright_grey << termcolor::bright_grey;
			else if (c == 'W')
				std::cout << termcolor::on_white << termcolor::white;
			else if (c == 'S')
				std::cout << termcolor::green << termcolor::on_green;
			else if (c == 'E')
				std::cout << termcolor::red << termcolor::on_red;
			else if (c == 'P')
				std::cout << termcolor::on_magenta << termcolor::magenta;
			std::cout << c << c << termcolor::reset ;
		}
		std::cout << termcolor::reset << std::endl;
	}
}

void Pathfinding::set_heuristic_distance_type(DISTANCE d)
{
	distance_type = d;
}

void Pathfinding::set_start_and_end_from_matrix(void)
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (matrix[i][j]->value == 'S')
				set_start(i, j, false);
			else if (matrix[i][j]->value == 'E')
				set_end(i, j, false);
		}
	}
}

void Pathfinding::set_diagonal(bool d)
{
	diagonal = d;
}

void Pathfinding::set_start(int x, int y, bool over)
{
	if (over && (managed_access(x, y)->value == 'S' || managed_access(x, y)->value == 'E'))
		return;
	if (!managed_access(x, y, 'S'))
		return;
	managed_access(_start_x, _start_y, '_');
	start = new Node('S');
	start->x = x;
	start->y = y;
	_start_x = x;
	_start_y = y;
}

void Pathfinding::set_end(int x, int y, bool over)
{
	if (over && (managed_access(x, y)->value == 'S' || managed_access(x, y)->value == 'E'))
		return;
	if (!managed_access(x, y, 'E'))
		return;
	managed_access(_end_x, _end_y, '_');
	end = new Node('E');
	end->x = x;
	end->y = y;
	_end_x = x;
	_end_y = y;
}

void Pathfinding::set_wall(int x, int y)
{
	if (managed_access(x, y)->value == 'E' || managed_access(x, y)->value == 'S')
		return;
	managed_access(x, y, 'W');
}

void Pathfinding::clear_at(int x, int y)
{
	if (matrix[x][y]->value == 'S' || matrix[x][y]->value == 'E')
		return;
	managed_access(x, y, '_');
}

void Pathfinding::clear(void)
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (matrix[i][j] != NULL && (matrix[i][j]->value == 'S' || matrix[i][j]->value == 'E'))
				continue;
			matrix[i][j] = new Node('_');
			matrix[i][j]->x = i;
			matrix[i][j]->y = j;
		}
	}
}

void Pathfinding::clear_all(bool del)
{
	if (del)
	{
		start = NULL;
		end = NULL;
		_start_x = _start_y = _end_x = _end_y = -1;
	}
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			matrix[i][j] = new Node('_');
			matrix[i][j]->x = i;
			matrix[i][j]->y = j;
		}
	}
}

void Pathfinding::clear_path(void)
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			matrix[i][j]->g = 0;
			matrix[i][j]->h = 0;
			if (matrix[i][j]->value != 'W' && matrix[i][j]->value != 'S' && matrix[i][j]->value != 'E')
				matrix[i][j]->value = '_';
		}
	}
	open_list.clear();
	closed_list.clear();
}

void Pathfinding::find(void)
{
	if (start == NULL || end == NULL)
		return;
	pathfinding(diagonal);
}

void Pathfinding::pathfinding(bool diag)
{
	_time = time(NULL);
	no_path = false;
	int cyc = 0;
	Node *current = start;
	closed_list.push(current);
	while (!current->equals(end))
	{
		cyc++;
		Node *temp = NULL;
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				if (!diag && ((x != 0 && y != 0) || x == y))
					continue;
				temp = managed_access(current->x + x, current->y + y);
				if (temp != NULL && (!temp->is_walkable() || closed_list.contains(temp)))
					continue;
				if (temp != NULL)
				{
					if (!open_list.contains(temp))
					{
						temp->g = current->g + 1;
						temp->h = get_distance(temp, end);
						temp->parent = current;
						open_list.push(temp);
					}
					else
					{
						if (temp->g < current->g)
						{
							temp->parent = current;
							temp->g = current->g + 1;
							temp->h = get_distance(temp, end);
						}
					}
				}
			}
		}
		if (open_list.item_count == 0)
			break;
		Node *next = open_list.get(0);
		for (int i = 0; i < open_list.item_count; i++)
		{
			Node *n = open_list.get(i);
			if (n->fscore() < next->fscore())
				next = n;
		}
		
		if (!next->equals(end) && save_analyze)
			next->value = 'A';
		open_list.remove(next);
		closed_list.push(next);
		current = next;
	}
	final_path();
	_time = time(NULL) - _time;
}

bool Pathfinding::managed_access(int x, int y, int c)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		matrix[x][y]->value = c;
		return true;
	}
	return false;
}

float Pathfinding::get_distance(Node *n1, Node *n2)
{
	if (distance_type == MANHATTAN)
		return manhattan_distance(n1, n2);
	if (distance_type == EUCLIDEAN)
		return euclidean_distance(n1, n2);
	if (distance_type == DIAGONAL)
		return diagonal_distance(n1, n2);
	return manhattan_distance(n1, n2);
}

void Pathfinding::final_path(void)
{
	if (!closed_list.get(closed_list.item_count - 1)->equals(end))
		no_path = true;
	Node *current = closed_list.get(closed_list.item_count - 1);
	ArrayList<Node> path(20);
	while (!current->equals(start))
	{
		if (!current->equals(end))
			path.push(current);
		current = current->parent;
	}
	for (int i = path.item_count - 1; i >= 0; i--)
	{
		Node *n = path.get(i);
		n->value = 'P';
	}
	if (no_path)
	{
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				if (matrix[i][j]->value == 'P')
					matrix[i][j]->value = 'N';
			}
		}
	}
}

float Pathfinding::manhattan_distance(Node *n1, Node *n2)
{
	return abs(n1->x - n2->x) + abs(n1->y - n2->y);
}

float Pathfinding::euclidean_distance(Node *n1, Node *n2)
{
	return (float)sqrt(pow((n1->x - n2->x), 2) + pow((n1->y - n2->y), 2));
}

float Pathfinding::diagonal_distance(Node *n1, Node *n2)
{
	return max(abs(n1->x-n2->x), abs(n1->y-n2->y));
}

Node *Pathfinding::managed_access(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		return matrix[x][y];
	return NULL;
}
