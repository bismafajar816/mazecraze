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

// hero functions mr-bullet
void create_mr_bullet(int herox, int heroy);
void clearhero(int herox, int heroy);
void move_hero_left();
void move_hero_right();
void move_hero_up();
void move_hero_down();
char i = 2;
char k = 19;

char hero[3][5] = {{' ', i, ' ', ' ', ' '},
                   {'<', '#', '-', '-', '>'},
                   {' ', k, ' ', ' ', ' '}};
int herox = 10;
int heroy = 5;

// hero bullet
void generateBullet();
void moveBullet();
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void makeBulletInactive(int idx);
int bulletX[100];
int bulletY[100];
bool isBulletActive[100];
int bulletCount = 0;

// enemy(mr-fighter)
void eraseEnemy();
void moveEnemy();
char h = 127;
char m = 193;
char j = 176;
char enemy[4][6] = {{' ', ' ', ' ', h, h, ' '},
                    {'<', '-', '-', m, m, '>'},
                    {' ', ' ', ' ', '@', '@', ' '},
                    {' ', ' ', ' ', '!', '!', ' '}};
string enemydirection = "down";

int enemyx = 20;
int enemyy = 5;

// enemy2
void printEnemy2();
void EraseEnemy2();
void moveEnemy2right();
string direction2 = "Right";
int enemy2x = 50;
int enemy2y = 10;

// enemy3
void printEnemy3();
void EraseEnemy3();
void moveEnemy3right();
string direction3 = "Left";
char w = 219;
char l = 254;
char enemy1[1][2] = {l, w};
int enemy3x = 30;
int enemy3y = 19;

// enemy 1 bullets
void generateBullet2();
void deletebulletfromarray(int index);
void makeBulletInactive2(int idx);
void printBullet2(int x, int y);
void eraseBullet2(int x, int y);
void moveBullet2();
int bulletX2[100];
int bulletY2[100];
bool isBulletActive2[100];
int bulletCount2 = 0;

// details
int health = 100;
int score = 0;
void maze();
void print_score(int score, int health);
void collision();
void health_detection();
int add = 0;

// menu
//pass by reference functions

int option2(char array2[][102], int size5);
int menu(char array2[][102], int size5);
void loadlogo(char array1[][57], int size4);
void displaylogo(char array1[][57], int size4);
void loadheader(char array2[][102], int size5);
void displayheader(char array2[][102], int size5);
void loadkeys(char array3[][58], int size6);
void displaykeys(char array3[][58], int size6);
void loadinstructions(char array4[][82], int size7);
void displayinstructions(char array4[][82], int size7);


