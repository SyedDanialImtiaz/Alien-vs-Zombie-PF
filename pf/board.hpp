#ifndef BOARD_HPP
#define BOARD_HPP
#include<vector>

class Board
{
private:
    std::vector< std::vector<char> >board_;
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
#endif