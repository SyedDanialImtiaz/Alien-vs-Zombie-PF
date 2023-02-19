#include "character.hpp"
#include <iostream>
using namespace std;

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

void Character::init(Board &b)
{
    setZombieSize(1 + rand() % 9);
    setAlienRow(b.getRow() / 2 + 1);
    setAlienColumn(b.getColumn() / 2 + 1);

    b.setObject(alienRow_, alienColumn_, 'A');

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

void Character::alienMove(Board &b, string command)
{
    if ( command == "up" )
    {
        b.setObject( alienRow_, alienColumn_, 'A' );
        b.setObject( alienRow_ - 1, alienColumn_, '.' );
    }
    else if ( command == "down" )
    {
        b.setObject( alienRow_, alienColumn_, 'A' );
        b.setObject( alienRow_ + 1, alienColumn_, '.' );
    }
    else if ( command == "left" )
    {
        b.setObject( alienRow_, alienColumn_, 'A' );
        b.setObject( alienRow_, alienColumn_ + 1, '.' );
    }
    else if ( command == "right" )
    {
        b.setObject( alienRow_, alienColumn_, 'A' );
        b.setObject( alienRow_, alienColumn_ - 1, '.' );
    }
}