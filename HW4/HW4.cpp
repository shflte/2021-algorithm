#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);

int main() {
    int T;
    long long len;
    long long* num;
    fin >> T;

    long long count;
    for (int i = 0; i < T; i++) {
        count = 0;
        fin >> len;
        num = new long long[len];
        for (int m = 0; m < len; m++) {
            fin >> num[m];
        }

        for (int j = 0; j < len - 1; j++) {
            for (int k = j + 1; k < len; k++) {
                if (2 * num[j] <= num[k]) {
                    count++;
                }
            }
        }
        fout << count << "\n";
        delete[] num;
    }

    fin.close();
    fout.close();

    return 0;
}

/*
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < num.size(); j++) {
            cout << num[j] << " ";
        }
        cout << "\n";
    }
    */