#include <iostream>
using namespace std;

class nqueen {
public:
    bool check(int arr[][10], int row, int col, int n);
    bool solve_nqueen(int arr[][10], int col, int n, int& solutions, int desired_solutions);
    int count_solutions(int n);
};

bool nqueen::check(int arr[][10], int row, int col, int n) {
    int i, j;

    // Check row on the left side
    for (i = 0; i < col; i++) {
        if (arr[row][i]) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (arr[i][j]) {
            return false;
        }
    }

    // Check lower diagonal on the left side
    for (i = row, j = col; j >= 0 && i < n; i++, j--) {
        if (arr[i][j]) {
            return false;
        }
    }

    return true;
}

bool nqueen::solve_nqueen(int arr[][10], int col, int n, int& solutions, int desired_solutions) {
    // To check if all queens are placed
    if (col >= n) {
        solutions++;

        // Displaying placed queens
        if (solutions <= desired_solutions) {
            cout << "===============================================================\n";
            cout << "Solution " << solutions << ":\n";
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (arr[k][l] == 1) {
                        cout << "q" << l + 1 << "\t";
                    } else {
                        cout << "0\t";
                    }
                }
                cout << "\n";
            }
            cout << "===============================================================\n";
        }

        if (solutions >= desired_solutions) {
            cout << "===============================================================\n";
            cout << "Desired number of solutions found. Exiting.\n";
            return true;
        }

        return false; // Continue searching for more solutions
    }

    for (int i = 0; i < n; i++) {
        if (check(arr, i, col, n)) {
            arr[i][col] = 1;

            // Display intermediate state
            cout << "===============================================================\n";
            cout << "Placed queen q" << col + 1 << " at row " << i + 1 << ", col " << col + 1 << "\n";
            cout << "Intermediate state:\n";
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (arr[k][l] == 1) {
                        cout << "q" << l + 1 << "\t";
                    } else {
                        cout << "0\t";
                    }
                }
                cout << "\n";
            }
            cout << "===============================================================\n";

            // Iterate to the next column
            if (solve_nqueen(arr, col + 1, n, solutions, desired_solutions)) {
                return true;
            }

            // Backtrack
            cout << "===============================================================\n";
            cout << "Backtrack queen q" << col + 1 << " from row " << i + 1 << ", col " << col + 1 << "\n";
            cout << "===============================================================\n";
            arr[i][col] = 0;
        }
    }

    return false;
}

int nqueen::count_solutions(int n) {
    // This function returns the known number of solutions for N-Queens problem for N from 1 to 10.
    // You can update it with the known values for larger N if needed.
    int known_solutions[] = {1, 0, 0, 2, 10, 4, 40, 92, 352, 724};
    if (n >= 1 && n <= 10) {
        return known_solutions[n - 1];
    } else {
        return -1; // Unknown for N > 10
    }
}

int main() {
    nqueen q1;
    int n;
    cout << "::Enter the chessboard size (size should be greater than 3):\n";
    cin >> n;

    if (n <= 3) {
        cout << "Please enter a size greater than 3:\n";
        cout << "===============================================================\n";
        return 1;
    }

    int desired_solutions;

    cout << "::Enter the number of solutions you want to find:\n";
    cin >> desired_solutions;

    int max_solutions = q1.count_solutions(n);

    if (max_solutions == -1 || desired_solutions > max_solutions) {
        cout << "===============================================================\n";
        cout << "Desired number of solutions is not feasible. Maximum possible solutions: " << max_solutions << "\n";
        cout << "===============================================================\n";
        return 1;
    }

    int solutions = 0;
    int arr[10][10] = {0}; // Normal array declaration

    cout << "Initially the board is:\n";
    // Initially setting value to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "0\t";
        }
        cout << "\n";
    }

    cout << "===============================================================\n";
    // Solve the problem
    q1.solve_nqueen(arr, 0, n, solutions, desired_solutions);
    cout << "===============================================================\n";

    cout << "AFTER PLACING THE QUEEN: \n";
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (arr[i][k] == 1) {
                cout << "q" << k + 1 << "\t";
            } else {
                cout << "0\t";
            }
        }
        cout << "\n";
    }

    cout << "===============================================================\n";
    return 0;
}
