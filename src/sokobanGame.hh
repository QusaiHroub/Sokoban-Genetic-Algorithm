#ifndef SOKOBAN
#define SOKOBAN

#include <vector>
#include <unordered_map>
#include <iostream>

using std::cout;
using std::vector;
using std::unordered_map;
using std::pair;

#include "constants.hh"
#include "utils.hh"
#include "types.hh"
#include "sokobanTypes.hh"

class Sokoban {
    Coords playerCoords;
    Grid originBoard, board;

    int countBoxes(Coords boxCoords, eInstruction direction) {
        if (isBox(this->board[boxCoords.first][boxCoords.second])) {
            return countBoxes(getCoords(direction, boxCoords), direction) + 1;
        }

        return 1;
    }

    void moveBox(Coords boxCoords) {
        if (isVoid(originBoard[boxCoords.first][boxCoords.second])) {
            this->board[boxCoords.first][boxCoords.second] = BOX_IN_PLACE;
        } else {
            this->board[boxCoords.first][boxCoords.second] = BOX;
        }
    }

    void movePlayer(eInstruction direction) {
        if (isVoid(this->originBoard[this->playerCoords.first][this->playerCoords.second])) {
            this->board[this->playerCoords.first][this->playerCoords.second] = VOID;
        } else {
            this->board[this->playerCoords.first][this->playerCoords.second] = EMPTY;
        }

        playerCoords = getCoords(direction, playerCoords);
        this->board[this->playerCoords.first][this->playerCoords.second] = PLAYER;
    }

    void movePlayerAndBox(eInstruction direction) {
        Coords newPlayerCoords = getCoords(direction, playerCoords),
            newBoxCoords = getCoords(direction, newPlayerCoords),
            lastBlockCoords;
        int numberOfBoxes = 0;

        if (isWall(this->board[newBoxCoords.first][newBoxCoords.second])) {
            return;
        }

        if (isBox(this->board[newBoxCoords.first][newBoxCoords.second])) {
            numberOfBoxes = this->countBoxes(newBoxCoords, direction);
            lastBlockCoords = getCoords(direction, newPlayerCoords, numberOfBoxes);

            if (isTraversible(this->board[lastBlockCoords.first][lastBlockCoords.second])) {
                for (int i = 0; i < numberOfBoxes; ++i) {
                    this->moveBox(getCoords(direction, newBoxCoords, i));
                }

                this->movePlayer(direction);
            }

        } else {
            this->moveBox(newBoxCoords);
            this->movePlayer(direction);
        }
    }

    unordered_map<eInstruction, eMaterial> getAdj() {
    	return {
    	    {LEFT, this->board[playerCoords.first][playerCoords.second - 1]},
    	    {RIGHT, this->board[playerCoords.first][playerCoords.second + 1]},
    	    {UP, this->board[playerCoords.first - 1][playerCoords.second]},
    	    {DOWN, this->board[playerCoords.first + 1][playerCoords.second]}
    	};
    }

public:
    Sokoban(Grid &board) {
	this->board = board;
	this->originBoard = board;

	for (usize i = 0; i < this->board.size(); ++i) {
	    for (usize j = 0; j < this->board[i].size(); ++j) {
	    	if (this->board[i][j] == PLAYER) {
	    	   playerCoords.first = i;
	    	   playerCoords.second = j;

	    	   break;
	    	}
	    }
	}
    }


    Coords getPlayerCoods() {
        return playerCoords;
    }

    void move(eInstruction direction) {
        unordered_map<eInstruction, eMaterial> adj = getAdj();

        if (adj.find(direction) != adj.end()) {
            if (isBox(adj[direction])) {
                this->movePlayerAndBox(direction);
            } else if (isTraversible(adj[direction])) {
                this->movePlayer(direction);
            }
        }
    }

    void print() {
    	for (usize i = 0; i < this->board.size(); ++i) {
	    for (usize j = 0; j < this->board[i].size(); ++j) {
	    	switch (this->board[i][j]) {
	    	case WALL:
	    	    cout << "#";
		    break;
		case BOX_IN_PLACE:
		    cout << "*";
		    break;
		case VOID:
		    cout << ".";
		    break;
		case BOX:
		    cout << "$";
		    break;
		case PLAYER:
		    cout << "?";
		    break;
		case EMPTY:
		    cout << " ";
	    	}
	    }

	    cout << '\n';
	}
    }

    Grid getBoard () {
       return board;
    }
};

#endif