#ifndef SIM_TYPES
#define SIM_TYPES

#include "sokobanTypes.hh"
#include "constants.hh"
#include "geneticAlgorithmTypes.hh"
#include "geneticAlgorithm.hh"

typedef Gene<eInstruction, Properties> Chromosome;
typedef GeneticAlgorithm<eInstruction, Chromosome> SimGeneticAlgorithm;

#endif