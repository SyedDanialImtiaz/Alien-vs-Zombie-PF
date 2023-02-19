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
#include <fstream>
using namespace std;


void displayCharacterAtributes(Character ch)            // To display character atributes
{
    cout << " Alien    : Life " << ch.getAlienLife() << ",\tAttack   " << ch.getAlienAttack() << endl;

    for(int x = 0; x < ch.getZombieSize(); x++)         // Loop for every zombie
    {
        cout << " Zombie " << x + 1 
             << " : Life " << ch.getZombieLife(x) 
             << ",\tAttack   " << ch.getZombieAttack(x) 
             << "\tRange   " << ch.getZombieRange(x) << endl;
    }
    cout << "\n\n";
}

void displayBoardInfo(Board b, Character ch)        // To display board info
{
    cout << "board row    => " << b.getRow() << endl
         << "board column => " << b.getColumn() << endl
         << "zombie size  => " << ch.getZombieSize() << endl;
}

void health(Character &ch, int initAlienHealth)         // For health object, will restore life of alien 
{                                                       // if alien's life has reach MAX capacity, function will stop
    int health = 20;
    for ( int h = 1; h <= health; h++)
    {
        if( ch.getAlienLife() != initAlienHealth )
        {
            ch.setAlienLife( ch.getAlienLife() + 1 );
        }
        else { break; }
    }
}

void rock(Board &b, Character ch)                        // For rock object
{                                                        // Will stop alien and reveal hidden object when hit
    char objects[] = {'<', '>', '^', 'v', 'h', 'p' };
    const int noOfObjects = 6;
    
    int objNo = rand() % noOfObjects;
    b.setObject( ch.getAlienRow(), ch.getAlienColumn(), objects[objNo] );
}

void pod(Character &ch)                                             // For pod object
{                                                                   // Will inflict instant 10 damage to RANDOM zombie
    int zombie = rand() % ch.getZombieSize();                       // note : I cannot afford the time & effort to do NEAREST zombie
    ch.setZombieLife( zombie, ch.getZombieLife(zombie) - 10 );
}

