// b7

#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;
    Node(char val) : data(val), left(NULL), right(NULL) {}
};

// Utility function to check if a character is an operator
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to construct expression tree from prefix expression
// Uses an index passed by reference to track current position in prefix string
Node *constructTree(const string &prefix, int &index)
{
    if (index >= (int)prefix.size())
        return NULL;

    char curr = prefix[index];
    index++;

    Node *node = new Node(curr);

    if (isOperator(curr))
    {
        node->left = constructTree(prefix, index);
        node->right = constructTree(prefix, index);
    }

    return node;
}

// Non-recursive postorder traversal using two stacks
void postorderTraversal(Node *root)
{
    if (!root)
        return;

    stack<Node *> s1, s2;
    s1.push(root);

    while (!s1.empty())
    {
        Node *curr = s1.top();
        s1.pop();
        s2.push(curr);

        if (curr->left)
            s1.push(curr->left);
        if (curr->right)
            s1.push(curr->right);
    }

    while (!s2.empty())
    {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}

// Function to delete the entire tree (postorder deletion)
void deleteTree(Node *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    string prefix = "+--a*bc/def";

    int index = 0;
    Node *root = constructTree(prefix, index);

    cout << "Postorder traversal (non-recursive): ";
    postorderTraversal(root);

    deleteTree(root);
    root = NULL;

    cout << "Expression tree deleted." << endl;

    return 0;
}
