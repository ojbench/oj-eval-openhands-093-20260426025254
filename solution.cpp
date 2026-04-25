#include <iostream>
#include <set>
#include <tuple>
using namespace std;

// Directions: 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int grid[10][10];

bool isValid(int x, int y) {
    return x >= 0 && x < 10 && y >= 0 && y < 10 && grid[x][y] != 0;
}

// Get next direction based on right-hand rule
// Priority: right turn > straight > left turn > U-turn
int getNextDirection(int x, int y, int dir) {
    // Try right turn first
    int rightDir = (dir + 1) % 4;
    int nx = x + dx[rightDir];
    int ny = y + dy[rightDir];
    if (isValid(nx, ny)) {
        return rightDir;
    }
    
    // Try straight
    nx = x + dx[dir];
    ny = y + dy[dir];
    if (isValid(nx, ny)) {
        return dir;
    }
    
    // Try left turn
    int leftDir = (dir + 3) % 4;
    nx = x + dx[leftDir];
    ny = y + dy[leftDir];
    if (isValid(nx, ny)) {
        return leftDir;
    }
    
    // Try U-turn
    int uTurnDir = (dir + 2) % 4;
    nx = x + dx[uTurnDir];
    ny = y + dy[uTurnDir];
    if (isValid(nx, ny)) {
        return uTurnDir;
    }
    
    // No valid move (shouldn't happen in valid input)
    return -1;
}

int main() {
    int startX = -1, startY = -1;
    
    // Read grid
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 4) {
                startX = i;
                startY = j;
                grid[i][j] = 1; // Treat starting position as empty
            }
        }
    }
    
    int x = startX, y = startY;
    int dir = 0; // Start facing UP
    int score = 0;
    
    // Track visited states to detect cycles
    set<tuple<int, int, int>> visited;
    
    while (true) {
        // Check for cycle
        if (visited.count({x, y, dir})) {
            cout << "Silly Pacman" << endl;
            return 0;
        }
        visited.insert({x, y, dir});
        
        // Get next direction
        int nextDir = getNextDirection(x, y, dir);
        if (nextDir == -1) {
            // No valid move, stuck (shouldn't happen)
            cout << "Silly Pacman" << endl;
            return 0;
        }
        
        // Move to next position
        dir = nextDir;
        x += dx[dir];
        y += dy[dir];
        
        // Check what's at the new position
        if (grid[x][y] == 2) {
            // Eat bean
            score += 2;
            grid[x][y] = 1; // Bean is eaten
        } else if (grid[x][y] == 3) {
            // Hit ghost
            score -= 500;
            break;
        }
    }
    
    cout << score << endl;
    return 0;
}
