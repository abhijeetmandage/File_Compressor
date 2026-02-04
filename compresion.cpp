#include<iostream>
#include<fstream>
#include<map>
using namespace std;
class node{
    char data;
    unsigned frequency;
    node* left;
    node* right;

    public:
    node(char d,unsigned f){
        data=d;
        frequency=f;
        left=NULL;
        right=NULL;
    }
};

map<char,string> huffmantree(map<char,int>& freq){

}
int main(){
    ifstream inf("input.txt");
    if(!inf){
        cout<<"file not found"<<endl;;
    }else{
        cout<<"Found"<<endl;
    }
    string text,line;
    while(getline(inf,line)){
        text+=line+'\n';
    }
    inf.close();
    map<char,int>freq;
    for(char c:text){
        freq[c]++;
    }
    for(auto v:freq){
        cout<<v.first<<" "<<v.second<<endl;
    }
    return 0; 
}