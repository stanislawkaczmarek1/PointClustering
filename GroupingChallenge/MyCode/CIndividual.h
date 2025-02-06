#ifndef CINDIVIDUAL_H
#define CINDIVIDUAL_H

#include "GroupingEvaluator.h"
#include <vector>
#include <random>
#include <utility>

namespace NGroupingChallenge
{
    class CIndividual
    {
    public:
        CIndividual(std::vector<int> v_genotype, CGroupingEvaluator& c_evaluator);

        double dGetFitness() const;
        const std::vector<int>& vGetGenotype() const;

        void vMutate(double d_mut_prob, mt19937& c_random_engine);
        void vMutate2(double d_mut_prob, mt19937& c_random_engine);
        pair<CIndividual, CIndividual> cCrossOver(double d_cross_prob, const CIndividual& c_other, mt19937& c_random_engine) const;
    private:
        std::vector<int> v_genotype;
        double d_fitness;
        CGroupingEvaluator& c_evaluator;
        std::mt19937 c_random_engine;

        void vUpdateFitness();
    };
}

#endif // CINDIVIDUAL_H


