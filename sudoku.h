#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <cstdio>
using namespace std;
#define NUM_SUDOKU 81
/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/

class Sudoku
{
public:
    Sudoku();
    int _sudoku[NUM_SUDOKU];
    
    //print table
    void print_table();

    
    // generate
    void generate();

    // transform
    void input_Sudoku_table();
    void transform();

    void swapNum(int x, int y);
    void swapRow(int x, int y);
    void swapCol(int x, int y);
    void rotate(int x);
    void flip(int x);

    // solve
    int solve();

private:
};

#endif // SUDOKU_H
