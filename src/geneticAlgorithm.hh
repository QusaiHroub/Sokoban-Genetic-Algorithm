#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include "geneticAlgorithmTypes.hh"

template<typename eInstructions, typename Gene>
class GeneticAlgorithm {
    const usize mPopulationSize;
    const double mMutRate;
    Population<Gene> mPopulation;
    FitnessTerminiateSignalContainer<Gene> *mFitnessTerminiateSignalContainer = nullptr;

    void InitPopulation (usize populationSize) {
        while (populationSize--) {
            Gene newGene = Gene();
            mPopulation.push_back({ newGene, mFitnessTerminiateSignalContainer->fitness(newGene) });
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
        double mut;

        for (usize i = 1; i < mPopulationSize; i += 2) {
            xoverResult = mPopulation[i].first.xover(mPopulation[i - 1].first);

			mut = (lRand() % 101) / 101.0;
            if (mut <= mMutRate) {
                xoverResult[lRand() & 1].mutation();
            }

            for (auto &gene: xoverResult) {
                mPopulation.push_back({gene, mFitnessTerminiateSignalContainer->fitness(gene)});
            }
        }
    }

public:
    GeneticAlgorithm(
        FitnessTerminiateSignalContainer<Gene> *fitnessTerminiateSignalContainer,
        usize populationSize = 100,
        double mutRate = 0.75
    ) :
    	mFitnessTerminiateSignalContainer(fitnessTerminiateSignalContainer),
        mPopulationSize(populationSize),
        mMutRate(mutRate) {

        InitPopulation(populationSize);
    }

    void train() {
        while (mFitnessTerminiateSignalContainer->terminiateSignal()) {
            selectNewParents();
            performXoverMutation();
        }
    }

    Gene getBest () {
    	return mPopulation.front().first;
    }
};

#endif