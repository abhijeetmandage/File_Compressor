#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include<vector>
using namespace std;
class node{
    public:

    char data;
    unsigned frequency;
    node* left;
    node* right;
    
    node(char d,unsigned f){
        data=d;
        frequency=f;
        left=NULL;
        right=NULL;
    }
};

class compare {
    bool operator()(node* l, node* r) {
        return l->frequency > r->frequency;
    }
};

void generatehuffmancode(node* root,string binarycode, map<char,string>&huffmanbinarycode){
    if(root==NULL){
        return;
    }
    if(root->data!='$'){
        huffmanbinarycode[root->data]=binarycode;
    }
    generatehuffmancode(root->left,binarycode+"0",huffmanbinarycode);
    generatehuffmancode(root->right,binarycode+"1",huffmanbinarycode);
}
map<char,string> huffmantree(map<char,int>& freq){
    priority_queue<node*,vector<node*>,compare>pq;

    for(auto f:freq){
        pq.push(new node(f.first,f.second));
    }
    
    while(pq.size()>1){
        node* first=pq.top();
        pq.pop();
        node* second=pq.top();
        pq.pop();
        node* parent=new node('$',first->frequency+second->frequency);
        parent->left=first;
        parent->right = second;
        pq.push(parent);
    }
    map<char,string>huffmanbinarycode;
    generatehuffmancode(pq.top(),"",huffmanbinarycode);
    return huffmanbinarycode;
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