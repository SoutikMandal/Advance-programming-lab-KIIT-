#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Node
{
    int key;
    Node* left;
    Node* right;

    Node(int value)
    {
        key = value;
        left = nullptr;
        right = nullptr;
    }
};


class BST
{
private:
    Node* root;

    Node* insertNode(Node* node, int key)
    {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);

        return node;
    }

    bool searchNode(Node* node, int key)
    {
        if (node == nullptr)
            return false;

        if (node->key == key)
            return true;

        if (key < node->key)
            return searchNode(node->left, key);

        return searchNode(node->right, key);
    }

    void inorderNode(Node* node)
    {
        if (node == nullptr)
            return;

        inorderNode(node->left);
        cout << node->key << " ";
        inorderNode(node->right);
    }

    void preorderNode(Node* node)
    {
        if (node == nullptr)
            return;

        cout << node->key << " ";
        preorderNode(node->left);
        preorderNode(node->right);
    }

    void postorderNode(Node* node)
    {
        if (node == nullptr)
            return;

        postorderNode(node->left);
        postorderNode(node->right);
        cout << node->key << " ";
    }

    Node* findMin(Node* node)
    {
        while (node != nullptr && node->left != nullptr)
            node = node->left;

        return node;
    }

    Node* deleteNode(Node* node, int key)
    {
        if (node == nullptr)
            return nullptr;

        if (key < node->key)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = deleteNode(node->right, key);
        }
        else
        {
            // CASE 1: No child
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            // CASE 2: Only right child
            else if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // CASE 2: Only left child
            else if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // CASE 3: Two children
            else
            {
                Node* successor = findMin(node->right);

                node->key = successor->key;

                node->right =
                    deleteNode(node->right, successor->key);
            }
        }

        return node;
    }
int heightNode(Node* node)
    {
        if (node == nullptr)
            return 0;

        int leftHeight = heightNode(node->left);
        int rightHeight = heightNode(node->right);

        return 1 + max(leftHeight, rightHeight);
    }
    void destroyTree(Node* node)
    {
        if (node == nullptr)
            return;

        destroyTree(node->left);
        destroyTree(node->right);

        delete node;
    }
    public:

    BST()
    {
        root = nullptr;
    }

    ~BST()
    {
        destroyTree(root);
    }


    void insert(int key)
    {
        root = insertNode(root, key);
    }


    bool search(int key)
    {
        return searchNode(root, key);
    }


    void inorder()
    {
        inorderNode(root);
        cout << endl;
    }


    void preorder()
    {
        preorderNode(root);
        cout << endl;
    }


    void postorder()
    {
        postorderNode(root);
        cout << endl;
    }


    void remove(int key)
    {
        root = deleteNode(root, key);
    }


    int height()
    {
        return heightNode(root);
    }
};

BST buildBST(const vector<int>& data)
{
    BST tree; 

    for(int x : data)
    tree.insert(x);
    
    return tree;
}

void part1()
{
     cout << "\n==\n";
     cout << "bst insertion and traversals";
     cout << "==\n\n";

     vector<int> keys ={50, 30, 70, 20, 40, 60, 80, 10};

     BST tree;

     cout << "Keys inserted: ";

    for (int x : keys)
    {
        cout << x << " ";
        tree.insert(x);
    }

    cout << "\n\n";

    cout << "Inorder Traversal:   ";
    tree.inorder();

    cout << "Preorder Traversal:  ";
    tree.preorder();

    cout << "Postorder Traversal: ";
    tree.postorder();

    cout << "\nVerification:\n";

    cout << "Sorted inorder\n";
    cout << "Expected sorted order: 10 20 30 40 50 60 70 80\n";

    int presentKey = 40;

    cout << "\nSearching for " << presentKey << ": ";

    if (tree.search(presentKey))
        cout << "Key is PRESENT in the BST.\n";
    else
        cout << "Key is ABSENT from the BST.\n";
        int absentKey = 90;

    cout << "Searching for " << absentKey << ": ";

    if (tree.search(absentKey))
        cout << "Key is PRESENT in the BST.\n";
    else
        cout << "Key is ABSENT from the BST.\n";
}

