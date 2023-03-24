#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;

void loadinstructions(char array4[][82], int size7);
void displayinstructions(char array4[][82], int size7);
main()
{
     int size7 = 6;
    char array4[6][82];
    loadinstructions(array4, size7);
    displayinstructions(array4,size7);
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
    for (int row = 0; row < size7; row++)
    {
        for (int col = 0; col < 80; col++)
        {
            cout << array4[row][col];
        }
        cout << endl;
    }
}
