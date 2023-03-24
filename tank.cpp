#include <iostream>
#include <windows.h>
using namespace std;
void printMaze();
void printTank();
void printEnemy();
void moveTankDown();
void moveTankLeft();
void moveTankUp();
void moveTankRight();
void moveEnemy();
void eraseEnemy();
void generateBullet();
void moveBullet();
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void makeBulletInactive(int idx);
void addScore();
void printScore();
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void bulletCollionWithEnemy();
void eraseTank();

int score = 0;
int timer = 3;
string enemyDirection = "Down";
// player character
char i = 2;
char k = 19;

char bullet1[5] = {' ', i, ' ', ' ', ' '};
char bullet2[5] = {'<', '#', '-', '-', '>'};
char bullet3[5] = {' ', k, ' ', ' ', ' '};
int herox = 15;
int heroy = 5;

// enemy character
char enemy1[6] = {' ', ' ', ' ', '-', '-', '-'};
char enemy2[6] = {'<', '=', '=', '(', '-', '('};
char enemy3[6] = {' ', ' ', ' ', '\\', '@', '/'};
char enemy4[6] = {' ', ' ', ' ', '*', '*', '*'};
// player coordinates
int tankX = 5;
int tankY = 5;
// enemy coordinates
int enemyX = 30;
int enemyY = 10;
// global arrays and variables //
// player bullets
int bulletX[100];
int bulletY[100];
bool isBulletActive[100];
int bulletCount = 0;

