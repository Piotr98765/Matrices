#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
using namespace std;

int numMatrices;

class Matrix {
private:
    int rows;
    int columns;
    vector<int> data;

public:
    Matrix() : rows(0), columns(0) {}
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
    friend void matrixAddition(vector<Matrix>& matrices);
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

void matrixAddition(vector<Matrix>& matrices) {
    int numOfMatricesToAdd;

    cout << "How many matrices do you want to add? ";
    cin >> numOfMatricesToAdd;

    vector<int> indices(numOfMatricesToAdd);

    cout << "Enter the indices of the matrices you want to add (1-" << matrices.size() << "):\n";

    for (int i = 0; i < numOfMatricesToAdd; i++) {
        cout << "Matrix " << i + 1 << ": ";
        cin >> indices[i];
        indices[i]--; // Adjust index to match vector indexing (starting from 0)
    }

    bool validIndices = true;
    Matrix result;

    for (int i = 0; i < numOfMatricesToAdd; i++) {
        if (indices[i] < 0 || indices[i] >= matrices.size()) {
            cout << "Invalid index for Matrix " << i + 1 << ". Please enter a valid index.\n";
            validIndices = false;
            break;
        }

        if (i == 0) {
            result = matrices[indices[i]];
        } else {
            Matrix& matrix = matrices[indices[i]];

            if (result.rows != matrix.rows || result.columns != matrix.columns) {
                cout << "Matrices have incompatible dimensions for addition.\n";
                return;
            }

            for (int j = 0; j < result.rows; j++) {
                for (int k = 0; k < result.columns; k++) {
                    result.data[j * result.columns + k] += matrix.data[j * result.columns + k];
                }
            }
        }
    }

    if (validIndices) {
        cout << "Result of addition:\n";
        matrices.push_back(result);
        numMatrices++;
        displayMatrix(result);
        cout << "\n";
    }
}

int main() {
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

    
    matrixAddition(matrices);

    for (int k = 0; k < numMatrices; k++) {
        cout << "This is " << k + 1 << " matrix." << "\n";
        displayMatrix(matrices[k]);
    }

    return 0;
}
