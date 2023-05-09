#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#define CELL 10

using namespace sf;
using namespace std;

void resetGrid(vector<vector<bool>> &grid);

void initialState(vector<vector<bool>> &grid, int fraction);

void drawCell(RenderWindow &window, int x, int y);

vector<vector<bool>> checkRules(vector<vector<bool>> grid);


int main() {
    RenderWindow window(VideoMode(CELL * 150, CELL * 100), "Test");
    window.setFramerateLimit(20);

    bool pause = true;

    vector<vector<bool>> cells(window.getSize().x / CELL, vector<bool>(window.getSize().y / CELL));
    resetGrid(cells);

    while (window.isOpen()) {
        Vector2i globalPosition = Mouse::getPosition();

        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                int xCell = event.mouseButton.x / CELL;
                int yCell = event.mouseButton.y / CELL;
                cells[xCell][yCell] = !cells[xCell][yCell];
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    pause = !pause;
                }
                if (event.key.code == Keyboard::BackSpace) {
                    resetGrid(cells);
                }

                if (event.key.code == Keyboard::Num2) {
                    initialState(cells, 2);
                }
                if (event.key.code == Keyboard::Num3) {
                    initialState(cells, 3);
                }
                if (event.key.code == Keyboard::Num4) {
                    initialState(cells, 4);
                }
                if (event.key.code == Keyboard::Num5) {
                    initialState(cells, 5);
                }
                if (event.key.code == Keyboard::Num6) {
                    initialState(cells, 6);
                }
            }
        }


        Color pauseColor(82, 87, 94, 255);
        window.clear(pause ? pauseColor : Color::Black);


        if (!pause) cells = checkRules(cells);


        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[0].size(); j++) {
                if (cells[i][j]) {
                    drawCell(window, i, j);
                }
            }
        }


        window.display();
    }
}

void resetGrid(vector<vector<bool>> &grid) {
    for (auto &column: grid) {
        fill(column.begin(), column.end(), false);
    }
}

void initialState(vector<vector<bool>> &grid, int fraction) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (rand() % fraction == 0) grid[i][j] = true;
            else grid[i][j] = false;
        }
    }
}

void drawCell(RenderWindow &window, int x, int y) {
    RectangleShape r(Vector2f(CELL, CELL));
    r.setPosition(x * CELL, y * CELL);
    window.draw(r);
}

vector<vector<bool>> checkRules(vector<vector<bool>> grid) {
    int xSize = grid.size();
    int ySize = grid[0].size();


    vector<vector<bool>> newGrid(xSize, vector<bool>(ySize));
    for (int i = 0; i < xSize; i++) {
        fill(newGrid[i].begin(), newGrid[i].end(), false);
    }


    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            bool current = grid[x][y];

            vector<bool> neighbours = {
                    (y - 1 >= 0) && grid[x][y - 1],
                    (x + 1 < xSize) && (y - 1 >= 0) && grid[x + 1][y - 1],
                    (x + 1 < xSize) && grid[x + 1][y],
                    (x + 1 < xSize) && (y + 1 < ySize) && grid[x + 1][y + 1],
                    (y + 1 < ySize) && grid[x][y + 1],
                    (x - 1 >= 0) && (y + 1 < ySize) && grid[x - 1][y + 1],
                    (x - 1 >= 0) && grid[x - 1][y],
                    (x - 1 >= 0) && (y - 1 >= 0) && grid[x - 1][y - 1],
            };

            int nActive = count(neighbours.begin(), neighbours.end(), true);


            if (!current && nActive == 3) {
                newGrid[x][y] = true;
            }

            if (current) {
                if (nActive <= 1 || nActive >= 4) {
                    newGrid[x][y] = false;
                } else {
                    newGrid[x][y] = true;
                }
            }
        }
    }

    return newGrid;
}



