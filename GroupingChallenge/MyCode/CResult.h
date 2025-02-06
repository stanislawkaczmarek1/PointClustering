#ifndef RESULT_H
#define RESULT_H

#include <vector>

using namespace std;

namespace NGroupingChallenge {
    
    class CResult 
    {
    public:
        CResult();

        CResult(const vector<int>& genotype, double fitness, bool is_initialized);

        vector<int> vGetGenotype() const;

        void vSetGenotype(const vector<int>& genotype);

        double dGetFitness() const;

        void vSetFitness(double fitness);

        bool bGetInitialized();

        void vSetInitialized(bool is_init);
    private:
        vector<int> v_genotype;
        double d_fitness;
        bool b_is_initialized;

    };



}
#endif // RESULT_H