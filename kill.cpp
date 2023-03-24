#include <iostream>
#include <fstream>
using namespace std;
#include <windows.h>
#include <conio.h>
void print_hero(char hero[3][5], int &herox, int &heroy, char array[][72], int size);
void clearhero(char hero[3][5], int &herox, int &heroy, char array[][72], int size);

void move_hero_left(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health);
void move_hero_right(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health);
void move_hero_up(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health);
void move_hero_down(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health);
void moveEnemy(int &bulletx, int &bullety, char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, int &bulletcount, string &enemydirection, int bulletX2[100], int bulletY2[100]);
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

void generateBullet(int &herox, int &heroy, int &bulletcount1, int bulletX[], int bulletY[]);
void moveBullet(int &bulletcount1, int bulletX[], int bulletY[]);
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void deletebulletfromarray(int x, int bulletX[], int bulletY[], int &bulletcount1);

// enemy bullets
void generatebullet(int &bulletx, int &bullety, int &enemyx, int &enemyy, int &bulletcount, int bulletX2[], int bulletY2[]);
void erasebullet(int w, int y);
void printbullet(int w, int y);
void movebullet(int bulletX2[100], int bulletY2[100], int &bulletcount);
void deletebulletfromarray1(int x, int bulletX2[100], int bulletY2[100], int &bulletcount);

void health_detection(int &herox, int &heroy, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health);
void print_score(int &score, int &health, int &e1_health, int &e2_health, int &e3_health);
void hero_stop_health(int &herox, int &heroy, int &health);
void enemy1_health(int &e1_health, int &enemyx, int &enemyy);
void enemy2_health(int &enemy2x, int &enemy2y, int &e2_health);
void enemy3_health(int &enemy3x, int &enemy3y, int &e3_health);

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

string parse_data(string line, int field);
void loaddatafromfile(int &herox, int &heroy, int &health, int &score, string line, int field);
void store(int &herox, int &heroy, int &health, int &score);

string parse_data_enemy(string line_enemy, int field_enemy);
void loaddatafromfile_enemy(int &enemyx, int &enemyy, int &e1_health, string line_enemy, int field_enemy);
void store_enemy(int &enemyx, int &enemyy, int &e1_health);

string parse_data_enemy2(string line_enemy2, int field_enemy2);
void loaddatafromfile_enemy2(int &enemy2x, int &enemy2y, int &e2_health, string line_enemy2, int field_enemy2);
void store_enemy2(int &enemy2x, int &enemy2y, int &e2_health);

