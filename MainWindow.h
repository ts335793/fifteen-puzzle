#ifndef _FifteenPuzzle_MainWindow_h_
#define _FifteenPuzzle_MainWindow_h_

#include <CtrlLib/CtrlLib.h>
#include "Board.h"

using namespace Upp;

class Board;
class Controller;

#define LAYOUTFILE <FifteenPuzzle/FifteenPuzzle.lay>
#include <CtrlCore/lay.h>

class MainWindow : public WithMainWindowLayout<Upp::TopWindow> {
public:
	typedef MainWindow CLASSNAME;
	MainWindow();
	Board & GetBoard();
	Label & GetNumberOfMoves();
	void SetController(Controller *controller);
};

#endif
