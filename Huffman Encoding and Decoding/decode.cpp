#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <utility>

using namespace std;

class TreeNode
{
public:
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    char value = '*';
    int frequency = -1;

    void preorder()
    {
        cout << value << "[" << frequency << "] ";
        if (left)
            left->preorder();
        if (right)
            right->preorder();
    }
};

struct compare
{

    //This will be used by the priority queue to compare two nodes and see which is larger
    bool operator()(TreeNode *&left, TreeNode *&right) const
    {
        if (left->frequency > right->frequency)
            return true;

        if (left->frequency == right->frequency)
            return left->value > right->value; // Comparing chars if they're equal frequency

        return false;
    }
};


TreeNode *merge(TreeNode *t1, TreeNode *t2)
{
    // Return a new node with t1 and t2 as children
    TreeNode *output = new TreeNode();

    // Fill this out
    output->frequency = t1->frequency + t2->frequency;
    output->left = t1;
    output->right = t2;

    return output;
}


// traverse the Huffman Tree and decode the encoded string
void decode(TreeNode *root, TreeNode *curr, string x)
{
    if (x.length() < 1)
    {
        cout << endl;
        return;
    }
    else if (curr->left == nullptr)
    {
        cout << curr->value;
        decode(root, root, x);
    }
    else
    {
        if (x[0] == '0')
        {
            x.erase(x.begin());
            decode(root, curr->left, x);
        }
        else
        {
            x.erase(x.begin());
            decode(root, curr->right, x);
        }
    }
}

int main()
{
    //Build tree
    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<TreeNode *, vector<TreeNode *>, compare> pq;
    map<char, int> map1;

    string letters, iteration;
    getline(cin, letters);
    getline(cin, iteration);

    //cout<<letters;
    //cout<<iteration;

    istringstream freq(iteration);
    int n;
    int i = 0;

   
    while (freq >> n)
    {
        map1[letters[i]] = n;
        i += 2;
    }
    map<char, int>::iterator itr;
    for (itr = map1.begin(); itr != map1.end(); ++itr)
    {
        TreeNode *n = new TreeNode();
        n->value = itr->first;
        n->frequency = itr->second;
        pq.push(n);
    }

    TreeNode *root = new TreeNode();

    while (pq.size() > 1)
    {
        TreeNode *l1 = pq.top();
        pq.pop();

        TreeNode *l2 = pq.top();
        pq.pop();

        pq.push(merge(l1, l2));
    }

    // root stores pointer to root of Huffman Tree
    root = pq.top();

    //Decode
    string HuffmanCode;
    getline(cin, HuffmanCode);
    decode(root, root, HuffmanCode + ' ');

    return 0;
}