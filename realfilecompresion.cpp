#include<iostream>
#include<fstream>
#include<map>
#include<queue>
using namespace std;
class node{
    public:
    char data;
    unsigned int frequency;
    node* left;
    node* right;

    node(char c,unsigned int f){
        data=c;
        frequency=f;
        left=right=NULL;
    }
};

class compare{
    public:
    bool operator()(node* l,node* r){
        return l->frequency> r->frequency;
    }
};

node* fromhuffmantree(map<char,int>&freq){
    priority_queue< node*,vector<node*>,compare>pq;
    
    for(auto p:freq){
        pq.push(new node(p.first,p.second));
    }
    while(pq.size()>1){
        node* first=pq.top();
        pq.pop();
        node* second=pq.top();
        pq.pop();
        node* parent=new node('$',first->frequency+second->frequency);
        parent->left=first;
        parent->right=second;
        pq.push(parent);
    }
    return pq.top();
}

void generatecode(node* root,string code,map<char,string>&huffmancode){
    if(!root)return;
    if(!root->left && !root->right){
        huffmancode[root->data]=code;
    }
    generatecode(root->left,code+'0',huffmancode);
    generatecode(root->right,code+'1',huffmancode);
}

int main(){
    ifstream in("input.txt");
    if(!in){
        cout<<"File not found"<<endl;
    }else{
        cout<<"File is found"<<endl;
    }

    map<char,int>freq;
    string text,line;
    while(getline(in,line)){
        text+=line+'\n';
    }
    for(auto c:text){
        freq[c]++;
    }
    in.close();


}