// C++(STL) program for Huffman Coding with STL
#include <bits/stdc++.h>
#include "main.h"
using namespace std;
#define REG "REG"
#define CLE "CLE"
#define PrintHT "PrintHT"
#define PrintAVL "PrintAVL"
#define PrintMH "PrintMH"
#define RH 1
#define EH 2
#define LH 3
class Restaurant
{
private:
    class Table
    {
    public:
        bool IsEmpty;
        string name;
        long long order; // numerical order of guests getting in restaurant
        int result;
        int num;  // number of times to order dish
        int area; // 0: inialize, delete; 1: area1, 2: area2
        Table(bool IsEmpty = 1, string name = "", long long order = 0, int result = 0, int num = 0, int area = 0)
        {
            this->IsEmpty = IsEmpty;
            this->name = name;
            this->order = order;
            this->result = result;
            this->num = num;
            this->area = area;
        }
        ~Table() {}
    };
    class AVLtree
    {
    public:
        class node;
        node *root;
        class node
        {
        public:
            Table *table;
            int Balance; // {RH, EH, LH}
            node *left;
            node *right;
            node(Table *table = 0, int Balance = EH, node *left = 0, node *right = 0)
            {
                this->table = table;
                this->left = left;
                this->right = right;
                this->Balance = Balance;
            }
        };
        node *RotateRight(node *&root)
        {
            node *temp = root->left;
            root->left = temp->right;
            temp->right = root;
            return temp;
        }
        node *RotateLeft(node *&root)
        {
            node *temp = root->right;
            root->right = temp->left;
            temp->left = root;
            return temp;
        }
        node *LeftBalance(node *&root, bool &taller)
        {
            node *left = root->left;
            if (left->Balance == LH)
            {
                // left of left
                root->Balance = EH;
                left->Balance = EH;
                root = RotateRight(root);
            }
            else
            {
                // right of left
                node *RightOfLeft = left->right;
                if (RightOfLeft->Balance == EH)
                {
                    root->Balance = EH;
                    left->Balance = EH;
                }
                else if (RightOfLeft->Balance == RH)
                {
                    root->Balance = EH;
                    left->Balance = LH;
                }
                else
                {
                    root->Balance = RH;
                    left->Balance = EH;
                }
                RightOfLeft->Balance = EH;
                root->left = RotateLeft(root->left);
                root = RotateRight(root);
            }
            taller = 0;
            return root;
        }
        node *RightBalance(node *root, bool &taller)
        {
            node *right = root->right;
            if (right->Balance == RH)
            {
                // right of right
                root->Balance = EH;
                right->Balance = EH;
                root = RotateLeft(root);
            }
            else
            {
                // left of right
                node *LeftOfRight = right->left;
                if (LeftOfRight->Balance == LH)
                {
                    root->Balance = EH;
                    right->Balance = RH;
                }
                else if (LeftOfRight->Balance == EH)
                {
                    root->Balance = EH;
                    right->Balance = EH;
                }
                else
                {
                    root->Balance = LH;
                    right->Balance = EH;
                }
                LeftOfRight->Balance = EH;
                root->right = RotateRight(right);
                root = RotateLeft(root);
            }
            taller = 0;
            return root;
        }
        node *insert(node *root, Table *t, bool &taller)
        {
            if (!root)
            {
                taller = 1;
                return new node(t);
            }
            if (root->table->result > t->result)
            {
                root->left = insert(root->left, t, taller);
                if (taller)
                {
                    // left sub tree is taller
                    if (root->Balance == LH)
                    {
                        root = LeftBalance(root, taller);
                    }
                    else if (root->Balance == EH)
                    {
                        root->Balance = LH;
                    }
                    else
                    {
                        root->Balance = EH;
                        taller = 0;
                    }
                }
            }
            else
            {
                root->right = insert(root->right, t, taller);
                if (taller)
                {
                    // right subtree is taller
                    if (root->Balance == LH)
                    {
                        taller = 0;
                        root->Balance = EH;
                    }
                    else if (root->Balance == EH)
                    {
                        root->Balance = RH;
                    }
                    else
                    {
                        root = RightBalance(root, taller);
                    }
                }
            }
            return root;
        }

