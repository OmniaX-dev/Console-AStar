#ifndef __NODE__H__
#define __NODE__H__

class Node
{
public:
	Node(void);
	Node(int v);
	bool equals(void *obj);
	bool is_walkable(void);
	float fscore(void);
	
public:
	int g;
	float h;
	Node *parent;
	int x;
	int y;
	int value;
};

#endif