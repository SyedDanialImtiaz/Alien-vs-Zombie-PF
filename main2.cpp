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
    
    void setRow(int row) { row_ = row; }
    void setColumn(int column) { column_ = column; }

    void init();
    void displayBoard();
    void setObject(int row, int column, char object) { board_[ getRow() - row ][ column - 1 ] = object; }
    char getObject(int row, int column) { return board_[ getRow() - row ][ column - 1 ]; }

    int changeRow();
    int changeColumn();

    int getRow() { return row_; }
    int getColumn() { return column_; }

};

Board::Board()
{   
    setRow(5 + rand() % 4 * 2);
    setColumn(7 + rand() % 8 * 2);
    init();
}

int Board::changeRow()
{   
    int newRow = 0;    

    cout << endl << "new row = "; cin >> newRow;
                          
    while(newRow <= 4 || newRow >= 17)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "new row = "; cin >> newRow;
    }

    return newRow % 2 == 0 ? newRow + 1 : newRow;
}

int Board::changeColumn()
{
    int newColumn = 0;

    cout << endl << "new column = "; cin >> newColumn;
    
    while(newColumn <= 6 || newColumn >= 31)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "new column = "; cin >> newColumn; 
    }                   

    return newColumn % 2 == 0 ? newColumn + 1 : newColumn;
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
    char alien = 'A';
    vector<char>zombie;

    int alienRow_;
    int alienColumn_;
    int zombieRow_[9], zombieColumn_[9];
    int alienLife_, alienAttack_;
    int zombieLife_[9], zombieAttack_[9], zombieRange_[9]; 
    int zombieSize_ = 1 + rand() % 9;;
    string alienInput_;
    int inMap_;

public :
    Character();

    void init(Board &b);

    void setZombieSize(int zombieSize) { zombieSize_ = zombieSize; }
    int getZombieSize() { return zombieSize_; }
    int changeZombieSize();

    int getZombieLife(int n) { return zombieLife_[n]; }
    int getZombieAttack(int n) { return zombieAttack_[n]; }
    int getZombieRange(int n) { return zombieRange_[n]; }

    void setAlienLife(int alienLife) { alienLife_ = alienLife; }
    void setAlienAttack(int alienAttack) { alienAttack_ = alienAttack; }

    int getAlienLife() { return alienLife_; }
    int getAlienAttack() { return alienAttack_; }

    void setAlienRow(int alienRow) { alienRow_ = alienRow; }
    void setAlienColumn(int alienColumn) { alienColumn_ = alienColumn; }

    int getAlienRow() { return alienRow_; }
    int getAlienColumn() { return alienColumn_; }

    void insideMap(int alienRow, int alienColumn);
    void alienMove(Board &b, string alienInput);
    void setInMap(int inMap) { inMap_ = inMap; }
    int getInMap() { return inMap_; }
};

Character::Character()
{ 
}

int Character::changeZombieSize()
{
    int newZombieSize = 0;    

    cout << endl << "new zombie size = "; cin >> newZombieSize;
                          
    while(newZombieSize <= 0 || newZombieSize >= 10)
    {
        cout << endl << " value too small/big! please enter a different value.";
        cout << endl << "new zombie size = "; cin >> newZombieSize;
    }

    return newZombieSize;
}

void Character::insideMap(int row, int column)
{
    Board b;

    if ( (row > 0 && row <= b.getRow()) && ( column > 0 && column <= b.getColumn()) )
        setInMap(1);
    else 
        setInMap(0);
}

void Character::alienMove(Board &b, string alienInput)
{
    if( alienInput == "up" )
    { 
        setAlienRow(alienRow_ + 1);
        insideMap( alienRow_, alienColumn_ );
        if ( inMap_ == 1 )
        {
            b.setObject(alienRow_, alienColumn_, alien); 
            b.setObject(alienRow_ - 1, alienColumn_, '.');
        }
        else
        {
            setAlienRow(alienRow_ - 1);
        }
    }
    else if( alienInput == "down" )
    {
        setAlienRow(alienRow_ - 1);
        insideMap(alienRow_, alienColumn_);
        if ( inMap_ == 1 )
        {
            b.setObject(alienRow_, alienColumn_, alien);
            b.setObject(alienRow_ + 1, alienColumn_, '.');
        }
        else
        {
            setAlienRow(alienRow_ + 1);
        }
    }
    else if( alienInput == "left" )
    {
        setAlienColumn(alienColumn_ - 1);
        insideMap(alienRow_, alienColumn_);
        if ( inMap_ == 1 )
        {
            b.setObject(alienRow_, alienColumn_, alien);
            b.setObject(alienRow_, alienColumn_ + 1, '.');
        }
        else
        {
            setAlienColumn(alienColumn_ + 1);
        }
        
    }
    else if( alienInput == "right" )
    {
        setAlienColumn(alienColumn_ + 1);
        insideMap(alienRow_, alienColumn_);
        if ( inMap_ == 1 )
        {
            b.setObject(alienRow_, alienColumn_, alien);
            b.setObject(alienRow_, alienColumn_ - 1, '.');
        }
        else
        {
            setAlienColumn(alienColumn_ - 1);
        }
    }
    else
    {
    }
}

