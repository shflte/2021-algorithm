#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <utility>
#include <unordered_set>
using namespace std;

typedef pair<int, int> queen; //row, col
typedef vector<queen>::iterator q_it; //queen vector iterator
            
vector<queen> q_l; //queen list
unordered_set<int> u_r; //used row
fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);
int num_sol;

bool valid(queen q) {
    int i = 0;
    for (q_it it = q_l.begin(); it != q_l.end(); it++) {
        if (q.first == it->first) return false;
        else if (q.second == it->second) return false;
        else if (abs(double(q.first - it->first) / double(q.second - it->second)) == 1) {
            return false;
        }
    }
    return true;
}

void solve(int row, int N) {
    if (row >= N) {
        num_sol++;
        return;
    }
    else if (u_r.count(row)) { //the row is used
        solve(row + 1, N);
        return;
    }
    for (int i = 0; i < N; i++) {
        if (valid(make_pair(row, i))) {
            q_l.push_back(make_pair(row, i));
            solve(row + 1, N);
            q_l.pop_back();
        }
    }
}

int main() {
    int T, N, M, row, col;

    fin >> T;
    for (int i = 0; i < T; i++) {
        fin >> N >> M;
        q_l.clear();
        num_sol = 0;
        for (int j = 0; j < M; j++) {
            fin >> row >> col;
            q_l.push_back(make_pair(row, col));
            u_r.insert(row);
        }

        if (N != 3 && N != 2) {
            solve(0, N);
        }
        fout << num_sol << "\n";
        u_r.clear();
    }
}