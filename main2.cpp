// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT2L 
// Names: SYED DANIAL IMTIAZ BIN SYED ABDUL RAHIM | HILMAN DANISH BIN HAMKA 
// IDs: 1221301145 | 1221301132  
// Emails: 1221301145@student.mmu.edu.my | 1221301132@student.mmu.edu.my  
// Phones: 011-59221496 | 019-4742703  
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

class Board
{
private:
    vector< vector<char> >board_;
    int row_; 
    int column_;
    
public:
    Board();
    
    void setRow(int row);
    void setColumn(int column);

    void init();
    void displayBoard();
    void setObject(int row, int column, char object);

    int changeRow();
    int changeColumn();

    int getRow();
    int getColumn();

};

Board::Board()
{   
    setRow(5 + rand() % 4 * 2);
    setColumn(7 + rand() % 8 * 2);
    init();
}

void Board::setRow(int row)
{
    row_ = row;
}

void Board::setColumn(int column)
{
    column_ = column;
}

int Board::getRow()
{
    return row_;
}

int Board::getColumn()
{
    return column_;
}

int Board::changeRow()
{   
    int newRow = 0;    

    cout << endl << "change row = ";
    cin >> newRow;                      

    while(newRow <= 4 || newRow >= 17)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "change row = ";
        cin >> newRow;
    }

    return newRow % 2 == 0 ? newRow + 1 : newRow;
}

int Board::changeColumn()
{
    int newColumn = 0;

    cout << endl << "change column = ";
        cin >> newColumn;

    while(newColumn <= 6 || newColumn >= 31)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "change column = ";
        cin >> newColumn;
    }                   

    return newColumn % 2 == 0 ? newColumn + 1 : newColumn;
}

void Board::setObject(int row, int column, char object)
{
    board_[ getRow() - row ][ column - 1 ] = object;
}

void Board::init()
{

    char objects[] = {'<', '>', '^', 'v', 'r', 'h', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    const int noOfObjects = 15;

    board_.resize(row_);
    for (int i = 0; i < row_; ++i)
    {
        board_[i].resize(column_);
    }

    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < column_; ++j)
        {
            int objNo = rand() % noOfObjects;
            board_[i][j] = objects[objNo];
        }
    }
}

void Board::displayBoard()
{
    pf::ClearScreen();

    for (int i = 0; i < row_; ++i)
    {
        cout << " ";
        for (int j = 0; j < column_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        cout << setw(2) << (row_ - i);

        for (int j = 0; j < column_; ++j)
        {
            cout << "|" << board_[i][j];
        }
        cout << "|" << endl;
    }

    cout << " ";
    for (int j = 0; j < column_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    cout << "  ";
    for (int j = 0; j < column_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < column_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl << endl;
}

class Character
{
private :
    int alienRow_, alienColumn_;
    int zombieRow_, zombieColumn_;

public :
    Character();

    void setPosAlien(Board &b);
    void setPosZombie(Board &b);

};

Character::Character()
{ 
}

void Character::setPosAlien(Board &b)
{
    char alien = 'A';

    alienRow_ = b.getRow() / 2 + 1;
    alienColumn_ = b.getColumn() / 2 + 1;

    b.setObject(alienRow_, alienColumn_, alien);
}

void Character::setPosZombie(Board &b)
{
    char zombie = 'Z';

    zombieRow_ = //random position
    zombieColumn_ = //random position

    b.setObject(zombieRow_, zombieColumn_, zombie);
}

void testSetRowAndColumnAndAlien()
{
    Board b;
    Character alien;
    b.setRow(b.changeRow());
    b.setColumn(b.changeColumn());
    b.init();
    alien.setPosAlien(b);
    b.displayBoard();
}

int main()
{
    srand(time(NULL));

    Board b;
    Character alien;

    
    b.displayBoard();

    testSetRowAndColumnAndAlien();
}

