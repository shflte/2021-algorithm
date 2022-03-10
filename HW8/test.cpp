#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);

int main() {
    int number;

    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 14; j++) {
            if (j == 0 || j == 1 || j == 13 || j == 14) number = 1;
            else number = 0;
            fout << "grid[" << setw(3) << i * 14 + j << "] <= " << number << "; ";
        }
        fout << "\n";
    }
}