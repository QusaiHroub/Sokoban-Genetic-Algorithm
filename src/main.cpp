#include <bits/stdc++.h>

using namespace std;

typedef unsigned int usize;

enum eInstructions {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Properties {
    const usize geneLenght = 100;
    const usize eInsturctionsLength = 4;
};

template <typename eInstructions>
class VGene {
public:
};

template <typename eInstructions, typename Properties>
class Gene: public VGene<eInstructions> {
    vector<eInstructions> mList;
    Properties mProperties;

public:
    Gene() {
        usize geneLenght = mProperties.geneLenght;
        for (usize i = 0; i < geneLenght; ++i) {
            mList.push_back(static_cast<eInstructions>(rand() % mProperties.eInsturctionsLength));
        }
    }
};

template<typename eInstructions, typename Gene>
class GeneticAlgorithm {
    const usize mPopulationSize;
    vector<pair<Gene, int>> mPopulation;
    auto (*mEvaluator)(Gene &gene) -> int;
    auto (*mTerminiationCriteriaNotSatisfied)() -> bool;

    void InitPopulation (usize populationSize) {
        while (populationSize--) {
            Gene newGene = Gene();
            mPopulation.push_back({ newGene, mEvaluator(newGene) });
        }
    }

    void selectNewParents () {
        usize populationSize = mPopulationSize;
        vector<pair<Gene, int>> newParents;
        sort(mPopulation.begin(), mPopulation.end(), [](pair<Gene, int> &a, pair<Gene, int> &b) -> bool {
            return a.second > b.second;
        });

        for (int i = 0; i < populationSize; ++i) {
            newParents.push_back(mPopulation[i]);
        }

        mPopulation = newParents();
    }

    void performXoverMutation () {

    }

public:
    GeneticAlgorithm(
        auto (*evaluator)(Gene &gene) -> int,
        auto (*terminiationCriteriaNotSatisfied)() -> bool,
        usize populationSize = 100
    ) :
        mEvaluator(evaluator),
        mTerminiationCriteriaNotSatisfied(terminiationCriteriaNotSatisfied),
        mPopulationSize(populationSize) {

        InitPopulation(populationSize);
    }

    void train() {
        while (mTerminiationCriteriaNotSatisfied()) {
            selectNewParents();
            performXoverMutation();
        }
    }
};

int main() {
    typedef Gene<eInstructions, Properties> Gene;
    GeneticAlgorithm<eInstructions, Gene> geneticAlgorithm(
        [](Gene &gene) -> int {
            return 0;
        },
        []() -> bool {
            return true;
        }
    );

    cout << "Done..." << endl;

    return 0;
}
