#include "Controller.h"
#include "MainWindow.h"
#include "Board.h"
//#include <iostream>

Controller::Controller()
{
	keepShowingSolution = false;
	isAbleToMovePuzzle = false;
}

Controller::Controller(const Controller & controller)
{
	keepShowingSolution = false;
	isAbleToMovePuzzle = false;
	stack = controller.stack;
}

Controller & Controller::operator=(const Controller & controller)
{
	*this = Controller(controller);
	return *this;
}
	
const GameState & Controller::GetState()
{
	return stack.Top();
}
	
void Controller::NewGame()
{
	stack.Clear();
	numberOfMoves = 0;
	keepShowingSolution = false;
	isAbleToMovePuzzle = true;
	
	GameState state;
	Upp::Point position;
	Upp::Vector<Upp::Point> possibleMoves;
	bool addedState;
	
	state.SetBeginningConfiguration();
	stack.Add(state);
	addedState = true;
	
	while(addedState == true && stack.GetCount() < 15)
	{
		possibleMoves = stack.Top().GetPossibleMoves();
		
		addedState = false;
		
		while(!possibleMoves.IsEmpty())
		{
			possibleMoves.Swap(Upp::Random() % possibleMoves.GetCount(), possibleMoves.GetCount() - 1);
			position = possibleMoves.Pop();
			GameState newState = GameState(stack.Top());
			newState.TryMove(position);
			
			if(stack.Find(newState) == -1)
			{
				stack.Add(newState);
				addedState = true;
				break;
			}
		}
		
	}
	
	//std::cout << stack.GetCount() << std::endl;
	
	mainWindow->GetBoard().Refresh();
	mainWindow->GetNumberOfMoves().SetLabel(String().Cat() << "Number of moves: " << numberOfMoves);
}
	
void Controller::ShowSolution()
{
	if(keepShowingSolution == false)
	{
		isAbleToMovePuzzle = false;
		keepShowingSolution = true;
		KeepShowingSolution();
	}
}

void Controller::KeepShowingSolution()
{
	if(stack.GetCount() > 1 && keepShowingSolution == true)
	{
		stack.Pop();
		mainWindow->GetBoard().Refresh();
		Upp::SetTimeCallback(300, Upp::THISBACK(KeepShowingSolution));
	}
	else
	{
		keepShowingSolution = false;
	}
}

void Controller::TryMove(Upp::Point position)
{
	if(isAbleToMovePuzzle == true)
	{
		GameState state(stack.Top());
		
		if(state.TryMove(position))
		{
			numberOfMoves++;
			while(stack.Find(state) != -1)
			{
				stack.Pop();
			}
			stack.Put(state);
			mainWindow->GetBoard().Refresh();
			mainWindow->GetNumberOfMoves().SetLabel(String().Cat() << "Number of moves: " << numberOfMoves);
			
			if(stack.GetCount() == 1)
			{
				Victory();
			}
		}
	}
}

void Controller::Help()
{
	PromptOK("This is some feature.");
}

void Controller::EndOfGame()
{
	isAbleToMovePuzzle = false;
}

void Controller::Victory()
{
	PromptOK("You won!");
	EndOfGame();
}

void Controller::SetMainWindow(MainWindow *mainWindow)
{
	this->mainWindow = mainWindow;
}