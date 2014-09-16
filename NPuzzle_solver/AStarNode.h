#pragma once

#include <memory>

template<typename T>
class AStarNode
{
public:
	AStarNode() :
		_parent(nullptr), _total(0), _cost(0), _heuristic(0)
	{ }

	AStarNode(AStarNode* parent, float cost, float heuristic, const T& state) :
		_parent(parent), _total(cost + heuristic), _cost(cost) _heuristic(heruistic), _state(state)
	{ }

	~AStarNode()
	{
		/*if (_parent != nullptr) {
			delete _parent;
		}*/
	}

	inline AStarNode& GetParent() const { return *_parent; }
	inline T& GetState() { return _state; }
	inline float GetHeuristic() const { return _heuristic; }
	inline float GetCost() const { return _cost; }
	inline float GetTotalCost() const { return _total; }

	inline float GetCostTo(AStarNode* node)
	{
		return _state.GetCostTo(node->_state);
	}

	inline void SetState(T& state) { _state = state; }

	inline void SetParent(AStarNode* parent) { _parent = parent; }
	inline void SetCost(float val) 
	{ 
		_cost = val;
	}
	inline void SetHeuristic(float val) 
	{ 
		_heuristic = val;
	}

	inline void UpdateTotalCost()
	{
		_total = _cost + _heuristic;
	}

	inline float EstimatedDistanceTo(AStarNode* node)
	{
		return _state.EstimatedDistanceTo(node->_state);
	}

	static AStarNode* CreateNode()
	{
		return new AStarNode;
	}

	static AStarNode* CreateNode(AStarNode* parent, float cost, float heuristic, const T& state)
	{
		return new AStarNode(parent, cost, heuristic, state);
	}

	bool operator<(const AStarNode& rhs)
	{
		return _total < rhs._total;
	}

	bool operator == (const AStarNode& rhs)
	{
		return _state == rhs._state;
	}
private:
	T _state;
	AStarNode* _parent;
	float _total, _cost, _heuristic;
};