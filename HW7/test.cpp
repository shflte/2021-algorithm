#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <unordered_set>

using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);

int main() {
    int T;
    fin >> T;
    for (int i = 0; i < T; i++) {
        fout << -1 << "\n";
    }

    return 0;           
}