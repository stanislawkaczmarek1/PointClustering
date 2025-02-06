#include "CGeneticAlgorithm.h"
#include <iostream>
#include "Config.h"

namespace NGroupingChallenge
{
    CGeneticAlgorithm::CGeneticAlgorithm(CGroupingEvaluator& c_evaluator)
        : c_evaluator(c_evaluator),
        i_pop_size(NGroupingChallenge::DEFAULT_POPULATION_SIZE),
        d_cross_prob(NGroupingChallenge::DEFAULT_CROSSOVER_PROBABILITY),
        d_mut_prob(NGroupingChallenge::DEFAULT_MUTATION_PROBABILITY),
        i_max_iterations(NGroupingChallenge::DEFAULT_MAX_ITERATIONS),
        c_random_engine(random_device{}()), 
        c_best_individual(CResult())
    {
    }

    void CGeneticAlgorithm::vRun()
    {
        c_best_individual = CResult();
        vInitializePopulation();

        for (int i = 0; i < i_max_iterations; i++)
        {
            vRunIteration();
            cout << "Iteration " << i << ": Best fitness = " << c_best_individual.dGetFitness() << endl;
        }
    }

    CResult CGeneticAlgorithm::cGetBestSolution() 
    {
        return c_best_individual;
    }

    void CGeneticAlgorithm::vInitializePopulation()
    {
        uniform_int_distribution<int> c_gene_dist(c_evaluator.iGetLowerBound(), c_evaluator.iGetUpperBound());

        for (int i = 0; i < i_pop_size; i++)
        {
            vector<int> v_genotype(c_evaluator.iGetNumberOfPoints());
            for (int& gene : v_genotype)
            {
                gene = c_gene_dist(c_random_engine);
            }

            v_population.emplace_back(v_genotype, c_evaluator);
        }
        
    }

    void CGeneticAlgorithm::vEvaluatePopulation()
    {
        CIndividual c_new_pop_best_individual = *min_element(v_population.begin(), v_population.end(),
            [](const CIndividual& individual1, const CIndividual& individual2) {
                return individual1.dGetFitness() < individual2.dGetFitness();
            });


        if (!c_best_individual.bGetInitialized()) {
            c_best_individual = CResult(c_new_pop_best_individual.vGetGenotype(), c_new_pop_best_individual.dGetFitness(), true);
        }
        else if (c_best_individual.dGetFitness() > c_new_pop_best_individual.dGetFitness()) {
            c_best_individual.vSetGenotype(c_new_pop_best_individual.vGetGenotype());
            c_best_individual.vSetFitness(c_new_pop_best_individual.dGetFitness());
        }

    }


    void CGeneticAlgorithm::vRunIteration()
    {
        vCrossover(d_cross_prob);
        vEvaluatePopulation();
        vMutate(d_mut_prob);
        vEvaluatePopulation();

    }


    void CGeneticAlgorithm::vMutate(double d_mut_prob) {
        for (CIndividual& cIndividual : v_population)
        {   
            cIndividual.vMutate(d_mut_prob, c_random_engine);
            //cIndividual.vMutate2(d_mut_prob, c_random_engine);
        }
    }

    void CGeneticAlgorithm::vCrossover(double d_cross_prob) {
        vector<CIndividual> v_next_population;
        while (v_next_population.size() < v_population.size())
        {
            const CIndividual& c_parent1 = cSelectParent();
            const CIndividual& c_parent2 = cSelectParent();


            auto c_children = c_parent1.cCrossOver(d_cross_prob, c_parent2, c_random_engine);
            v_next_population.push_back(c_children.first);
            if (v_next_population.size() < v_population.size())
            {
                v_next_population.push_back(c_children.second);
            }

        }
        v_population = move(v_next_population);
    }


    const CIndividual& CGeneticAlgorithm::cSelectParent()
    {
        uniform_int_distribution<size_t> c_index_dist(0, v_population.size() - 1);
        const CIndividual& c_candidate1 = v_population[c_index_dist(c_random_engine)];
        const CIndividual& c_candidate2 = v_population[c_index_dist(c_random_engine)];
        return (c_candidate1.dGetFitness() < c_candidate2.dGetFitness()) ? c_candidate1 : c_candidate2;
    }


    void CGeneticAlgorithm::vSetPopulationSize(int i_pop_size)
    {   
        if (i_pop_size > 0) {
            this->i_pop_size = i_pop_size;
        }
        
    }

    void CGeneticAlgorithm::vSetCrossoverProbability(double d_cross_prob)
    {
        if (d_cross_prob > 0 && d_cross_prob < 1) {
            this->d_cross_prob = d_cross_prob;
        }
        
    }

    void CGeneticAlgorithm::vSetMutationProbability(double d_mut_prob)
    {   
        if (d_mut_prob > 0 && d_mut_prob < 1) {
            this->d_mut_prob = d_mut_prob;
        }
    }

    void CGeneticAlgorithm::vSetMaxIterations(int i_max_iterations)
    {   
        if (i_max_iterations > 0) {
            this->i_max_iterations = i_max_iterations;
        }
    }

}
