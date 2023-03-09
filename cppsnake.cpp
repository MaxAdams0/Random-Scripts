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

#define FIELD_HEIGHT 9
#define FIELD_WIDTH 12

#define SNAKE_MAX_LENGTH (FIELD_HEIGHT*FIELD_WIDTH)

map<string, char> snakeset = {
    {"head", static_cast<char>(148)}, // 
    {"vert", static_cast<char>(186)}, // 
    {"horz", static_cast<char>(205)}, // 
    {"topL", static_cast<char>(187)}, // 
    {"topR", static_cast<char>(201)}, // 
    {"botL", static_cast<char>(188)}, // 
    {"botR", static_cast<char>(200)}  //
};

map<string, char> gameset = {
    {"void", static_cast<char>(32)},  // [Blank Space]
    {"appl", static_cast<char>(254)}, // ■
    {"arrL", static_cast<char>(17)},  // 
    {"arrR", static_cast<char>(16)},  // 
    {"arrU", static_cast<char>(30)},  // 
    {"arrD", static_cast<char>(31)}   // 
};

struct SnakeSegment {
    int x;
    int y;
    int dir; // direction; 1,2,3,4 = N,E,S,W
    bool isHead; // is it the snake's head
};

int main()
{
    // https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers
    SetConsoleOutputCP(437); // CP437 (IBM437) Code

    // The field viewable to the player
    char display_field[12][9];
    for (int col=0; col<12; col++){
        for (int row=0; row<9; row++){
            display_field[col][row] = gameset["void"];
        }
    }

    // The snake's "segments", or pixels
    SnakeSegment snake[SNAKE_MAX_LENGTH];
    snake[0] = {4,1,2,true};
    snake[1] = {4,0,2,false};

    // Game Loop
    while (true)
    {
        int key = _getch(); // get key value

        switch(key) {
            case KEY_ESC:
                //cout << "ESC" << endl;
                break;
            case KEY_ENTER:
                //cout << "ENTER" << endl;
                break;
        }

        // arrow keys can return 0 or 244 depending on num lock
        // second call is for second value returned by arrow key
        if (key == 0 || key == 244) {
            switch(_getch()) {
                case KEY_UP:
                    if (snake[0].dir == 3) {break;}
                    snake[0].dir = 1;
                    break;
                case KEY_DOWN:
                    if (snake[0].dir == 1) {break;}
                    snake[0].dir = 3;
                    break;
                case KEY_LEFT:
                    if (snake[0].dir == 2) {break;}
                    snake[0].dir = 4;
                    break;
                case KEY_RIGHT:
                    if (snake[0].dir == 4) {break;}
                    snake[0].dir = 2;
                    break;
            }
        }
        int snake_length = sizeof(snake)/sizeof(SnakeSegment);

        for (int i=snake_length; i>0; i--){
            snake[i].dir = snake[i-1].dir;
        }

        int dx = 0;
        int dy = 0;
        for (int i=0; i<snake_length; i++){
            switch(snake[i].dir){
                case 1:
                    dy = 1;
                    break;
                case 2:
                    dx = 1;
                    break;
                case 3:
                    dy = -1;
                    break;
                case 4:
                    dx = -1;
                    break;
            }
            snake[i].x += dx;
            snake[i].y += dy;
        }

        for (int i=0; i<snake_length; i++){
            cout << snake[i].x << ", " << snake[i].y << endl;
            display_field[snake[i].x][snake[i].y] = gameset["appl"];
        }
        
        system("cls");
        for (auto &col : display_field) {
            for (auto &elem : col) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }

    return 0;
}