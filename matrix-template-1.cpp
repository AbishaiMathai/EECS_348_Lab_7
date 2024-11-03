#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
    int data[SIZE][SIZE];  // 2D array for matrix data (using int for simplicity)

public:
    // Read values from a file into a matrix
    void readFromFile(ifstream& file) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                file >> data[i][j];
            }
        }
    }

    // Display a matrix
    void display() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << setw(5) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Add two matrices (operator overloading for +)
    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Multiply two matrices (operator overloading for *)
    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < SIZE; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Compute the sum of matrix diagonal elements
    int sumOfDiagonals() const {
        int mainDiagonalSum = 0;
        int secondaryDiagonalSum = 0;
        for (int i = 0; i < SIZE; ++i) {
            mainDiagonalSum += data[i][i];
            secondaryDiagonalSum += data[i][SIZE - 1 - i];
        }
        return mainDiagonalSum + secondaryDiagonalSum;
    }

    // Swap matrix rows
    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= SIZE || row2 < 0 || row2 >= SIZE) {
            cerr << "Error: Invalid row indices." << endl;
            return;
        }
        for (int i = 0; i < SIZE; ++i) {
            swap(data[row1][i], data[row2][i]);
        }
    }
};

int main() {
    ifstream file("matrix-data.txt");
    if (!file) {
        cerr << "Error: Unable to open file" << endl;
        return 1;
    }

    Matrix mat1, mat2;

    cout << "Reading Matrix 1 from file..." << endl;
    mat1.readFromFile(file);  // Reads the first 4x4 matrix
    cout << "Matrix 1:" << endl;
    mat1.display();

    cout << "Reading Matrix 2 from file..." << endl;
    mat2.readFromFile(file);  // Reads the second 4x4 matrix
    cout << "Matrix 2:" << endl;
    mat2.display();

    Matrix sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    sum.display();

    Matrix product = mat1 * mat2;
    cout << "Product of matrices:" << endl;
    product.display();

    cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;

    mat1.swapRows(1, 3);
    cout << "Matrix 1 after swapping rows 0 and 2:" << endl;
    mat1.display();

    file.close();
    return 0;
}
