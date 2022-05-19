#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include "geneticAlgorithmTypes.hh"

template<typename eInstructions, typename Gene>
class GeneticAlgorithm {
    const usize mPopulationSize;
    Population<Gene> mPopulation;
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
        Population<Gene> newParents;
        sort(mPopulation.begin(), mPopulation.end(), [](pair<Gene, int> &a, pair<Gene, int> &b) -> bool {
            return a.second > b.second;
        });

        for (usize i = 0; i < populationSize; ++i) {
            newParents.push_back(mPopulation[i]);
        }

        mPopulation = newParents;
    }

    void performXoverMutation () {
        vector<Gene> xoverResult;

        for (usize i = 1; i < mPopulationSize; i += 2) {
            xoverResult = mPopulation[i].first.xover(mPopulation[i - 1].first);

            if (lRand() % 101 <= 17) {
                xoverResult[lRand() & 1].mutation();
            }

            for (auto &gene: xoverResult) {
                mPopulation.push_back({gene, mEvaluator(gene)});
            }
        }
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

    Gene getBest () {
        return mPopulation.front().first;
    }
};

#endif