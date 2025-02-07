# Point Clustering 🧬

This C ++ project, developed for university classes, addresses the problem of clustering points in an n-dimensional space using a genetic algorithm. The algorithm optimizes the assignment of points to clusters, aiming to minimize the intra-cluster distances.

---

## 💡 **Problem Description**

- **Input Data:**
  - A set of m points, each having n dimensions
  - A maximum number of k clusters that can be formed
  - The project uses a class `CGaussianGroupingEvaluatorFactory`, which enables the creation of problem instances using a Gaussian distribution

- **Representation of Individuals:**
  - Each individual is represented by a genotype, which is a vector of integers corresponding to the cluster assignment for each point. The fitness of an individual is evaluated based on the distances between points in the same group (minimizing intra-cluster distances).

- **Fitness Function:**
  - The goal of the algorithm is to cluster the points in such a way that the distances between points within each group are minimized, which is evaluated by the fitness function.

 ---
 
## 🧠 **Algorithm**
The project utilizes a **genetic algorithm** to solve the clustering problem. The algorithm works as follows:
1. **Initialization:** An initial population of potential solutions (cluster assignments) is randomly generated.
2. **Selection:** Solutions with better fitness (lower intra-cluster distances) are selected for reproduction.
3. **Crossover and Mutation:** New solutions are created by combining existing ones (crossover) and introducing random variations (mutation).
4. **Termination:** The algorithm terminates when a predefined number of generations is reached.

---
