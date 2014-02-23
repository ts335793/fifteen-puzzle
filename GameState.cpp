#include "GameState.h"

void GameState::SetPosition(Upp::Point position, int value)
{
	matrix[position.y][position.x] = value;
}
	
bool GameState::IsInside(Upp::Point position) const
{
	return 0 <= position.x && position.x <= 3 && 0 <= position.y && position.y <= 3;
}
	
GameState::GameState()
{
}

GameState::GameState(const GameState & state)
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			matrix[i][j] = state.matrix[i][j];
		}
	}
	
	emptyPosition = state.emptyPosition;
}

GameState & GameState::operator=(const GameState & state)
{
	*this = GameState(state);
	return *this;
}

int GameState::GetPosition(Upp::Point position) const
{
	return matrix[position.y][position.x];
}

Upp::Point GameState::GetEmptyPosition() const
{
	return emptyPosition;
}

bool GameState::TryMove(Upp::Point position)
{
	if(((emptyPosition.x == position.x && Upp::tabs(emptyPosition.y - position.y) == 1) ||
	   (emptyPosition.y == position.y && Upp::tabs(emptyPosition.x - position.x) == 1)) &&
	   IsInside(position))
	{
		SetPosition(emptyPosition, GetPosition(position));
		emptyPosition = position;
		SetPosition(emptyPosition, EMPTY);
		
		return true;
	}
	else
	{
		return false;
	}
}

bool GameState::IsEmpty(Upp::Point position) const
{
	return position == emptyPosition;
}

Upp::Vector<Upp::Point> GameState::GetPossibleMoves() const
{
	Upp::Vector<Upp::Point> possibleMoves;
	
	for(int i = 0; i < 4; i++)
	{
		Upp::Point position(emptyPosition.x + DX[i], emptyPosition.y + DY[i]);
		if(IsInside(position))
		{
			possibleMoves.Add(position);
		}
	}
	
	return possibleMoves;
}

void GameState::SetBeginningConfiguration()
{
	emptyPosition = Upp::Point(3, 3);
	for(int x = 0; x < 4; x++)
	{
		for(int y = 0; y < 4; y++)
		{
			SetPosition(Upp::Point(x, y), y * 4 + x + 1);
		}
	}
	SetPosition(emptyPosition, EMPTY);
}

Upp::String GameState::ToString()
{
	Upp::String output;
	output << "Empty position " << emptyPosition.x << " " << emptyPosition.y << "\n";
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			output << GetPosition(Upp::Point(x, y)) << " ";
		}
		output << "\n";
	}
	return output;
}

GameState::operator unsigned() const
{
	Upp::CombineHash hash;
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			hash = Upp::CombineHash((unsigned)hash, GetPosition(Upp::Point(x, y)));
		}
	}
   	return hash;
}

const int GameState::EMPTY = 0;
const int GameState::DX[4] = { 0, 0, 1, -1 };
const int GameState::DY[4] = { 1, -1, 0, 0 };

unsigned GetHashValue(const GameState & state)
{
	Upp::CombineHash hash;
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			hash = Upp::CombineHash((unsigned)hash, state.GetPosition(Upp::Point(x, y)));
		}
	}
    return hash;
}