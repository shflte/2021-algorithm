#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>

using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);
map<int, list<int> > al;


set<int> bfs() {
    set<int> result;
    queue<int> q;
    unordered_map<int, bool> color; // 0->blue, 1->green
    unordered_map<int, bool> visited;
    list<int>::iterator it;

    int current, current_color;
    q.push(0);
    color[0] = 0;
    visited[0] = 1;
    result.insert(0);

    while (!q.empty()) {
        current = q.front();
        current_color = color[q.front()];
        if (current_color == 0) {
            result.insert(current);
        }

        // if (current == 4) {
        //     cout << "\n";
        //     for (auto l : al) {
        //         cout << l.first << ": ";
        //         for (auto m : l.second) {
        //             cout << m << " ";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n";
        // }

        q.pop();
        // cout << current << "\n";
        for (it = al[current].begin(); it != al[current].end(); it++) {
            if (!visited[*it]) {
                q.push(*it);
                visited[*it] = true;
                color[*it] = (current_color == 0) ? 1 : 0;
            }
            else if (visited[*it] && color[*it] == current_color) {
                // cout << current << " " << current_color << " " << *it << "\n";
                result.clear();
                result.insert(-1);
                return result;
            }
        }
    }
    return result;
}

int main() {
    int E, va, vb;
    set<int> result;

    fin >> E;
        for (int i = 0; i < E; i++) {
            fin >> va >> vb;
            al[va].push_back(vb);
            al[vb].push_back(va);
        }

        // for (auto y : al[3]) {
        //     cout << y << "\n";
        // }
        result = bfs();
        auto it = result.begin();
        for (int g = 0; g < result.size() - 1; g++) {
            fout << *it << ",";
            it++;
        }
        fout << *it;

        fout << "\n" << -1 << "\n";


    fin.close();
    fout.close();
}