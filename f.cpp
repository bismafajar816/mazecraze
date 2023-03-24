#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <conio.h>
void print_hero(char hero[3][5], int &herox, int &heroy, char array[][72], int size);
void clearhero(char hero[3][5], int &herox, int &heroy, char array[][72], int size);

void move_hero_left(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void move_hero_right(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void move_hero_up(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void move_hero_down(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void moveEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, string &enemydirection);
void printEnemy(char enemy[][6], int size1, int enemyx, int enemyy, char array[][72], int size, string &enemydirection);
void eraseEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, string &enemydirection);


void printEnemy2(char array[][72], int size, char enemy2[][2], int e2_size, int &enemy2x, int &enemy2y, string &direction2);
void EraseEnemy2(char array[][72], int size, char enemy2[][2], int e2_size, int &enemy2x, int &enemy2y, string &direction2);
void moveEnemy2right(char array[][72], int size, char enemy2[][2], int e2_size, int &enemy2x, int &enemy2y, string &direction2);
void printEnemy3(char array[][72], int size, char enemy3[][2], int e3_size, int &enemy3x, int &enemy3y, string &direction3);
void EraseEnemy3(char array[][72], int size, char enemy3[][2], int e3_size, int &enemy3x, int &enemy3y, string &direction3);
void moveEnemy3right(char array[][72], int size, char enemy3[][2], int e3_size, int &enemy3x, int &enemy3y, string &direction3);

void loadmaze(char array[][72], int size);
void displaymaze(char array[][72], int size);
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

void print_score(int &score);
main()
{
    system("cls");
    // maze
    int size = 35;
    char array[size][72];

    // hero
    char i = 2;
    char k = 19;

    char hero[3][5] = {{' ', i, ' ', ' ', ' '},
                       {'<', '#', '-', '-', '>'},
                       {' ', k, ' ', ' ', ' '}};
    int herox = 10;
    int heroy = 5;

    // enemy 1
    char h = 127;
    char m = 193;
    char j = 176;
    int size1 = 4;
    char enemy[size1][6] = {{' ', ' ', h, h, ' ', ' '},
                            {'<', '-', '-', m, m, '>'},
                            {' ', ' ', ' ', '@', '@', ' '},
                            {' ', ' ', ' ', '!', '!', ' '}};
    string enemydirection = "down";
    int enemyx = 19;
    int enemyy = 2;

    // enemy2
    string direction2 = "Right";
    char o = 219;
    char q = 254;
    int e2_size = 1;
    char enemy2[e2_size][2] = {o, q};

    int enemy2x = 50;
    int enemy2y = 10;

    // enemy3
    string direction3 = "Left";
    char w = 219;
    char l = 254;
    int e3_size = 1;
    char enemy3[e3_size][2] = {l, w};
    int enemy3x = 30;
    int enemy3y = 30;

    

    // health & score system
    int score = 0;
    loadmaze(array, size);
    displaymaze(array, size);
    while (true)
    {
        print_score(score);
        print_hero(hero, herox, heroy, array, size);

        if (GetAsyncKeyState(VK_LEFT))
        {
            move_hero_left(hero, herox, heroy, array, size, score);
            Sleep(10);
        }

        if (GetAsyncKeyState(VK_RIGHT))
        {
            move_hero_right(hero, herox, heroy, array, size, score);
            Sleep(10);
        }

        if (GetAsyncKeyState(VK_UP))
        {
            move_hero_up(hero, herox, heroy, array, size, score);
            Sleep(10);
        }

        if (GetAsyncKeyState(VK_DOWN))
        {
            move_hero_down(hero, herox, heroy, array, size, score);
            Sleep(10);
        }
        moveEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection );
        Sleep(20);
        moveEnemy2right(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
        Sleep(20);
        moveEnemy3right(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
        Sleep(10);
    }
}
void loadmaze(char array[][72], int size)
{
    string line;
    fstream maze;
    int row = 0;
    maze.open("maze.txt", ios::in);
    while (getline(maze, line))
    {
        for (int index = 0; index < line.length(); index++)
        {
            array[row][index] = line[index];
        }
        row++;
    }
}
void displaymaze(char array[][72], int size)
{
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < 71; col++)
        {
            cout << array[row][col];
        }
        cout << endl;
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
void print_hero(char hero[3][5], int &herox, int &heroy, char array[][72], int size)
{
    gotoxy(herox, heroy);

    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << hero[i][j];
        }
    }

    gotoxy(herox, heroy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << hero[i][j];
        }
    }

    gotoxy(herox, heroy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << hero[i][j];
        }
    }
}
void move_hero_left(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score)
{

    char nextLocation1 = getCharAtxy(herox - 1, heroy);
    char nextLocation2 = getCharAtxy(herox - 1, heroy + 1);
    char nextLocation3 = getCharAtxy(herox, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox, heroy + 3);
    char nextLocation6 = getCharAtxy(herox - 6, heroy + 2);

    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation6 == ' ')
    {
        clearhero(hero, herox, heroy, array, size);
        herox--;
        print_hero(hero, herox, heroy, array, size);
    }
    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' || nextLocation4 == '.' || nextLocation5 == '.' || nextLocation6 == '.')
    {
        score = score + 1;
        clearhero(hero, herox, heroy, array, size);
        herox--;
        print_hero(hero, herox, heroy, array, size);
    }
}

