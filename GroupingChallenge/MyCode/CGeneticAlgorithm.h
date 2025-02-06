#ifndef CGENETICALGORITHM_H
#define CGENETICALGORITHM_H

#include "CIndividual.h"
#include "GroupingEvaluator.h"
#include <vector>
#include <random>
#include "CResult.h"

namespace NGroupingChallenge
{
    class CGeneticAlgorithm
    {
    public:
        CGeneticAlgorithm(CGroupingEvaluator& c_evaluator);

        void vSetPopulationSize(int i_pop_size);
        void vSetCrossoverProbability(double d_cross_prob);
        void vSetMutationProbability(double d_mut_prob);
        void vSetMaxIterations(int i_max_iterations);

        void vRun();
        CResult cGetBestSolution();
    private:
        CGroupingEvaluator& c_evaluator;
        int i_pop_size;
        double d_cross_prob;
        double d_mut_prob;
        int i_max_iterations;
        std::mt19937 c_random_engine;

        std::vector<CIndividual> v_population;
        CResult c_best_individual;

        void vInitializePopulation();
        void vEvaluatePopulation();
        void vRunIteration();

        void vMutate(double d_mut_prob);
        void vCrossover(double d_cross_prob);


        const CIndividual& cSelectParent();
    };
}

#endif // CGENETICALGORITHM_H

