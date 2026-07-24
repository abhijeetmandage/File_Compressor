#include <iostream>
#include <fstream>
#include <map>
#include <queue>
using namespace std;
class node
{
    public:
        char data;
        unsigned int frequency;
        node *left;
        node *right;

        node(char c, unsigned int f)
        {
            data = c;
            frequency = f;
            left = right = NULL;
        }
};

class compare
{
    public:
        bool operator()(node *l, node *r)
        {
            return l->frequency > r->frequency;
        }
};

node *fromhuffmantree(map<char, int> &freq)
{
    priority_queue<node *, vector<node *>, compare> pq;

    for (auto p : freq)
    {
        pq.push(new node(p.first, p.second));
    }

    while (pq.size() > 1)
    {
        node *first = pq.top();
        pq.pop();
        node *second = pq.top();
        pq.pop();
        node *parent = new node('$', first->frequency + second->frequency);
        parent->left = first;
        parent->right = second;
        pq.push(parent);
    }
    return pq.top();
}

void generatecode(node *root, string code, map<char, string> &huffmancode)
{
    if (!root)
        return;
    if (!root->left && !root->right)
        huffmancode[root->data] = code;
    generatecode(root->left, code + '0', huffmancode);
    generatecode(root->right, code + '1', huffmancode);
}

void compression(const string &inputfile, const string outputfile, map<char, int> &freq, string text)
{
    ifstream in(inputfile, ios::binary);
    if (!in)
        cout << "file is not found" << endl;

    node *root = fromhuffmantree(freq);
    map<char, string> binarycode;
    generatecode(root, "", binarycode);

    // stoare all bits in string
    string bits = "";
    for (auto c : text)
    {
        bits += binarycode[c];
    }

    ofstream out(outputfile, ios::binary);
    if (!out)
    {
        cout << "file not found" << endl;
        return;
    }

    int n = freq.size();
    out.write((char *)&n, sizeof(n));

    for (auto &v : freq)
    {
        out.write(&v.first, sizeof(v.first));
        out.write((char *)&v.second, sizeof(v.second));
    }

    int bitecount = bits.size();
    out.write((char *)&bitecount, sizeof(bitecount));

    char byte = 0;
    int count = 0;

    for (char b : bits)
    {
        byte = (byte << 1) | (b - '0');
        count++;

        if (count == 8)
        {
            out.put(byte);
            byte = 0;
            count = 0;
        }
    }
    if (count > 0)
    {
        byte = byte << (8 - count);
        out.put(byte);
    }
    out.close();
    cout << "compresion done: " << outputfile << endl;
}

string decompressinram(const string &inputefile)
{
    ifstream in(inputefile, ios::binary);
    if (!in)
        cout << "file is not found" << endl;
    int n;
    in.read((char *)&n, sizeof(n));
    map<char, int> freq;
    for (int i = 0; i < n; i++)
    {
        char c;
        int f;
        in.read(&c, sizeof(c));
        in.read((char *)&f, sizeof(f));
        freq[c] = f;
    }
    int bitcount;
    in.read((char *)&bitcount, sizeof(bitcount));

    vector<char> bytes((istreambuf_iterator<char>(in)), {});
    in.close();

    node *root = fromhuffmantree(freq);
    string bit = "";
    for (char byte : bytes)
    {
        for (int i = 7; i >= 0; i--)
        {
            if (bit.size() == bitcount)
                break;
            bit += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    string output = "";
    node *curr = root;
    for (char b : bit)
    {
        curr = (b == '0') ? curr->left : curr->right;

        if (curr->left == NULL && curr->right == NULL)
        {
            output += curr->data;
            curr = root;
        }
    }
    return output;
}
int main()
{
    ifstream in("input.txt");
    if (!in)
        cout << "File not found" << endl;
    else
        cout << "File is found" << endl;
    cout<<"---------------------------------------------------------"<<endl;
    string inputefile = "input.txt";
    string compresed_file = "compresed_input.txt";

    map<char, int> freq;
    string text, line;
    while (getline(in, line))
    {
        text += line + '\n';
    }
    for (auto c : text)
    {
        freq[c]++;
    }
    in.close();

    compression(inputefile, compresed_file, freq, text);
    cout<<"---------------------------------------------------------"<<endl;
    ifstream inf(inputefile, ios::binary | ios::ate);
    ifstream comf(compresed_file, ios::binary | ios::ate);
    cout << "Original File Size: " << (double)inf.tellg() / 1024 << " " << "kb" << endl;
    cout << "Compresed File Size: " << (double)comf.tellg() / 1024 << " " << "kb" << endl;
    cout<<"---------------------------------------------------------"<<endl;

    string decompresedtext = decompressinram(compresed_file);
    cout << "\nDecompressed Text:\n";
    cout << "---------------------------------------------------------\n";
    cout << decompresedtext << endl;
    inf.close();
    comf.close();
    return 0;
}