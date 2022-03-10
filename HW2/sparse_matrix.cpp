#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class node{
	public:
		int row, col;
		int val;
};

class matrix{
    public:
        int row, col;
        list <node*> temp;
};


int main(){
    
    ifstream infile;
	infile.open("input.txt");
	ofstream output("output.txt");
	string buffer;
    map <string, matrix*> m;

	while(!infile.eof()){
		infile >> buffer;
		if(!buffer.compare("Matrix")){
			infile >> buffer;
			m[buffer] = new matrix;
        }
        else if(!buffer.compare("Init")){
			int row, col;
            infile >> buffer >> row >> col;
			m[buffer]->row = row;
			m[buffer]->col = col;
        }
        else if(!buffer.compare("Assign")){
            int row, col, val;
            infile >> buffer >> row >> col >> val;
			node* n = new node;
			n->row = row;
			n->col = col;
			n->val = val;
			m[buffer]->temp.push_back(n);
        }
        else if(!buffer.compare("Print")){
			infile >> buffer;
            int a = 0;
            for(auto s : m[buffer]->temp){
                if(!a++){
                    output << "(" << s->row << " " << s->col << " " << s->val << ")";
                }
                else
				    output << " " << "(" << s->row << " " << s->col << " " << s->val << ")";
			}
            output << "\n";
        }
        else if(!buffer.compare("Delete")){
            infile >> buffer;
            for(auto s : m[buffer]->temp){
                delete s;
            }
			delete m[buffer];
        }
        else if(!buffer.compare("Mult")){
            string word1, word2, word3;
            infile >> word1 >> word2 >> word3;

            map <pair<int, int>, int> cur;
            //map <pair<int, int>, int>:: iterator i;
            map <pair<int, int>, int> ans;

            for(auto s : m[word1]->temp){
                cur[make_pair(s->row, s->col)] = s->val;
            }

            for(auto s : cur){
                for(auto i : m[word2]->temp){
                    if(s.first.second == i->row){
                        ans[make_pair(s.first.first, i->col)] += s.second * i->val;
                    }
                }
            }

            for(auto s : ans){
                node* n = new node;
                n->row = s.first.first;
                n->col = s.first.second;
                n->val = s.second;
                if(n->val != 0)
                    m[word3]->temp.push_back(n);
                else 
                    delete n;
            }


        }
        else if(!buffer.compare("Add")){
            string word1, word2, word3;
            infile >> word1 >> word2 >> word3;

            map <pair<int, int>, int> cur;
            map <pair<int, int>, int>:: iterator i;

            for(auto s : m[word1]->temp){
                cur[make_pair(s->row, s->col)] = s->val;
            }

            for(auto s : m[word2]->temp){
                if((i = cur.find(make_pair(s->row, s->col))) != cur.end())
                    cur[make_pair(s->row, s->col)] += s->val;
                else{
                    cur[make_pair(s->row, s->col)] = s->val;
                }
            }

            for(auto s : cur){
                node* n = new node;
                n->row = s.first.first;
                n->col = s.first.second;
                n->val = s.second;
                if(n->val != 0)
                    m[word3]->temp.push_back(n);
                else 
                    delete n;
            }
        }
    }

    infile.close();
    output.close();

    return 0;
}