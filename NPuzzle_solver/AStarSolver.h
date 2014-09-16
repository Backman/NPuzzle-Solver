#pragma once

#include "AStarNode.h"
#include <queue>
#include <algorithm>
#include <vector>

template<class State>
class AStarSolver
{
public:
	typedef AStarNode<State> Node;
	typedef AStarNode<State>* NodePtr;

	AStarSolver() :
		_start(nullptr), _goal(nullptr)
	{
	}

	AStarSolver(NodePtr start, NodePtr goal) :
		_start(start), _goal(goal)
	{ }

	~AStarSolver()
	{
		DeleteAllNodes();
	}

	void Expand(std::vector<NodePtr>* expandList, NodePtr node)
	{
		node->GetState().Expand(expandList, &node->GetState());
	}

	void Solve()
	{
		if (!_start || !_goal) {
			return;
		}
		NodePtr current = nullptr;
		_steps = 0;
		_openList.push_back(_start);
		while (!_openList.empty()) {
			++_steps;
			current = _openList.back();
			_openList.pop_back();

			if (*current == *_goal) {
				_goal->SetParent(&current->GetParent());
				_goal->SetCost(current->GetCost());

				return;
			}
			
			_expandList.clear();
			Expand(&_expandList, current);

			for (int i = 0; i < _expandList.size(); ++i) {
				NodePtr child = _expandList[i];
				float newCost = current->GetCost() + current->GetCostTo(child);

				std::vector<NodePtr>::iterator openListIt;
				for (openListIt = _openList.begin(); openListIt != _openList.end(); ++openListIt) {
					if (child == (*openListIt)) {
						break;
					}
				}

				if (openListIt != _openList.end()) {
					if ((*openListIt)->GetCost() <= newCost) {
						DeleteNode(child);
						continue;
					}
				}

				std::vector<NodePtr>::iterator closedListIt;
				for (closedListIt = _closedList.begin(); closedListIt != _closedList.end(); ++closedListIt) {
					if (child == (*closedListIt)) {
						break;
					}
				}

				if (closedListIt != _closedList.end()){
					if ((*closedListIt)->GetCost() <= newCost) {
						DeleteNode(child);
						continue;
					}
				}

				if (openListIt != _openList.end()) {
					DeleteNode((*openListIt));
					_openList.erase(openListIt);

					std::sort(_openList.begin(), _openList.end(), comparer);
				}

				if (closedListIt != _closedList.end()) {
					DeleteNode((*closedListIt));
					_closedList.erase(closedListIt);
					
				}

				child->SetParent(current);
				child->SetCost(newCost);
				child->SetHeuristic(child->EstimatedDistanceTo(_goal));
				child->UpdateTotalCost();

				_openList.push_back(child);

				std::sort(_openList.begin(), _openList.end(), comparer);
			}

			_closedList.push_back(current);
		}
	}

	bool NodeCompare(const Node& x, const Node& y)
	{
		return x.GetTotalCost() > y.GetTotalCost();
	}

	struct NodeComparer
	{
		bool operator()(const Node& a, const Node& b) const
		{
			return a.GetTotalCost() > b.GetTotalCost();
		}
		bool operator()(const Node* a, const Node* b) const
		{
			return a->GetTotalCost() > b->GetTotalCost();
		}
	} comparer;

	void DeleteSolverNodes() {
		DeleteNode(_start);
		DeleteNode(_goal);
	}

	void DeleteAllNodes() 
	{
		while (!_openList.empty()) {
			DeleteNode(_openList.back());
			_openList.pop_back();
		}

		while (!_closedList.empty()) {
			DeleteNode(_closedList.back());
			_closedList.pop_back();
		}

		DeleteNode(_start);
		DeleteNode(_goal);
	}

	void DeleteNode(NodePtr node) {
		if (node != NULL) {
			delete node;
			node = nullptr;
		}
	}

	int GetSteps() const { return _steps; }

private:
	std::vector<NodePtr> _openList;
	std::vector<NodePtr> _closedList;
	std::vector<NodePtr> _expandList;

	NodePtr _start, _goal, _current;

	int _steps;
};