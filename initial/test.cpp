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
private:
    class Table;
    Table *table;
    int count1;      // count 1st area
    int count2;      // count 2nd area
    long long order; // numerical order of guests getting in restaurant
    map<int, Table *> area1;
    queue<Table *> FIFO;
    stack<Table *> LRCO;

    class Table
    {
    public:
        bool IsEmpty;
        string name;
        long long order; // numerical order of guests getting in restaurant
        int result;
        int num;  // number of times to order dish
        int area; // 0: inialize, delete; 1: area1, 2: area2
        Table()
        {
            order = 0;
            IsEmpty = 1;
            name = "";
            result = 0;
            num = 0;
            area = 0;
        }
        ~Table() {}
    };

public:
    Restaurant()
    {
        table = new Table[MAXSIZE];
        count1 = 0;
        count2 = 0;
        order = 0;
    }
    ~Restaurant() {}
    bool IsTableEmpty(const int &id)
    {
        if (id >= 1 && id <= MAXSIZE)
            return table[id].IsEmpty;
        return 0;
    }
    bool IsContainingGuest(const int &id, const int &result, const string &name)
    {
        if (id >= 1 && id <= MAXSIZE)
        {
            if (table[id].result != result)
                return 0;
            if (table[id].name != name)
                return 0;
            return 1;
        }
        return 0;
    }
    int InsertGuest(const int &result, const string &name)
    {
        if (count1 + count2 == MAXSIZE)
        {
        }
        else
        {
            int id = result % MAXSIZE + 1;
            while (!table[id].IsEmpty)
            {
                id++;
                if (id > MAXSIZE)
                    id = 1;
            }
            table[id].IsEmpty = 0;
            table[id].name = name;
            table[id].order = order;
            order++;
            table[id].result = result;
            table[id].num = 1;
            /*bool IsEmpty;
            string name;
            long long order;
            int result;
            int num;*/
            Table *temp = &table[id];
            int ii = temp - table;
            FIFO.push(temp);
            return id;
        }
        return 0;
    }
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
int EncryptingName(const string &name, map<char, string> &m2)
{
    string s;
    for (unsigned i = name.size() - 1; i >= 0; i--)
    {
        s = m2[name[i]] + s;
        if (s.size() >= 15)
            break;
    }
    if (s.size() > 15)
    {
        return stoi(s.substr(s.size() - 15, 15), 0, 2);
    }
    else
        return stoi(s, 0, 2);
}
bool IsGuestInRestaurant(Restaurant &r, const string &name, unordered_map<string, pair<int, int>> &EncryptedName)
{
    for (int i = 1; i <= MAXSIZE; i++)
    {
        if (!r.IsTableEmpty(i))
        {
            if (r.IsContainingGuest(i, EncryptedName[name].first, name))
            {
                return 1;
            }
        }
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
void simulate(string filename)
{
    ifstream filein(filename, ios::in);
    if (filein.is_open())
    {
        Restaurant r;
        string line = "";
        // consist of name already transformed into number
        // string: name
        // first int: result, second int: id
        unordered_map<string, pair<int, int>> EncryptedName;
        while (getline(filein, line))
        {
            string ins = "";
            int num = 0;
            string name = "";
            if (CheckIns(line, ins, name, num))
            {
                if (ins == REG)
                {
                    if (EncryptedName.find(name) == EncryptedName.end())
                    {
                        if (name.size() == 1)
                        {
                            EncryptedName[name].first = 1;
                        }
                        else
                        {
                            map<char, int> m1;
                            map<char, string> m2;
                            for (char i : name)
                            {
                                m1[i]++; // create map with key (charater), data (frequency)
                            }
                            HuffmanTree ht;
                            ht.BuildTree(m1, m2);
                            int result = EncryptingName(name, m2);
                            EncryptedName[name].first = result;
                        }
                    }
                    if (IsGuestInRestaurant(r, name, EncryptedName))
                    {
                    }
                    else
                    {
                        int id = r.InsertGuest(EncryptedName[name].first, name); // return id
                        EncryptedName[name].second = id;
                    }
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
}
int main(int argc, char *argv[])
{
    string fileName = "test.txt";
    simulate(fileName);
    return 0;
}