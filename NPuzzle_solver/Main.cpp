
#include "NPuzzleState.h"
#include "AStarNode.h"
#include "AStarSolver.h"
#include <iostream>



#define SUCEESS 0;
#define FAIL 1;



int main(int argc, char* argv[])
{
	

	NPuzzleState startState(NPuzzleState::StartState);
	NPuzzleState goalState(NPuzzleState::GoalState);

	AStarNode<NPuzzleState>* start = AStarNode<NPuzzleState>::CreateNode();
	AStarNode<NPuzzleState>* goal = AStarNode<NPuzzleState>::CreateNode();

	start->SetState(startState);
	goal->SetState(goalState);

	AStarSolver<NPuzzleState> aStar(start, goal);

	aStar.Solve();

	std::cout << "Steps: " << aStar.GetSteps() << std::endl;
	std::cin.get();
	return SUCEESS;
}