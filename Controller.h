#ifndef _FifteenPuzzle_Controller_h_
#define _FifteenPuzzle_Controller_h_

#include <CtrlLib/CtrlLib.h>
#include "GameState.h"

class MainWindow;

class Controller
{
private:
	Upp::Index<GameState> stack;
	int numberOfMoves;
	MainWindow *mainWindow;
	bool keepShowingSolution;
	void KeepShowingSolution();
	bool isAbleToMovePuzzle;
public:
	typedef Controller CLASSNAME;
	Controller();
	Controller(const Controller & controller);
	Controller & operator=(const Controller & controller);
	const GameState & GetState();
	void NewGame();
	void ShowSolution();
	void TryMove(Upp::Point position);
	void Help();
	void EndOfGame();
	void Victory();
	void SetMainWindow(MainWindow *mainWindow);
};

#endif
