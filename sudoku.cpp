#include <iostream>

using namespace std;

typedef pair<int, int> Box;

void printBox(Box box) {
	// cout << box.first << ", " << box.second << endl;
}

void printBoard(int board[9][9]) {
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			cout << board[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl; 
}

bool isBoardValid(int board[9][9], Box location) {
	bool rowChecker[9] = {false};
	bool colChecker[9] = {false};

	for (int i = 0; i < 9; ++i)
	{
		int rowVal = board[location.first][i];
		if (rowVal != 0) {
			if (colChecker[rowVal-1]) {
				// cout << "row: " << location.first << ", " << i << endl;
				return false;
			}
			colChecker[rowVal-1] = true;
		}

		int colVal = board[i][location.second];
		if (colVal != 0) {
			// cout << "colVal:" colVal 
			if (rowChecker[colVal-1]) {
				// cout << "col: " << i << ", " << location.second << endl;
				return false;
			}
			rowChecker[colVal-1] = true;
		}
	}
	
	bool squareChecker[9] = {false};
	int firstRow = location.first - (location.first % 3);
	int firstCol = location.second - (location.second % 3);

	for (int row = firstRow; row < firstRow + 3; ++row)
	{
		for (int col = firstCol; col < firstCol + 3; ++col)
		{
			int val = board[row][col];
			// cout << "s: " << row << ", " << col << " --- " << val << endl;
			if (val != 0) {
				if (squareChecker[val-1]) {
					// cout << "square: " << row << ", " << col << endl;
					return false;
				}
				squareChecker[val-1] = true;
			}
		}
	}
	return true;
}

// TODO: a little innefficent, small Boxes evaluated 2 extra times each (6 extra times)
bool isBoardValid(int board[9][9]) {
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			if (!isBoardValid(board, make_pair(i,j))) {
				return false;
			}
		}
	}
	return true;
}

Box findFirstOpen(int board[9][9], Box startingPos = make_pair(0,0)) {
	for (int i = startingPos.first; i < 9; ++i)
	{
		for (int j = startingPos.second; j < 9; ++j)
		{
			if (board[i][j] == 0) {
				return make_pair(i, j);
			}
		}
	}
	return make_pair(-1, -1);
}

bool solve(int board[9][9]);

bool fillBoxAndSolve(int board[9][9], Box box) {
	printBox(box);
	for (int i = 9; i > 0; --i)
	{
		board[box.first][box.second] = i;
		// cout << i << endl;
		// TODO; innefficient, get list of possible numbers instead
		if (!isBoardValid(board, box)) {
			continue;
		}
		// printBoard(board);
		bool attempt = solve(board);
		if (attempt) {
			return true;
		}
		printBox(box);
	}
	board[box.first][box.second] = 0;
	return false;
}

bool solve(int board[9][9]) {
	Box firstBox = findFirstOpen(board, make_pair(0, 0));
	// printBoard(board);
	if(firstBox.first == -1) {
		return isBoardValid(board);
	}
	return fillBoxAndSolve(board, firstBox);
}

int main(int argc, char const *argv[])
{
	int board1[9][9] = {
		{2, 0, 0, 3, 0, 0, 0, 0, 0},
		{8, 0, 4, 9, 6, 2, 0, 0, 3},
		{0, 1, 3, 8, 0, 0, 2, 0, 0},
		{0, 0, 0, 0, 2, 0, 3, 9, 0},
		{5, 0, 7, 0, 0, 0, 6, 2, 1},
		{0, 3, 2, 0, 0, 6, 0, 0, 0},
		{3, 2, 5, 0, 0, 9, 1, 4, 0},
		{6, 0, 1, 2, 5, 0, 8, 0, 9},
		{0, 0, 0, 0, 0, 1, 0, 0, 2}
	};

	int board2[9][9] = {
		{4, 0, 5, 0, 0, 8, 0, 2, 0},
		{0, 0, 0, 1, 0, 0, 0, 0, 0},
		{0, 2, 0, 0, 6, 7, 0, 9, 0},
		{0, 0, 8, 0, 0, 0, 0, 3, 0},
		{5, 0, 6, 0, 0, 0, 2, 0, 1},
		{0, 1, 0, 0, 0, 0, 4, 0, 0},
		{0, 8, 0, 9, 7, 0, 0, 6, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 9, 0, 8, 0, 0, 5, 0, 7}
	};

	bool result = solve(board2);
	cout << "result: " << result << endl;
	printBoard(board2);
	return 0;
}



