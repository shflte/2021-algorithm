#include<iostream>
#include<fstream>
#include<map>
#include<vector>

using namespace std;

int count;
int node;
long long ans;
long long previous; //previous vertex
long long shift; //next vertex


void FindElement(map<long long,vector<long long> > &Chain, long long current){
    

    //cout<<count<<endl;

    if(count==1){
        previous=current;
        current=Chain[current].front();
        if(Chain[current].front()==previous){
            shift=Chain[current].back();
        }
        else{
            shift=Chain[current].front();
        }
    }
    else{
        previous=current;
        current=shift;
        if(Chain[current].front()==previous){
            shift=Chain[current].back();
        }
        else{
            shift=Chain[current].front();
        }
    }
    if(count==node){
        ans=current;
        return;
    }
    count++;
    //can see how the data store in the container
    // cout<<"previous"<<previous<<endl;
    // cout<<"current"<<current<<endl;
    // cout<<"shift"<<shift<<endl;
    FindElement(Chain, current);


};

int main(void){
    ifstream fin;
    fin.open("input.txt");
    ofstream fout;
    fout.open("output.txt");

    int T,N;
    long long v1,v2, current;

    //the key is the index
    //the value are two vertexes near by the vertexes

    fin>>T;
    while(T--){
        fin>>N>>node;
        count=1;
        map<long long,vector<long long> >Chain; 
        Chain.clear();

        for(int i=0;i<(N-1);i++){

            fin>>v1>>v2;

            if(Chain[v1].size()==0 && Chain[v2].size()==0){
                Chain[v1].push_back(v2);
                Chain[v2].push_back(v1);
            }
            else if(Chain[v1].size()>0 && v1==Chain[Chain[v1].front()].front()){
                Chain[v1].push_back(v2);
                Chain[v2].push_back(v1);
            }

        }

            //compare with the vertexes connected with only one vertex, dertermine which is head
            vector<long long>head; 
            head.clear();
           
            for(auto i: Chain){
                if(i.second.size()==1){
                    head.push_back(i.first);
                }
            }
            if(head[0]>head[1]){
                current=head[0];
            }
            else{current=head[1];}
        

        previous=current;
        FindElement(Chain,current);
        fout<<ans<<endl;
     }


    fin.close();
    fout.close();
    return 0;

}
