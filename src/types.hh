#ifndef TYPES
#define TYPES

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
typedef unsigned int usize;

#endif