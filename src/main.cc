#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <stdexcept>

using std::sort;
using std::cout;
using std::set;
using std::string;
using std::invalid_argument;

#include "sokobanGame.hh"
#include "sokobanTypes.hh"
#include "constants.hh"
#include "simTypes.hh"
#include "geneticAlgorithmTypes.hh"
#include "utils.hh"

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

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        throw invalid_argument("Error you should provide level name");
    }

    Grid board = readBoard(argv[1]);
    Sokoban sokoban(board);
    sokoban.print();

    SokobanFitnessTerminiateSignalContainer<Chromosome> *sokobanFitnessTerminiateSignalContainer = new SokobanFitnessTerminiateSignalContainer<Chromosome>(board);
    SimGeneticAlgorithm geneticAlgorithm(
        dynamic_cast<FitnessTerminiateSignalContainer<Chromosome> *>(sokobanFitnessTerminiateSignalContainer),
        200
    );

    geneticAlgorithm.train();

    Chromosome chromosome = geneticAlgorithm.getBest();
    printChromosome(chromosome);

    chromosome.reset();
    while (chromosome.hasNext() && !sokoban.isEnd()) {
        sokoban.move(chromosome.getNext());
    }

    cout << "End the game: ";
    if (sokoban.isEnd()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    sokoban.print();
    cout << "Number of Boxes that are not In Place: " << sokoban.numberOfBoxesNotInPlace() << '\n';
    cout << "Number of Boxes that are stuck: " << sokoban.numberOfStuckBoxes() << '\n';
    cout << "Total Boxes in the game: " << sokoban.numberOfBoxes() << '\n';
    set<Coords> c = sokoban.getCoordsForStuckBoxes();
    for (auto it: c) {
        cout << it.first << ' ' << it.second << '\n';
    }

    cout << "Done...\n";

    delete sokobanFitnessTerminiateSignalContainer;

    return 0;
}
