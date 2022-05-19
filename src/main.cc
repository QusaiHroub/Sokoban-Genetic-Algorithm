#include <algorithm>
#include <iostream>

using std::sort;
using std::cout;

#include "sokobanGame.hh"
#include "sokobanTypes.hh"
#include "constants.hh"
#include "simTypes.hh"

int itr = 100; // This only for testing.
auto terminiateSignal() -> bool {
    return itr--; // TODO
}

auto fitness (Chromosome &gene) -> int {
    return lRand() % int(1e9 + 7); // TODO
}

int main() {
    SimGeneticAlgorithm geneticAlgorithm(
        fitness,
        terminiateSignal
    );

    Sokoban sokoban(example);

    geneticAlgorithm.train();

    Chromosome chromosome = geneticAlgorithm.getBest();

    for (auto &it: chromosome.getInstructionsList()) {
        cout << it << " ";
    }

    cout << "Done...\n";

    return 0;
}
