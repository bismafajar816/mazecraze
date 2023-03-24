#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;
// supporting functions
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void loadmaze(char array[][72], int size);
void displaymaze(char array[][72], int size);
void print_hero(char hero[3][5], int &herox, int &heroy, char array[][72], int size);
void clearhero(char hero[3][5], int &herox, int &heroy, char array[][72], int size);

void move_hero_left(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void move_hero_right(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void move_hero_up(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);
void move_hero_down(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score);

void generateBullet(int &herox, int &heroy, int &bulletcount1, int bulletX[], int bulletY[]);
void moveBullet(int &bulletcount1, int bulletX[], int bulletY[]);
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void deletebulletfromarray(int x, int bulletX[], int bulletY[], int &bulletcount1);
main()
{
    system("cls");
    // maze
    int size = 35;
    char array[size][72];
    int score = 0;
    // hero
    char i = 2;
    char k = 19;

    char hero[3][5] = {{' ', i, ' ', ' ', ' '},
                       {'<', '#', '-', '-', '>'},
                       {' ', k, ' ', ' ', ' '}};
    int herox = 10;
    int heroy = 5;
    // hero bullets
    int bulletX[100];
    int bulletY[100];
    bool isBulletActive[100];
    int bulletcount1 = 0;

    loadmaze(array, size);
    displaymaze(array, size);
    while (true)
    {
        // print_score(score);
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
        if (GetAsyncKeyState(VK_SPACE))
        {
           generateBullet(herox,heroy,bulletcount1,bulletX,bulletY);
           Sleep(20);
        }
        moveBullet(bulletcount1, bulletX,bulletY);
        Sleep(20);
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

void generateBullet(int &herox, int &heroy, int &bulletcount1, int bulletX[], int bulletY[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);
    bulletX[bulletcount1] = herox + 5;
    bulletY[bulletcount1] = heroy + 1;
    // isBulletActive[bulletcount1] = true;
    gotoxy(herox + 6, heroy);
    cout << "*";
    bulletcount1++;
}
// move bullet
void moveBullet(int &bulletcount1, int bulletX[], int bulletY[])
{
    for (int x = 0; x < bulletcount1; x++)
    {

        char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);
        if (next != ' ')
        {
            eraseBullet(bulletX[x], bulletY[x]);
            deletebulletfromarray(x, bulletX, bulletY, bulletcount1);
        }
        else
        {
            eraseBullet(bulletX[x], bulletY[x]);
            bulletX[x] = bulletX[x] + 1;
            printBullet(bulletX[x], bulletY[x]);
        }
    }
}
// supporting functions//
void printBullet(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 4;
    SetConsoleTextAttribute(hConsole, k);
    gotoxy(x, y);
    cout << "*";
}
void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void deletebulletfromarray(int x, int bulletX[], int bulletY[], int &bulletcount1)
{
    for (int i = x; i < bulletcount1; i++)
    {
        bulletX[i] = bulletX[i + 1];
        bulletY[i] = bulletY[i + 1];
    }
    bulletcount1--;
}

void health_detection(int &herox, int &heroy, char enemy[][],int &enemy2x , int &enemy3x, int &health )
{
    for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            if (herox == enemy[i][j] || herox == enemy[i][j] || herox == enemy[i][j] || herox == enemy[i][j] || herox == enemy2x || herox == enemy3x || herox == 'o')
            {
                health--;
            }
            else if (herox + 2 == enemy[i][j] || herox + 2 == enemy[i][j] || herox + 2 == enemy[i][j] || herox + 2 == enemy[i][j] || herox + 2 == enemy2x || herox + 2 == enemy3x || herox + 2 == 'o')
            {
                health--;
            }
        }
    }
}