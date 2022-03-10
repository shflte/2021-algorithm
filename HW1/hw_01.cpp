#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "data.hpp"

using namespace std;
/*
struct tTestData { 
    int cnt; //# of seq
    int seq_size[cnt]; //size of each seq
    int data[cnt][20000]; 
};
void solve(tTestData* test_data) {
    ofstream file("output.txt");

    int num_of_seq = test_data->cnt;
    int** a = new int*[num_of_seq];
    for (int i = 0; i < num_of_seq; i++) {
        a[i] = new int[test_data->seq_size[i]];

        for (int j = 0; j < test_data->seq_size[i]; j++) {
            a[i][j] = test_data->data[i][j];
        }
        
        sort(a[i], a[i] + test_data->seq_size[i]);

        for (int m = 0; m < test_data->seq_size[i]; m++) {
            file << a[i][m] << " ";
        }
        file << "\n";
    }

    file.close();
    return;
}
*/

void solve(tTestData* test_data) {
    vector<vector<int>> t(test_data->cnt);

    for (int i = 0; i < test_data->cnt; i++) {
        t[i].resize(test_data->seq_size[i]);
        for (int j = 0; j < test_data->seq_size[i]; j++) {
            t[i][j] = test_data->data[i][j];
        }
    }

    ofstream file("output.txt");
    for (int m = 0; m < test_data->cnt; m++) {
        sort(t[m].begin(), t[m].end());

        for (auto n : t[m]) file << n << " ";
        file << "\n";
    }
    file.close();

    return;
}