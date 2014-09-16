#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include "AStarNode.h"

enum class TILE
{
	SPACE,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT
};

const int WIDTH = 4;
const int HEIGHT = 4;

class NPuzzleState
{
public:
	static TILE GoalState[WIDTH * HEIGHT];
	static TILE StartState[WIDTH * HEIGHT];
	TILE Board[WIDTH * HEIGHT];

	NPuzzleState()
	{
		memcpy(Board, GoalState, sizeof(TILE)* WIDTH * HEIGHT);
	}

	NPuzzleState(TILE* tiles)
	{
		memcpy(Board, tiles, sizeof(TILE)* WIDTH * HEIGHT);
	}

	~NPuzzleState()
	{

	}


	bool operator == (const NPuzzleState& rhs)
	{
		for (int i = 0; i < WIDTH * HEIGHT; ++i) {
			if (Board[i] != rhs.Board[i]) {
				return false;
			}
		}

		return true;
	}

	float EstimatedDistanceTo(NPuzzleState& state)
	{
		int i, cx, cy, ax, ay, h = 0, s, t;

		TILE correctFollowerTo[HEIGHT * WIDTH] = 
		{
			TILE::SPACE,	TILE::TWO,		TILE::THREE,
			TILE::FOUR,		TILE::FIVE,		TILE::SIX,
			TILE::SEVEN,	TILE::EIGHT,	TILE::ONE
		};

		int clockwiseTileOf[WIDTH * HEIGHT] = 
		{
			1,	2,	5,
			0,	-1,	8,
			3,	6,	7
		};

		int tileX[WIDTH * HEIGHT] = 
		{
			1,	0,	1,
			2,	2,	2,
			1,	0,	0
		};

		int tileY[WIDTH * HEIGHT] = 
		{
			1,	0,	0,
			0,	1,	2,
			2,	2,	1
		};

		s = 0;

		if (Board[(WIDTH * HEIGHT) / 2] != state.Board[(WIDTH * HEIGHT) / 2]) {
			s = 1;
		}

		for (int i = 0; i < (WIDTH * HEIGHT); ++i) {
			if (Board[i] == TILE::SPACE) {
				continue;
			}

			cx = tileX[(int)Board[i]];
			cy = tileY[(int)Board[i]];

			ax = i % WIDTH;
			ay = i / WIDTH;

			h += abs(cx - ax);
			h += abs(cy - ay);

			if (ax == (WIDTH / 2) && ay == (HEIGHT / 2)) {
				continue;
			}

			if (correctFollowerTo[(int)Board[i]] != Board[clockwiseTileOf[i]]) {
				s += 2;
			}
		}

		t = h + (3 * s);

		return (float)t;
	}

	void GetSpacePosition(NPuzzleState* state, int* rx, int* ry)
	{
		for (int y = 0; y < HEIGHT; ++y) {
			for (int x = 0; x < WIDTH; ++x) {
				if (state->Board[(y*WIDTH) + x] == TILE::SPACE) {
					*rx = x;
					*ry = y;

					return;
				}
			}
		}
	}

	int GetTile(int x, int y, TILE* tiles)
	{
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
			return -1;
		}

		if (tiles[(y * WIDTH) + x] == TILE::SPACE) {
			return 0;
		}

		return 1;
	}

	bool CanMove(TILE* fromTiles, TILE* toTiles, int spx, int spy, int tx, int ty)
	{
		int t;

		if (GetTile(spx, spy, fromTiles) == 0) {
			if (GetTile(tx, ty, fromTiles) == 1) {
				for (int i = 0; i < WIDTH * HEIGHT; ++i) {
					toTiles[i] = fromTiles[i];
				}

				toTiles[(ty * WIDTH) + tx] = fromTiles[(spy * WIDTH) + spx];
				toTiles[(spy * WIDTH) + spx] = fromTiles[(ty * WIDTH) + tx];

				return true;
			}
		}

		return false;
	}

	void Expand(std::vector<AStarNode<NPuzzleState>*>* expandList, NPuzzleState* parentState) 
	{
		NPuzzleState state;

		int spx, spy;

		GetSpacePosition(this, &spx, &spy);

		if (CanMove(Board, state.Board, spx, spy, spx, spy - 1)) {
			AStarNode<NPuzzleState>* node = AStarNode<NPuzzleState>::CreateNode();
			node->SetState(state);
			expandList->push_back(node);
		}
		if (CanMove(Board, state.Board, spx, spy, spx, spy + 1)) {
			AStarNode<NPuzzleState>* node = AStarNode<NPuzzleState>::CreateNode();
			node->SetState(state);
			expandList->push_back(node);
		}
		if (CanMove(Board, state.Board, spx, spy, spx - 1, spy)) {
			AStarNode<NPuzzleState>* node = AStarNode<NPuzzleState>::CreateNode();
			node->SetState(state);
			expandList->push_back(node);
		}
		if (CanMove(Board, state.Board, spx, spy, spx + 1, spy)) {
			AStarNode<NPuzzleState>* node = AStarNode<NPuzzleState>::CreateNode();
			node->SetState(state);
			expandList->push_back(node);
		}
	}

	float GetCostTo(NPuzzleState& nextState)
	{
		return 1.0f;
	}

	void PrintState()
	{
		char str[100];

		sprintf_s(str, "%c %c %c\n%c %c %c\n%c %c %c\n",
			(int)Board[0] + '0',
			(int)Board[1] + '0',
			(int)Board[2] + '0',
			(int)Board[3] + '0',
			(int)Board[4] + '0',
			(int)Board[5] + '0',
			(int)Board[6] + '0',
			(int)Board[7] + '0',
			(int)Board[8] + '0'
			);

		std::cout << str << std::endl;
	}

private:

};

TILE NPuzzleState::GoalState[] = 
{ 
	TILE::ONE,
	TILE::TWO,
	TILE::THREE,
	TILE::EIGHT,
	TILE::SPACE,
	TILE::FOUR,
	TILE::SEVEN,
	TILE::SIX,
	TILE::FIVE
};

TILE NPuzzleState::StartState[] =
{
	TILE::TWO,
	TILE::EIGHT,
	TILE::THREE,
	TILE::ONE,
	TILE::SIX,
	TILE::FOUR,
	TILE::SEVEN,
	TILE::SPACE,
	TILE::FIVE,
};