void move_hero_right(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score)
{
    char nextLocation1 = getCharAtxy(herox + 2, heroy);
    char nextLocation2 = getCharAtxy(herox + 5, heroy + 1);
    char nextLocation3 = getCharAtxy(herox + 2, heroy + 2);
    char nextLocation4 = getCharAtxy(herox, heroy);
    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation4 == ' ')
    {
        clearhero(hero, herox, heroy, array, size);
        herox++;
        print_hero(hero, herox, heroy, array, size);
    }

    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' && nextLocation4 == ' ')
    {
        score = score + 1;

        clearhero(hero, herox, heroy, array, size);
        herox++;
        print_hero(hero, herox, heroy, array, size);
    }
}
void move_hero_up(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score)
{
    char nextLocation1 = getCharAtxy(herox + 1, heroy - 1);
    char nextLocation2 = getCharAtxy(herox, heroy - 1);
    char nextLocation3 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox + 3, heroy);
    char nextLocation5 = getCharAtxy(herox + 4, heroy);

    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation4 == ' ' && nextLocation5 == ' ')
    {
        clearhero(hero, herox, heroy, array, size);
        heroy--;
        print_hero(hero, herox, heroy, array, size);
    }
    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' || nextLocation4 == '.' || nextLocation5 == '.')
    {
        score = score + 1;
        clearhero(hero, herox, heroy, array, size);
        heroy--;
        print_hero(hero, herox, heroy, array, size);
    }
}
void move_hero_down(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score)
{
    char nextLocation1 = getCharAtxy(herox, heroy + 2);
    char nextLocation2 = getCharAtxy(herox + 1, heroy + 3);
    char nextLocation3 = getCharAtxy(herox + 2, heroy + 2);
    char nextLocation4 = getCharAtxy(herox + 3, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 4, heroy + 2);

    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation4 == ' ' && nextLocation5 == ' ')
    {
        clearhero(hero, herox, heroy, array, size);
        heroy++;
        print_hero(hero, herox, heroy, array, size);
    }
    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' || nextLocation4 == '.' || nextLocation5 == '.')
    {
        score = score + 1;
        clearhero(hero, herox, heroy, array, size);
        heroy++;
        print_hero(hero, herox, heroy, array, size);
    }
}
void clearhero(char hero[3][5], int &herox, int &heroy, char array[][72], int size)
{

    gotoxy(herox, heroy);
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
    gotoxy(herox, heroy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
    gotoxy(herox, heroy + 2);

    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << " ";
        }
    }
}
void printEnemy(char enemy[][6], int size1, int enemyx, int enemyy, char array[][72], int size, string &enemydirection)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 10;
    SetConsoleTextAttribute(hConsole, k);

    gotoxy(enemyx, enemyy);
    cout << enemy[0][1];
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << enemy[i][j];
        }
    }
    gotoxy(enemyx, enemyy + 1);
    for (int i = 1; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << enemy[i][j];
        }
    }
    gotoxy(enemyx, enemyy + 2);
    for (int i = 2; i < 3; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << enemy[i][j];
        }
    }
    gotoxy(enemyx, enemyy + 3);
    for (int i = 3; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            cout << enemy[i][j];
        }
    }
}

void moveEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, string &enemydirection)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);

    int counter = 0;
    // while (counter % 3 == 0)
    // {
    //     moveBullet2(bulletX2, bulletY2, isBulletActive2, bulletCount2, enemyx, enemyy, index);
    //     counter++;
    // }
    int l = 10;
    SetConsoleTextAttribute(hConsole, l);
    if (enemydirection == "up")
    {
        char next = getCharAtxy(enemyx, enemyy - 4);
        char next1 = getCharAtxy(enemyx + 1, enemyy - 1);
        char next2 = getCharAtxy(enemyx + 2, enemyy);
        char next3 = getCharAtxy(enemyx + 5, enemyy);
        char next4 = getCharAtxy(enemyx + 6, enemyy);
        if ((next == ' ') && (next1 == ' ') && (next2 == ' ') && (next3 == ' ') && (next4 == ' '))
        {
            eraseEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
            enemyy--;
            printEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
        }
        if (next == '#' || next1 == '#' || next2 == '#' || next3 == '#' || next4 == '#')
        {
            enemydirection = "down";
        }
    }
    if (enemydirection == "down")
    {
        char next = getCharAtxy(enemyx, enemyy + 2);
        char next1 = getCharAtxy(enemyx + 1, enemyy + 2);
        char next2 = getCharAtxy(enemyx + 2, enemyy + 2);
        char next3 = getCharAtxy(enemyx + 5, enemyy + 2);
        char next4 = getCharAtxy(enemyx + 6, enemyy + 2);

        char next5 = getCharAtxy(enemyx + 3, enemyy + 5);
        char next6 = getCharAtxy(enemyx + 4, enemyy + 5);
        if ((next == ' ' || next == '.') || (next1 == ' ' || next1 == '.') || (next2 == ' ' || next2 == '.') || (next3 == ' ' || next3 == '.') || (next4 == ' ' || next4 == '.') || (next5 == ' ' || next5 == '.') || (next6 == ' ' || next6 == '.'))
        {
            eraseEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
            enemyy++;

            printEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
        }
        if (next == '#' || next1 == '#' || next2 == '#' || next3 == '#' || next4 == '#' || next5 == '#' || next6 == '#')
        {
            enemydirection = "up";
        }
    }
}
void eraseEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, string &enemydirection)
{
    gotoxy(enemyx, enemyy);
    for (int x = 0; x < 6; x++)
    {
        cout << " ";
    }
    gotoxy(enemyx, enemyy + 1);
    for (int x = 0; x < 6; x++)
    {
        cout << " ";
    }
    gotoxy(enemyx, enemyy + 2);
    for (int x = 0; x < 6; x++)
    {
        cout << " ";
    }
    gotoxy(enemyx, enemyy + 3);
    for (int x = 0; x < 6; x++)
    {
        cout << " ";
    }
}

void printEnemy2(char array[][72], int size, char enemy2[][2], int e2_size, int &enemy2x, int &enemy2y, string &direction2)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 9;
    SetConsoleTextAttribute(hConsole, k);

    gotoxy(enemy2x, enemy2y);
    for (int i = 0; i < 2; i++)
    {
        cout << enemy2[i];
    }
}
void EraseEnemy2(char array[][72], int size, char enemy2[][2], int e2_size, int &enemy2x, int &enemy2y, string &direction2)
{

    gotoxy(enemy2x, enemy2y);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
}
void moveEnemy2right(char array[][72], int size, char enemy2[][2], int e2_size, int &enemy2x, int &enemy2y, string &direction2)
{

    if (direction2 == "Left")
    {
        char next = getCharAtxy(enemy2x - 1, enemy2y);

        if (next == ' ')
        {

            EraseEnemy2(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
            enemy2x--;
            printEnemy2(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
        }

        if (next == '#')
        {
            direction2 = "Right";
        }
    }

    if (direction2 == "Right")
    {
        char next = getCharAtxy(enemy2x + 3, enemy2y);

        if (next == ' ')
        {
            EraseEnemy2(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
            enemy2x++;
            printEnemy2(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
        }
        if (next == '#')
        {
            direction2 = "Left";
        }
    }
}
void printEnemy3(char array[][72], int size, char enemy3[][2], int e3_size, int &enemy3x, int &enemy3y, string &direction3)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);

    gotoxy(enemy3x, enemy3y);
    for (int l = 0; l < 1; l++)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << enemy3[l][i];
        }
    }
}
void EraseEnemy3(char array[][72], int size, char enemy3[][2], int e3_size, int &enemy3x, int &enemy3y, string &direction3)
{
    gotoxy(enemy3x, enemy3y);
    for (int l = 0; l < 1; l++)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << " ";
        }
    }
}
void moveEnemy3right(char array[][72], int size, char enemy3[][2], int e3_size, int &enemy3x, int &enemy3y, string &direction3)
{

    if (direction3 == "Left")
    {
        char next = getCharAtxy(enemy3x - 1, enemy3y);

        if (next == ' ')
        {

            EraseEnemy3(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
            enemy3x--;
            printEnemy3(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
        }

        if (next == '#')
        {
            direction3 = "Right";
        }
    }

    if (direction3 == "Right")
    {
        char next = getCharAtxy(enemy3x + 2, enemy3y);

        if (next == ' ')
        {
            EraseEnemy3(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
            enemy3x++;
            printEnemy3(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
        }
        if (next == '#')
        {
            direction3 = "Left";
        }
    }
}
void print_score(int &score)
{
    gotoxy(75, 15);
    cout << "Score: " << score;
}

