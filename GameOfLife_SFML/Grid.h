#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include "Cell.h"

using namespace sf;
using namespace std;

class Grid
{
public:
	Grid();
	void PopulateGrid(RenderWindow& window);
	void ScanSurrounding(Cell& cell);
	void Redraw(RenderWindow& window);
	void CalculateNextFrame();

	vector<shared_ptr<Cell>> cellsVectorArray;

	Vector2<int> gridSize;

	Texture aliveCellTexture;
	Texture deadCellTexture;

private:

};

