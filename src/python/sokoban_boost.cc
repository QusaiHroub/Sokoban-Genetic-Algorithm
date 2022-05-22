#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <stdexcept>
#include <boost/python.hpp>

using std::sort;
using std::cout;
using std::set;
using std::string;
using std::invalid_argument;

#include "../sokobanTypes.hh"
#include "../constants.hh"
#include "../simTypes.hh"
#include "../geneticAlgorithmTypes.hh"
#include "../utils.hh"
#include "../types.hh"
#include "../sokobanGame.hh"


class SokobanBoost {
    Grid board;
    Sokoban sokoban;
    Chromosome chromosome;
    vector<string> str;

    template<typename Chromosome>
    class SokobanFitnessTerminiateSignalContainer : public FitnessTerminiateSignalContainer<Chromosome> {
        int itr = 2000; // This only for testing.
        Grid mBoard;
    public:
        SokobanFitnessTerminiateSignalContainer(Grid board) : mBoard(board) {}

        auto terminiateSignal () -> bool {
            return itr--; // TODO
        }

        auto fitness (Chromosome &chromosome) -> int {
            Sokoban sokoban(mBoard);
            int result = 0;

            while (chromosome.hasNext() && !sokoban.isEnd()) {
                sokoban.move(chromosome.getNext());
            }

            result = chromosome.getNumberOfUnused() + (sokoban.numberOfStuckBoxes() * -2000) + (sokoban.numberOfBoxesNotInPlace() * -10) +
                    ((sokoban.numberOfBoxes() - sokoban.numberOfBoxesNotInPlace()) * 5);

            return result;
        }
    };

public:
    SokobanBoost() {
        cout << "read board\n";
        board = readBoard("easy.txt");
        cout << "done ... \n";
        sokoban = Sokoban(board);
        this->str = this->sokoban.str();
        SokobanFitnessTerminiateSignalContainer<Chromosome> *sokobanFitnessTerminiateSignalContainer = new SokobanFitnessTerminiateSignalContainer<Chromosome>(board);
        SimGeneticAlgorithm geneticAlgorithm(
            dynamic_cast<FitnessTerminiateSignalContainer<Chromosome> *>(sokobanFitnessTerminiateSignalContainer),
            200
        );

        cout << "training ...\n";
        geneticAlgorithm.train();

        chromosome = geneticAlgorithm.getBest();
        chromosome.reset();

        cout << "Done...\n";

        delete sokobanFitnessTerminiateSignalContainer;
    }

    void move () {
        if (chromosome.hasNext() && !sokoban.isEnd()) {
            sokoban.move(chromosome.getNext());
        }

        this->str = this->sokoban.str();
    }

    bool isTheGameEnd () {
        return this->sokoban.isEnd();
    }

    char getAt(int i, int j) {
        return this->str[i][j];
    }
};

BOOST_PYTHON_MODULE(sokoban_boost)
{
    using namespace boost::python;

    auto move = static_cast<void (SokobanBoost::*)()>(&SokobanBoost::move);
    auto isTheGameEnd = static_cast<bool (SokobanBoost::*)()>(&SokobanBoost::isTheGameEnd);
    auto getAt = static_cast<char (SokobanBoost::*)(int, int)>(&SokobanBoost::getAt);

    class_<SokobanBoost>("Sokoban")
        .def("move", &SokobanBoost::move)
        .def("is_end", &SokobanBoost::isTheGameEnd)
        .def("get_at", &SokobanBoost::getAt)
    ;
}
