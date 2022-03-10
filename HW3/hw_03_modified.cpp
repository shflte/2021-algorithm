#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);
int num_sol;

int placed[50];

bool valid(int* row, int* col, int* N) {
    for (int i = 0; i < *N; i++) {
        if (placed[i] == -1) continue;
        else if (*col == placed[i]) return false;
        else if (abs(double(*col - placed[i]) / double(*row - i)) == 1) return false;
    }
    return true;
}

void solve(int row, int* N) {
    if (row >= *N) {
        num_sol++;
        return;
    }
    else if (placed[row] != -1) { //the row is used
        solve(row + 1, N);
        return;
    }
    for (int i = 0; i < *N; i++) {
        if (valid(&row, &i, N)) {
            placed[row] = i;
            solve(row + 1, N);
            placed[row] = -1;
        }
    }
}

int main() {
    int T, N, M, row, col;

    fin >> T;
    for (int i = 0; i < T; i++) {
        num_sol = 0;
        fin >> N >> M;
        
        for (int j = 0; j < N; j++) placed[j] = -1;

        num_sol = 0;
        for (int j = 0; j < M; j++) {
            fin >> row >> col;
            placed[row] = col;
        }

        if (N != 3 && N != 2) solve(0, &N);
        fout << num_sol << "\n";
    }
}