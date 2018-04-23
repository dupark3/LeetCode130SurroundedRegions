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
    void PrintBoard(const vector< vector<char> >& board){
        size_t max_rows = board.size();
        size_t max_columns = board[0].size();
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                cout << board[row][column];
            }
        cout << endl;
        }
    }

    bool InfectNeighbors(vector< vector<char> >& board){
        size_t max_rows = board.size();
        size_t max_columns = board[0].size();
        bool InfectionMade = false;
        
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                if (board[row][column] == 'I'){

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

                }
                
            }
        }
        return InfectionMade;
    }

    void InfectBorders(vector< vector<char> >& board){
        size_t max_rows = board.size();
        size_t max_columns = board[0].size();

        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                if (row == 0) { // on top row
                    if(board[row][column] == 'O') {
                        board[row][column] = 'I';
                        if (board[row+1][column] == 'O') board[row+1][column] = 'I';
                    }
                } else if (row != 0 && row != max_rows - 1) { // in middle rows
                    if (column == 0 || column == max_columns -1){ // on left/right edge
                        if (board[row][column] == 'O') {
                            board[row][column] = 'I'; 
                        }
                    }
                    if (column == 0){
                        column = max_columns - 2; // will advance next loop to max_columns-1, the last col
                    }
                } else if (row == max_rows - 1) { // on bottom row
                    if(board[row][column] == 'O') {
                        board[row][column] = 'I';
                    }
                }
            }
        }
    }

    void FlipRemainingOs(vector< vector<char> >& board){
        size_t max_rows = board.size();
        size_t max_columns = board[0].size();
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                if(board[row][column] == 'O')
                    board[row][column] = 'X';
            }
        }

    }

    void Disinfect(vector< vector<char> >& board){
        size_t max_rows = board.size();
        size_t max_columns = board[0].size();
        for (int row = 0; row != max_rows; ++row){
            for (int column = 0; column != max_columns; ++column){
                if(board[row][column] == 'I')
                    board[row][column] = 'O';
            }
        }
    }

    void solve(vector< vector<char> >& board) {
        if(!board.empty()){
            size_t max_rows = board.size();
            size_t max_columns = board[0].size();
            // initial infect: go through and "infect" border O's into I's 
            InfectBorders(board);
            
            // continuous infect: go through and "infect" until no more infections happen
            while(InfectNeighbors(board))
                ; // nothing to do but keep infecting       

            // flip all remaining uninfected O's into X's
            FlipRemainingOs(board);

            // flip back infected I's into O's
            Disinfect(board);    
        }
        
    }
};

int main(){
    vector< vector<char> > board= { {'X', 'X', 'X', 'X'},
                                    {'X', 'O', 'O', 'X'},
                                    {'X', 'X', 'O', 'X'},
                                    {'X', 'O', 'X', 'X'}};

    Solution s;
    s.solve(board);
    s.PrintBoard(board);

    return 0;
}