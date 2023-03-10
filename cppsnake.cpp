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
    {"tail", static_cast<char>(240)}, // TEMPORARY
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

struct SnakeTail {
    int posX;
    int posY;
};

const int FIELD_HEIGHT = 20;  // add 2 to intended amount because of walls
const int FIELD_WIDTH = 26;
const int FIELD_SIZE = FIELD_HEIGHT*FIELD_WIDTH; // The total field size, including walls
const int FIELD_PA_SIZE = (FIELD_HEIGHT-2)*(FIELD_WIDTH-2); // field size only accessable by snake

char field[FIELD_SIZE];

bool gameOver = false;
bool gamePaused = false;
int gameTick = 0;
int tailLength = 1;

SnakeHead snake = {
    snake.posX = (int)(FIELD_WIDTH/2),
    snake.posY = (int)(FIELD_HEIGHT/2),
    snake.direction = 2
};
SnakeTail tail[FIELD_PA_SIZE];

void inputHandler(int keyValue) {
    // Menu keys
    switch(keyValue) {
            case KEY_ESC:
                gameOver = true;
                break;
            case KEY_ENTER:
                gamePaused = !gamePaused;
                break;
        }

    // arrow keys can return 0 or 244 depending on num lock
    // second call is for second value returned by arrow key
    if (keyValue == 0 || keyValue == 244) {
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
    for (int i=0; i<FIELD_SIZE; i++){
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

    cout << snake.posX << ", " << snake.posY << ", " << snake.direction << " | " << gameTick << endl;
    field[snake.posX+snake.posY * FIELD_WIDTH] = snakeset["head"];

    for (int i=0; i<tailLength; i++) {
        field[tail[i].posX + tail[i].posY * FIELD_WIDTH] = snakeset["tail"];
    }
    
    for (int i=1; i<FIELD_SIZE; i++){
        if (field[i] == gameset["wall"]) cout << field[i] << field[i];
        else cout << field[i] << " ";
        if (i%FIELD_WIDTH == 0) {cout << endl;}
    }
    // idk what's wrong, but theres a gap in bottom right. here's a lazy fix...
    cout << gameset["wall"] << gameset["wall"];
}

void updateSnake() {
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

    if (field[newX + newY * FIELD_WIDTH] == gameset["appl"]) {
        tailLength++;
    }

    if (tailLength > 0) {
        tail[0].posX = snake.posX;
        tail[0].posY = snake.posY;
    }

    for (int i=tailLength; i>1; i--) {
        tail[i].posX = tail[i-1].posX;
        tail[i].posY = tail[i-1].posY;
    }
    
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

    // Game Loop
    while (!gameOver)
    {
        if (kbhit()) inputHandler(getch());

        if (gamePaused) continue;

        if (gameTick % 5 == 0) {
            updateSnake();
            printField();
        }

        gameTick++;
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