main()
{
    // refernces 
    system("cls");
    int size = 35;
    char array[35][72];
    loadmaze(array, size);
    int size4 = 18;
    char array1[23][57];
    loadlogo(array1, size4);
    displaylogo(array1, size4);
    cout << "Press any key to continue: ";
    getch();

    int size5 = 8;
    char array2[8][102];
    loadheader(array2, size5);

    int size6 = 6;
    char array3[6][58];
    loadkeys(array3, size6);

      int size7 = 6;
    char array4[6][82];
    loadinstructions(array4, size7);

    int menu_choice = menu(array2, size5);
    if (menu_choice == 1)
    {
        system("cls");

        displaymaze(array, size);
        while (true)
        {

            if (health >= 0)
            {
                print_score(score, health);
                create_mr_bullet(herox, heroy);

                if (GetAsyncKeyState(VK_LEFT))
                {
                    move_hero_left();
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_RIGHT))
                {
                    move_hero_right();
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_UP))
                {
                    move_hero_up();
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_DOWN))
                {
                    move_hero_down();
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_SPACE))
                {
                    generateBullet();
                    Sleep(10);
                }

                moveBullet();
                moveEnemy();
                Sleep(20);
                moveBullet2();
                Sleep(20);
                moveEnemy2right();
                moveEnemy3right();
                collision();
                Sleep(10);
            }
        }
    }
    if (menu_choice == 2)
    {
        int opt = option2(array2, size5);

        if (opt == 1)
        {
            displaykeys(array3, size6);
            cout << "Press any key to continue: ";
            getch();
            opt = option2(array2, size5);
        }
       else if (opt == 2)
        {
            displayinstructions(array4,size7);
            cout << "Press any key to continue: ";
            getch();
            menu(array2, size5);
            menu_choice = menu(array2, size5);
            
        }

       else if (opt == 3)
        {
            menu(array2, size5);
        }
    }
    else
    {
        displayheader(array2, size5);
        menu(array2, size5);
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

void loadlogo(char array1[][57], int size4)
{
    string line;
    fstream maze;
    int row = 0;
    maze.open("logo.txt", ios::in);
    while (getline(maze, line))
    {
        for (int index = 0; index < line.length(); index++)
        {
            array1[row][index] = line[index];
        }
        row++;
    }
}
void displaylogo(char array1[][57], int size4)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 3;
    SetConsoleTextAttribute(hConsole, k);
    cout << endl;
    cout << endl;
    cout << endl;
    for (int row = 0; row < size4; row++)
    {
        for (int col = 0; col < 56; col++)
        {
            cout << array1[row][col];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

void loadheader(char array2[][102], int size5)
{
    string line;
    fstream maze;
    int row = 0;
    maze.open("header.txt", ios::in);
    while (getline(maze, line))
    {
        for (int index = 0; index < line.length(); index++)
        {
            array2[row][index] = line[index];
        }
        row++;
    }
}
void displayheader(char array2[][102], int size5)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 14;
    SetConsoleTextAttribute(hConsole, k);
    cout << endl;
    cout << endl;
    cout << endl;

    for (int row = 0; row < size5; row++)
    {
        for (int col = 0; col < 101; col++)
        {
            cout << array2[row][col];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
}
void loadkeys(char array3[][58], int size6)
{
    string line;
    fstream maze;
    int row = 0;
    maze.open("keys.txt", ios::in);
    while (getline(maze, line))
    {
        for (int index = 0; index < line.length(); index++)
        {
            array3[row][index] = line[index];
        }
        row++;
    }
}
void displaykeys(char array3[][58], int size6)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 9;
    SetConsoleTextAttribute(hConsole, k);
    cout << endl;
    cout << endl;
    for (int row = 0; row < size6; row++)
    {
        for (int col = 0; col < 57; col++)
        {
            cout << array3[row][col];
        }
        cout << endl;
    }
}

void loadinstructions(char array4[][82], int size7)
{
    string line;
    fstream maze;
    int row = 0;
    maze.open("instructions.txt", ios::in);
    while (getline(maze, line))
    {
        for (int index = 0; index < line.length(); index++)
        {
            array4[row][index] = line[index];
        }
        row++;
    }
}
void displayinstructions(char array4[][82], int size7)
{
      HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    for (int row = 0; row < size7; row++)
    {
        for (int col = 0; col < 80; col++)
        {
            cout << array4[row][col];
        }
        cout << endl;
    }
}


int menu(char array2[][102], int size5)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 6;
    SetConsoleTextAttribute(hConsole, k);
    system("cls");
    displayheader(array2, size5);
    int option;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Menu" << endl;
    cout << "___________________________________" << endl;
    cout << "1. Start" << endl;
    cout << "2. Option" << endl;
    cout << "3. Exit" << endl;
    cout << endl;
    cout << "Your Choice: " << endl;
    cin >> option;
    return option;
}
int option2(char array2[][102], int size5)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);
    system("cls");
    displayheader(array2, size5);
    int choice;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "_________________________________" << endl;
    cout << "1. Keys" << endl;
    cout << "2. Instructions" << endl;
    cout << "3. Exit" << endl;
    cout << endl;
    cout << "Your Choice" << endl;
    cin >> choice;
    return choice;
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
void create_mr_bullet(int herox, int heroy)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 2;
    SetConsoleTextAttribute(hConsole, k);

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
void clearhero(int herox, int heroy)
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
void move_hero_left()
{

    char nextLocation1 = getCharAtxy(herox - 1, heroy);
    char nextLocation2 = getCharAtxy(herox - 1, heroy + 1);
    char nextLocation3 = getCharAtxy(herox, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox, heroy + 3);
    char nextLocation6 = getCharAtxy(herox - 6, heroy + 3);
    health_detection();
    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation6 == ' ')
    {
        clearhero(herox, heroy);
        herox--;
        create_mr_bullet(herox, heroy);
    }
    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' || nextLocation4 == '.' || nextLocation5 == '.' || nextLocation6 == '.')
    {
        score = score + 1;
        clearhero(herox, heroy);
        herox--;
        create_mr_bullet(herox, heroy);
    }
}
// health detection
void health_detection()
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
void move_hero_right()
{
    char nextLocation1 = getCharAtxy(herox + 2, heroy);
    char nextLocation2 = getCharAtxy(herox + 5, heroy + 1);
    char nextLocation3 = getCharAtxy(herox + 2, heroy + 2);
    char nextLocation4 = getCharAtxy(herox, heroy);
    health_detection();
    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation4 == ' ')
    {
        clearhero(herox, heroy);
        herox++;
        create_mr_bullet(herox, heroy);
    }

    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' && nextLocation4 == ' ')
    {
        score = score + 1;

        clearhero(herox, heroy);
        herox++;
        create_mr_bullet(herox, heroy);
    }
}
void move_hero_up()
{
    char nextLocation1 = getCharAtxy(herox + 1, heroy - 1);
    char nextLocation2 = getCharAtxy(herox, heroy - 1);
    char nextLocation3 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox + 3, heroy);
    char nextLocation5 = getCharAtxy(herox + 4, heroy);
    health_detection();
    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation4 == ' ' && nextLocation5 == ' ')
    {
        clearhero(herox, heroy);
        heroy--;
        create_mr_bullet(herox, heroy);
    }
    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' || nextLocation4 == '.' || nextLocation5 == '.')
    {
        score = score + 1;
        clearhero(herox, heroy);
        heroy--;
        create_mr_bullet(herox, heroy);
    }
}
void move_hero_down()
{
    char nextLocation1 = getCharAtxy(herox, heroy + 2);
    char nextLocation2 = getCharAtxy(herox + 1, heroy + 3);
    char nextLocation3 = getCharAtxy(herox + 2, heroy + 2);
    char nextLocation4 = getCharAtxy(herox + 3, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 4, heroy + 2);
    health_detection();
    if (nextLocation1 == ' ' && nextLocation2 == ' ' && nextLocation3 == ' ' && nextLocation4 == ' ' && nextLocation5 == ' ')
    {
        clearhero(herox, heroy);
        heroy++;
        create_mr_bullet(herox, heroy);
    }
    if (nextLocation1 == '.' || nextLocation2 == '.' || nextLocation3 == '.' || nextLocation4 == '.' || nextLocation5 == '.')
    {
        score = score + 1;
        clearhero(herox, heroy);
        heroy++;
        create_mr_bullet(herox, heroy);
    }
}
void print_score(int score, int health)
{
    gotoxy(90, 15);
    cout << "Score : " << score + add;
    gotoxy(90, 17);
    cout << "Health : " << health << " ";
}
void generateBullet()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);
    bulletX[bulletCount] = herox + 5;
    bulletY[bulletCount] = heroy + 1;
    isBulletActive[bulletCount] = true;
    gotoxy(herox + 6, heroy);
    cout << "*";
    bulletCount++;
}
// move bullet
void moveBullet()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);
            if (next != ' ')
            {
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
            }
            else
            {
                eraseBullet(bulletX[x], bulletY[x]);
                bulletX[x] = bulletX[x] + 1;
                printBullet(bulletX[x], bulletY[x]);
            }
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
void makeBulletInactive(int idx)
{
    isBulletActive[idx] = false;
}
void printEnemy()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 10;
    SetConsoleTextAttribute(hConsole, k);

    gotoxy(enemyx, enemyy);
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
void moveEnemy()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);
    int counter = 0;
    while (counter % 3 == 0)
    {
        generateBullet2();
        counter++;
    }
    int l = 10;
    SetConsoleTextAttribute(hConsole, l);
    if (enemydirection == "up")
    {
        char next = getCharAtxy(enemyx, enemyy - 4);
        char next1 = getCharAtxy(enemyx + 1, enemyy);
        char next2 = getCharAtxy(enemyx + 2, enemyy);
        char next3 = getCharAtxy(enemyx + 5, enemyy);
        char next4 = getCharAtxy(enemyx + 6, enemyy);
        if ((next == ' ' || next == '.') || (next1 == ' ' || next1 == '.') || (next2 == ' ' || next2 == '.') || (next3 == ' ' || next3 == '.') || (next4 == ' ' || next4 == '.'))
        {
            eraseEnemy();
            enemyy--;
            printEnemy();
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
            eraseEnemy();
            enemyy++;
            printEnemy();
        }
        if (next == '#' || next1 == '#' || next2 == '#' || next3 == '#' || next4 == '#' || next5 == '#' || next6 == '#')
        {
            enemydirection = "up";
        }
    }
}
void eraseEnemy()
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
void collision()
{

    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {
            if (bulletX[x] + 1 == enemyx && (bulletY[x] == enemyy || bulletX[x] == enemyy + 2 || bulletY[x] == enemyy + 3))
            {
                add++;
            }
            if (enemyx - 1 == bulletX[x] && enemyy + 1 == bulletY[x])
            {
                add++;
            }
        }
    }
}
void printEnemy2()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 9;
    SetConsoleTextAttribute(hConsole, k);
    char j = 219;
    char l = 254;
    char enemy[2] = {j, l};
    gotoxy(enemy2x, enemy2y);
    for (int i = 0; i < 2; i++)
    {
        cout << enemy[i];
    }
}
void EraseEnemy2()
{

    gotoxy(enemy2x, enemy2y);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
}
void moveEnemy2right()
{

    if (direction2 == "Left")
    {
        char next = getCharAtxy(enemy2x - 1, enemy2y);

        if (next == ' ')
        {

            EraseEnemy2();
            enemy2x--;
            printEnemy2();
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
            EraseEnemy2();
            enemy2x++;
            printEnemy2();
        }
        if (next == '#')
        {
            direction2 = "Left";
        }
    }
}

