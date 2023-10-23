#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <iostream>

using namespace sf;
using namespace std;

//AutoPlay related
bool isAutoPLaying = false;
float dt;
float timerSec = 0.08f;
float timer;
Clock m_clockTime;

bool isRMBPressed = false;

void PlayNextFrame(Grid& gameGrid, RenderWindow& window)
{
    gameGrid.CalculateNextFrame();
    gameGrid.Redraw(window);
}

void AutoPlayNextFrame(Grid& gameGrid, RenderWindow& window)
{
    dt = m_clockTime.restart().asSeconds();
    timer += dt;
    if (timerSec <= timer)
    {
        timer = 0;
        PlayNextFrame(gameGrid, window);
    }
}

void InputHandler(Event event, Grid& gameGrid, RenderWindow& window)
{
    Vector2i mousePosition = Mouse::getPosition(window);

    if (isRMBPressed)
    {
        for (shared_ptr<Cell> cell : gameGrid.cellsVectorArray)
        {
            if (cell->cellShape.getGlobalBounds().contains(Vector2f(mousePosition)))
            {
                cell->OnClicked(event);
            }
            cell->OnRedraw();
        }
        gameGrid.Redraw(window);
    }
    if (event.type == Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == Mouse::Left)
        {
            for (shared_ptr<Cell> cell : gameGrid.cellsVectorArray)
            {
                if (cell->cellShape.getGlobalBounds().contains(Vector2f(mousePosition)))
                {
                    cell->OnClicked(event);
                }
                cell->OnRedraw();
            }
            gameGrid.Redraw(window);
        }
        if (event.mouseButton.button == Mouse::Right)
        {
            isRMBPressed = true;
        }
    }
    if (event.type == Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == Mouse::Right)
            isRMBPressed = false;
    }
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Space)
        {
            isAutoPLaying = true;
        }
    }
    if (event.type == Event::KeyReleased)
    {
        if (event.key.code == Keyboard::Space)
        {
            isAutoPLaying = false;
            timer = timerSec;
        }
    }

    if (event.type == Event::Closed)
    {
        window.close();
    }
}

int main()
{
    RenderWindow window(VideoMode(900, 900), "P-A's GameOfLife", Style::Titlebar | Style::Close);
    
    window.clear();
    Font font;
    font.loadFromFile("assets/light-arial.ttf");
    Text loadingText;
    loadingText.setPosition(window.getSize().x / 2 - 140, window.getSize().y / 2 - 70);
    loadingText.setFont(font);
    loadingText.setCharacterSize(70);
    loadingText.setString("LOADING...");
    window.draw(loadingText);
    window.display();


    Text tuto1;
    Text tuto2;
    tuto1.setFont(font);
    tuto1.setCharacterSize(24);
    tuto1.setString("- Press SPACE to play single frame \n- Hold SPACE to auto-play \n- Click LMB to change a cell state \n- Hold and drag RMB to draw alive cells");
    tuto1.setPosition(3, 0);
    tuto1.setFillColor(Color::Black);

    Grid gameGrid;
    gameGrid.gridSize.x = window.getSize().x / 10; //divisé par la size d'une cell
    gameGrid.gridSize.y = window.getSize().y / 10;
    gameGrid.PopulateGrid(window);
    window.draw(tuto1);
    window.draw(tuto2);
    window.display();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            InputHandler(event, gameGrid, window);

            if (isAutoPLaying)
                AutoPlayNextFrame(gameGrid, window);
        }
    }

    return 0;
}
