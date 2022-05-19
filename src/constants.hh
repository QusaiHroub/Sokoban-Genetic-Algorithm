#ifndef CONSTATNS
#define CONSTATNS

#include <vector>

using std::vector;

#include "sokobanTypes.hh"
#include "types.hh"

vector<vector<eMaterial>> example = {
  {EMPTY, EMPTY, WALL, WALL, WALL, WALL, WALL, EMPTY},
  {WALL, WALL, WALL, EMPTY, EMPTY, EMPTY, WALL, EMPTY},
  {WALL, VOID, PLAYER, BOX, EMPTY, EMPTY, WALL, EMPTY},
  {WALL, WALL, WALL, EMPTY, BOX, VOID, WALL, EMPTY},
  {WALL, VOID, WALL, WALL, BOX, EMPTY, WALL, EMPTY},
  {WALL, EMPTY, WALL, EMPTY, VOID, EMPTY, WALL, WALL},
  {WALL, BOX, EMPTY, BOX_IN_PLACE, BOX, BOX, VOID, WALL},
  {WALL, EMPTY, EMPTY, EMPTY, VOID, EMPTY, EMPTY, WALL},
  {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
};

struct Properties {
    const static usize geneLength = 250;
    const static usize eInsturctionsLength = 4;
    const static usize pivot = 57;
};

#endif