void printEnemy3()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);

    gotoxy(enemy3x, enemy3y);
    for (int l = 0; l < 1; l++)
    {
        for (int i = 0; i < 2; i++)
        {
            cout << enemy1[l][i];
        }
    }
}
void EraseEnemy3()
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
void moveEnemy3right()
{

    if (direction3 == "Left")
    {
        char next = getCharAtxy(enemy3x - 1, enemy3y);

        if (next == ' ')
        {

            EraseEnemy3();
            enemy3x--;
            printEnemy3();
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
            EraseEnemy3();
            enemy3x++;
            printEnemy3();
        }
        if (next == '#')
        {
            direction3 = "Left";
        }
    }
}
void generateBullet2()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 8;
    SetConsoleTextAttribute(hConsole, k);
    bulletX2[bulletCount2] = enemyx - 1;
    bulletY2[bulletCount2] = enemyy + 1;
    isBulletActive2[bulletCount2] = true;
    gotoxy(enemyx - 1, enemyy + 1);
    cout << "o";
    bulletCount2++;
}
void moveBullet2()
{
    for (int x = 0; x < bulletCount2; x++)
    {

        char next = getCharAtxy(bulletX2[x] + 1, bulletY2[x]);
        if (next == ' ')
        {
            eraseBullet2(bulletX2[x], bulletY2[x]);
            bulletX2[x] = bulletX2[x] + 1;
            printBullet2(bulletX2[x], bulletY2[x]);
        }

        else
        {
            eraseBullet2(bulletX2[x], bulletY2[x]);
            deletebulletfromarray(x);
        }
    }
}
void deletebulletfromarray(int index)
{
    for (int i = index; i < bulletCount2; i++)
    {
        bulletX2[i] = bulletX2[i + 1];
        bulletY2[i] = bulletY2[i + 1];
    }
    bulletCount2--;
}
void printBullet2(int x, int y)
{
    gotoxy(x, y);
    cout << "o";
}
void eraseBullet2(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}
void makeBulletInactive2(int idx)
{
    isBulletActive2[idx] = false;
}
