#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
    // your code starts here
    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    Minisat::vec<Minisat::Lit> literals(numVar + 1);
    for (unsigned int i = 0; i < numVar + 1; ++i)
    {
        literals[i] = Minisat::mkLit(solver->newVar());
    }
	for (std::vector<std::vector<int>>::const_iterator it = cnf.begin(); it != cnf.end(); ++it)
	{
		std::vector<int> clause = *it;
        Minisat::vec<Minisat::Lit> lters;
		for (std::vector<int>::iterator itt = clause.begin(); itt != clause.end(); ++itt)
		{
            if (*itt < 0)
            {
                lters.push(~literals[-*itt]);
            }
            else
            {
                lters.push(literals[*itt]);
            }
		}
        solver->addClause(lters);
	}
    return solver->solve();
}
