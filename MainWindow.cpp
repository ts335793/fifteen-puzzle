#include "MainWindow.h"
#include "Controller.h"

Board & MainWindow::GetBoard()
{
	return board;
}

Label & MainWindow::GetNumberOfMoves()
{
	return numberOfMoves;
}

MainWindow::MainWindow()
{
	CtrlLayout(*this, "Fifteen Puzzle");
}

void MainWindow::SetController(Controller *controller)
{
	showSolution.WhenPush = Upp::callback(controller, &Controller::ShowSolution);
	newGame.WhenPush = Upp::callback(controller, &Controller::NewGame);
	help.WhenPush = Upp::callback(controller, &Controller::Help);
	board.SetController(controller);
}