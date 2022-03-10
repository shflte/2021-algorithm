#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iterator>
#include <utility>
#include <regex>
#include <map>
#include <typeinfo>
//#include "data.hpp"
using namespace std;

const int max_data_size = 12794;
const int buffer_size = 50;

struct tTestData { 
    int line_num;
    char data[max_data_size][buffer_size]; 
};

typedef pair<pair<int, int>, int> cell; 
typedef map<string, vector<cell> > matrix;

enum command {Matrix, Init, Assign, Delete, Mult, Add, Print};

command which_cmd(char* str) {
    if (strcmp(str, "Matrix") == 0) return Matrix;
    else if (strcmp(str, "Init") == 0) return Init;
    else if (strcmp(str, "Assign") == 0) return Assign;
    else if (strcmp(str, "Delete") == 0) return Delete;
    else if (strcmp(str, "Mult") == 0) return Mult;
    else if (strcmp(str, "Add") == 0) return Add;
    else if (strcmp(str, "Print") == 0) return Print;

    return Matrix;
}

//return true if x > y
bool bigger_int_pair(pair<int, int> x, pair<int, int> y) {
    if (x.first > y.first) return true;
    else if (x.first == y.first) {
        if (x.second > y.second) return true;
    }
    return false;
}

void swap_mat_element(vector<cell>::iterator it_i, vector<cell>::iterator it_j) {
    cell temp = *it_j;
    *it_j = *it_i;
    *it_i = temp;
}

///Quick sort the matrix///////////
int partition(vector<cell>::iterator front, int len, int start);

void QuickSort(vector<cell>::iterator front, int len, int start) {
    if (len <= 1) return;

    int end = partition(front, len, start); //end position of the former partition
    int len_for = end - start + 1,
        len_lat = len - len_for; //len for/lat: former/latter
    QuickSort(front, len_for, start); //sort former partition
    QuickSort(front, len_lat, end + 1); //sort latter partition

    return;
}

int partition(vector<cell>::iterator front, int len, int start){
    if (len <= 1) return start;

    int end = start - 1, pivot = start + len - 1; //end: end of the former partition
                                          
    for (int i = start; i < start + len; i++) {
        if (bigger_int_pair((front + pivot)->first , (front + i)->first)) {
            end++;
            swap_mat_element(front + i, front + end);
        }
    }
    swap_mat_element(front + end + 1, front + pivot);

    return end;
}
////////////

cell make_cell(int row, int col, int value) {
    return make_pair(make_pair(row, col), value);
}

void solve(tTestData* test_data) {
    matrix mat;

    fstream output_stream("output.txt", std::ios::out | std::ios::trunc);

    for (int l = 0; l < test_data->line_num; l++) {
        string line(test_data->data[l]);
        istringstream iss(line);

        char* cmd = strtok(test_data->data[l], " ");

        command the_command = which_cmd(cmd);
        switch (the_command) {
            case 0: {
                string str_cmd, the_mat;
                iss >> str_cmd >> the_mat;

                mat[the_mat];

                break;
            }
            case 1: {
                
                break;
            }
            case 2: {
                string str_cmd, the_mat, row, col, value;
                iss >> str_cmd >> the_mat >> row >> col >> value;

                mat[the_mat].push_back(make_cell(stoi(row), stoi(col), stoi(value)));

                break;
            }
            case 3: {
                string str_cmd, the_mat;
                iss >> str_cmd >> the_mat;

                mat[the_mat].clear();

                break;
            }
            case 4: {
                string str_cmd, mat_a, mat_b, mat_c;
                iss >> str_cmd >> mat_a >> mat_b >> mat_c; 

                vector<cell>::iterator it_a = mat[mat_a].begin(),
                it_b = mat[mat_b].begin();
                
                QuickSort(it_a, mat[mat_a].size(), 0);
                QuickSort(it_b, mat[mat_b].size(), 0);

                for (;it_a < mat[mat_a].end(); it_a++) {
                    for (vector<cell>::iterator it_b_loop = it_b ;it_b_loop < mat[mat_b].end(); it_b_loop++) {
                        if ((it_a->first.second == it_b_loop->first.first) && ((it_a->second * it_b_loop->second) != 0)) {
                            mat[mat_c].push_back(make_cell(it_a->first.first, it_b_loop->first.second, it_a->second * it_b_loop->second));
                        }
                    }
                }

                //check if one coordinate appear twice
                vector<cell>::iterator it_c = mat[mat_c].begin();
                for (vector<cell>::iterator it_c_i = it_c; it_c_i < mat[mat_c].end(); it_c_i++) {
                    for (vector<cell>::iterator it_c_j = it_c; it_c_j < mat[mat_c].end(); it_c_j++) {
                        if ((it_c_i->first == it_c_j->first) && (it_c_i != it_c_j)) {
                            it_c_i->second += it_c_j->second;
                            mat[mat_c].erase(it_c_j);
                            it_c_j--;
                        }
                    }
                }

                QuickSort(it_c, mat[mat_c].size(), 0);

                break;
            }
            case 5: {
                string str_cmd, mat_a, mat_b, mat_c;
                iss >> str_cmd >> mat_a >> mat_b >> mat_c; 

                vector<cell>::iterator it_a = mat[mat_a].begin(),
                it_b = mat[mat_b].begin();
                
                QuickSort(it_a, mat[mat_a].size(), 0);
                QuickSort(it_b, mat[mat_b].size(), 0);

                while ((it_a != mat[mat_a].end()) || (it_b != mat[mat_b].end())) {
                    if (it_a == mat[mat_a].end()) {
                        if (it_b->second != 0) {
                            mat[mat_c].push_back(*it_b);
                        }
                        it_b++;
                    }
                    else if (it_b == mat[mat_b].end()) {
                        if (it_a->second != 0) {
                            mat[mat_c].push_back(*it_a);
                        }
                        it_a++;
                    }
                    else {
                        if (it_a->first == it_b->first) {
                            if ((it_a->second != 0) || (it_b->second != 0)) {
                                mat[mat_c].push_back(make_cell(it_a->first.first,it_b->first.second,it_a->second + it_b->second));
                            }
                            it_a++;
                            it_b++;
                        }
                        else if (bigger_int_pair(it_a->first, it_b->first)) {
                            if (it_b->second != 0) {
                                mat[mat_c].push_back(*it_b);
                            }
                            it_b++;
                        }
                        else {
                            if (it_a->second != 0) {
                                mat[mat_c].push_back(*it_a);
                            }
                            it_a++;
                        }
                    }
                }

                for (vector<cell>::iterator it = mat[mat_c].begin(); it < mat[mat_c].end(); it++) {
                    if (it->second == 0) {
                        mat[mat_c].erase(it);
                        it--;
                    }
                }

                break;
            }
            case 6: {
                string str_cmd, the_mat;
                iss >> str_cmd >> the_mat;

                for (vector<cell>::iterator it = mat[the_mat].begin(); it < mat[the_mat].end(); it++) {
                    output_stream << "(" << it->first.first << " " << it->first.second << " " << it->second << ") ";
                }
                output_stream << "\n";

                break;
            }
        }
    }
    output_stream.close();
}

int main() {

    fstream input_stream("input.txt", ios::in);
    int line_number = 12794;
    tTestData* test_data = new tTestData;
    test_data->line_num = line_number;

    for (int i = 0; i < line_number; i++) {
        input_stream.getline(test_data->data[i], 50, '\n');
    }

    solve(test_data);

    return 0;

}