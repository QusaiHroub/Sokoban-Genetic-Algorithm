# Sokoban-Genetic-Algorithm-Solver
Purpose
-------

The purpose of this project is to solve a Sokoban puzzle using genetic algorithm.

Build
-----
```
mkdir build
cd build
meson ..
ninja
```

Build Python boost
------------------
```
mkdir build
cd build
cmake ..
make
```

Note: You have to copy src/python/main.py into the same folder alongside with sokoban_boost.so to run the GUI.
