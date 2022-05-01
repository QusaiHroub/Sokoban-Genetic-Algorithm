#include <bits/stdc++.h>

using namespace std;

typedef unsigned int usize;

unsigned long long lRand() {
	std::random_device rd;
	std::mt19937_64 eng(rd());
	std::uniform_int_distribution<unsigned long long> distr;

	return distr(eng);
}

enum eInstructions {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Properties {
    const static usize geneLength = 100;
    const static usize eInsturctionsLength = 4;
    const static usize pivot = 57;
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
        usize geneLength = mProperties.geneLength;
        for (usize i = 0; i < geneLength; ++i) {
            mList.push_back(static_cast<eInstructions>(lRand() % mProperties.eInsturctionsLength));
        }
    }

    Gene(vector<eInstructions> &instructions) : mList(instructions) {

    }

    vector<eInstructions> getInstructionsList () {
        return mList;
    }

    vector<Gene> xover (Gene &parent) {
        vector<eInstructions> parentIns = parent.getInstructionsList();
        vector<Gene> result;
        const int pivot = mProperties.pivot;

        vector<eInstructions> childIns = vector<eInstructions>(
            parentIns.begin(),
            parentIns.begin() + pivot
        );
        childIns.insert(childIns.end(), this->mList.begin() + pivot, this->mList.end());
        result.push_back(Gene(childIns));

        childIns = vector<eInstructions>(
            this->mList.begin(),
            this->mList.begin() + pivot
        );
        childIns.insert(childIns.end(), parentIns.begin() + pivot, parentIns.end());
        result.push_back(Gene(childIns));

        return result;
    }

    void mutation () {
        int index1 = lRand() % mList.size(),
            index2 = lRand() % mList.size();

        swap(mList[index1], mList[index2]);
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
    cout << mPopulation.front().second << endl;
        return mPopulation.front().first;
    }
};

typedef Gene<eInstructions, Properties> Chromosome;

int itr = 100; // This only for testing.
auto terminiateSignal() -> bool {
    return itr--; // TODO
}

auto fitness (Chromosome &gene) -> int {
    return lRand() % int(1e9 + 7); // TODO
}

int main() {
    GeneticAlgorithm<eInstructions, Chromosome> geneticAlgorithm(
        fitness,
        terminiateSignal
    );

    geneticAlgorithm.train();

    Chromosome chromosome = geneticAlgorithm.getBest();

    for (auto &it: chromosome.getInstructionsList()) {
        cout << it << " ";
    }

    cout << "Done..." << endl;

    return 0;
}
