/*
Leet Code #130

1. Surrounded regions shouldn’t be on the border, which means that any 'O' on the
   border of the board are not flipped to 'X'. 
2. Any 'O' that is not on the border and it is not connected to an 'O' on the
   border will be flipped to 'X'. 
3. Two cells are connected if they are adjacent cells connected horizontally or
   vertically.  

*/
#include <cstddef> // size_t
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void PrintBoard(const vector< vector<char> >& board, size_t max_rows, size_t max_columns){
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                cout << board[row][column];
            }
        cout << endl;
        }
    }

    void InfectBorders(vector< vector<char> >& board, size_t max_rows, size_t max_columns){
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                
                // on top row
                if (row == 0) { 
                    if(board[row][column] == 'O') board[row][column] = 'I';                        
                } 
                
                // in middle rows
                else if (row > 0 && row < max_rows - 1) { 
                    // no need to check if on left or right edge
                    if (board[row][column] == 'O') board[row][column] = 'I'; 

                    // advance the next loop to the last column, ++(max_columns - 2)
                    if (column == 0 && max_columns > 1) column = max_columns - 2; 
                    // else, we only have one column or we are on the right edge
                    else column = max_columns - 1;
                } 

                // on bottom row
                else { 
                    if(board[row][column] == 'O') board[row][column] = 'I';
                }
            } // end of inner loop (columns)
        } // end of outer loop (rows)

    }

    bool InfectNeighbors(vector< vector<char> >& board, size_t max_rows, size_t max_columns){
        bool InfectionMade = false;
        
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                if (board[row][column] == 'I'){
                    // check below, above, left, and right
                    if(row != max_rows-1       && board[row+1][column] == 'O'){
                        board[row+1][column] = 'I';
                        InfectionMade = true;
                    } 
                    if(row != 0                && board[row-1][column] == 'O') {
                        board[row-1][column] = 'I';
                        InfectionMade = true;
                    }
                    if(column != 0             && board[row][column-1] == 'O') {
                        board[row][column-1] = 'I';
                        InfectionMade = true;
                    }
                    if(column != max_columns-1 && board[row][column+1] == 'O') {
                        board[row][column+1] = 'I';
                        InfectionMade = true;
                    }
                } else if (board[row][column] == 'O'){
                    // check below, above, left, and right
                    if(row != max_rows-1       && board[row+1][column] == 'I'){
                        board[row+1][column] = 'I';
                        InfectionMade = true;
                    } 
                    if(row != 0                && board[row-1][column] == 'I') {
                        board[row-1][column] = 'I';
                        InfectionMade = true;
                    }
                    if(column != 0             && board[row][column-1] == 'I') {
                        board[row][column-1] = 'I';
                        InfectionMade = true;
                    }
                    if(column != max_columns-1 && board[row][column+1] == 'I') {
                        board[row][column+1] = 'I';
                        InfectionMade = true;
                    }
                }
            } // end of inner loop (columns)
        } // end of outer loop (rows)
        
        return InfectionMade;
    }

    void FlipBack(vector< vector<char> >& board, size_t max_rows, size_t max_columns){
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                if(board[row][column] == 'O') board[row][column] = 'X';
                if(board[row][column] == 'I') board[row][column] = 'O';
            }
        }
    }

    void solve(vector< vector<char> >& board) {
        if(!board.empty()){
            size_t max_rows = board.size();
            size_t max_columns = board[0].size();

            // initial infect: go through and "infect" border O's into I's 
            InfectBorders(board, max_rows, max_columns);
            
            cout << "borders done" << endl;
            // continuous infect: go through and "infect" until no more infections happen
            while(InfectNeighbors(board, max_rows, max_columns))
                cout << "infecting" << endl; // nothing to do but keep infecting

            // flip all remaining uninfected O's into X's and I's back to O's
            FlipBack(board, max_rows, max_columns);
        }
        
    }
};

int main(){
    
    vector< vector<char> > board= { {'X', 'X', 'X', 'X', 'O', 'X'},
                                    {'X', 'O', 'O', 'O', 'O', 'O'},
                                    {'X', 'X', 'O', 'O', 'O', 'X'},
                                    {'X', 'O', 'X', 'X', 'X', 'O'} };
    if (board.empty())
        return 1;
    
    Solution s;
    s.solve(board);
    s.PrintBoard(board, board.size(), board[0].size());
    
    
    return 0;
}