#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


class Matrix {
private:
	int rows;
	int columns;
	int** data;
public:
	Matrix(int numRows, int numColumns) : rows(numRows), columns(numColumns){
		data = new int*[rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new int[columns];
		}
	}

	void fillWithNums() {
	    for (int i = 0; i < rows; i++) {
	        for (int j = 0; j < columns; j++) {
	            data[i][j] = rand() % 100;
	        }
	    }
	}

	void display() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				cout << data[i][j] << " ";
			}
			cout << "\n";
		}
	}
};


int main() { 

	int numMatrices;
	cout << "How many matrices? ";
	cin >> numMatrices;
	cout << "\n";

	int rows;
	cout << "How many rows in each matrix? ";
	cin >> rows;
	cout << "\n";

	int columns;
	cout << "How many columns in each matrix? ";
	cin >> columns;
	cout << "\n";

	srand(time(0));

	vector<Matrix> matrices;

	for (int k=0; k < numMatrices; k++) {
		Matrix matrix(rows, columns);
		matrix.fillWithNums();
		matrices.push_back(matrix);
	}

	for (int k = 0; k < numMatrices; k++) {
		cout << "This is " << k + 1 << " matrix." << "\n";
		matrices[k].display();
	}

	return 0;
}