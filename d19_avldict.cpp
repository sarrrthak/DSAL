// d19

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

// AVL Tree Node structure
struct Node
{
    string keyword;
    string meaning;
    Node *left;
    Node *right;
    int height;

    Node(string k, string m)
    {
        keyword = k;
        meaning = m;
        left = right = NULL;
        height = 1;
    }
};

// Function to get the height of the tree
int height(Node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

// Function to perform right rotation
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right) + 1);
    x->height = max(height(x->left), height(x->right) + 1);

    return x;
}

// Function to perform left rotation
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right) + 1);
    y->height = max(height(y->left), height(y->right) + 1);

    return y;
}

// Get the balance factor of the node
int getBalance(Node *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

// Insert a keyword into the AVL tree
Node *insert(Node *root, string keyword, string meaning)
{
    // Perform the normal BST insertion
    if (root == NULL)
        return new Node(keyword, meaning);

    if (keyword < root->keyword)
        root->left = insert(root->left, keyword, meaning);
    else if (keyword > root->keyword)
        root->right = insert(root->right, keyword, meaning);
    else
        return root; // Duplicate keywords are not allowed

    // Update height of this ancestor node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor and balance the tree
    int balance = getBalance(root);

    // Left Left case
    if (balance > 1 && keyword < root->left->keyword)
        return rightRotate(root);

    // Right Right case
    if (balance < -1 && keyword > root->right->keyword)
        return leftRotate(root);

    // Left Right case
    if (balance > 1 && keyword > root->left->keyword)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left case
    if (balance < -1 && keyword < root->right->keyword)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find a keyword in the tree
Node *find(Node *root, string keyword)
{
    if (root == NULL || root->keyword == keyword)
        return root;

    if (keyword < root->keyword)
        return find(root->left, keyword);

    return find(root->right, keyword);
}

// In-order traversal to display the dictionary
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->keyword << ": " << root->meaning << endl;
        inorder(root->right);
    }
}

// Find the maximum comparisons required to find a keyword
int maxComparisons(Node *root)
{
    if (root == NULL)
        return 0;

    int leftComparisons = maxComparisons(root->left);
    int rightComparisons = maxComparisons(root->right);

    return 1 + max(leftComparisons, rightComparisons);
}

int main()
{
    Node *root = NULL;

    // Add some initial keywords
    root = insert(root, "Apple", "A fruit");
    root = insert(root, "Banana", "Another fruit");
    root = insert(root, "Cat", "An animal");

    // Display dictionary (in ascending order)
    cout << "Dictionary (Ascending Order):" << endl;
    inorder(root);

    // Find a keyword
    string keyword;
    cout << "Enter keyword to find: ";
    cin >> keyword;

    Node *result = find(root, keyword);
    if (result != NULL)
        cout << "Found: " << result->keyword << ": " << result->meaning << endl;
    else
        cout << "Keyword not found!" << endl;

    // Display maximum comparisons required for finding a keyword
    cout << "Maximum comparisons for finding a keyword: " << maxComparisons(root) << endl;

    return 0;
}
