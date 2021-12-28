#include <iostream>
#include "Pathfinding.h"
#include "utilities.h"

const int width = 45;
const int height = 30;

//This matrix gets rotated 90 degrees due to a bug
int matrix[width][height] = {
	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},
	{'W','S',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W','W','W','W','W','W','W',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ','W','W','W','W','W','W','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ','W','W','W','W','W','W','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W','W','W','W','W','W',' ','W','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ','W','W','W','W','W','W','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W','W','W',' ','W','W','W','W','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W','W','W','W','W','W','W',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W','W','W','W','W','W','W',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ',' ',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ','W','W','W','W','W','W','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W'},
	{'W',' ',' ',' ','W',' ','W',' ',' ','W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','E','W'},
	{'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}
};

Node ***get_node_matrix(int rows, int columns, bool set_start_and_end);

int main(void)
{
	Pathfinding pf(width, height);
	pf.matrix = get_node_matrix(width, height, false);
	pf.set_start_and_end_from_matrix();
	pf.print_matrix();
	std::cout << "\nPress Enter to find the path";
	std::cin.get();
	std::cout << "Allow diagonal? (y/n) ";
	char diag = 'N';
	std::cin >> diag;
	pf.pathfinding(diag == 'y' || diag == 'Y');
	pf.print_matrix();
	//std::cout << pf.get_time() << std::endl;
	return 0;
}

Node ***get_node_matrix(int rows, int columns, bool set_start_and_end)
{
	Node ***mat = alloc_2d_array<Node*>(rows, columns);
	for (int y = 0; y < columns; y++)
	{
		for (int x = 0; x < rows; x++)
		{
			mat[x][y] = new Node(matrix[x][y]);
			mat[x][y]->x = x;
			mat[x][y]->y = y;
		}
	}
	if (set_start_and_end)
	{
		mat[0][0]->value = 'S';
		mat[rows - 1][columns - 1]->value = 'E';
	}
	return mat;
}