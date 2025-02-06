#include "CIndividual.h"
#include <iostream>

namespace NGroupingChallenge
{


    CIndividual::CIndividual(vector<int> v_genotype, CGroupingEvaluator& c_evaluator)
        : v_genotype(v_genotype), c_evaluator(c_evaluator)
    {
        vUpdateFitness();
    }

    double CIndividual::dGetFitness() const
    {
        return d_fitness;
    }

    const vector<int>& CIndividual::vGetGenotype() const
    {
        return v_genotype;
    }


    void CIndividual::vMutate(double d_mut_prob, mt19937& c_random_engine)
    {
        uniform_real_distribution<double> c_probability_dist(0.0, 1.0);
        uniform_int_distribution<int> c_gene_dist(c_evaluator.iGetLowerBound(), c_evaluator.iGetUpperBound());

        for (int& gene : v_genotype)
        {
            if (c_probability_dist(c_random_engine) < d_mut_prob)
            {
                gene = c_gene_dist(c_random_engine);
            }
        }


        vUpdateFitness();

    }

    void CIndividual::vMutate2(double d_mut_prob, mt19937& c_random_engine) {
        uniform_real_distribution<double> c_probability_dist(0.0, 1.0);
        if (c_probability_dist(c_random_engine) < d_mut_prob)
        {
            uniform_int_distribution<size_t> c_cross_dist(1, v_genotype.size() - 1);
            size_t i_cross_point = c_cross_dist(c_random_engine);            
            std::reverse(v_genotype.begin() + i_cross_point, v_genotype.end());

        }
    }

    pair<CIndividual, CIndividual> CIndividual::cCrossOver(double d_cross_prob, const CIndividual& c_other, mt19937& c_random_engine) const
    {
        uniform_real_distribution<double> c_probability_dist(0.0, 1.0);
        if (c_probability_dist(c_random_engine) < d_cross_prob) {
            uniform_int_distribution<size_t> c_cross_dist(1, v_genotype.size() - 1);
            size_t i_cross_point = c_cross_dist(c_random_engine);

            vector<int> v_child1(v_genotype.begin(), v_genotype.begin() + i_cross_point);
            vector<int> v_child2(c_other.v_genotype.begin(), c_other.v_genotype.begin() + i_cross_point);

            v_child1.insert(v_child1.end(), c_other.v_genotype.begin() + i_cross_point, c_other.v_genotype.end());
            v_child2.insert(v_child2.end(), v_genotype.begin() + i_cross_point, v_genotype.end());

            return {
            CIndividual(v_child1, c_evaluator),
            CIndividual(v_child2, c_evaluator)
            };
        }
        else {
            return {
            CIndividual(v_genotype, c_evaluator),
            CIndividual(c_other.v_genotype, c_other.c_evaluator)
            };
        }
    } 
    
    void CIndividual::vUpdateFitness()
    {
        d_fitness = c_evaluator.dEvaluate(v_genotype);
        /*std::cout << "Genotype: ";
        for (int gene : v_genotype) {
            std::cout << gene << " ";
        }
        std::cout << " -> Fitness: " << d_fitness << std::endl;*/
    }

}