void Character::init(Board &b)
{
    setAlienRow(b.getRow() / 2 + 1);
    setAlienColumn(b.getColumn() / 2 + 1);

    b.setObject(alienRow_, alienColumn_, alien);

    alienLife_ = 100 + rand() % 4 * 50;
    alienAttack_ = 0;

    zombie = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for(int n = 0; n < zombieSize_; n++)
    {
        zombieRow_[n] = 1 + rand() % b.getRow();
        zombieColumn_[n] = 1 + rand() % b.getColumn();

        b.setObject(zombieRow_[n], zombieColumn_[n], zombie[n]);

        zombieLife_[n] = 100 + rand() % 5 * 50;
        zombieAttack_[n] = 5 + rand() % 5 * 5;
        zombieRange_[n] = 1 + rand() % 3;
    }
}

class GameObject
{
private :
    char arrow_;

public :
    GameObject();
    
    void arrow(Character &ch);
    void health(Character &ch);
    void pod(Character &ch);
    void rock(Character &ch);
    void trail(Character &ch);

};

GameObject::GameObject()
{      
}

void GameObject::health(Character &ch)
{
    ch.setAlienLife( ch.getAlienLife() + 20 );
}

void GameObject::arrow(Character &ch)
{

}

void GameObject::pod(Character &ch)
{
    
}

void GameObject::trail(Character &ch)
{
    
}

void GameObject::rock(Character &ch)
{
    
}

void displayCharacterAtributes(Character ch)
{
    cout << " Alien    : Life " << ch.getAlienLife() << ",\tAttack   " << ch.getAlienAttack() << endl;

    for(int x = 0; x < ch.getZombieSize(); x++)
    {
        cout << " Zombie " << x + 1 
             << " : Life " << ch.getZombieLife(x) 
             << ",\tAttack   " << ch.getZombieAttack(x) 
             << "\tRange   " << ch.getZombieRange(x) << endl;
    }
    cout << "\n\n";
}

void displayBoardInfo(Board b, Character ch)
{
    cout << "board row    => " << b.getRow() << endl
         << "board column => " << b.getColumn() << endl
         << "zombie size  => " << ch.getZombieSize() << endl << endl;
}

int main()
{
    srand(time(NULL));

    Board b;
    Character ch;
    string command;

    ch.init(b);

    displayBoardInfo(b, ch);

    b.setRow(b.changeRow());
    b.setColumn(b.changeColumn());
    ch.setZombieSize(ch.changeZombieSize());

    b.init();
    ch.init(b);

    char quit = 'n';
    do{
        b.displayBoard();
        displayCharacterAtributes(ch);

        cout << "\n<Command> => "; cin >> command;

        if (command == "up")
        {
            for(int m = ch.getAlienRow(); m <= b.getRow(); m++)
            {
                
            }
        }
        else if ( command == "down")
        {

        }
        else if ( command == "left")
        {

        }
        else if ( command == "right")
        {

        }
        else if (command == "arrow")
        {
            int ArrowRow, ArrowColumn;
            string direction;
            cout << "Enter row, column and direction => "; cin >> ArrowRow >> ArrowColumn >> direction;
                
            char arrow = b.getObject(ArrowRow, ArrowColumn);
            char newArrow;
             if (direction == "up")
            { 
                newArrow = '^';
                b.setObject(ArrowRow, ArrowColumn, newArrow); 
            }
            else if (direction == "down")
            { 
                newArrow = 'v';
                b.setObject(ArrowRow, ArrowColumn, newArrow); 
            }
            else if (direction == "left")
            { 
                newArrow = '<';
                b.setObject(ArrowRow, ArrowColumn, newArrow); 
            }
            else if (direction == "right")
            { 
                newArrow = '>';
                b.setObject(ArrowRow, ArrowColumn, newArrow); 
            }

            cout << "Arrow " << arrow << " is switched to " << newArrow << endl;
            pf::Pause();
        }
        else if (command == "help")
        {
            cout << "\nCommands\n"
                 << "1. up     - Move up.\n"
                 << "2. down   - Move down.\n"
                 << "3. left   - Move left.\n"
                 << "4. right  - Move right.\n"
                 << "5. arrow  - Change the direction of the arrow.\n"
                 << "6. help   - Display these user commands.\n"
                 << "7. save   - Save the current game.\n"
                 << "8. load   - Load a game.\n"
                 << "9. quit   - Quit the game.\n";
            pf::Pause();
        }
        else if (command == "save")
        {

        }
        else if (command == "load")
        {

        }
        else if (command == "quit")
        {
            cout << "Are you sure? (y/n) : "; cin >> quit;

            if (quit == 'y')
            {    
                cout << "Goodbye!\n";
                break;
            }
        }
        else
        {
            cout << "invalid command! Please try again\n";
            pf::Pause();
        }

    }while(quit == 'n');

}