string parse_data_enemy3(string line_enemy3, int field_enemy3);
void loaddatafromfile_enemy3(int &enemy3x, int &enemy3y, int &e3_health, string line_enemy3, int field_enemy3);
void store_enemy3(int &enemy3x, int &enemy3y, int &e3_health);

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

    // hero bullets
    int bulletX[100];
    int bulletY[100];
    bool isBulletActive[100];
    int bulletcount1 = 0;

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
    int e2_health = 5;
    char enemy2[e2_size][2] = {o, q};
    int enemy2x = 50;
    int enemy2y = 10;

    // enemy3
    string direction3 = "Left";
    char w = 219;
    char l = 254;
    int e3_size = 1;
    int e3_health = 5;
    char enemy3[e3_size][2] = {l, w};
    int enemy3x = 30;
    int enemy3y = 30;

    // enemy 1 bullets
    int bulletx = 0;
    int bullety = 0;
    int bulletX2[100];
    int bulletY2[100];
    bool isBulletActive2[100];
    int bulletcount = 0;
    int index;
    int e1_health = 5;
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

    // health & score system
    int score = 0;
    int health = 100;
    int enemy_counter = 0;

    string line;
    int field;
    string line_enemy;
    int field_enemy;
    string line_enemy2;
    int field_enemy2;
    string line_enemy3;
    int field_enemy3;

    loadmaze(array, size);
    loaddatafromfile(herox, heroy, health, score, line, field);
    loaddatafromfile_enemy(enemyx, enemyy, e1_health, line_enemy, field_enemy);
    loaddatafromfile_enemy2(enemy2x, enemy2y, e2_health, line_enemy2, field_enemy2);
    loaddatafromfile_enemy3(enemy3x, enemy3y, e3_health, line_enemy3, field_enemy3);

    int menu_choice = menu(array2, size5);
    if (menu_choice == 1)
    {
        system("cls");
        displaymaze(array, size);
        while (true)
        {

            loaddatafromfile(herox, heroy, health, score, line, field);
            loaddatafromfile_enemy(enemyx, enemyy, e1_health, line_enemy, field_enemy);
            loaddatafromfile_enemy2(enemy2x, enemy2y, e2_health, line_enemy2, field_enemy2);
            loaddatafromfile_enemy3(enemy3x, enemy3y, e3_health, line_enemy3, field_enemy3);

            if (health >= 0 && score < 97)
            {
                hero_stop_health(herox, heroy, health);
                enemy3_health(enemy3x, enemy3y, e3_health);
                enemy2_health(enemy2x, enemy2y, e2_health);
                print_score(score, health, e1_health, e2_health, e3_health);
                print_hero(hero, herox, heroy, array, size);

                if (GetAsyncKeyState(VK_LEFT))
                {
                    move_hero_left(hero, herox, heroy, array, size, score, enemy, size1, enemy2x, enemy3x, health);
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_RIGHT))
                {
                    move_hero_right(hero, herox, heroy, array, size, score, enemy, size1, enemy2x, enemy3x, health);
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_UP))
                {
                    move_hero_up(hero, herox, heroy, array, size, score, enemy, size1, enemy2x, enemy3x, health);
                    Sleep(10);
                }

                if (GetAsyncKeyState(VK_DOWN))
                {
                    move_hero_down(hero, herox, heroy, array, size, score, enemy, size1, enemy2x, enemy3x, health);
                    Sleep(10);
                }
                if (GetAsyncKeyState(VK_SPACE))
                {
                    generateBullet(herox, heroy, bulletcount1, bulletX, bulletY);
                    Sleep(20);
                }
                // hero bullets
                moveBullet(bulletcount1, bulletX, bulletY);
                Sleep(20);
                if (e1_health > 0)
                {
                    moveEnemy(bulletx, bullety, enemy, size1, enemyx, enemyy, array, size, bulletcount, enemydirection, bulletX2, bulletY2);
                    Sleep(10);
                    enemy1_health(e1_health, enemyx, enemyy);
                    movebullet(bulletX2, bulletY2, bulletcount);
                }
                else
                {
                    enemy_counter++;
                    for (int x = 0; x < bulletcount; x++)
                    {
                        movebullet(bulletX2, bulletY2, bulletcount);
                        eraseEnemy(enemy, size1, enemyx, enemyy, array, size, enemydirection);
                    }
                }

                if (e2_health > 0)
                {
                    moveEnemy2right(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
                    Sleep(20);
                }
                else
                {
                    enemy_counter++;
                    e2_health = 0;
                    EraseEnemy2(array, size, enemy2, e2_size, enemy2x, enemy2y, direction2);
                }
                if (e3_health > 0)
                {
                    moveEnemy3right(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
                    Sleep(20);
                }
                else
                {

                    e3_health = 0;
                    EraseEnemy3(array, size, enemy3, e3_size, enemy3x, enemy3y, direction3);
                    enemy_counter++;
                }
                store(herox, heroy, health, score);
                store_enemy(enemyx, enemyy, e1_health);
                store_enemy2(enemy2x, enemy2y, e2_health);
                store_enemy3(enemy3x, enemy3y, e3_health);
            }
        }
    }
    if (menu_choice == 2)
    {
        cout << menu_choice;
        int opt = option2(array2, size5);
        if (opt == 1)
        {
            displaykeys(array3, size6);
            cout << "Press any key to continue: ";
            getch();
            opt = option2(array2, size5);
            menu_choice = menu(array2, size5);
        }
        if (opt == 2)
        {
            displayinstructions(array4, size7);
            cout << "Press any key to continue: ";
            getch();
            opt = option2(array2, size5);
            menu_choice = menu(array2, size5);
            cout << menu_choice;
        }
        if (opt == 3)
        {
            opt = option2(array2, size5);
            menu_choice = menu(array2, size5);
        }
        menu_choice = menu(array2, size5);
    }
    if (menu_choice != 1 && menu_choice != 2)
    {
        displayheader(array2, size5);
        menu_choice = menu(array2, size5);
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
void hero_stop_health(int &herox, int &heroy, int &health)
{

    char nextLocation1 = getCharAtxy(herox - 1, heroy);
    char nextLocation2 = getCharAtxy(herox - 1, heroy + 1);
    char nextLocation3 = getCharAtxy(herox, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox + 6, heroy + 1);
    char nextLocation6 = getCharAtxy(herox + 2, heroy + 2);
    if (herox - 1 == 'o' || herox + 2 == 'o' || herox + 3 == 'o' || (herox - 1 == 'o' && heroy + 1 == 'o') || (herox + 6 == 'o' && heroy + 1 == 'o') || (herox - 1 == 'o' && heroy + 2 == 'o') || (herox + 3 == 'o' && heroy + 2 == 'o'))
    {
        health--;
    }
    if (nextLocation1 == 'o' || nextLocation2 == 'o' || nextLocation3 == 'o' || nextLocation4 == 'o' || nextLocation5 == 'o' || nextLocation6 == 'o')
    {
        health--;
    }
}
void health_detection(int &herox, int &heroy, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health)
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
void store(int &herox, int &heroy, int &health, int &score)
{
    fstream file;
    file.open("hero.txt", ios::out);
    file << herox << "," << heroy << "," << health << "," << score << endl;
    file.close();
}
void loaddatafromfile(int &herox, int &heroy, int &health, int &score, string line, int field)
{

    fstream file;
    file.open("hero.txt", ios::in);
    while (getline(file, line))
    {

        herox = stoi(parse_data(line, 1));
        heroy = stoi(parse_data(line, 2));
        health = stoi(parse_data(line, 3));
        score = stoi(parse_data(line, 4));
    }
    file.close();
    if (health <= 0)
    {
        health = 100;
    }
}
string parse_data(string line, int field)
{
    string item = "";
    int commacount = 1;
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            commacount++;
        }
        else if (commacount == field)
        {
            item = item + line[i];
        }
    }
    return item;
}
void move_hero_left(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health)
{

    char nextLocation1 = getCharAtxy(herox - 1, heroy);
    char nextLocation2 = getCharAtxy(herox - 1, heroy + 1);
    char nextLocation3 = getCharAtxy(herox, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox, heroy + 3);
    char nextLocation6 = getCharAtxy(herox - 6, heroy + 2);
    health_detection(herox, heroy, enemy, size1, enemy2x, enemy3x, health);
    hero_stop_health(herox, heroy, health);
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
    if (nextLocation1 == 'o' || nextLocation2 == 'o' || nextLocation3 == 'o' || nextLocation4 == 'o' || nextLocation5 == 'o' || nextLocation6 == 'o')
    {
        health--;
    }
}

