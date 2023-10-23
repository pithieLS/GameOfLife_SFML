#include "Cell.h"

Cell::Cell()
{}

Cell::Cell(int cell_X, int cell_Y, 
			Texture& aliveCellTexture, Texture& deadCellTexture, 
			RenderWindow& window)
{
	cellShapeSize.x = 10;
	cellShapeSize.y = 10;

	cellShape.setSize(Vector2f(cellShapeSize));
	cellShape.setFillColor(Color::White);

	coords.x = cell_X;
	coords.y = cell_Y;

	sptrAliveCellTexture = make_shared<Texture>(aliveCellTexture);
	sptrDeadCellTexture = make_shared<Texture>(deadCellTexture);
}

void Cell::OnClicked(Event event)
{
	if(event.mouseButton.button == Mouse::Left)
		isAlive = !isAlive;
	else
		isAlive = true;

	OnStateChanged();
}

void Cell::OnStateChanged()
{
	lastStateIsAlive = isAlive;
	OnRedraw();
}

void Cell::OnRedraw()
{
	if (isAlive == true)
	{
		cellShape.setFillColor(Color::Blue);
		//cellShape.setTexture(sptrAliveCellTexture.get());
	}
	else
	{
		cellShape.setFillColor(Color::White);
		//cellShape.setTexture(sptrDeadCellTexture.get());
	}
}

void Cell::CalculateNextState()
{
	int aliveNearCellNb = 0;
	for (shared_ptr<Cell> _cell : nearCellVector)
	{
		if (_cell->lastStateIsAlive)
			aliveNearCellNb++;
	}

	if (isAlive && aliveNearCellNb < 2)
		isAlive = false;
	if (isAlive && aliveNearCellNb == 2 || aliveNearCellNb == 3)
		isAlive = true;
	if (isAlive && aliveNearCellNb > 3)
		isAlive = false;
	if (isAlive == false && aliveNearCellNb == 3)
		isAlive = true;
	OnRedraw();
}
