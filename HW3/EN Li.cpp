#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

//------------------------------------------------------

class ChessBoard 
{
public:
	ChessBoard(int, int); 		// n x n chessboard;
	void findSolutions();
//private:
	const bool available;
	const int squares, norm;						
	bool *column, *leftDiagonal, *rightDiagonal;	
	int  *positionInRow;
	int howMany;									//how many solutions
	
	//char m[10][10];									
	void putQueen(int);
	void printBoard();
	void initializeBoard();
	void Delete();									
	
	void prePlace();
	int M;					//the number of preplaced element
	int preplace[50][2]={};
	vector<int> solution;
	map<int, int> Map;
	//int solution[100000000]={};
};

ChessBoard::ChessBoard(int n, int m) : available(true), squares(n), norm(squares - 1), M(m)
{
	initializeBoard();

}

void ChessBoard::initializeBoard() 
{
	register int i;							
	column = new bool[squares];
	positionInRow = new int[squares];
	leftDiagonal = new bool[squares * 2 - 1];	
	rightDiagonal = new bool[squares * 2 - 1];	
	
	for (i = 0; i < squares; i++)
		positionInRow[i] = -1;					
											
	for (i = 0; i < squares; i++)
		column[i] = available;			//available=1		
		
	for (i = 0; i < squares * 2 - 1; i++)
		leftDiagonal[i] = rightDiagonal[i] = available;
	
	howMany = 0;
	solution.clear();
}

void ChessBoard::prePlace()
{
	for (int i = 0; i < M; i++)
	{
		int qrow = preplace[i][0];
		int qcol = preplace[i][1];
		positionInRow[qrow] = qcol;
		column[qcol] = !available;
		leftDiagonal[qrow + qcol] = !available;
		rightDiagonal[qrow - qcol + norm] = !available;
	}
	
}


void ChessBoard::putQueen(int row) 
{
	//Step1:preplace?
	
	
	while(1)
	{
		auto item = Map.find(row);
	    if (item != Map.end()) 
		{
	        row++;
	        continue;
	    } 
		else 
		{
	        break;
	    }
	}
    

	
	
	for (int col = 0; col < squares; col++) 
	{
		//Step2:isSafe?
		if (column[col] == available &&
			leftDiagonal[row + col] == available &&
			rightDiagonal[row - col + norm] == available)
		{
			positionInRow[row] = col;
			column[col] = !available;
			leftDiagonal[row + col] = !available;
			rightDiagonal[row - col + norm] = !available;
			
			//Step3:recursion
			if (row < squares-1)
			{
				putQueen(row+1);
			}
			else printBoard();
			
			//Step4:reset
			column[col] = available;
			leftDiagonal[row + col] = available;
			rightDiagonal[row - col + norm] = available;
		}
	}
}


void ChessBoard::printBoard() 
{
	howMany++;
}

void ChessBoard::Delete() 
{
	delete[]column;
	delete[]positionInRow;
	delete[]leftDiagonal;
	delete[]rightDiagonal;
}

void ChessBoard::findSolutions() {
	putQueen(0);
	solution.push_back(howMany);
	Delete();
}

//----------------------------------------------------------------------------------------

int main()
{
	ifstream file;
	file.open("input.txt");
	
	int testcase, n, m;
	int arr[50][2]={};
	vector<int> Solution;
	file >> testcase;
	
	while(testcase--)
	{
		
		//Step1:read file
		file >> n >> m;
		for(int i=0; i<m; i++)
		{
			file >> arr[i][0] >> arr[i][1];
		}
		//Step2:construct board
		ChessBoard board(n, m);
		for(int i=0; i<m; i++)
		{
			int qrow = arr[i][0];
			int qcol = arr[i][1];
			board.Map[qrow] = qcol;
			board.preplace[i][0] = arr[i][0];
			board.preplace[i][1] = arr[i][1];
		}
		board.prePlace();
		//Step3:solve
		board.findSolutions();
		for(int i=0; i<board.solution.size(); i++)
		{
			Solution.push_back(board.solution[i]);
		}
		
	}
	
	fstream newFile;
	newFile.open("output.txt", ios::out);
	for(int i=0; i<Solution.size(); i++)
	{
		newFile << Solution[i] << endl;
	}
	newFile.close();
	
	return 0;
}
