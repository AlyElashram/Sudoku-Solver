// Sudoku Solver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
void print(vector<vector<int>>* matrix) {

    for (auto i = matrix->begin(); i != matrix->end(); i++) {
        for (auto j = i->begin(); j != i->end(); j++) {
            cout << static_cast<int>(*j) << " ";
        }
        cout << "\n";
    }
}
bool isPlausible(int number, int row,int column, vector<vector<int>>* matrix) {

    auto end = (*matrix)[row].end();
    auto begin = (*matrix)[row].begin();

    // search row
        for (auto j = begin; j != end; j++) {
            if (*j == number) return false;
        }

    // search column 
        int size = matrix->size();
        for (int i = 0; i != matrix->size(); i++) {
            if ((*matrix)[i][column] == number) return false;
        }
        
    // search square
        int squareBeginRow = (row / 3) * 3;
        int squareBeginColumn = (column / 3) * 3;
        for (int i = squareBeginRow ; i != squareBeginRow + 3 ; i++) {
            for (int j = squareBeginColumn; j != squareBeginColumn + 3; j++) {
                if ((*matrix)[i][j] == number) return false;
            }
        }
        return true;
}
pair<int,int> findEmpty(vector<vector<int>>* matrix) {
    
    for (int y = 0; y != matrix->size();y++) {
        for (auto x = 0; x != matrix->at(y).size(); x++) {
            if ((*matrix)[y][x] == 0) return std::make_pair(x, y);
        }
    }
    return std::make_pair(-1,-1);

}

bool solve(vector<vector<int>>* matrix) {
    // base case no empty cells were found
    pair<int,int> position = findEmpty(matrix);
    if ( position == std::make_pair(-1,-1)) {
        return true;
    }
    for (int i = 1; i < 10; i++) {
        if (isPlausible(i, position.first, position.second, matrix)) {
            (*matrix)[position.second][position.first] = i;
            if (solve(matrix)) { return true; }
            (*matrix)[position.second][position.first] = 0;
        }
    }
    return false;
}

int main()
{
    vector<vector<int>> vec = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
  
    print(&vec);
    solve(&vec);
    //cout << isPlausible(2, 8, 8, &vec);
    print(&vec);
    return 0;
}

