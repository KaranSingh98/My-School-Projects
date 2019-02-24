#include "MazeSolver.h"

using namespace std;

int main ()
{

  MazeSolver solver("input5.txt");

  if(solver.mazeIsReady())
  {
    solver.solveMaze();

    solver.printSolution();
  }
}
