#ifndef _DATA_H_
#define _DATA_H_

#include <fstream>

#define max_test_num 20
struct tTestData {
    int testcase_num;
    int seq_num[max_test_num];
    int seq[max_test_num][50000];
};

extern void solve (tTestData *t);

bool load_data(tTestData* test_data) {
    std::ifstream ifs("input.txt");

    if (!ifs.is_open()) return false;

    ifs >> test_data->testcase_num;

    for (int i = 0; i < test_data->testcase_num; i++) {
        ifs >> test_data->seq_num[i];
        for (int j = 0; j < test_data->seq_num[i]; j++)
            ifs >> test_data->seq[i][j];
    }

    ifs.close();
    return true;
}

int main () {
    tTestData t;
    if (!load_data(&t)) return 1;
    solve(&t);
    return 0;
}

#endif
