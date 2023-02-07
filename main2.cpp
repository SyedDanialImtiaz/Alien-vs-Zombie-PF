// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT2L 
// Names: SYED DANIAL IMTIAZ BIN SYED ABDUL RAHIM | HILMAN DANISH BIN HAMKA | ADAM BIN AZMANHAZIM
// IDs: 1221301145 | 1221301132 | 1211102573
// Emails: 1221301145@student.mmu.edu.my | 1221301132@student.mmu.edu.my | 1211102573@student.mmu.edu.my
// Phones: 011-59221496 | 019-4742703 | 013-8119776
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

    cout << endl << "new row = ";
    cin >> newRow;                      

    while(newRow <= 4 || newRow >= 17)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "new row = ";
        cin >> newRow;
    }

    return newRow % 2 == 0 ? newRow + 1 : newRow;
}

int Board::changeColumn()
{
    int newColumn = 0;

    cout << endl << "new column = ";
        cin >> newColumn;

    while(newColumn <= 6 || newColumn >= 31)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "new column = ";
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
    int zombieRow_[9], zombieColumn_[9];
    int alienLife_, alienAttack_;
    int zombieLife_[9], zombieAttack_[9]; 

public :
    Character();

    int zombieSize = 1 + rand() % 9;

    void init(Board &b);

    void setZombieSize(int zom);
    int getZombieSize();
    int changeZombieSize();

    int getZombieLife(int n);
    int getZombieAttack(int n);

    int getAlienLife();
    int getAlienAttack();
};

Character::Character()
{ 
}

void Character::setZombieSize(int zom)
{
    zombieSize = zom;
}

int Character::getZombieSize()
{
    return zombieSize;
}

int Character::changeZombieSize()
{
    int newZombieSize = 0;    

    cout << endl << "new zombie size = ";
    cin >> newZombieSize;                      

    while(newZombieSize <= 0 || newZombieSize >= 10)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "new zombie size = ";
        cin >> newZombieSize;
    }

    return newZombieSize;
}

int Character::getZombieLife(int n)
{
    return zombieLife_[n];
}

int Character::getZombieAttack(int n)
{
    return zombieAttack_[n];
}

int Character::getAlienLife()
{
    return alienLife_;
}

int Character::getAlienAttack()
{
    return alienAttack_;
}

void Character::init(Board &b)
{
    char alien = 'A';

    alienRow_ = b.getRow() / 2 + 1;
    alienColumn_ = b.getColumn() / 2 + 1;

    b.setObject(alienRow_, alienColumn_, alien);

    alienLife_ = 100 + rand() % 4 * 50;
    alienAttack_ = 0;

    char zombie[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for(int n = 0; n < zombieSize; n++)
    {
        zombieRow_[n] = 1 + rand() % b.getRow();
        zombieColumn_[n] = 1 + rand() % b.getColumn();

        b.setObject(zombieRow_[n], zombieColumn_[n], zombie[n]);

        zombieLife_[n] = 100 + rand() % 5 * 50;
        zombieAttack_[n] = 5 + rand() % 5 * 5;
    }
}

class GameObject
{
private :

public :
    GameObject();

};

GameObject::GameObject()
{   
}

void displayCharacterAtributes(Character ch)
{
    cout << "\tAlien    : Life " << ch.getAlienLife() << ",\tAttack   " << ch.getAlienAttack() << endl;

    for(int x = 0; x < ch.getZombieSize(); x++)
    {
        cout << "\tZombie " << x + 1 << " : Life " << ch.getZombieLife(x) << ",\tAttack   " << ch.getZombieAttack(x) << endl;
    }
    cout << "\n\n";
}

int main()
{
    srand(time(NULL));

    Board b;
    Character ch;

    ch.init(b);

    b.displayBoard();

    cout << "board row    => " << b.getRow() << endl
         << "board column => " << b.getColumn() << endl
         << "zombie size  => " << ch.getZombieSize() << endl << endl;

    b.setRow(b.changeRow());
    b.setColumn(b.changeColumn());
    ch.setZombieSize(ch.changeZombieSize());

    b.init();
    ch.init(b);

    b.displayBoard();

    cout << "board row    => " << b.getRow() << endl
         << "board column => " << b.getColumn() << endl
         << "zombie size  => " << ch.getZombieSize() << endl << endl;

    displayCharacterAtributes(ch);
}

