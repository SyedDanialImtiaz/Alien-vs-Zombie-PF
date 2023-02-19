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
#include "pf/board.hpp"
#include "pf/character.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;


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
         << "zombie size  => " << ch.getZombieSize() << endl;
}

int main()
{
    pf::ClearScreen();
    srand(time(NULL));

    Board b;
    Character ch;
    string command;

    ch.init(b);

    displayBoardInfo(b, ch);

    char changeSetting = 'n';
    cout << "\nDo you want to change the Settings? (y/n) : "; cin >> changeSetting;
    
    if ( changeSetting == 'y')
    {
        pf::ClearScreen();
        b.setRow(b.changeRow());
        b.setColumn(b.changeColumn());
        ch.setZombieSize(ch.changeZombieSize());
    }

    b.init();
    ch.init(b);

    command = "input";
    char quit = 'n';
    do{
        b.displayBoard();
        displayCharacterAtributes(ch);

        if ( command == "input" ) { cout << "\n<Command> => "; cin >> command; }

        if( command == "trailreset")
        {
            char objects[] = {'<', '>', '^', 'v', 'r', 'h', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
            const int noOfObjects = 15;
            for ( int i = 1; i <= b.getRow(); i++ )
            {
                for ( int j = 1; j <= b.getColumn(); j++ )
                {
                    if ( b.getObject(i, j) == '.' )
                    {
                        int objNo = rand() % noOfObjects;
                        b.setObject(i, j, objects[objNo] ); 
                    }
                }
            }
            command = "input";
        }
        else if (command == "up")
        {   
            int r = ch.getAlienRow();
            while ( r < b.getRow() )
            {
                ch.setAlienRow( ch.getAlienRow() + 1 );
                if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == ' ' || b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '.' )
                {
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() - 1, ch.getAlienColumn(), '.');
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    ch.setAlienRow( ch.getAlienRow() - 1 );
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                r++;
                if ( r == b.getRow() ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                
                pf::Pause();            
            }
        }
        else if ( command == "down")
        {
            int r = ch.getAlienRow();
            while ( r > 1 )
            {
                ch.setAlienRow( ch.getAlienRow() - 1 );
                if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == ' ' || b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '.' )
                {
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow() + 1, ch.getAlienColumn(), '.');
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    ch.setAlienRow( ch.getAlienRow() + 1 );
                    pf::Pause();
                    command = "trailreset";
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                r--;
                if ( r == 0 ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                    
                pf::Pause();            
            }
        }
        else if ( command == "left")
        {
            int c = ch.getAlienColumn();
            while ( c > 1 )
            {
                ch.setAlienColumn( ch.getAlienColumn() - 1 );
                if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == ' ' || b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '.' )
                {
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() + 1, '.');
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    ch.setAlienColumn( ch.getAlienColumn() + 1 );
                    pf::Pause();
                    command = "trailreset";
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                c--;
                if ( c == 0 ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                    
                pf::Pause();            
            }
        }
        else if ( command == "right")
        {
            int c = ch.getAlienColumn();
            while ( c < b.getColumn() )
            {
                ch.setAlienColumn( ch.getAlienColumn() + 1 );
                if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == ' ' || b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '.' )
                {
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), 'A' );
                    b.setObject( ch.getAlienRow(), ch.getAlienColumn() - 1, '.');
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    ch.setAlienColumn( ch.getAlienColumn() - 1 );
                    pf::Pause();
                    command = "trailreset";
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                c--;
                if ( c == 0 ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                    
                pf::Pause();            
            }
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
            command = "input";
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
            command = "input";
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
            command = "input";
            pf::Pause();
        }

    }while(quit == 'n');

}
