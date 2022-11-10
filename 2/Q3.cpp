#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 9;
const int ROW = N;
const int COL = N;
const int small_table = 3;

// get table from user
void get_table(vector<vector<int>>& table)
{
    for (int row = 0; row < (int)table.size(); row++)
    {
        for (int col = 0; col < (int)table[row].size(); col++)
        {
            cin >> table[row][col];
        }
    }
}

// print table
void print_result(vector<vector<int>>& table) {
    for (int row = 0; row < (int)table.size(); row++)
    {
        for (int col = 0; col < (int)table[row].size(); col++)
        {
                cout << table[row][col] << " ";
        }
        cout << endl;
     }
}

//rule num 1 : A number is not repeated twice in the row.
bool check_row(vector<vector<int>>& table, int row, int num) {
    for (int i = 0; i < ROW; i++)
        if (table[row][i] == num)
            return false;
    return true;
}

//rule num 2 : A number is not repeated twice in the column.
bool check_col(vector<vector<int>>& table, int col, int num) {

    for (int j = 0; j < COL; j++) {
        if (table[j][col] == num)
            return false;
    }
    return true;
}

//rule num 3 : A number is not repeated twice in particular 3*3 matrix.
bool check_small_table(vector<vector<int>>& table, int row, int col, int num) {
    int first_row = row - row % small_table;
    int first_col = col - col % small_table;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (table[i + first_row][j + first_col] == num)
                return false;
    return true;
}

//find empty location 
bool Empty_place_finder(vector<vector<int>>& table, int& row, int& col) {
    for (row = 0; row < ROW; row++)
        for (col = 0; col < COL; col++)
            if (table[row][col] == 0) 
                return false;
    return true;
}

bool solve_Sudoku(vector<vector<int>>& table , int row, int col)
{
    //check empty places if all of them are full the program is completed
    if (Empty_place_finder(table, row, col)) { return true; }
    
    //valid numbers are 1 - 9
    for (int num = 1; num <= 9; num++) { 

        //check row,col & particular 3*3 matrix.
        if (check_row(table, row, num) &&
            check_col(table, col, num) &&
            check_small_table( table, row, col ,num)) {

            table[row][col] = num;


            //recursively find other rooms to fill
            if (solve_Sudoku(table, row,col)) 
                return true;
            //turn it 0 when the checks are false and check another number
            table[row][col] = 0; 
        }
    }
    return false;
}

int main()
{
    vector<vector<int>> table(ROW, vector<int>(COL));//create table matrix
    get_table(table);//get input

    //check if ih can be solved
    if (solve_Sudoku(table, 0, 0))
        print_result(table);
    else cout << "can not be solved" << endl;
}