void move_hero_right(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health)
{
    char nextLocation1 = getCharAtxy(herox + 2, heroy);
    char nextLocation2 = getCharAtxy(herox + 5, heroy + 1);
    char nextLocation3 = getCharAtxy(herox + 2, heroy + 2);
    char nextLocation4 = getCharAtxy(herox, heroy);
    health_detection(herox, heroy, enemy, size1, enemy2x, enemy3x, health);
    hero_stop_health(herox, heroy, health);
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

    if (nextLocation1 == 'o' || nextLocation2 == 'o' || nextLocation3 == 'o' && nextLocation4 == 'o')
    {
        health--;
    }
}
void move_hero_up(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health)
{
    char nextLocation1 = getCharAtxy(herox + 1, heroy - 1);
    char nextLocation2 = getCharAtxy(herox, heroy - 1);
    char nextLocation3 = getCharAtxy(herox + 2, heroy);
    char nextLocation4 = getCharAtxy(herox + 3, heroy);
    char nextLocation5 = getCharAtxy(herox + 4, heroy);
    health_detection(herox, heroy, enemy, size1, enemy2x, enemy3x, health);
    hero_stop_health(herox, heroy, health);

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
    if (nextLocation1 == 'o' || nextLocation2 == 'o' || nextLocation3 == 'o' || nextLocation4 == 'o' || nextLocation5 == 'o')
    {
        health--;
    }
}
void move_hero_down(char hero[3][5], int &herox, int &heroy, char array[][72], int size, int &score, char enemy[][6], int size1, int &enemy2x, int &enemy3x, int &health)
{
    char nextLocation1 = getCharAtxy(herox, heroy + 2);
    char nextLocation2 = getCharAtxy(herox + 1, heroy + 3);
    char nextLocation3 = getCharAtxy(herox + 2, heroy + 2);
    char nextLocation4 = getCharAtxy(herox + 3, heroy + 2);
    char nextLocation5 = getCharAtxy(herox + 4, heroy + 2);
    health_detection(herox, heroy, enemy, size1, enemy2x, enemy3x, health);
    hero_stop_health(herox, heroy, health);
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
    if (nextLocation1 == 'o' || nextLocation2 == 'o' || nextLocation3 == 'o' || nextLocation4 == 'o' || nextLocation5 == 'o')
    {
        health--;
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
void generatebullet(int &bulletx, int &bullety, int &enemyx, int &enemyy, int &bulletcount, int bulletX2[], int bulletY2[])
{
    bulletx = enemyy + 1;
    bullety = enemyx + 3;
    bulletX2[bulletcount] = bulletx;
    bulletY2[bulletcount] = bulletx;
    gotoxy(bulletX2[bulletcount], bulletY2[bulletcount]);
    cout << "o";
    bulletcount++;
}
void erasebullet(int w, int y)
{
    gotoxy(w, y);
    cout << " ";
}
void movebullet(int bulletX2[100], int bulletY2[100], int &bulletcount)
{
    for (int x = 0; x < bulletcount; x++)
    {

        char next = getCharAtxy(bulletX2[x] + 1, bulletY2[x]);
        if (next == ' ')
        {
            erasebullet(bulletX2[x], bulletY2[x]);
            bulletX2[x] = bulletX2[x] + 1;
            printbullet(bulletX2[x], bulletY2[x]);
        }

        else
        {
            erasebullet(bulletX2[x], bulletY2[x]);
            deletebulletfromarray1(x, bulletX2, bulletY2, bulletcount);
        }
    }
}
void store_enemy(int &enemyx, int &enemyy, int &e1_health)
{
    fstream file;
    file.open("enemy.txt", ios::out);
    file << enemyx << "," << enemyy << "," << e1_health << endl;
    file.close();
}
void loaddatafromfile_enemy(int &enemyx, int &enemyy, int &e1_health, string line_enemy, int field_enemy)
{

    fstream file;
    file.open("enemy.txt", ios::in);
    while (getline(file, line_enemy))
    {

        enemyx = stoi(parse_data(line_enemy, 1));
        enemyy = stoi(parse_data(line_enemy, 2));
        e1_health = stoi(parse_data(line_enemy, 3));
    }
    file.close();
    if (e1_health <= 0)
    {
        e1_health = 5;
    }
}
string parse_data_enemy(string line_enemy, int field_enemy)
{
    string item = "";
    int commacount = 1;
    for (int i = 0; i < line_enemy.length(); i++)
    {
        if (line_enemy[i] == ',')
        {
            commacount++;
        }
        else if (commacount == field_enemy)
        {
            item = item + line_enemy[i];
        }
    }
    return item;
}
void printbullet(int w, int y)
{
    gotoxy(w, y);
    cout << "o";
}

void deletebulletfromarray1(int x, int bulletX2[100], int bulletY2[100], int &bulletcount)
{
    for (int i = x; i < bulletcount; i++)
    {
        bulletX2[i] = bulletX2[i + 1];
        bulletY2[i] = bulletY2[i + 1];
    }
    bulletcount--;
}
void moveEnemy(int &bulletx, int &bullety, char enemy[][6], int size1, int &enemyx, int &enemyy, char array[][72], int size, int &bulletcount, string &enemydirection, int bulletX2[100], int bulletY2[100])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k = 5;
    SetConsoleTextAttribute(hConsole, k);

    int counter = 0;
    while (counter % 3 == 0)
    {
        bulletx = enemyx + 3;
        bullety = enemyy + 1;
        generatebullet(bulletx, bullety, enemyx, enemyy, bulletcount, bulletX2, bulletY2);

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

void enemy1_health(int &e1_health, int &enemyx, int &enemyy)
{
    char next = getCharAtxy(enemyx + 1, enemyy);
    char next1 = getCharAtxy(enemyx + 4, enemyy);
    char next2 = getCharAtxy(enemyx - 1, enemyy + 1);
    char next3 = getCharAtxy(enemyx + 7, enemyy + 1);
    char next4 = getCharAtxy(enemyx + 2, enemyy + 2);
    char next5 = getCharAtxy(enemyx + 5, enemyy + 2);
    char next6 = getCharAtxy(enemyx + 5, enemyy + 3);
    char next7 = getCharAtxy(enemyx + 2, enemyy + 3);
    if (next == '*' || next1 == '*' || next2 == '*' || next3 == '*' || next4 == '*' || next5 == '*' || next6 == '*' || next7 == '*')
    {
        e1_health--;
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
        cout << enemy2[0][i];
    }
}
void store_enemy2(int &enemy2x, int &enemy2y, int &e2_health)
{
    fstream file;
    file.open("enemy2.txt", ios::out);
    file << enemy2x << "," << enemy2y << "," << e2_health << endl;
    file.close();
}
void loaddatafromfile_enemy2(int &enemy2x, int &enemy2y, int &e2_health, string line_enemy2, int field_enemy2)
{

    fstream file;
    file.open("enemy2.txt", ios::in);
    while (getline(file, line_enemy2))
    {

        enemy2x = stoi(parse_data(line_enemy2, 1));
        enemy2y = stoi(parse_data(line_enemy2, 2));
        e2_health = stoi(parse_data(line_enemy2, 3));
    }
    file.close();
    if (e2_health <= 0)
    {
        e2_health = 5;
    }
}
string parse_data_enemy2(string line_enemy2, int field_enemy2)
{
    string item = "";
    int commacount = 1;
    for (int i = 0; i < line_enemy2.length(); i++)
    {
        if (line_enemy2[i] == ',')
        {
            commacount++;
        }
        else if (commacount == field_enemy2)
        {
            item = item + line_enemy2[i];
        }
    }
    return item;
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
void enemy2_health(int &enemy2x, int &enemy2y, int &e2_health)
{
    char next = getCharAtxy(enemy2x - 1, enemy2y);
    char next1 = getCharAtxy(enemy2x + 2, enemy2y);
    if (next == '*' || next1 == '*')
    {
        e2_health--;
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
void store_enemy3(int &enemy3x, int &enemy3y, int &e3_health)
{
    fstream file;
    file.open("enemy3.txt", ios::out);
    file << enemy3x << "," << enemy3y << "," << e3_health << endl;
    file.close();
}
void loaddatafromfile_enemy3(int &enemy3x, int &enemy3y, int &e3_health, string line_enemy3, int field_enemy3)
{

    fstream file;
    file.open("enemy3.txt", ios::in);
    while (getline(file, line_enemy3))
    {

        enemy3x = stoi(parse_data(line_enemy3, 1));
        enemy3y = stoi(parse_data(line_enemy3, 2));
        e3_health = stoi(parse_data(line_enemy3, 3));
    }
    file.close();
    if (e3_health <= 0)
    {
        e3_health = 5;
    }
}
string parse_data_enemy3(string line_enemy3, int field_enemy3)
{
    string item = "";
    int commacount = 1;
    for (int i = 0; i < line_enemy3.length(); i++)
    {
        if (line_enemy3[i] == ',')
        {
            commacount++;
        }
        else if (commacount == field_enemy3)
        {
            item = item + line_enemy3[i];
        }
    }
    return item;
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
void enemy3_health(int &enemy3x, int &enemy3y, int &e3_health)
{
    char next = getCharAtxy(enemy3x - 1, enemy3y);
    char next1 = getCharAtxy(enemy3x + 2, enemy3y);
    if (next == '*' || next1 == '*')
    {
        e3_health--;
    }
}
void print_score(int &score, int &health, int &e1_health, int &e2_health, int &e3_health)
{
    gotoxy(75, 15);
    cout << "MR_BULLET aka HERO Score: " << score;
    gotoxy(75, 16);
    cout << "Hero Health: " << health << " ";
    gotoxy(75, 17);
    cout << "MR_FIGHTER aka GREEN Enemy Health: " << e1_health << " ";
    gotoxy(75, 18);
    cout << "MR_BLUE Health: " << e2_health << " ";
    gotoxy(75, 19);
    cout << "MR-PURPLE Health: " << e3_health << " ";
}
