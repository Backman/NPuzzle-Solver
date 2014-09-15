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

	AStarSolver() :
		_current(nullptr), _start(nullptr), _goal(nullptr)
	{ }

	AStarSolver(Node* start, Node* goal) :
		_current(nullptr), _start(start), _goal(goal)
	{ }

	~AStarSolver()
	{
		DeleteAllNodes();
	}

	std::vector<Node*>& Expand(Node* node)
	{
		return std::vector<Node*>();
	}

	void Solve()
	{
		if (!_start || !_goal) {
			return;
		}
		
		_steps = 0;
		_openList.push_back(_start);
		while (!_openList.empty()) {
			++_steps;
			_current = _openList.back();
			_openList.pop_back();

			if (_current->GetState() == _goal.GetState()) {
				return;
			}
			
			_expandList.clear();
			_expandList = Expand(_current);

			for (int i = 0; i < _expandList.size(); ++i) {
				Node* child = _expandList[i];
				float newCost = _current->GetCost() + _current->GetCostTo(child);

				std::vector<Node*>::iterator openListIt;
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

				std::vector<Node*>::iterator closedListIt;
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

				if (openListNode != nullptr) {
					DeleteNode((*openListIt));
					_openList.erase(openListIt);

					std::sort(_openList.begin(), _openList.end(), NodeCompare);
				}

				if (closedListIt != _closedList.end()) {
					DeleteNode((*closedListIt));
					_closedList.erase(closedListIt);
					
				}

				child->SetParent(_current);
				child->SetCost(newCost);
				child->SetHeuristic(child->EstimatedDistanceTo(_goal));
				child->UpdateTotalCost();

				_openList.push_back(child);

				std::sort(_openList.begin(), _openList.end(), NodeCompare);
			}

			_closedList.push_back(_current);
		}
	}

	bool NodeCompare(const Node& x, const Node& y)
	{
		return x.GetTotalCost() > y.GetTotalCost();
	}

	void DeleteAllNodes() 
	{
		while (!_openList.empty()) {
			DeleteNode(_openList.pop());
		}

		while (!_closedList.empty()) {
			DeleteNode(_closedList.back());
			_closedList.pop_back();
		}

		DeleteNode(_start);
		DeleteNode(_goal);
		DeleteNode(_current);
	}

	void DeleteNode(Node* node) {
		if (node != nullptr) {
			delete node;
			node = nullptr;
		}
	}

	int GetSteps() const { return _steps; }

private:
	std::vector<Node*> _openList;
	std::vector<Node*> _closedList;
	std::vector<Node*> _expandList;

	Node* _start, _goal, _current;

	int _steps;
};