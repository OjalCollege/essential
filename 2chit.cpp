#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

// Node structure for Huffman Tree
struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Custom comparator for the priority queue (min-heap)
struct Compare
{
    bool operator()(Node *l, Node *r)
    {
        return l->freq > r->freq;
    }
};

// Function to generate Huffman Codes by traversing the tree
void generateCodes(Node *root, string code, unordered_map<char, string> &huffmanCode)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    { // Leaf node
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to build the Huffman Tree and generate codes
unordered_map<char, string> huffmanEncoding(const string &text)
{
    // Calculate frequencies
    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    // Priority queue to build the Huffman Tree
    priority_queue<Node *, vector<Node *>, Compare> minHeap;

    // Create a leaf node for each character and push it into the heap
    for (auto &pair : freq)
    {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // Merge nodes until there is only one node left in the heap
    while (minHeap.size() > 1)
    {
        Node *left = minHeap.top();
        minHeap.pop();
        Node *right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with left and right children
        Node *newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    // Root of the Huffman Tree
    Node *root = minHeap.top();

    // Generate Huffman Codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    return huffmanCode;
}

int main()
{
    string text = "BCAADDDCCACACAC";
    unordered_map<char, string> huffmanCode = huffmanEncoding(text);

    cout << " Char | Huffman code " << endl;
    cout << "----------------------" << endl;
    for (auto &pair : huffmanCode)
    {
        cout << "  " << pair.first << "   |    " << pair.second << endl;
    }

    return 0;
}
