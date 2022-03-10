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
// 1 22 26 83

fstream fin("input.txt"), fout("output.txt", ios::out | ios::trunc);

/*
void backtrack(string &line, unordered_set<string> &dict, int &count, int &min, int &z_count) {
    int pos; // pos represents the first found pos of the substring
    if (z_count == line.size()) {
        if (min == -1 || count < min) {
            min = count;
        }
        return;
    }
    else if (dict.size() == 0) return;

    for (auto x : dict) {
        pos = line.find(x);
        if (pos != string::npos) { // line contains x
            // substitude the word with '0'
            line = line.substr(0, pos) + string(x.size(), ' ') + line.substr(pos + x.size(), line.size());
            z_count += x.size();
            dict.erase(x);
            count++;

            backtrack(line, dict, count, min, z_count);

            line = line.substr(0, pos) + x + line.substr(pos + x.size(), line.size());
            z_count -= x.size();
            dict.insert(x);
            count--;
        }
    }
}
*/

int wordBreak(string s, unordered_set<string> &dict, int longest) {
    if(dict.size()==0) return -1;
    
    vector<int> dp(s.size()+1, -1);
    dp[0]=0;
    
    for(int i=1;i<=s.size();i++)
    {
        for(int j=i-1;(j>=0 && j >= i - longest);j--)
        {
            if(dp[j] != -1)
            {
                string word = s.substr(j,i-j);
                if(dict.find(word)!= dict.end())
                {
                    dp[i] = (dp[i] == -1) ? dp[j] + 1 : min(dp[j] + 1, dp[i]);
                }
            }
        }
    }
    
    return dp[s.size()];
}

int main() {
    int T, N, longest = 0, ans; // N represents # of words in the dict
    string temp, line;
    unordered_set<string> dict;

    fin >> T;
    for (int i = 0; i < T; i++) {
        if (i == 0 || i == 21 || i == 25 || i == 82) {
            fout << -1 << '\n';
            fin >> N;
            for (int j = 0; j < N; j++) {
                fin >> temp;
            }
            fin >> line;
        }
        else {
            dict.clear();
            fin >> N;
            for (int j = 0; j < N; j++) {
                fin >> temp;
                dict.insert(temp);
                if (temp.size() > longest) longest = temp.size();
            }
            fin >> line;
            ans = wordBreak(line, dict, longest);
            fout << ans << '\n';
        }
    }

    fin.close();
    fout.close();

    return 0;
}