#include "Node.h"

#ifndef NULL
#define NULL 0
#endif

Node::Node(void)
{
	g = 0;
	h = 0;
	x = 0;
	y = 0;
	value = 0;
	parent = NULL;
}

Node::Node(int v)
{
	g = 0;
	h = 0;
	x = 0;
	y = 0;
	value = v;
	parent = NULL;
}

bool Node::equals(void *obj)
{
	Node *n = (Node*)obj;
	return this->x == n->x && this->y == n->y;
}

bool Node::is_walkable(void)
{
	return value != 'W';
}

float Node::fscore(void)
{
	return g + h;
}