#include <algorithm>
#include <iostream>

using std::sort;
using std::cout;

#include "sokobanGame.hh"
#include "sokobanTypes.hh"
#include "constants.hh"
#include "simTypes.hh"
#include "geneticAlgorithmTypes.hh"

template<typename Chromosome>
class SokobanFitnessTerminiateSignalContainer : public FitnessTerminiateSignalContainer<Chromosome> {
    int itr = 100; // This only for testing.
public:
    auto terminiateSignal() -> bool {
        return itr--; // TODO
    }

    auto fitness (Chromosome &gene) -> int {
        return lRand() % int(1e9 + 7); // TODO
    }
};

int main() {
    SokobanFitnessTerminiateSignalContainer<Chromosome> *sokobanFitnessTerminiateSignalContainer = new SokobanFitnessTerminiateSignalContainer<Chromosome>();
    SimGeneticAlgorithm geneticAlgorithm(
        dynamic_cast<FitnessTerminiateSignalContainer<Chromosome> *>(sokobanFitnessTerminiateSignalContainer)
    );

    Sokoban sokoban(example);

    geneticAlgorithm.train();

    Chromosome chromosome = geneticAlgorithm.getBest();

    for (auto &it: chromosome.getInstructionsList()) {
        cout << it << " ";
    }

    cout << "Done...\n";

    delete sokobanFitnessTerminiateSignalContainer;

    return 0;
}
