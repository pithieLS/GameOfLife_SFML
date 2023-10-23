#include "Grid.h"

Grid::Grid()
{
	aliveCellTexture.loadFromFile("assets/aliveCellTexture.png");
	deadCellTexture.loadFromFile("assets/deadCellTexture.png");
}

void Grid::ScanSurrounding(Cell& cell)
{
	int x = cell.coords.x;
	int y = cell.coords.y;

	for (shared_ptr<Cell> nearCell : cellsVectorArray)
	{
		Vector2<int> nearCellCoords = nearCell->coords;

		if (nearCellCoords.x == x - 1 && nearCellCoords.y == y - 1
		 || nearCellCoords.x == x - 1 && nearCellCoords.y == y
	     || nearCellCoords.x == x - 1 && nearCellCoords.y == y + 1
		 || nearCellCoords.x == x && nearCellCoords.y == y - 1
		 || nearCellCoords.x == x && nearCellCoords.y == y + 1
		 || nearCellCoords.x == x + 1 && nearCellCoords.y == y - 1
		 || nearCellCoords.x == x + 1 && nearCellCoords.y == y
		 || nearCellCoords.x == (x + 1) && nearCellCoords.y == (y + 1))
			cell.nearCellVector.push_back(nearCell);
	}
}

void Grid::PopulateGrid(RenderWindow& window)
{
	for (int columnNb = 0; columnNb < gridSize.y; columnNb++)
	{
		for (int rowNb = 0; rowNb < gridSize.x; rowNb++)
		{
			shared_ptr<Cell> createdCell = make_shared<Cell>(rowNb, columnNb, aliveCellTexture, deadCellTexture, window);
			cellsVectorArray.push_back(createdCell);
			
			createdCell->cellShape.setPosition(createdCell->cellShape.getSize().x * rowNb, 
						 createdCell->cellShape.getSize().y * columnNb);
			window.draw(createdCell->cellShape);
		}
	}
	for (shared_ptr<Cell> _cell : cellsVectorArray)
	{
		ScanSurrounding(*_cell);
	}
}

void Grid::Redraw(RenderWindow& window)
{
	window.clear();
	for (shared_ptr<Cell> _cell : cellsVectorArray)
	{
		_cell->OnRedraw();
		window.draw(_cell->cellShape);
	}
	window.display();
}

void Grid::CalculateNextFrame()
{
	for (shared_ptr<Cell> _cell : cellsVectorArray)
	{
		_cell->CalculateNextState();
	}
	for (shared_ptr<Cell> _cell : cellsVectorArray)
	{
		_cell->lastStateIsAlive = _cell->isAlive;
	}
}
