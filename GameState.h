#ifndef _FifteenPuzzle_State_h_
#define _FifteenPuzzle_State_h_

#include <CtrlLib/CtrlLib.h>

class GameState : Upp::Moveable<GameState>
{
private:
	int matrix[4][4];
	Upp::Point emptyPosition;
	static const int EMPTY;
	static const int DX[4];
	static const int DY[4];
	
	void SetPosition(Upp::Point position, int value);
	bool IsInside(Upp::Point position) const;
public:
	GameState();
	GameState(const GameState & state);
	GameState & operator=(const GameState & state);
	int GetPosition(Upp::Point position) const;
	Upp::Point GetEmptyPosition() const;
	bool TryMove(Upp::Point position);
	bool IsEmpty(Upp::Point position) const;
	Upp::Vector<Upp::Point> GetPossibleMoves() const;
	void SetBeginningConfiguration();
	Upp::String ToString();
	operator unsigned() const;
};

unsigned GetHashValue(const GameState & state);

#endif