void part2()
{
    cout << "\n==\n";
    cout << "PART 2: BST DELETION\n";
    cout << "==\n";

    vector<int> keys = {50, 30, 70, 20, 40, 60, 80, 10};
    cout << "\n1. DELETE LEAF NODE\n";

    BST tree1 = buildBST(keys);

    cout << "Before deletion: ";
    tree1.inorder();

    cout << "Deleting leaf node: 10\n";

    tree1.remove(10);

    cout << "After deletion:  ";
    tree1.inorder();

    cout << "\n3. DELETE NODE WITH TWO CHILDREN\n";

    BST tree3 = buildBST(keys);

    cout << "Before deletion: ";
    tree3.inorder();

    cout << "Deleting node: 30\n";
    cout << "Node 30 has two children (20 and 40).\n";

    tree3.remove(30);

    cout << "After deletion:  ";
    tree3.inorder();
}
vector<int> generateRandom(int n)
{
    vector<int> data(n);

    for (int i = 0; i < n; i++)
        data[i] = i + 1;

    random_device rd;
    mt19937 g(rd());

    shuffle(data.begin(), data.end(), g);

    return data;
}

vector<int> generateSorted(int n)
{
    vector<int> data(n);

    for (int i = 0; i < n; i++)
        data[i] = i + 1;

    return data;
}

vector<int> generateReverseSorted(int n)
{
    vector<int> data(n);

    for (int i = 0; i < n; i++)
        data[i] = n - i;

    return data;
}

struct Result
{
    int n;
    string type;

    double buildTime;
    int height;

    double searchTime;
    double deleteTime;
};

Result testPerformance(vector<int> data, string type)
{
    int n = data.size();

    BST tree;
    auto startBuild = high_resolution_clock::now();

    for (int x : data)
        tree.insert(x);

    auto endBuild = high_resolution_clock::now();

    double buildTime =
        duration<double, milli>(endBuild - startBuild).count();

            int treeHeight = tree.height();
            
            mt19937 gen(12345);

    uniform_int_distribution<int> dist(1, n);

    auto startSearch = high_resolution_clock::now();

    for (int i = 0; i < 1000; i++)
    {
        int key = dist(gen);

        tree.search(key);
    }

    auto endSearch = high_resolution_clock::now();

    double searchTime =
        duration<double, micro>(endSearch - startSearch).count();

        auto startDelete = high_resolution_clock::now();

    for (int i = 0; i < 500; i++)
    {
        tree.remove(data[i]);
    }

    auto endDelete = high_resolution_clock::now();

    double deleteTime =
        duration<double, micro>(endDelete - startDelete).count();


    Result result;

    result.n = n;
    result.type = type;
    result.buildTime = buildTime;
    result.height = treeHeight;
    result.searchTime = searchTime;
    result.deleteTime = deleteTime;

    return result;
}
void part3()
{
    cout << "\n============================================\n";
    cout << "PART 3: PERFORMANCE ANALYSIS\n";
    cout << "============================================\n\n";


    vector<int> sizes = {1000, 5000, 10000};

    vector<Result> results;


    for (int n : sizes)
    {
        cout << "Testing n = " << n << "...\n";


        // Random
        vector<int> randomData = generateRandom(n);

        results.push_back(
            testPerformance(randomData, "Random")
        );

        vector<int> sortedData = generateSorted(n);

        results.push_back(
            testPerformance(sortedData, "Sorted")
        );
vector<int> reverseData = generateReverseSorted(n);

        results.push_back(
            testPerformance(reverseData, "Reverse-Sorted")
        );
    }
cout << "\n\n";
    cout << "==\n";
    cout << "                 BST PERFORMANCE RESULTS\n";
    cout << "==\n";

    cout << left
         << setw(8)  << "N"
         << setw(18) << "Input"
         << setw(15) << "Build(ms)"
         << setw(12) << "Height"
         << setw(18) << "Search(us)"
         << setw(18) << "Delete(us)"
         << endl;

    cout << "--\n";


    for (const Result& r : results)
    {
        cout << left
             << setw(8)  << r.n
             << setw(18) << r.type
             << setw(15) << fixed << setprecision(3)
             << r.buildTime
             << setw(12) << r.height
             << setw(18) << r.searchTime
             << setw(18) << r.deleteTime
             << endl;
    }

ofstream file("bst_results.csv");

    file << "N,Input,Build_Time_ms,Height,"
         << "Search_1000_us,Delete_500_us\n";


    for (const Result& r : results)
    {
        file << r.n << ","
             << r.type << ","
             << fixed << setprecision(6)
             << r.buildTime << ","
             << r.height << ","
             << r.searchTime << ","
             << r.deleteTime
             << "\n";
    }

    file.close();


    cout << "\nResults saved to: bst_results.csv\n";
}
int main()
{
    cout << "====================================================\n";
    cout << "           BINARY SEARCH TREE (BST)\n";
    cout << "====================================================\n";


    // Part 1
    part1();


    // Part 2
    part2();


    // Part 3
    part3();


    cout << "\n==\n";
    cout << "Program completed successfully.\n";
    cout << "==\n";


    return 0;
}
