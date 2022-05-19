#ifndef GENETIC_ALGORITHM_TYPES
#define GENETIC_ALGORITHM_TYPES

#include <vector>

using std::vector;
using std::pair;
using std::swap;

#include "types.hh"
#include "geneticAlogrithmUtils.hh"

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


typedef unsigned int usize;

template<typename Gene>
using Population = vector<pair<Gene, int>>;

#endif