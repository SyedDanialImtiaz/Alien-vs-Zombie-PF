#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <vector>
#include <string>
#include "board.hpp"

class Character
{
private :
    std::vector<char>zombie;

    int alienRow_;
    int alienColumn_;
    int zombieRow_[9], zombieColumn_[9];
    int alienLife_, alienAttack_;
    int zombieLife_[9], zombieAttack_[9], zombieRange_[9]; 
    int zombieSize_;
    std::string alienInput_;

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

    void alienMove(Board &b, string command);

};
#endif