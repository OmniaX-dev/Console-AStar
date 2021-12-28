## Console A-Star pathfinding in C++

This is a simple A-Star implementation written in C++ as a console application.
   
It has the possibility to enable/disable diagonal movement, and it also has three different types of heuristic-distance:
* Manhattan
* Euclidean
* Diagonal
   
These can be changed by using the `set_heuristic_distance_type(...)` method of the **Pathfinding** class, by passing either of this constants: *MANHATTAN*, *EUCLIDEAN* or *DIAGONAL*.

The start matrix
![](SCREENSHOT/astar_default_matrix.png)
   
The path with diagonal movement enabled
![](SCREENSHOT/astar_path_diag.png)
   
The path with diagonal movement disabled
![](SCREENSHOT/astar_path_nodiag.png)
   
* White squares are walls
* Green square is the start
* Red square is the end
* Purple squares are the path
   
To compile this project, open a terminal (or command prompt) in the project's directory, and run:
```
g++ *.cpp -o a-star
```
This will create the executable **a-star** (or **a-star.exe** in Windows) inside the project's directory.
   
This project is powered by the beautiful TermColor header-only library, found at: https://github.com/ikalnytskyi/termcolor