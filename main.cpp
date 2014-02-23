#include <CtrlLib/CtrlLib.h>
#include "Controller.h"
#include "MainWindow.h"
#include "Board.h"
#include <iostream>

GUI_APP_MAIN
{
	MainWindow mainWindow;
	Controller controller;
	
	mainWindow.SetController(&controller);
	controller.SetMainWindow(&mainWindow);
	
	controller.NewGame();
	mainWindow.Run();
}
