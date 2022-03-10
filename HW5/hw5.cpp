#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

typedef vector<list<int> > lists;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);

int main() {
    int T, N, I, v1, v2, first_v_idx, ans;
    lists _lists;
    fin >> T;
    bool exist, first_v_is_end;
    list<int>::iterator first_v_begin, first_v_end;
    list<int> temp;

    for (int i = 0; i < T; i++) {
        fin >> N >> I;
        for (int j = 0; j < N - 1; j++) {
            exist = first_v_is_end = false;
            fin >> v1 >> v2;
            //fout << "v1: " << v1 << "; v2: " << v2 << "\n";
            for (int k = 0; k < _lists.size(); k++) {
                //check if one of the vert. exist in any one of the list. If exist, attach.
                if (!exist) {
                    if (*(_lists[k].begin()) == v1) {
                        _lists[k].push_front(v2);
                        exist = true;
                        first_v_idx = k;
                    }
                    else if (*(--_lists[k].end()) == v1) {
                        _lists[k].push_back(v2);
                        exist = true;
                        first_v_is_end = true;
                        first_v_idx = k;
                    }
                    else if (*(_lists[k].begin()) == v2) {
                        _lists[k].push_front(v1);
                        exist = true;
                        first_v_idx = k;
                    }
                    else if (*(--_lists[k].end()) == v2) {
                        _lists[k].push_back(v1);
                        exist = true;
                        first_v_is_end = true;
                        first_v_idx = k;
                    }
                }
                //if one of them exist, find if the other end exist. 
                //if another one found, merge them
                else {
                    //another one found at begin
                    if ((*(_lists[k].begin()) == v1) || (*(_lists[k].begin()) == v2)) {
                        if (first_v_is_end) {
                            for (auto iter = ++_lists[k].begin(); iter != _lists[k].end(); iter++) {
                                _lists[first_v_idx].push_back(*iter);
                            } 
                        }
                        else {
                            for (auto iter = ++_lists[k].begin(); iter != _lists[k].end(); iter++) {
                                _lists[first_v_idx].push_front(*iter);
                            } 
                        }
                        _lists.erase(_lists.begin() + k);
                    }
                    //another one found at end 
                    else if ((*(--_lists[k].end()) == v1) || (*(--_lists[k].end()) == v2)) {
                        if (first_v_is_end) {
                            for (auto iter = --_lists[k].end(); iter != _lists[k].begin(); ) {
                                _lists[first_v_idx].push_back(*(--iter));
                            } 
                        }
                        else {
                            for (auto iter = --_lists[k].end(); iter != _lists[k].begin(); ) {
                                _lists[first_v_idx].push_front(*(--iter));
                            } 
                        }
                        _lists.erase(_lists.begin() + k);
                    }
                }
            }
            //if not exist, create a new list to store the edge.
            if (!exist) {
                temp.push_back(v1);
                temp.push_back(v2);
                _lists.push_back(temp);
                temp.clear();
            }
            //check
                //     fout << "pair: " << j << "; T: " << i << "; N = " << N << "; I = " << I << "; size of list[0] = " << _lists[0].size() 
                //     << "; front: " << *(_lists[0].begin()) << "; end: " << *(--_lists[0].end()) << "\n";
                // for (int m = 0; m < _lists.size(); m++) {
                // fout << "list: " << m << "; size = " << _lists[m].size()<<"\n";
                // for (auto it = _lists[m].begin(); it != _lists[m].end(); it++) {
                //     fout << *it << " ";
                // }
                // fout <<"\n";
                // }
            //check
        }
        //pairs are already merge into a single list
        if (*(_lists[0].begin()) > *(--_lists[0].end())) {
            auto it = _lists[0].begin(); 
            advance(it, I);
            fout << *(it);
        }
        else {
            auto it = _lists[0].begin(); 
            advance(it, N - 1 - I);
            fout << *(it);
        }
        fout << "\n";

        _lists.clear();
    }

    return 0;
}