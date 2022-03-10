#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

using namespace std;

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);

int main() {
    int n, l, w, p, r, ans_count;
    double pos_l, pos_r, temp, clm, clr; //clm: current left most; clr: current largest right
    bool gap;
    list<pair<double, double> > segments;
    list<pair<double, double> >::iterator iter;
    while (!fin.eof()) {
        fin >> n >> l >> w;
        //input the circles, calculate the segments, build up the list
        for (int i = 0; i < n; i++) {
            fin >> p >> r;
            if (double(r) > double(w) / 2.0) {
                //calculate the pos_l & pos_r
                temp = sqrt(r * r - double(double(w) / 2.0) * double(double(w) / 2.0));
                pos_l = p - temp;
                pos_r = p + temp;
                //insert the segment to the list according to the pos_l
                if (segments.empty()) {
                    segments.push_back(make_pair(pos_l, pos_r));
                }
                else {
                    iter = segments.begin();
                    while (pos_l > iter->first && iter != segments.end()) iter++;
                    segments.insert(iter, make_pair(pos_l, pos_r));
                }
            }
        }
        //count the minimal # of circle(segments) required
        ans_count = 0;
        clm = 0;
        clr = 0;
        gap = false;
        iter = segments.begin();
        while (iter != segments.end() && clr < l) {
            // cout << "clm: " << clm << "; clr: " << clr << "\n";   
            if (iter->second > clr && iter->first <= clm) {
                clr = iter->second;
            }
            else if (iter->first > clm && clm == clr) {
                gap = true;
            }
            else if (iter->first > clm) {
                clm = clr;
                ans_count++;
                iter--;
            }
            iter++;
        }
        if (clr < l || gap) {
            fout << -1 << "\n";
        }
        else if (n == 0) {
            fout << 0 << "\n";
        }
        else {
            fout << ans_count + 1 << "\n";  // + 1: left the loop when clr >= l, 
                                            //      but the final segment is not counted
        }
        
        // for (auto x : segments) fout << "left: " << x.first << "; right: " << x.second << "\n";

        segments.clear();
    }

    fin.close();
    fout.close();

    return 0;
}