#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#define CELL 10

using namespace sf;
using namespace std;

void resetGrid(vector<vector<bool>> *grid);

void initialState(vector<vector<bool>> *grid, int fraction);

void drawCell(RenderWindow &window, int x, int y);

void checkRules(vector<vector<bool>> &grid, vector<vector<bool>> &gridInBackground);


int main() {
    RenderWindow window(VideoMode(CELL * 150, CELL * 100), "The Game Of Life", Style::None);
    window.setFramerateLimit(20);

    bool pause = true;

    vector<vector<bool>> cells(window.getSize().x / CELL, vector<bool>(window.getSize().y / CELL));
    vector<vector<bool>> cellsChanging(window.getSize().x / CELL, vector<bool>(window.getSize().y / CELL));
    resetGrid(&cells);
    resetGrid(&cellsChanging);

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
                    resetGrid(&cells);
                }

                if (event.key.code == Keyboard::Num2) {
                    initialState(&cells, 2);
                }
                if (event.key.code == Keyboard::Num3) {
                    initialState(&cells, 3);
                }
                if (event.key.code == Keyboard::Num4) {
                    initialState(&cells, 4);
                }
                if (event.key.code == Keyboard::Num5) {
                    initialState(&cells, 5);
                }
                if (event.key.code == Keyboard::Num6) {
                    initialState(&cells, 6);
                }
            }
        }


        Color pauseColor(82, 87, 94, 255);
        window.clear(pause ? pauseColor : Color::Black);


        if (!pause) checkRules(cells, cellsChanging);


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

void resetGrid(vector<vector<bool>> *grid) {
    for (auto &column: *grid) {
        fill(column.begin(), column.end(), false);
    }
}

void initialState(vector<vector<bool>> *grid, int fraction) {
    for (auto &column: *grid) {
        for (auto cell: column) {
            cell = (rand() % fraction == 0);
        }
    }
}

void drawCell(RenderWindow &window, int x, int y) {
    RectangleShape r(Vector2f(CELL, CELL));
    r.setPosition(x * CELL, y * CELL);
    window.draw(r);
}

void checkRules(vector<vector<bool>> &grid, vector<vector<bool>> &gridInBackground) {
    int xSize = grid.size();
    int ySize = grid[0].size();


    resetGrid(&gridInBackground);


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
                gridInBackground[x][y] = true;
            }

            if (current) {
                if (nActive <= 1 || nActive >= 4) {
                    gridInBackground[x][y] = false;
                } else {
                    gridInBackground[x][y] = true;
                }
            }
        }
    }

    grid = gridInBackground;
}



