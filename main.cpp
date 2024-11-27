#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace sf;

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

void initializeGrid() {
    srand(time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = rand() % 2;  // Randomly initialize cells as alive or dead
        }
    }
}

void renderGrid(RenderWindow &window) {
    int x, y;
    
    window.clear();
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (x = 0; x < gridWidth; ++x) {
        for (y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");
    
    initializeGrid();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        renderGrid(window);

        sleep(milliseconds(100));
    }

    return 0;
}
