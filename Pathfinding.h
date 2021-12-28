#ifndef __PATHFINDING__H__
#define __PATHFINDING__H__

#include "Structs.h"
#include "Node.h"

enum DISTANCE {MANHATTAN, EUCLIDEAN, DIAGONAL};

class Pathfinding
{
public:
	Pathfinding(void);
	Pathfinding(int w, int h);
	void set_heuristic_distance_type(DISTANCE d);
	void set_start_and_end_from_matrix(void);
	void set_diagonal(bool d);
	void set_start(int x, int y, bool over);
	void set_end(int x, int y, bool over);
	void set_wall(int x, int y);
	void clear_at(int x, int y);
	void clear(void);
	void clear_all(bool del);
	void clear_path(void);
	void find(void);
	void pathfinding(bool diag);
	inline long int get_time(void){return _time;}
	
	void print_matrix(void);
	
private:
	bool managed_access(int x, int y, int c);
	float get_distance(Node *n1, Node *n2);
	void final_path(void);
	float manhattan_distance(Node *n1, Node *n2);
	float euclidean_distance(Node *n1, Node *n2);
	float diagonal_distance(Node *n1, Node *n2);
	Node *managed_access(int x, int y);
	
public:
	Node ***matrix;
	DISTANCE distance_type;
	bool no_path;
	
private:
	Node *start;
	Node *end;
	int _start_x;
	int _start_y;
	int _end_x;
	int _end_y;
	ArrayList<Node> open_list;
	ArrayList<Node> closed_list;
	int width;
	int height;
	bool diagonal;
	long int _time;
	bool save_analyze;
};

#endif