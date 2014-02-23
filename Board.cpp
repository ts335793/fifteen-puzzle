#include "Board.h"
#include "Controller.h"
#include "GameState.h"
#include <iostream>

#define IMAGEFILE <FifteenPuzzle/PuzzleBackground.iml>
#include <Draw/iml_source.h>
//#include <iostream>

Board::Board() : Picture()
{
}

void Board::SetController(Controller *controller)
{
	this->controller = controller;
}

void Board::Refresh()
{
	Upp::Size size = GetSize();
	int puzzleWidth = size.cx / 4;
	int puzzleHeight = size.cy / 4;
	
	//std::cout << "Puzzle size: " << size.cx << " " << size.cy << std::endl;
	
	Upp::DrawingDraw boardDraw(size);
	boardDraw.DrawRect(size, Upp::Gray());
	
	for(int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
		{
			if(!controller->GetState().IsEmpty(Upp::Point(x, y)))
			{
				int number = controller->GetState().GetPosition(Upp::Point(x, y));
				Upp::String fieldNumber = Upp::AsString(number);
				Upp::Size size = Upp::GetTextSize(fieldNumber, Upp::Arial(20).Bold());
				
				Upp::DrawingDraw puzzleDraw(Upp::Size(puzzleWidth, puzzleHeight));
				
				if(coveredPuzzle == Upp::Point(x, y))
				{
					puzzleDraw.DrawImage(Upp::Size(puzzleWidth, puzzleHeight), IMAGECLASS::CoveredPuzzleBackground());
					puzzleDraw.DrawText((puzzleWidth - size.cx) / 2, (puzzleHeight - size.cy) / 2, fieldNumber, Upp::Arial(20).Bold(), Upp::Black());
				}
				else
				{
					puzzleDraw.DrawImage(Upp::Size(puzzleWidth, puzzleHeight), IMAGECLASS::PuzzleBackground());
					puzzleDraw.DrawText((puzzleWidth - size.cx) / 2, (puzzleHeight - size.cy) / 2, fieldNumber, Upp::Arial(20).Bold(), Upp::White());
				}
				
				boardDraw.DrawDrawing(x * puzzleWidth, y * puzzleHeight, puzzleWidth, puzzleHeight, puzzleDraw.GetResult());
			}
		}
	}
	
	*this = boardDraw.GetResult();
}

void Board::MouseMove(Upp::Point position, Upp::dword keyflags)
{
	int x = position.x / (GetSize().cx / 4);
	int y = position.y / (GetSize().cy / 4);
	
	coveredPuzzle = Upp::Point(x, y);
	
	Refresh();
}

void Board::MouseLeave()
{
	coveredPuzzle = Upp::Point(-1, -1);
	
	Refresh();
}
	
void Board::LeftUp(Upp::Point position, Upp::dword keyflags)
{
	int x = position.x / (GetSize().cx / 4);
	int y = position.y / (GetSize().cy / 4);
	
	controller->TryMove(Upp::Point(x, y));
}
	
Board & Board::operator=(Upp::Drawing drawing)
{
	Upp::Picture::operator=(drawing);
	return *this;
}

bool Board::Key(Upp::dword key, int count)
{
	Upp::Point emptyPosition = controller->GetState().GetEmptyPosition();
	
	switch(key)
	{
		case Upp::K_UP:
			controller->TryMove(Upp::Point(emptyPosition.x, emptyPosition.y - 1));
			break;
		case Upp::K_LEFT:
			controller->TryMove(Upp::Point(emptyPosition.x - 1, emptyPosition.y));
			break;
		case Upp::K_DOWN:
			controller->TryMove(Upp::Point(emptyPosition.x, emptyPosition.y + 1));
			break;
		case Upp::K_RIGHT:
			controller->TryMove(Upp::Point(emptyPosition.x + 1, emptyPosition.y));
			break;
	}
	return true;
}