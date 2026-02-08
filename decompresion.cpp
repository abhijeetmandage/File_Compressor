#include<iostream>
#include<map>
#include<fstream>
using namespace std;

map<string,char>loadrev_code(string filename){
    ifstream in(filename);
    map<string,char>reverse;

    string  line;

    while(getline(in,line)){
        if(line.empty()) continue;
        if(line.substr(0,2)=="\\n"){
            string bcode=line.substr(3);
            reverse[bcode]='\n';
        }else if(line.substr(0,3)=="' '"){
             string bcode=line.substr(4);
            reverse[bcode]=' '; 
        }else{
             char symbol = line[0];
            string bcode = line.substr(2);
            reverse[bcode]=symbol;
        }
    }
    in.close();
    return reverse;
}

void  decodebinary_file(string binfile,string hcodefile,string outputfile){
   map<string,char>reversecode=loadrev_code(hcodefile);

   ifstream in(binfile,ios::binary);
   ofstream out(outputfile);

   int toatalBits;
   in.read((char*)&toatalBits,sizeof(toatalBits));

   string currentbits="";
   char byte;
   int readbits=0;

   while(in.get(byte)&&readbits<toatalBits){
    for(int i=7;i>=0 && readbits<toatalBits;i--){
        char bit=((byte>>i) & 1)?'1':'0';
        currentbits+=bit;
        readbits++;

        if(reversecode.count(currentbits)){
            out<<reversecode[currentbits];
            currentbits="";
        }
    }
   }
   in.close();
   out.close();
   cout<<"original text restoared in file "<<outputfile<<endl;
}
int main(){
    decodebinary_file("compresedbinary_file.bin","codeinfo.txt","decoded_outputfile.txt");
    return 0;
}