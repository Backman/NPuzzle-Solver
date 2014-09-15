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
		if (_parent) {
			delete _parent;
		}
		_parent = nullptr;
	}

	inline AStarNode& GetParent() const { return *_parent; }
	inline T& GetState() const { return _state; }
	inline float GetHeuristic() const { return _heuristic; }
	inline float GetCost() const { return _cost; }
	inline float GetTotalCost() const { return _total; }

	inline float GetCostTo(AStarNode* node) const
	{
		return _state.GetCostTo(node->_state);
	}

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
		return state.EstimatedDistanceTo(node->_state);
	}

	template<typename State>
	static AStarNode<State>* CreateNode();

	template<typename State>
	static AStarNode<State>* CreateNode(AStarNode<State>* parent, float cost, float heuristic, const State& state);

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

template<typename State>
AStarNode<State>* CreateNode()
{
	return new AStarNode<State>;
}

template<typename State>
AStarNode<State>* CreateNode(AStarNode<State>* parent, float cost, float heuristic, const State& state)
{
	return new AStarNode<State>(parent, cost, heuristic, state);
}