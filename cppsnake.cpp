#include <Windows.h>
#include <iostream>
#include <map>
#include <conio.h>
using namespace std;

// for maps and KEY_defines: https://www.ascii-codes.com/
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

map<string, char> snakeset = {
    {"head", static_cast<char>(148)}, // ö
    {"vert", static_cast<char>(186)}, // ║
    {"horz", static_cast<char>(205)}, // ═
    {"topL", static_cast<char>(187)}, // ╗
    {"topR", static_cast<char>(201)}, // ╔
    {"botL", static_cast<char>(188)}, // ╝
    {"botR", static_cast<char>(200)}  // ╚
};

map<string, char> gameset = {
    {"void", static_cast<char>(32)},
    {"appl", static_cast<char>(254)}, // ■
    {"wall", static_cast<char>(177)}  // ▒
};

struct SnakeHead {
    int posX;
    int posY;
    int direction; // direction; 1,2,3,4 = N,E,S,W = W,D,S,A
};

const int FIELD_HEIGHT = 18 + 2;  // add 2 to intended amount because of walls
const int FIELD_WIDTH = 24 + 2;
const int MAP_SIZE = (FIELD_HEIGHT*FIELD_WIDTH);

char field[MAP_SIZE];
bool gameOver = false;
bool gamePaused = false;
int game_tick = 0;
SnakeHead snake = {
    snake.posX = (int)(FIELD_WIDTH/2),
    snake.posY = (int)(FIELD_HEIGHT/2),
    snake.direction = 2
};

void inputHandler(int key_value) {
    // Menu keys
    switch(key_value) {
            case KEY_ESC:
                gameOver = true;
                break;
            case KEY_ENTER:
                gamePaused = !gamePaused;
                break;
        }

    // arrow keys can return 0 or 244 depending on num lock
    // second call is for second value returned by arrow key
    if (key_value == 0 || key_value == 244) {
        switch(_getch()) {
        case KEY_UP:
            if (snake.direction != 3) snake.direction = 1;
            break;
        case KEY_DOWN:
            if (snake.direction != 1) snake.direction = 3;
            break;
        case KEY_LEFT:
            if (snake.direction != 2) snake.direction = 4;
            break;
        case KEY_RIGHT:
            if (snake.direction != 4) snake.direction = 2;
            break;
        }
    }
}

bool checkSnakeState() {
    return false;
}

void printField() {
    for (int i=0; i<MAP_SIZE; i++){
        if (i%FIELD_WIDTH-1 == 0 ||
            i%FIELD_WIDTH == 0 ||
            i<FIELD_WIDTH || 
            i>FIELD_WIDTH*(FIELD_HEIGHT-1)) {
            field[i] = gameset["wall"];
        } else {
            field[i] = gameset["void"];
        }
    }

    system("cls");

    cout << snake.posX << ", " << snake.posY << ", " << snake.direction << " | " << game_tick << endl;
    field[snake.posX+snake.posY * FIELD_WIDTH] = gameset["appl"];
    
    for (int i=1; i<MAP_SIZE; i++){
        if (field[i] == gameset["wall"]) cout << field[i] << field[i];
        else cout << field[i] << " ";
        if (i%FIELD_WIDTH == 0) {cout << endl;}
    }
    // idk what's wrong, but theres a gap in bottom right. here's a lazy fix...
    cout << gameset["wall"] << gameset["wall"];
}

void updatePosition() {
    int dx = 0;
    int dy = 0;
    switch(snake.direction){
    case 1:
        dy = -1;
        break;
    case 2:
        dx = 1;
        break;
    case 3:
        dy = 1;
        break;
    case 4:
        dx = -1;
        break;
    }

    int newX = snake.posX + dx;
    int newY = snake.posY + dy;

    if (field[newX + newY * FIELD_WIDTH] == gameset["wall"]) {
        gameOver = true;
    } else {
        snake.posX = newX;
        snake.posY = newY;
    }
}

int main()
{
    // https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
    SetConsoleOutputCP(437); // CP437 (IBM437) Code

    int snake_length = 1;

    // Game Loop
    while (!gameOver)
    {
        if (kbhit()) inputHandler(getch());

        if (gamePaused) continue;

        if (game_tick%5 == 0) {
            updatePosition();
            printField();
        }

        game_tick++;
        Sleep(10);
    }

    return 0;
}

/*TO DO:
- apple generator
- snake's tail
- self-collision
- cpu clock-based tickrate instead of Sleep()
- snake bendy characters (topL,topR,botL,botR)*/