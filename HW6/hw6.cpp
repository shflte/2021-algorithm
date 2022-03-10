#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);
enum operations {
    INSERT, 
    FIND,
    ERASE,
    ENUM,
    CLEAR
};
operations op_code(string a) {
    if (a == "INSERT") return INSERT;
    else if (a == "FIND") return FIND;
    else if (a == "ERASE") return ERASE;
    else if (a == "ENUM") return ENUM;
    else if (a == "CLEAR") return CLEAR;
}

int main() {
    string op, key, value, key2;
    int hash_key;
    hash<string> str_hash;
    list<pair <string, string> > MiehPu;
    list<pair <string, string> >::iterator prev_query = MiehPu.begin();

    while (!fin.eof()) {
        fin >> op;
        switch (op_code(op)) {
            case INSERT: {
                fin >> key >> value;
                key = key.substr(4, key.length() - 1);
                value = value.substr(6, value.length() - 1);
                auto iter = MiehPu.begin();
                while (iter != MiehPu.end() && iter->first < key) iter++;
                if (MiehPu.empty()) {
                    MiehPu.insert(iter, make_pair(key, value));
                    fout << "INSERT " << key << " SUCCESS!\n";
                }
                else if (iter->first == key) 
                    fout << "INSERT " << key << " FAIL!\n";
                else if (iter->first > key || iter == MiehPu.end()) {
                    MiehPu.insert(iter, make_pair(key, value));
                    fout << "INSERT " << key << " SUCCESS!\n";
                }
                break;
            }
            case FIND: {
                fin >> key;
                key = key.substr(4, key.length() - 1);

                auto iter = prev_query;
                iter++;
                while (iter->first != key && iter != prev_query) {
                    if (iter == MiehPu.end() || iter->first > key) iter = MiehPu.begin();
                    else iter++;
                }
                if (iter->first == key) {
                    fout << "FIND "<< key << ":" << iter->second << "!\n";
                    prev_query = iter;
                }
                else if (iter == prev_query) {
                    fout << key << " NOT FOUND!\n";
                }
                break;
            }
            case ERASE: {
                fin >> key;
                key = key.substr(4, key.length() - 1);
                bool erased = false;

                for (auto erase_iter = MiehPu.begin(); erase_iter != MiehPu.end(); erase_iter++) {
                    if (erase_iter->first == key) {
                        MiehPu.erase(erase_iter);
                        fout << "ERASE " << key << " SUCCESS!\n";
                        erased = true;
                        break;
                    }
                }
                if (!erased) fout << "ERASE " << key << " FAIL!\n";

                break;
            }
            case ENUM: {
                fin >> key >> key2;
                key = key.substr(4, key.length() - 1);
                key2 = key2.substr(4, key2.length() - 1);
                auto iter1 = MiehPu.begin();
                while (iter1 != MiehPu.end() && iter1->first != key) iter1++;
                auto iter2 = MiehPu.begin();
                while (iter2 != MiehPu.end() && iter2->first != key2) iter2++;

                if (iter1 == MiehPu.end() && iter2 == MiehPu.end()) {
                    if (!MiehPu.empty()) 
                        for (auto iter = MiehPu.begin(); iter != MiehPu.end(); iter++) {
                            fout << "ENUM " << iter->first << ":" << iter->second << "\n"; 
                        }
                }
                else if (iter1 != MiehPu.end() && iter2 == MiehPu.end()) {
                    if (!MiehPu.empty()) 
                        for (auto iter = iter1; iter != MiehPu.end(); iter++) {
                            fout << "ENUM " << iter->first << ":" << iter->second << "\n"; 
                        }
                }
                else if (iter1 == MiehPu.end() && iter2 != MiehPu.end()) {
                    if (!MiehPu.empty()) {    
                        for (auto iter = MiehPu.begin(); iter != iter2; iter++) {
                            fout << "ENUM " << iter->first << ":" << iter->second << "\n"; 
                        }
                        fout << "ENUM " << iter2->first << ":" << iter2->second << "\n"; 
                    }
                }
                else {
                    if (!MiehPu.empty()) {
                        for (auto iter = iter1; iter != iter2; iter++) {
                            fout << "ENUM " << iter->first << ":" << iter->second << "\n"; 
                        }
                        fout << "ENUM " << iter2->first << ":" << iter2->second << "\n"; 
                    }
                }
                break;
            }
            case CLEAR: {
                MiehPu.clear();
                break;
            }
            default : {
                break;
            }
        }
    }
    // for (auto x : MiehPu) {
    //     cout << x.first << "\n";
    // }

    return 0;
}