#include "CResult.h"

namespace NGroupingChallenge {
    CResult::CResult() : v_genotype(), d_fitness(0.0), b_is_initialized(false) {}

    CResult::CResult(const vector<int>& genotype, double fitness, bool is_initialized)
        : v_genotype(genotype), d_fitness(fitness), b_is_initialized(is_initialized) {}


    vector<int> CResult::vGetGenotype() const {
        return v_genotype;
    }

    void CResult::vSetGenotype(const vector<int>& genotype) {
        v_genotype = genotype;
    }

    double CResult::dGetFitness() const {
        return d_fitness;
    }

    void CResult::vSetFitness(double fitness) {
        d_fitness = fitness;
    }

    bool CResult::bGetInitialized() {
        return b_is_initialized;
    }

    void CResult::vSetInitialized(bool is_init) {
        b_is_initialized = is_init;
    }

}