main()
{
    system("cls");
    printMaze();
    printTank();
    printEnemy();
    while (true)
    {
        printScore();
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveTankLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveTankRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveTankUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            moveTankDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }
        if (timer == 3)
        {
            moveEnemy();
            timer = 0;
        }

        moveBullet();
        bulletCollionWithEnemy();
        timer++;
        Sleep(90);
    }
}
void printMaze()
{
    char v = 12;
    cout << "########################################################################################################" << endl;
    cout << "#                                                                                                       #  " << endl;
    cout << "#    #####      #######     #    #    ########          #          #      #                             #       " << endl;
    cout << "#    #####         #        # #  #    #       #         #          #      # #    .      #    .    #     #     " << endl;
    cout << "#    #             #        #  # #    #       #         #     ######      #   #  .      #    .    #     #        " << endl;
    cout << "#    #          #######     #    #    #######           #          #      # #    .      #    .    #     #    " << endl;
    cout << "#                                                                  #      #      .      #    .    #     #   " << endl;
    cout << "#          ##########################################################            .      #    .    #     #       " << endl;
    cout << "#                                       .........................   #            .      #    .    #     #        " << endl;
    cout << "#        #   #  .   #      #                       .                #            .      #    .    #     #           " << endl;
    cout << "#         # #   .   #      #   #                   .          #######            .      #    .    #     #          " << endl;
    cout << "#          #    .   #      #  #######              .    ######   .               .      #    .    #     #            " << endl;
    cout << "#          #   ##   #      #   #    #              #####       .  .              .      #    .    #     #                " << endl;
    cout << "#          #   ##    ######    #                              .   .              .       #       #      #" << endl;
    cout << "#                                                    .........    .              .        #     #       #" << endl;
    cout << "#    ..............................                               .              .         #   #        #" << endl;
    cout << "#                                                                 .              .           #          #" << endl;
    cout << "#         # # # # # # # # # # # #                                 .                    . ....           # " << endl;
    cout << "#                                                    #         #  .                  .                  #   " << endl;
    cout << "#    ...............................                 #         #  .                 .                   # " << endl;
    cout << "#                   .                                #         #  .                .     #    #         #  " << endl;
    cout << "#                   .                                #    #    #  .               .      ######         #  " << endl;
    cout << "#      #########    .                                #   # #   #  .   ########   .            #         #   " << endl;
    cout << "#          #        .                                #  #   #  #  .   #      #   .            #         #" << endl;
    cout << "#          #        .  .............                 #         #  .   #########  .       #    #         #  " << endl;
    cout << "#          #        .               .                                             .      ######         #" << endl;
    cout << "#          #        .                .                                             .         ############" << endl;
    cout << "#          #        .                 ......................                        .        #     " << v << "    #" << endl;
    cout << "############        .     #########################        ###############            .       #    .    #  " << endl;
    cout << "#                   .                             #       #                            .       #   .    #  " << endl;
    cout << "# ...................                             #      #    ##########                .          .    # " << endl;
    cout << "#             .       ############################       #   #          #                .         .    #  " << endl;
    cout << "###########   .                                          #  #           #                  .........    #              " << endl;
    cout << "#         #   .......                                    # #            #                          .    #                   " << endl;
    cout << "#         #########  .                                   ##             #                      #   .    #              " << endl;
    cout << "#                    . .................................                #                    #     .    #               " << endl;
    cout << "#.....................                                                                      #      .    # " << endl;
    cout << "########################################################################################################              " << endl;
}
void printTank()
{
    gotoxy(herox, heroy);
    for (int i = 0; i < 5; i++)
    {
        cout << bullet1[i];
    }

    gotoxy(herox, heroy + 1);
    for (int i = 0; i < 5; i++)
    {
        cout << bullet2[i];
    }

    gotoxy(herox, heroy + 2);
    for (int i = 0; i < 5; i++)
    {
        cout << bullet3[i];
    }
}
void printEnemy()
{
    gotoxy(enemyX, enemyY);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << enemy1[idx];
    }

    gotoxy(enemyX, enemyY + 1);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << enemy2[idx];
    }

    gotoxy(enemyX, enemyY + 2);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << enemy3[idx];
    }

    gotoxy(enemyX, enemyY + 3);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << enemy4[idx];
    }
}
// CHARACTER MOVEMENT //
void moveTankLeft()
{
    char next = getCharAtxy(herox - 1, heroy);
    if (next == ' ')
    {
        eraseTank();
        herox = heroy - 1;
        printTank();
    }
    if (next == '.')
    {
        eraseTank();
        herox = heroy - 1;
        printTank();
    }
}
void moveTankRight()
{
    char next = getCharAtxy(herox + 6, heroy);
    if (next == ' ')
    {
        eraseTank();
        herox = herox + 1;
        printTank();
    }
    if (next == '.')
    {
        eraseTank();
        herox = heroy + 1;
        printTank();
    }
}
void moveTankUp()
{
    char next = getCharAtxy(tankX, tankY - 1);
    if (next == ' ')
    {
        eraseTank();
        heroy = heroy - 1;
        printTank();
    }
    if (next == '.')
    {
        eraseTank();
        heroy = heroy - 1;
        printTank();
    }
}
void moveTankDown()
{
    char next = getCharAtxy(tankX, tankY + 2);
    if (next == ' ')
    {
        eraseTank();
        heroy = heroy + 1;
        printTank();
    }
    if (next == '.')
    {
        eraseTank();
        heroy = heroy + 1;
        printTank();
    }
}
void moveEnemy()
{
    if (enemyDirection == "Up")
    {
        char next = getCharAtxy(enemyX, enemyY - 1);
        if (next == ' ')
        {
            eraseEnemy();
            enemyY--;
            printEnemy();
        }
        else if (next == '#')
        {
            enemyDirection = "Down";
        }
    }
    if (enemyDirection == "Down")
    {
        char next = getCharAtxy(enemyX, enemyY + 4);
        if (next == ' ')
        {
            eraseEnemy();
            enemyY++;
            printEnemy();
        }
        if (next == '#')
        {
            enemyDirection = "Up";
        }
    }
}
void eraseEnemy()
{
    gotoxy(enemyX, enemyY);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 1);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 2);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 3);
    for (int idx = 0; idx < 6; idx++)
    {
        cout << " ";
    }
}
void eraseTank()
{
    gotoxy(herox, heroy);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }

    gotoxy(herox, heroy + 1);
    for (int i = 0; i < 5; i++)
    {
        cout << " ";
    }

    gotoxy(herox, heroy + 2);
    for (int i = 0; i < 2; i++)
    {
        cout << " ";
    }
}
void generateBullet()
{
    bulletX[bulletCount] = tankX + 7;
    bulletY[bulletCount] = tankY;
    isBulletActive[bulletCount] = true;
    gotoxy(tankX + 7, tankY);
    cout << ".";
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
    gotoxy(x, y);
    cout << ".";
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
// collisionn detection
// collision with enemy
void bulletCollionWithEnemy()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (isBulletActive[x] == true)
        {

            if (bulletX[x] + 1 == enemyX && (bulletY[x] == enemyY || bulletY[x] == enemyY + 2 || bulletY[x] == enemyY + 3))
            {
                addScore();
            }
            if (enemyX - 1 == bulletX[x] && enemyY + 1 == bulletY[x])
            {
                addScore();
            }
        }
    }
}
// reward score
void addScore()
{
    score++;
}
void printScore()
{
    gotoxy(110, 3);
    cout << "score : " << score;
}
// supporting functions
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
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
