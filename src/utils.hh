#ifndef UTILS
#define UTILS

using std::pair;

#include "constants.hh"
#include "sokobanTypes.hh"

bool isBox (eMaterial cell) {
    return cell == BOX || cell == BOX_IN_PLACE;
}

bool isBoxNotInPlace (eMaterial cell) {
	return cell == BOX;
}

bool isBoxInPlace (eMaterial cell) {
	return cell == BOX_IN_PLACE;
}

bool isEmpty (eMaterial cell) {
    return cell == EMPTY;
}

bool isWall (eMaterial cell) {
    return cell == WALL;
}

bool isVoid (eMaterial cell) {
    return cell == VOID || cell == BOX_IN_PLACE;
}

bool isPlayer (eMaterial cell) {
    return cell == PLAYER;
}

bool isTraversible (eMaterial cell) {
    return isVoid(cell) || isEmpty(cell);
}

Coords getCoords (eInstruction direction, Coords oldCordinations, int addition = 1) {
    switch (direction) {
        case LEFT:
            oldCordinations.second -= addition;

            return oldCordinations;
        case RIGHT:
            oldCordinations.second += addition;

            return oldCordinations;
        case UP:
            oldCordinations.first -= addition;

            return oldCordinations;
        case DOWN:
            oldCordinations.first += addition;

            return oldCordinations;
    }

    return oldCordinations;
}

#endif