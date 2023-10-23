#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Cell
{
public:
	Cell();
	Cell(int cell_X, int cell_Y, 
		Texture& aliveCellTexture, Texture& deadCellTexture, 
		RenderWindow& window);
	void OnClicked(Event event);
	void OnStateChanged();
	void OnRedraw();
	void CalculateNextState();

	Vector2<int> coords;

	vector<shared_ptr<Cell>> nearCellVector;

	RectangleShape cellShape;

	Vector2<int> cellShapeSize;

	//Declare cell state variable
	bool isAlive = false;
	bool lastStateIsAlive = false;

	shared_ptr<Texture> sptrAliveCellTexture;
	shared_ptr<Texture> sptrDeadCellTexture;

private:


};

