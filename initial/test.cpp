// C++(STL) program for Huffman Coding with STL
#include <bits/stdc++.h>
using namespace std;

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
                return l->data > r->data;
            return (l->freq > r->freq);
        }
    };
};

// Test func
template <typename T1, typename T2>
void PrintMap(const map<T1, T2> &m)
{
    for (auto it = m.begin(); it != m.end(); it++)
        cout << it->first << ": " << it->second << endl;
}
int main()
{
    map<char, int> st;
    map<char, string> m;
    // string str = "huahoangnhat";
    string str = "huynhvutanphat";
    for (int i = 0; i < str.size(); i++)
        st[str[i]]++;
    HuffmanTree h;
    h.BuildTree(st, m);
    PrintMap<char, string>(m);
    return 0;
}