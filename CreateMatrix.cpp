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

    int getRows() const {
        return rows;
    }

    int getColumns() const {
        return columns;
    }

    int getElement(int row, int column) const {
        return data[row * columns + column];
    }

    friend void displayMatrix(vector<Matrix>& matrices);
    friend void matrixAddition(vector<Matrix>& matrices);
    friend void matrixSubtraction(vector<Matrix>& matrices);
    friend void matrixMultiplyConstant(vector<Matrix>& matrices);
    friend void matrixMultiply(vector<Matrix>& matrices);
};

vector<Matrix> createMatrices() {
    cout << "How many matrices to create? ";
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

    return matrices;
}

void displayMatrix( vector<Matrix>& matrices) {
    for (int k = 0; k < matrices.size(); k++) {
        cout << "This is matrix " << k + 1 << ":\n";
        Matrix& matrix = matrices[k];
        for (int i = 0; i < matrix.getRows(); i++) {
            for (int j = 0; j < matrix.getColumns(); j++) {
                cout << matrix.getElement(i, j) << " ";
            }
            cout << "\n";
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
        matrices.push_back(result);
        numMatrices++;
        cout << "\n";
    }
}

void matrixSubtraction(vector<Matrix>& matrices) {
    int numOfFirstMatrix;
    int numOfSecondMatrix;

    cout << "Which matrices do you want to subtract?" << "\n";

    cout << "First matrix: ";
    cin >> numOfFirstMatrix;
    numOfFirstMatrix -= 1;

    cout << "Second matrix: ";
    cin >> numOfSecondMatrix;
    numOfSecondMatrix -= 1;

    Matrix matrix1 = matrices[numOfFirstMatrix];
    Matrix matrix2 = matrices[numOfSecondMatrix];  

    if (matrix1.rows != matrix2.rows || matrix1.columns != matrix2.columns) {
        cout << "Matrices have incompatible dimensions for subtraction.";
        return;
    }
    Matrix result(matrix1.rows, matrix1.columns);
    for (int i = 0; i < matrix1.rows; i++) {
        for (int j = 0; j < matrix1.columns; j++) {
            result.data[i * matrix1.columns + j] = matrix1.data[i * matrix1.columns + j] -
                                                   matrix2.data[i * matrix1.columns + j];
        }
    }
    cout << "Result of subtraction: " << "\n";
    matrices.push_back(result);
    numMatrices++;


}

void matrixMultiplyConstant(vector<Matrix>& matrices) {
    int constant;
    int numOfFirstMatrix;
    cout << "Type constant by which you want to multiply the matrix: ";
    cin >> constant;
    cout << "Type which matrix to multiply by the constant: ";
    cin >> numOfFirstMatrix;
    numOfFirstMatrix -= 1;
    Matrix matrix1 = matrices[numOfFirstMatrix];
    Matrix result(matrix1.getRows(), matrix1.getColumns());
    for (int i = 0; i < matrix1.getRows(); i++) {
        for (int j = 0; j < matrix1.getColumns(); j++) {
            result.data[i * matrix1.getColumns() + j] = matrix1.getElement(i, j) * constant;
        }
    }
    matrices.push_back(result);
    numMatrices++;
}

void matrixMultiply(vector<Matrix>& matrices) {
    bool exitMenu = false;
    while (!exitMenu) {
        cout << "Which type of operation do you want to perform?\n";
        cout << "1. Multiply by constant\n";
        cout << "2. Multiply two matrices\n";
        cout << "3. Back to main menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                matrixMultiplyConstant(matrices);
                break;
            case 2:
                break;
            case 3:
                exitMenu = true;
                break;
            case 4:
                cout << "Invalid choice. Please try again.\n";
                break;            
        }

    }
}

int main() {

    vector<Matrix> matrices;
    cout << "Welcome to Matrix Program ";
    cout << "\n\n";

    bool exitMainMenu  = false;

    while (!exitMainMenu ) {
        cout << "Menu:\n";
        cout << "1. Create matrices\n";
        cout << "2. Display matrices\n";
        cout << "3. Perform matrix addition\n";
        cout << "4. Perform matrix subtraction\n";
        cout << "5. Perform matrix multiply\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                matrices = createMatrices();
                break;
            case 2:
                displayMatrix(matrices);
                break;
            case 3:
                matrixAddition(matrices);
                break;
            case 4:
                matrixSubtraction(matrices);
                break;
            case 5:
                matrixMultiply(matrices);
                break;
            case 6:
                exitMainMenu  = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}