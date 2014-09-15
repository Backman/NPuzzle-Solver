#pragma once

#include <vector>

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
			TILE::SPACE,
			TILE::TWO,
			TILE::THREE,
			TILE::FOUR,
			TILE::FIVE,
			TILE::SIX,
			TILE::SEVEN,
			TILE::EIGHT,
			TILE::ONE
		};

		int clockwiseTileOf[WIDTH * HEIGHT] = 
		{
			1,
			2,
			5,
			0,
			-1,
			8,
			3,
			6,
			7
		};

		int tileX[WIDTH * HEIGHT] = 
		{
			1,
			0,
			1,
			2,
			2,
			2,
			1,
			0,
			0
		};

		int tileY[WIDTH * HEIGHT] = 
		{
			1,
			0,
			0,
			0,
			1,
			2,
			2,
			2,
			1
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

	bool CanMove(TILE* fromTiles, TILE* toTiles, int spx, int tx, int ty)
	{

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