#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <conio.h>

void moveEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, int &bulletcount, string &enemydirection, int &bulletx, int &bullety);
void printEnemy(char enemy[][6], int size1, int enemyx, int enemyy, char array[][72], int size, string &enemydirection);
void eraseEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, string &enemydirection);
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void loadmaze(char array[][72], int size);
void displaymaze(char array[][72], int size);

void generatebullet(int &bulletx, int &bullety, int &enemyx, int &enemyy, int &bulletcount);
void erasebullet(int bulletx, int bullety);
void printbullet(int &bulletx, int &bullety);
void movebullet(int &bulletx, int &bullety, int &bulletcount);
main()
{
    int enemyx = 19;
    int enemyy = 4;

    system("cls");
    // maze
    int size = 35;
    char array[size][72];

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
    int bulletx;
    int bullety;
    int bulletX[100];
    int bulletY[100];
    int bulletcount = 0;
    loadmaze(array, size);
    displaymaze(array, size);
    while (true)
    {
        moveEnemy(enemy, size1, enemyx, enemyy, array, size, bulletcount, enemydirection, bulletx, bullety);
        Sleep(10);
        movebullet(bulletx, bullety, bulletcount);
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

void moveEnemy(char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, int &bulletcount, string &enemydirection, int &bulletx, int &bullety)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);

    int counter = 0;
    while (counter % 3 == 0)
    {
        generatebullet(bulletx, bullety, enemyx, enemyy, bulletcount);
        counter++;
    }

    int l = 10;
    SetConsoleTextAttribute(hConsole, l);
    if (enemydirection == "up")
    {
        char next = getCharAtxy(enemyx, enemyy - 4);
        char next1 = getCharAtxy(enemyx + 1, enemyy - 1);
        char next2 = getCharAtxy(enemyx + 2, enemyy);
        char next3 = getCharAtxy(enemyx + 5, enemyy);
        char next4 = getCharAtxy(enemyx + 6, enemyy);
        if ((next == ' ') && (next1 == ' ') && (next2 == ' '))
        {
            eraseEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
            enemyy--;
            printEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
        }
        if (next == '#' || next1 == '#' || next2 == '#')
        {
            enemydirection = "down";
        }
    }
    // || next3 == '#' || next4 == '#' && (next3 == ' ')
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

void generatebullet(int &bulletx, int &bullety, int &enemyx, int &enemyy, int &bulletcount , int bulletX2[100] , int bulletY2[100])
{
    bulletx = enemyx + 8;
    bullety = enemyy + 1;
    bulletX2[bulletcount] = bulletx;
    bulletY2[bulletcount] = bullety;
    gotoxy(bulletx, bullety);
    cout << "o";
    bulletcount++;
}
void erasebullet(int bulletX2[100], int bulletY2[100])
{
    int x;
    gotoxy(bulletX2[x], bulletY2[x]);
    cout << " ";

}
void movebullet(int &bulletx, int &bullety, int &bulletcount, int bulletX2[100] , int bulletY2[100])
{
    for (int x = 0; x < bulletcount; x++)
    {
        
        char next = getCharAtxy(bulletX2[x] + 1, bulletY2[x]);
        if (next == ' ')
        {
            erasebullet(bulletX2[x], bulletY2[x]);
            bulletX2[x]++;
            printbullet(bulletx, bullety);
        }

        else
        {
            erasebullet(bulletx, bullety);
            // deletebulletfromarray(enemyx, enemyy);
        }
    }
}
void printbullet(int bulletX2[100], int bulletY2[100])
{
    int x;
    gotoxy(bulletX2[x], bulletY2[x]);
    cout << "o";
}