        node *DeleteRightBalance(node *root, bool &isShorter)
        {
            if (root->Balance == LH)
            {
                root->Balance = EH;
            }
            else if (root->Balance == EH)
            {
                isShorter = 0;
                root->Balance = RH;
            }
            else
            {
                node *right = root->right;
                if (right->Balance == LH)
                {
                    node *LeftOfRight = right->left;
                    if (LeftOfRight->Balance == LH)
                    {
                        right->Balance = RH;
                        root->Balance = EH;
                    }
                    else if (LeftOfRight->Balance == EH)
                    {
                        right->Balance = EH;
                        root->Balance = EH;
                    }
                    else
                    {
                        root->Balance = LH;
                        right->Balance = EH;
                    }
                    LeftOfRight->Balance = EH;
                    root->right = RotateRight(right);
                    root = RotateLeft(root);
                }
                else
                {
                    if (right->Balance == EH)
                    {
                        root->Balance = RH;
                        right->Balance = LH;
                        isShorter = 0;
                    }
                    else
                    {
                        root->Balance = EH;
                        right->Balance = EH;
                    }
                    root = RotateLeft(root);
                }
            }
            return root;
        }
        node *DeleteLeftBalance(node *root, bool &isShorter)
        {
            if (root->Balance == RH)
            {
                root->Balance = EH;
            }
            else if (root->Balance == EH)
            {
                isShorter = 0;
                root->Balance = LH;
            }
            else
            {
                node *left = root->left;
                if (left->Balance == RH)
                {
                    node *RightOfLeft = left->right;
                    if (RightOfLeft->Balance == RH)
                    {
                        left->Balance = LH;
                        root->Balance = EH;
                    }
                    else if (RightOfLeft->Balance == EH)
                    {
                        left->Balance = EH;
                        root->Balance = EH;
                    }
                    else
                    {
                        root->Balance = RH;
                        left->Balance = EH;
                    }
                    RightOfLeft->Balance = EH;
                    root->left = RotateLeft(left);
                    root = RotateRight(root);
                }
                else
                {
                    if (left->Balance == EH)
                    {
                        root->Balance = LH;
                        left->Balance = RH;
                        isShorter = 0;
                    }
                    else
                    {
                        root->Balance = EH;
                        left->Balance = EH;
                    }
                    root = RotateRight(root);
                }
            }
            return root;
        }
        node *remove(node *root, Table *t, bool &isSuccessful, bool &isShorter)
        {
            if (!root)
            {
                isSuccessful = 0;
                isShorter = 0;
                return 0;
            }
            if (root->table->result > t->result)
            {
                root->left = remove(root->left, t, isSuccessful, isShorter);
                if (isShorter)
                {
                    root = DeleteRightBalance(root, isShorter);
                }
            }
            else if (root->table->result < t->result)
            {
                root->right = remove(root->right, t, isSuccessful, isShorter);
                if (isShorter)
                {
                    root = DeleteLeftBalance(root, isShorter);
                }
            }
            else
            {
                if (root->table == t)
                {
                    if (!root->right)
                    {
                        node *temp = root->left;
                        isSuccessful = 1;
                        isShorter = 1;
                        delete root;
                        return temp;
                    }
                    else if (!root->left)
                    {
                        node *temp = root->right;
                        isSuccessful = 1;
                        isShorter = 1;
                        delete root;
                        return temp;
                    }
                    else
                    {
                        node *temp = root->right;
                        while (temp->left)
                            temp = temp->left;
                        root->table = temp->table;
                        root->right = remove(root->right, temp->table, isSuccessful, isShorter);
                        if (isShorter)
                        {
                            root = DeleteLeftBalance(root, isShorter);
                        }
                    }
                }
                else
                {
                    root->right = remove(root->right, t, isSuccessful, isShorter);
                    if (isShorter)
                    {
                        root = DeleteLeftBalance(root, isShorter);
                    }
                    if (!isSuccessful)
                    {
                        root->left = remove(root->left, t, isSuccessful, isShorter);
                        if (isShorter)
                        {
                            root = DeleteRightBalance(root, isShorter);
                        }
                    }
                }
            }
            return root;
        }
        void destruct(node *root)
        {
            if (!root)
                return;
            destruct(root->left);
            destruct(root->right);
            delete root;
        }

