#ifndef UTILS
#define UTILS

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using std::cin;
using std::cout;
using std::string;
using std::pair;
using std::vector;
using std::freopen;

#include "constants.hh"
#include "sokobanTypes.hh"
#include "simTypes.hh"

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

eMaterial decode (char ch) {
	switch (ch) {
	case '#':
		return WALL;
	case '*':
		return BOX_IN_PLACE;
	case '.':
		return VOID;
	case '$':
		return BOX;
	case '?':
		return PLAYER;
	case ' ': case '0':
		return EMPTY;
	}

	throw std::invalid_argument("");
}

Grid readBoard (string fileName) {
	Grid board;
	usize n;
	char ch;
	string path = "./../share/ai-project/puzzles/" + fileName;

	if (freopen(path.c_str(), "r", stdin)) {
		cin >> n;
		cin.ignore();

		while (n--) {
			board.push_back(vector<eMaterial>());

			while (true) {
				ch = getchar();

				if (ch == '\n') {
					break;
				}

				board.back().push_back(decode(ch));
			}
		}
	} else {
		cout << "Error: Can not read file at path: " << path << '\n';
	}

	return board;
}

string decodeIns(eInstruction ins) {
	switch (ins) {
	case LEFT:
		return "left";
	case RIGHT:
		return "right";
	case UP:
		return "up";
	case DOWN:
		return "down";
	default:
		throw std::invalid_argument("invalid valie for ins");
	}
}

void printChromosome (Chromosome &chromosome) {
	chromosome.reset();
	while (chromosome.hasNext()) {
		cout << decodeIns(chromosome.getNext()) << ' ';
	}
	cout << '\n';
}

#endif