int main()
{
    pf::ClearScreen();
    srand(time(NULL));

    Board b;
    Character ch;

    ch.init(b);

    displayBoardInfo(b, ch);

    char changeSetting = 'n';                                                           // Give the user the option to change game setting
    cout << "\nDo you want to change the Settings? (y/n) : "; cin >> changeSetting;     // if they want to
    
    if ( changeSetting == 'y')
    {
        pf::ClearScreen();
        b.setRow(b.changeRow());
        b.setColumn(b.changeColumn());
        ch.setZombieSize(ch.changeZombieSize());
    }

    b.init();
    ch.init(b);

    const int initAlienLife = ch.getAlienLife();
    string command = "input";
    char quit = 'n';
    do{
        b.displayBoard();
        displayCharacterAtributes(ch);

        if ( command == "input" ) { cout << "\n<Command> => "; cin >> command; }     // User input command here

        if( command == "trailreset")                                // For resetting the trail that alien left behind when moving
        {
            char objects[] = {'<', '>', '^', 'v', 'r', 'h', 'p', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
            const int noOfObjects = 15;
            for ( int i = 1; i <= b.getRow(); i++ )                 
            {                                                   // For checking in every row and column if there is a trail('.') 
                for ( int j = 1; j <= b.getColumn(); j++ )
                {
                    if ( b.getObject(i, j) == '.' )
                    {
                        int objNo = rand() % noOfObjects;       // Trails are resetted to random objects
                        b.setObject(i, j, objects[objNo] ); 
                    }
                }
            }
            command = "input";
        }
        else if (command == "up")               // All this is pretty self-explanatory :)
        {   
            int r = ch.getAlienRow();
            while ( r < b.getRow() )
            {
                ch.setAlienRow( ch.getAlienRow() + 1 );
                if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == ' ' || b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '.' )
                {
                    ch.alienMove(b, "up");
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";                  // Found pod, deal damage
                    pod(ch);
                    ch.alienMove(b, "up");
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";               // Found health, restore alien life
                    ch.alienMove(b, "up");
                    health(ch, initAlienLife);
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";             // Found arrow, change direction according to arrow
                    ch.alienMove(b, "up");  
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "up";
                    pf::Pause();
                    break;          // <-- this break is for exitting loop to execute another command that was given
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "up");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "up");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "up");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";                 // Found rock, alien stop and reveal hidden object
                    rock(b, ch);
                    ch.setAlienRow( ch.getAlienRow() - 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";     // <-- this is for executing the trail reset command above  
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '1' ||  
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '2' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '3' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '4' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '5' ||         // Found zombie, ....nothing happen :(
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '6' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '7' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '8' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '9' )
                {
                    cout << "\nAlien hit a zombie\n";
                    ch.setAlienRow( ch.getAlienRow() - 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }

                b.displayBoard();
                displayCharacterAtributes(ch);
                r++;
                if ( r == b.getRow() ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }      // If the supposed position is outside the board, the loop will exit
             
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
                    ch.alienMove(b, "down");
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    pod(ch);
                    ch.alienMove(b, "down");
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    ch.alienMove(b, "down");
                    health(ch, initAlienLife);
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "down");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "down");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "down");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "down");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    rock(b, ch);
                    ch.setAlienRow( ch.getAlienRow() + 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '1' ||  
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '2' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '3' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '4' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '5' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '6' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '7' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '8' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '9' )
                {
                    cout << "\nAlien hit a zombie\n";
                    ch.setAlienRow( ch.getAlienRow() + 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                r--;
                if ( r == 1 ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                    
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
                    ch.alienMove(b, "left");
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    pod(ch);
                    ch.alienMove(b, "left");
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    ch.alienMove(b, "left");
                    health(ch, initAlienLife);
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "left");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "left");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "left");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "left");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    rock(b, ch);
                    ch.setAlienColumn( ch.getAlienColumn() + 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '1' ||  
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '2' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '3' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '4' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '5' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '6' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '7' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '8' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '9' )
                {
                    cout << "\nAlien hit a zombie\n";
                    ch.setAlienColumn( ch.getAlienColumn() + 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                c--;
                if ( c == 1 ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                    
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
                    ch.alienMove(b, "right");
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'p')
                {
                    cout << "\nAlien found pod\n";
                    pod(ch);
                    ch.alienMove(b, "right");
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'h')
                {
                    cout << "\nAlien found health\n";
                    ch.alienMove(b, "right");
                    health(ch, initAlienLife);
                    pf::Pause();
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '^' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "right");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "up";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'v' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "right");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "down";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '<' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "right");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "left";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '>' )
                {
                    cout << "\nAlien finds an arrow\n";
                    ch.alienMove(b, "right");
                    ch.setAlienAttack( ch.getAlienAttack() + 20 );
                    command = "right";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == 'r' )
                {
                    cout << "\nAlien hit a rock\n";
                    rock(b, ch);
                    ch.setAlienColumn( ch.getAlienColumn() - 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                else if ( b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '1' ||  
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '2' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '3' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '4' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '5' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '6' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '7' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '8' || 
                          b.getObject( ch.getAlienRow(), ch.getAlienColumn() ) == '9' )
                {
                    cout << "\nAlien hit a zombie\n";
                    ch.setAlienColumn( ch.getAlienColumn() - 1 );
                    ch.setAlienAttack(0);
                    command = "trailreset";
                    pf::Pause();
                    break;
                }
                
                b.displayBoard();
                displayCharacterAtributes(ch);
                c++;
                if ( c == b.getColumn() ) { cout << "\nAlien hit the border\n"; command = "trailreset"; }
                    
                pf::Pause();            
            }
        }
        else if (command == "arrow")            // This command will allow the user to change the direction of designated arrow
        {
            int ArrowRow, ArrowColumn;
            string direction;
            cout << "Enter row, column and direction => "; cin >> ArrowRow >> ArrowColumn >> direction;     // User will input row, column and direction they want
                
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
            command = "input";                                   // <-- This command will allow the user to input new command
            pf::Pause();
        }
        else if (command == "help")             // Will display available commands
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
        else if (command == "save")         // Sorry, not available
        {
            cout << "This function is not available at the moment.\n";
            command = "input";
            pf::Pause();
        }
        else if (command == "load")         // Same reason as above
        {
            cout << "This function is not available at the moment.\n";
            command = "input";
            pf::Pause();
        }
        else if (command == "quit")         // Will allow the user to quit the game if they want to
        {
            cout << "Are you sure? (y/n) : "; cin >> quit;      // Just to be sure, you know

            if (quit == 'y')
            {    
                cout << "Goodbye!\n";
                break;
            }
        }
        else
        {
            cout << "invalid command! Please try again\n";      // If user input wrong command
            command = "input";
            pf::Pause();
        }

    }while(quit == 'n');

}
