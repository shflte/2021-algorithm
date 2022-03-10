#ifndef _DATA_H_
#define _DATA_H_

#include <fstream>

struct tTestCase {
    int n;
    int i;
    int edges[50000][2];
};

struct tTestData {
    int t;
    struct tTestCase testcase[10];
};

extern void solve (tTestData *t);

bool load_data(tTestData* test_data) {
    std::ifstream ifs("input.txt");

    if (!ifs.is_open()) return false;

    ifs >> test_data->t;
    for (int cases = 0; cases < test_data->t; ++cases) {
        struct tTestCase *temp = &(test_data->testcase[cases]);

        ifs >> temp->n >> temp->i;

        for(int j = 0; j < (temp->n) - 1; j++) {
            ifs >> temp->edges[j][0] >> temp->edges[j][1];
        }
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
