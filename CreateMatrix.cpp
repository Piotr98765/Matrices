#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
using namespace std;

class Matrix {
private:
    int rows;
    int columns;
    vector<int> data;

public:
    Matrix(int numRows, int numColumns) : rows(numRows), columns(numColumns), data(numRows * numColumns) {}

    void fillWithNums() {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(0, 99);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                data[i * columns + j] = distribution(generator);
            }
        }
    }

    friend void displayMatrix(const Matrix& matrix);
    friend void matrixAddition(vector<Matrix>& matrices, const Matrix& matrix1, const Matrix& matrix2);
};

void displayMatrix(const Matrix& matrix) {
    int rows = matrix.rows;
    int columns = matrix.columns;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix.data[i * columns + j] << " ";
        }
        cout << "\n";
    }
}

void matrixAddition(vector<Matrix>& matrices, const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.rows != matrix2.rows || matrix1.columns != matrix2.columns) {
        cout << "Matrices have incompatible dimensions for addition.";
        return;
    }

    Matrix result(matrix1.rows, matrix1.columns);

    for (int i = 0; i < matrix1.rows; i++) {
        for (int j = 0; j < matrix1.columns; j++) {
            result.data[i * matrix1.columns + j] = matrix1.data[i * matrix1.columns + j] +
                                                   matrix2.data[i * matrix1.columns + j];
        }
    }

    cout << "Result of addition: " << "\n";
    matrices.push_back(result);
    displayMatrix(result);
}

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

    for (int k = 0; k < numMatrices; k++) {
        Matrix matrix(rows, columns);
        matrix.fillWithNums();
        matrices.push_back(matrix);
    }

    for (int k = 0; k < numMatrices; k++) {
        cout << "This is " << k + 1 << " matrix." << "\n";
        displayMatrix(matrices[k]);
    }

    matrixAddition(matrices, matrices[0], matrices[1]);

    return 0;
}