        AVLtree()
        {
            root = 0;
        }
        ~AVLtree()
        {
            destruct(root);
        }
        void insert(Table *t)
        {
            bool taller = 0;
            this->root = insert(this->root, t, taller);
        }
        void remove(Table *t)
        {
            bool isSuccessful = 0;
            bool isShorter = 0;
            this->root = remove(this->root, t, isSuccessful, isShorter);
        }
        void printAVL(Table *table)
        {
            queue<node *> temp;
            if (root)
            {
                temp.push(root);
                while (temp.size())
                {
                    node *top = temp.front();
                    temp.pop();
                    if (top->left)
                        temp.push(top->left);
                    if (top->right)
                        temp.push(top->right);
                    int id = top->table - table;
                    cout << id << '-' << top->table->result << '-' << top->table->num << endl;
                }
            }
        }
        void printBinaryTree(string prefix, node *root, bool isLeft, bool hasRightSibling)
        {
            if (!root && isLeft && hasRightSibling)
            {
                cout << prefix << char(195) << char(196) << endl;
            }
            if (!root)
                return;
            cout << prefix;
            if (isLeft && hasRightSibling)
                cout << char(195) << char(196);
            else
                cout << char(192) << char(196);
            cout << root->table->result << '\n';
            printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->left, true, root->right);
            printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->right, false, root->right);
        }
        void printBinaryTree()
        {
            printBinaryTree("", root, false, false);
        }
    };
    class MinHeap
    {
    public:
        Table *elements[MAXSIZE];
        int cnt;
        inline bool a_less_than_b(const int &a, const int &b)
        {
            return elements[a]->num < elements[b]->num || elements[a]->num == elements[b]->num && elements[a]->order < elements[b]->order;
        }
        friend class Restaurant;
        void remove(const int &position)
        {
            if (cnt == 0)
                return;
            elements[position] = elements[cnt - 1];
            cnt--;
            ReHeapDown(position);
            ReHeapUp(position);
        }
        int find(Table *&t)
        {
            for (int i = 0; i < cnt; i++)
            {
                if (t == elements[i])
                    return i;
            }
            return -1;
        }
        void ReHeapUp(const int &position)
        {
            if (position >= cnt)
                return;
            if (position > 0)
            {
                int parent = (position - 1) / 2;
                if (a_less_than_b(position, parent))
                {
                    swap(elements[position], elements[parent]);
                    ReHeapUp(parent);
                }
            }
        }
        void ReHeapDown(const int &position)
        {
            if (position < 0)
                return;
            int left = position * 2 + 1;
            int right = position * 2 + 2;
            int smaller;
            if (left <= cnt - 1)
            {
                if (right <= cnt - 1 && a_less_than_b(right, left))
                {
                    smaller = right;
                }
                else
                    smaller = left;
                if (a_less_than_b(smaller, position))
                {
                    swap(elements[smaller], elements[position]);
                    ReHeapDown(smaller);
                }
            }
        }
        void insert(Table *&t)
        {
            int last = cnt;
            cnt++;
            elements[last] = t;
            ReHeapUp(last);
        }
        void remove(Table *&t)
        {
            if (cnt == 0)
                return;
            int position = find(t);
            if (position == -1)
                return;
            elements[position] = elements[cnt - 1];
            cnt--;
            ReHeapDown(position);
            ReHeapUp(position);
        }
        void printMH(const int &num, Table *table)
        {
            if (num < 0 || num >= cnt)
                return;
            int left = num * 2 + 1;
            int right = num * 2 + 2;
            int id = elements[num] - table;
            cout << id << '-' << elements[num]->num << endl;
            printMH(left, table);
            printMH(right, table);
        }
        MinHeap()
        {
            for (int i = 0; i < MAXSIZE; i++)
            {
                elements[i] = 0;
            }
            cnt = 0;
        }
        ~MinHeap() {}
    };
    // elements in restaurant
    Table table[MAXSIZE + 1];
    int count1;      // count 1st area
    int count2;      // count 2nd area
    long long order; // numerical order of guests getting in restaurant
    map<int, Table *> area1;
    AVLtree area2;
    deque<Table *> FIFO;
    deque<Table *> LRCO;
    MinHeap LFCO;
    // internal function
    void InsertIntoArea2(int id)
    {
        if (count2 == MAXSIZE / 2)
        {
            InsertIntoArea1(id);
        }
        else
        {
            table[id].area = 2;
            count2++;
            Table *temp = &table[id];
            area2.insert(temp);
        }
    }
    void InsertIntoArea1(int id)
    {
        if (count1 == MAXSIZE / 2)
        {
            InsertIntoArea2(id);
        }
        else
        {
            int h_func = table[id].result % (MAXSIZE / 2);
            int i = 0;
            while (area1.find((h_func + i) % (MAXSIZE / 2)) != area1.end())
            {
                i++;
            }
            table[id].area = 1;
            Table *temp = &table[id];
            area1[(h_func + i) % (MAXSIZE / 2)] = temp;
            count1++;
        }
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
    void EraseInArea(Table *guest)
    {
        if (guest->area == 1)
        {
            auto it = area1.begin();
            for (; it != area1.end(); it++)
                if (it->second == guest)
                    break;
            if (it == area1.end())
            {
                cout << "Tim trong area 1 khong thay\n";
                system("pause");
            }
            else
                area1.erase(it);
        }
        else
            area2.remove(guest);
    }

public:
    // external function
    Restaurant()
    {
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

    int InsertGuest(const int &result, const string &name)
    {
        if (count1 + count2 == MAXSIZE)
        {
            int opt = result % 3;
            Table *temp = 0;
            if (opt == 0)
            {
                temp = FIFO.front();
                EraseInArea(temp);
                FIFO.pop_front();
                LRCO.erase(find(LRCO.begin(), LRCO.end(), temp));
                LFCO.remove(temp);
            }
            else if (opt == 1)
            {
                temp = LRCO.front();
                EraseInArea(temp);
                LRCO.pop_front();
                FIFO.erase(find(FIFO.begin(), FIFO.end(), temp));
                LFCO.remove(temp);
            }
            else
            {
                temp = LFCO.elements[0];
                EraseInArea(temp);
                LFCO.remove(0);
                FIFO.erase(find(FIFO.begin(), FIFO.end(), temp));
                LRCO.erase(find(LRCO.begin(), LRCO.end(), temp));
            }
            // test
            if (!temp)
                system("pause");
            // insert new guest
            int id = temp - table;
            table[id].name = name;
            table[id].order = order;
            order++;
            table[id].result = result;
            table[id].num = 1;
            temp = &table[id];
            FIFO.push_back(temp);
            LRCO.push_back(temp);
            LFCO.insert(temp);
            if (table[id].area == 1)
            {
                count1--;
                InsertIntoArea1(id);
            }
            else
            {
                count2--;
                InsertIntoArea2(id);
            }
            return id;
        }
        else
        {
            int id = result % MAXSIZE + 1;
            while (!table[id].IsEmpty)
            {
                id++;
                if (id == MAXSIZE + 1)
                    id = 1;
            }

            table[id].IsEmpty = 0;
            table[id].name = name;
            table[id].order = order;
            order++;
            table[id].result = result;
            table[id].num = 1;
            Table *temp = &table[id];
            FIFO.push_back(temp);
            LRCO.push_back(temp);
            LFCO.insert(temp);
            if (result & 1)
            {
                // result is odd --> area 1
                InsertIntoArea1(id);
            }
            else
            {
                // result is even --> area 2
                InsertIntoArea2(id);
            }
            return id;
        }
    }
    void GuestOrderDish(const int &id, const string &name)
    {
        // test
        if (table[id].name != name)
            system("pause");
        /* WHEN num ++
        LRCO change
        LFCO change*/
        Table *temp = &table[id];
        table[id].num++;
        LRCO.erase(find(LRCO.begin(), LRCO.end(), temp));
        LRCO.push_back(temp);
        // LFCO.ReHeapDown(temp);
        LFCO.remove(temp);
        LFCO.insert(temp);
    }

    void RemoveGuest(const int &id)
    {
        if (id < 1)
        {
            deque<Table *> temp;
            while (FIFO.size())
            {
                Table *guest = FIFO.front();
                if (guest->area == 2)
                {
                    FIFO.pop_front();
                    temp.push_back(guest);
                }
                else
                {
                    int index = guest - table;
                    RemoveGuest(index);
                }
            }
            swap(temp, FIFO);
        }
        else if (id > MAXSIZE)
        {
            deque<Table *> temp;
            while (FIFO.size())
            {
                Table *guest = FIFO.front();
                if (guest->area == 1)
                {
                    FIFO.pop_front();
                    temp.push_back(guest);
                }
                else
                {
                    int index = guest - table;
                    RemoveGuest(index);
                }
            }
            swap(temp, FIFO);
        }
        else if (!table[id].IsEmpty)
        {
            Table *temp = &table[id];
            temp->IsEmpty = 1;
            EraseInArea(temp);
            if (temp->area == 1)
                count1--;
            else
                count2--;
            FIFO.erase(find(FIFO.begin(), FIFO.end(), temp));
            LRCO.erase(find(LRCO.begin(), LRCO.end(), temp));
            LFCO.remove(temp);
        }
    }
    void printHT()
    {
        for (auto it = area1.begin(); it != area1.end(); it++)
        {
            int id = it->second - table;
            cout << id << '-' << it->second->result << '-' << it->second->num << endl;
        }
    }
    void printAVL()
    {
        area2.printAVL(&table[0]);
    }
    void printMH()
    {
        LFCO.printMH(0, &table[0]);
    }
    friend bool IsGuestInRestaurant(Restaurant &r, const string &name, unordered_map<string, pair<int, int>> &EncryptedName);
    friend void PrintRestaurant(const string &line, Restaurant &r);
};
class HuffmanTree
{
private:
    class Node;
    Node *root;
    long long order;

public:
    HuffmanTree() : root(0), order(0) {}
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
            pq.push(new Node(it->first, it->second, order));
            order++;
        }
        while (pq.size() != 1)
        {
            left = pq.top();
            pq.pop();
            right = pq.top();
            pq.pop();
            top = new Node('|', left->freq + right->freq, order, left, right);
            order++;
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
        // order get in queue
        long long order;
        Node(char data = '|', unsigned freq = 0, long long order = 0, Node *left = 0, Node *right = 0)
        {
            this->left = left;
            this->right = right;
            this->order = order;
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
            {
                if (l->data == r->data)
                    return l->order > r->order;

                else
                    return l->data > r->data;
            }
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
        for (char i : name)
        {
            if (i < 'A' || i > 'Z' && i < 'a' || i > 'z')
                return 0;
        }
        //
        return 1;
    }
    else if (ins == CLE)
    {
        string temp = line.substr(FirstSpace + 1);
        for (char i : temp)
        {
            if (i < '0' || i > '9' || i != '-')
                return 0;
        }
        num = stoi(temp);
        return 1;
    }
    return 0;
}
int EncryptingName(const string &name, map<char, string> &m2)
{
    string s;
    for (int i = int(name.size()) - 1; i >= 0; i--)
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

void PrintRestaurant(const string &line, Restaurant &r)
{
    cout << line << '\n';
    cout << "---------------\n\n";
    cout << "khu vuc 1: " << r.count1 << endl;
    cout << "khu vuc 2: " << r.count2 << endl;
    cout << "FIFO: result-id-num-name\n\n";
    for (unsigned i = 0; i < r.FIFO.size(); i++)
    {
        cout << r.FIFO.at(i)->result << '-' << (r.FIFO.at(i) - r.table) << '-' << r.FIFO.at(i)->num << '-' << r.FIFO.at(i)->name << endl;
    }
    cout << "LRCO: result-id-num-name\n\n";
    for (unsigned i = 0; i < r.LRCO.size(); i++)
    {
        cout << r.LRCO.at(i)->result << '-' << (r.LRCO.at(i) - r.table) << '-' << r.LRCO.at(i)->num << '-' << r.LRCO.at(i)->name << endl;
    }
    cout << "LFCO: result-id-num-name\n\n";
    for (int i = 0; i < r.LFCO.cnt; i++)
    {
        cout << i << ": " << r.LFCO.elements[i]->result << '-' << r.LFCO.elements[i] - r.table << '-' << r.LFCO.elements[i]->num << '-' << r.LFCO.elements[i]->name << endl;
    }
    cout << "Map: key-result-id-num-name\n\n";
    for (auto it = r.area1.begin(); it != r.area1.end(); it++)
    {
        cout << it->first << '-' << it->second->result << '-' << it->second - r.table << '-' << it->second->num << '-' << it->second->name << endl;
    }
    cout << "AVL:\n\n";
    r.area2.printBinaryTree();
    cout << "-----------------\n";
}
int a, b, c;
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
                    if (name != "")
                    {
                        if (EncryptedName.find(name) == EncryptedName.end())
                        {

                            map<char, int> m1;
                            map<char, string> m2;
                            for (char i : name)
                            {
                                m1[i]++; // create map with key (charater), data (frequency)
                            }
                            if (m1.size() == 1)
                            {
                                string temp(name);
                                for (unsigned i = 0; i < temp.size(); i++)
                                {
                                    temp[i] = '1';
                                }
                                int result = stoi(temp, 0, 2);
                                EncryptedName[name].first = result;
                            }
                            else
                            {
                                HuffmanTree ht;
                                ht.BuildTree(m1, m2);
                                int result = EncryptingName(name, m2);
                                EncryptedName[name].first = result;
                            }
                        }
                        if (IsGuestInRestaurant(r, name, EncryptedName))
                        {
                            r.GuestOrderDish(EncryptedName[name].second, name); // input: id, name --> return none
                        }
                        else
                        {
                            int id = r.InsertGuest(EncryptedName[name].first, name); // input: result, name --> return id
                            EncryptedName[name].second = id;
                        }
                    }
                }
                else if (ins == CLE)
                {
                    r.RemoveGuest(num);
                }
                else if (ins == PrintAVL)
                {
                    r.printAVL();
                }
                else if (ins == PrintHT)
                {
                    r.printHT();
                }
                else if (ins == PrintMH)
                {
                    r.printMH();
                }
                // PrintRestaurant(line, r);
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