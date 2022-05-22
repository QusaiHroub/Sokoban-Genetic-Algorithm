#ifndef SOKOBAN
#define SOKOBAN

#include <vector>
#include <unordered_map>
#include <iostream>
#include <set>

using std::cout;
using std::vector;
using std::unordered_map;
using std::pair;
using std::set;

#include "constants.hh"
#include "utils.hh"
#include "types.hh"
#include "sokobanTypes.hh"

class Sokoban {
    Coords playerCoords;
    Grid originBoard, board;
    usize boxesNotInPlace = 0, boxes = 0;
    bool player = false;
    set<Coords> stuckBoxes;

    unordered_map<eInstruction, eMaterial> getAdj(Coords coords) {
    	return {
    	    {LEFT, this->board[coords.first][coords.second - 1]},
    	    {RIGHT, this->board[coords.first][coords.second + 1]},
    	    {UP, this->board[coords.first - 1][coords.second]},
    	    {DOWN, this->board[coords.first + 1][coords.second]}
    	};
    }

    int countBoxes(Coords boxCoords, eInstruction direction) {
        if (isBox(this->board[boxCoords.first][boxCoords.second])) {
            return countBoxes(getCoords(direction, boxCoords), direction) + 1;
        }

        return 1;
    }

    void moveBox(Coords boxCoords, bool wasNotInPlace = false) {
        if (isVoid(originBoard[boxCoords.first][boxCoords.second])) {
            this->board[boxCoords.first][boxCoords.second] = BOX_IN_PLACE;

            if (wasNotInPlace) {
            	--boxesNotInPlace;
            }
        } else {
            this->board[boxCoords.first][boxCoords.second] = BOX;

            if (!wasNotInPlace) {
            	++boxesNotInPlace;
            }
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
            lastBlockCoords,
            temp;
        int numberOfBoxes = 0;

        if (isWall(this->board[newBoxCoords.first][newBoxCoords.second])) {
            return;
        }

        if (isBox(this->board[newBoxCoords.first][newBoxCoords.second])) {
            numberOfBoxes = this->countBoxes(newBoxCoords, direction);
            lastBlockCoords = getCoords(direction, newPlayerCoords, numberOfBoxes);

            if (isTraversible(this->board[lastBlockCoords.first][lastBlockCoords.second])) {
                for (int i = 0; i < numberOfBoxes; ++i) {
                	temp = getCoords(direction, newPlayerCoords, i);
                    this->moveBox(
                    	getCoords(direction, newBoxCoords, i),
                    	isBoxNotInPlace(this->board[temp.first][temp.second])
                    );
                }

                this->movePlayer(direction);

                unordered_map<eInstruction, eMaterial> adj = getAdj(lastBlockCoords);

		        if (
					!isVoid(this->originBoard[lastBlockCoords.first][lastBlockCoords.second]) &&
					(isWall(adj[LEFT]) || isWall(adj[RIGHT])) &&
					(isWall(adj[UP]) || isWall(adj[DOWN]))
				) {
				    stuckBoxes.insert(lastBlockCoords);
				}
            }
        } else {
            this->moveBox(
            	newBoxCoords,
            	isBoxNotInPlace(this->board[newPlayerCoords.first][newPlayerCoords.second])
            );
            this->movePlayer(direction);
            unordered_map<eInstruction, eMaterial> adj = getAdj(newBoxCoords);

		    if (
		    	!isVoid(this->originBoard[newBoxCoords.first][newBoxCoords.second]) &&
		    	(isWall(adj[LEFT]) || isWall(adj[RIGHT])) &&
		    	(isWall(adj[UP]) || isWall(adj[DOWN]))
		    ) {
		        stuckBoxes.insert(newBoxCoords);
		    }
        }
    }

public:
	Sokoban() {}

    Sokoban(Grid &board) {
		this->board = board;
		this->originBoard = board;

		for (usize i = 0; i < this->board.size(); ++i) {
			for (usize j = 0; j < this->board[i].size(); ++j) {
				if (!player && isPlayer(this->board[i][j])) {
				   playerCoords.first = i;
				   playerCoords.second = j;

				   player = true;
				}

				if (isBoxNotInPlace(this->board[i][j])) {
					++boxesNotInPlace;
				}

				if (isBox(this->board[i][j])) {
					++boxes;
				}
			}
		}
    }


    Coords getPlayerCoods() {
        return playerCoords;
    }

    void move(eInstruction direction) {
        unordered_map<eInstruction, eMaterial> adj = getAdj(playerCoords);

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

    vector<string> str() {
    	vector<string> result;

    	for (usize i = 0; i < this->board.size(); ++i) {
    		result.push_back(string());

			for (usize j = 0; j < this->board[i].size(); ++j) {
				switch (this->board[i][j]) {
					case WALL:
						result.back().push_back('#');
						break;
					case BOX_IN_PLACE:
						result.back().push_back('*');
						break;
					case VOID:
						result.back().push_back('.');
						break;
					case BOX:
						result.back().push_back('$');
						break;
					case PLAYER:
						result.back().push_back('?');
						break;
					case EMPTY:
						result.back().push_back(' ');
					}
			}
		}

    	return result;
    }

    Grid getBoard () {
       return board;
    }

    bool isEnd () {
    	return boxesNotInPlace == 0;
    }

    usize numberOfBoxes () {
    	return boxes;
    }

    usize numberOfBoxesNotInPlace () {
    	return boxesNotInPlace;
    }

    usize numberOfStuckBoxes () {
    	return stuckBoxes.size();
    }

    set<Coords> getCoordsForStuckBoxes () {
    	return stuckBoxes;
    }
};

#endif