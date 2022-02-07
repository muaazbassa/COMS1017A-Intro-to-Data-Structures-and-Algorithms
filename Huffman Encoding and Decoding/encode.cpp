#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

using namespace std;

map<char, string> code;

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
    bool operator()(TreeNode *v1, TreeNode *v2) const
    {
        if (v1->frequency > v2->frequency)
        {
            return true;
        }
        else if (v1->frequency < v2->frequency)
        {
            return false;
        }
        else if (v1->value > v2->value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

void PrintOutput(string output, int total){
    
    cout << output << endl;
    cout << "Total Bits (Original):" << total * 8 << endl;
    cout << "Total Bits (Coded):" << output.length() << endl;
}

TreeNode* getNode(char ch, int freq, TreeNode* left, TreeNode* right)
{
	TreeNode* node = new TreeNode();

	node->value = ch;
	node->frequency = freq;
	node->left = left;
	node->right = right;

	return node;
}

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

void encode(TreeNode *curr, string str)
{
    if (curr->left == nullptr)
    {
        code.insert(make_pair(curr->value, str));
        return;
    }
    encode(curr->left, str + "0");
    encode(curr->right, str + "1");
}

int main()
{
    // This is how to use the tree
    //    TreeNode *l1 = new TreeNode();
    //    TreeNode *l2 = new TreeNode();

    //    l1->value = 'i';
    //    l1->frequency = 4;

    //    l2->value = 'h';
    //    l2->frequency = 4;

    //    l1->preorder(); cout << endl;

    //    if(*l1 < *l2){
    //        cout << "L1 <  L2" << endl;
    //    }else{
    //        cout << "L1 >= L2" << endl;
    //    }

    string line;
    getline(cin, line);

    // Build frequency table
    // count frequency of appearance of each character and store it in a map
    map<char, int> freq;
    for (int i = 0; i < line.size(); ++i)
    {
        freq[line[i]]++;
    }

    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<TreeNode *, vector<TreeNode *>, compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

    // Create the tree
    TreeNode *root = new TreeNode();

    vector<int> num;
    // sepearte the letters, increases the count and outputs that
    while (pq.size() != 1)
    {
        if (pq.top()->value != '*')
        {
            cout << pq.top()->value << ' ';
            num.push_back(pq.top()->frequency);
        }
        TreeNode *l1 = pq.top();
        pq.pop();
        if (pq.top()->value != '*')
        {
            cout << pq.top()->value << ' ';
            num.push_back(pq.top()->frequency);
        }
        TreeNode *l2 = pq.top();
        pq.pop();

        pq.push(merge(l1, l2));
    }
    cout << endl;
    int total = 0;
    for (int i = 0; i < num.size(); ++i)
    {
        cout << num[i] << ' ';
        total += num[i];
    }
    cout << endl;

    // root stores pointer to root of Huffman Tree
    root = pq.top();

    // Encode the string
    encode(root, "");

    // Output encoding
    map<char, string>::iterator itr;
    string final;

    // traverse the Huffman Tree and store Huffman Codes in a map
    for (int i = 0; i < line.size(); ++i)
    {
        itr = code.find(line[i]);
        final += itr->second;
    }
    
    //Prints Huffmancode and Total Bits
    PrintOutput(final, total);

    return 0;
}
