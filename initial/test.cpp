// C++(STL) program for Huffman Coding with STL
#include <bits/stdc++.h>
#include "main.h"
using namespace std;
#define REG "REG"
#define CLE "CLE"
#define PrintHT "PrintHT"
#define PrintAVL "PrintAVL"
#define PrintMH "PrintMH"
class Restaurant
{
    bool id[MAXSIZE + 1];
};
class HuffmanTree
{
private:
    class Node;
    Node *root;

public:
    HuffmanTree() : root(0) {}
    ~HuffmanTree()
    {
        destruct(this->root);
    }
    void BuildTree(const map<char, int> &m1, map<char, string> &m2)
    {

        Node *left, *right, *top;
        priority_queue<Node *, vector<Node *>, compare> pq;
        // Create priority queue
        for (auto it = m1.begin(); it != m1.end(); it++)
        {
            pq.push(new Node(it->first, it->second));
        }
        while (pq.size() != 1)
        {
            left = pq.top();
            pq.pop();
            right = pq.top();
            pq.pop();
            top = new Node('|', left->freq + right->freq, left, right);
            pq.push(top);
        }
        this->root = pq.top();
        HuffmanCode(this->root, m2, "");
    }

private:
    void HuffmanCode(Node *root, map<char, string> &m, string s)
    {
        if (!root)
            return;
        HuffmanCode(root->left, m, s + '0');
        HuffmanCode(root->right, m, s + '1');
        if (root->data != '|')
        {
            m[root->data] = s;
        }
    }
    void destruct(Node *root)
    {
        if (!root)
            return;
        destruct(root->left);
        destruct(root->right);
        delete root;
    }
    class Node
    {
        // protected:
    public:
        // One of the input characters
        char data;
        // Frequency of the character
        unsigned freq;
        // Left and right child
        Node *left, *right;
        Node(char data = '|', unsigned freq = 0, Node *left = 0, Node *right = 0)
        {
            this->left = left;
            this->right = right;
            this->data = data;
            this->freq = freq;
        }
        ~Node() {}
        friend class HuffmanTree;
    };
    struct compare
    {
        /*if return 1, l is behind r
                return 0, r is behind l*/
        bool operator()(Node *l, Node *r)
        {
            if (l->freq == r->freq)
                return l->data >= r->data;
            return (l->freq > r->freq);
        }
    };
};
bool CheckIns(const string &line, string &ins, string &name, int &num)
{
    int CountSpace = 0;
    int i = line.find(' ');
    int FirstSpace = i;
    while (i != -1)
    {
        CountSpace++;
        i = line.find(' ', i + 1);
    }
    if (CountSpace > 1)
        return 0;
    if (!CountSpace)
    { // count space = 0
        if (line == PrintAVL || line == PrintHT || line == PrintMH)
        {
            ins = line;
            return 1;
        }
        return 0;
    }
    // count space = 1
    ins = line.substr(0, FirstSpace);
    if (ins == REG)
    {
        name = line.substr(FirstSpace + 1);
        // have not checked name yet
        //
        return 1;
    }
    else if (ins == CLE)
    {
        num = stoi(line.substr(FirstSpace + 1));
        return 1;
    }
    return 0;
}
// Test func
template <typename T1, typename T2>
void PrintMap(const map<T1, T2> &m)
{
    for (auto it = m.begin(); it != m.end(); it++)
        cout << it->first << ": " << it->second << endl;
}
int main()
{
    string filename = "test.txt";
    ifstream filein(filename, ios::in);
    if (filein.is_open())
    {
        string line = "";

        while (getline(filein, line))
        {
            string ins = "";
            int num = 0;
            string name = "";
            if (CheckIns(line, ins, name, num))
            {
                if (ins == REG)
                {
                    map<char, int> m1;
                    map<char, string> m2;
                    for (char i : name)
                    {
                        m1[i]++;
                    }
                    HuffmanTree ht;
                    ht.BuildTree(m1, m2);
                    PrintMap<char, string>(m2);
                }
                else if (ins == CLE)
                {
                }
                else if (ins == PrintAVL)
                {
                }
                else if (ins == PrintHT)
                {
                }
                else if (ins == PrintMH)
                {
                }
            }
        }
        filein.close();
    }
    else
        cout << "Open fail\n";
    return 0;
}