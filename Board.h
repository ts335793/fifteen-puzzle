#ifndef _FifteenPuzzle_Board_h_
#define _FifteenPuzzle_Board_h_

#include <CtrlLib/CtrlLib.h>

#define IMAGEFILE <FifteenPuzzle/PuzzleBackground.iml>
#include <Draw/iml_header.h>

class Controller;

class Board : public Upp::Picture
{
private:
	Controller *controller;
	Upp::Point coveredPuzzle;
public:
	Board();
	void SetController(Controller *controller);
	void Refresh();
	void LeftUp(Upp::Point position, Upp::dword keyflags);
	void MouseMove(Upp::Point position, Upp::dword keyflags);
	void MouseLeave();
	Board & operator=(Upp::Drawing drawing);
	bool Key(Upp::dword key, int count);
};

#endif
