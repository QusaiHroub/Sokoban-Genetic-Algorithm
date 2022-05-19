#include <algorithm>
#include <iostream>
#include <set>

using std::sort;
using std::cout;
using std::set;

#include "sokobanGame.hh"
#include "sokobanTypes.hh"
#include "constants.hh"
#include "simTypes.hh"
#include "geneticAlgorithmTypes.hh"

template<typename Chromosome>
class SokobanFitnessTerminiateSignalContainer : public FitnessTerminiateSignalContainer<Chromosome> {
    int itr = 2000; // This only for testing.
public:
    auto terminiateSignal () -> bool {
        return itr--; // TODO
    }

    auto fitness (Chromosome &chromosome) -> int {
        Sokoban sokoban(example);
        int result = 0;

        while (chromosome.hasNext() && !sokoban.isEnd()) {
            sokoban.move(chromosome.getNext());
        }

        return result + chromosome.getNumberOfUnused() + (sokoban.numberOfStuckBoxes() * -2000) + (sokoban.numberOfBoxesNotInPlace() * -10) +
                ((sokoban.numberOfBoxes() - sokoban.numberOfBoxesNotInPlace()) * 5);
    }
};

int main() {
    SokobanFitnessTerminiateSignalContainer<Chromosome> *sokobanFitnessTerminiateSignalContainer = new SokobanFitnessTerminiateSignalContainer<Chromosome>();
    SimGeneticAlgorithm geneticAlgorithm(
        dynamic_cast<FitnessTerminiateSignalContainer<Chromosome> *>(sokobanFitnessTerminiateSignalContainer),
        200
    );

    Sokoban sokoban(example);

    cout << sokoban.numberOfBoxes() << ' ' << sokoban.numberOfBoxesNotInPlace() << '\n';

    geneticAlgorithm.train();

    Chromosome chromosome = geneticAlgorithm.getBest();

    for (auto &it: chromosome.getInstructionsList()) {
        cout << it << " ";
    }

    sokoban.print();
    chromosome.reset();
    while (chromosome.hasNext() && !sokoban.isEnd()) {
        sokoban.move(chromosome.getNext());
    }

    if (sokoban.isEnd()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    sokoban.print();
    cout << sokoban.numberOfStuckBoxes() << '\n';
    set<Coords> c = sokoban.getCoordsForStuckBoxes();
    for (auto it: c) {
        cout << it.first << ' ' << it.second << '\n';
    }

    cout << "Done...\n";

    delete sokobanFitnessTerminiateSignalContainer;

    return 0;
}
