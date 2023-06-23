#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	int rows = 3;
	int columns = 3;

	int** matrix = new int*[rows];

	for (int i = 0; i < rows; i++){
		matrix[i] = new int[columns];
	}

	for (int i=0; i < rows; i++){
		for (int j=0; j < columns; j++){
			matrix[i][j]= rand() % 100; 
		}
	}

	for (int i=0; i < rows; i++){
		for (int j=0; j < columns; j++){
			cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}


	for (int i = 0; i < rows; i++){
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}

