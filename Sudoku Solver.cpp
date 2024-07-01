#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;
void print(vector<vector<int>>* matrix) {
	for (auto i = matrix->begin(); i != matrix->end(); i++) {
		for (auto j = i->begin(); j != i->end(); j++) {
			cout << *j << " ";
		}
		cout << "\n";
	}
}
bool isPlausible(int number, int row, int column, vector<vector<int>>* matrix) {

	auto end = (*matrix)[row].end();
	auto begin = (*matrix)[row].begin();

	// search row
	for (auto j = begin; j != end; j++) {
		if (*j == number) return false;
	}

	// search column
	for (int i = 0; i != matrix->size(); i++) {
		if ((*matrix)[i][column] == number) return false;
	}

	// search square
	int squareBeginRow = (row / 3) * 3;
	int squareBeginColumn = (column / 3) * 3;
	for (int i = squareBeginRow; i != squareBeginRow + 3; i++) {
		for (int j = squareBeginColumn; j != squareBeginColumn + 3; j++) {
			if ((*matrix)[i][j] == number) return false;
		}
	}
	return true;
}
pair<int, int> findEmpty(vector<vector<int>>* matrix) {

	for (int y = 0; y < matrix->size(); y++) {
		for (auto x = 0; x != matrix->at(y).size(); x++) {
			if ((*matrix)[y][x] == 0) return std::make_pair(x, y);
		}
	}
	return std::make_pair(-1, -1);

}

bool solve(vector<vector<int>>* matrix) {
	pair<int, int> position = findEmpty(matrix);
	if (position == std::make_pair(-1, -1)) {
		return true;
	}
	for (int i = 1; i <= 9; i++) {
		if (isPlausible(i, position.second, position.first, matrix)) {
			(*matrix)[position.second][position.first] = i;
			if (solve(matrix)) { return true; }
			(*matrix)[position.second][position.first] = 0;
		}
	}
	return false;
}

int main()
{
	ifstream stream = ifstream("puzzle_list.txt");
	if(!stream)
	{
		cout << "Failed to read file";
	}
	char c;
	vector<vector<int>> puzzle =vector<vector<int>>();
	vector<int> row;
	int i=0;
	while(stream.get(c) && i<9)
	{
		if(c =='\n')
		{
			i++;
			puzzle.push_back(row);
			row.clear();
		}
		else
		{
			row.push_back(c - '0');
		}

	}
	print(&puzzle);
	solve(&puzzle);
	cout << "--------------------------------------------------------\n";
	print(&puzzle);
	return 0;
}

