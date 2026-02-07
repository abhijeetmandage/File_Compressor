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
    public:
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

void compresedtext(string bits,string filename){
    ofstream out(filename);
    out<<bits;
    out.close();
}

void compresedbinaryfile(string bits,string filename){
    ofstream file(filename,ios::binary);

    char byts=0;
    int count=0;
    for(int i=0;i<bits.length();i++){
        byts=byts<<1;

        if(bits[i]=='1'){
            byts=byts|1;
        }
        count++;

        if(count==8){
            file.put(byts);
            byts=0;
            count=0;
        }
    }
    if(count>0){
        byts=byts<<(8-count);
        file.put(byts);
    }
    file.close();
}

void savecodeinfile(map<char,string>&huffmanbinarycode,string filename){
    ofstream out(filename);
    for(auto p:huffmanbinarycode){
        if(p.first=='\n'){
            out<<"\\n "<<p.second<<endl;
        }else if(p.first==' '){
            out<<"' ' "<<p.second<<endl;
        }else{
            out<<p.first<<" "<<p.second<<endl;
        }
    }
    out.close();

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
    map<char,string>hcode=huffmantree(freq);
    string compresedtext1="";
    for(auto c:text){
        compresedtext1+=hcode[c];
    }
    //compresed code file 
    compresedtext(compresedtext1,"compreseddatafile.txt");
    //compresed binary file
    compresedbinaryfile(compresedtext1,"compresedbinary_file.bin");
    //save code (in the from 0 and 1)
    savecodeinfile(hcode,"codeinfo.txt");
    cout<<"Compresion Complete"<<endl;
    cout<<"Size of original file is "<<text.length()*8<<" bits"<<endl;
    ifstream f("compresedbinary_file.bin", ios::binary | ios::ate);
    cout << "size of compressed file is " << f.tellg()*8 << " bits" << endl;
    return 0; 
}