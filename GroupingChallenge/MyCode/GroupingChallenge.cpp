#include "CGeneticAlgorithm.h"
#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "Optimizer.h"

using namespace NGroupingChallenge;

int main()
{
	CGaussianGroupingEvaluatorFactory cFactory(5, 100, 5);//iNumberOfGroups, iNumberOfPoints, iNumberOfMultivariateGaussianDistributions

	cFactory.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0)
		.cAddDimension(-100, 100, 1.0, 1.0);

	CGroupingEvaluator* pc_evaluator = cFactory.pcCreateEvaluator(0);


	CGeneticAlgorithm c_ga(*pc_evaluator);
	c_ga.vSetPopulationSize(50);
	c_ga.vSetCrossoverProbability(0.7);
	c_ga.vSetMutationProbability(0.1);
	c_ga.vSetMaxIterations(100);

	c_ga.vRun();

	CResult c_best_solution = c_ga.cGetBestSolution();
	cout << "Best fitness: " << c_best_solution.dGetFitness() << endl;
	cout << "Best genotype: ";
	vector<int> gen = c_best_solution.vGetGenotype();
	for (size_t i = 0; i < gen.size(); i++)
	{
		cout << gen.at(i);
	}
	cout << endl;

	delete pc_evaluator;
	return 0;
}