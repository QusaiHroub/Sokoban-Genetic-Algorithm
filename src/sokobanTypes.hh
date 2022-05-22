#ifndef SOKOBAN_TYPES
#define SOKOBAN_TYPES

#include <vector>

using std::vector;
using std::pair;

enum eMaterial {
    WALL,
    EMPTY,
    BOX,
    BOX_IN_PLACE,
    VOID,
    PLAYER
};

enum eStatus {
    SUCCESS,
    FAIL
};

enum eInstruction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

typedef pair<int, int> Coords;
typedef vector<vector<eMaterial>> Grid;

#endif