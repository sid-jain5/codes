#include<bits/stdc++.h>

using namespace std;

struct node
{
    int data;
    struct node* left;
    struct node* right;
};

typedef struct node node;

node* newNode(int data)
{
    node* temp = new node;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}
node* addNodeBST(node* head, int data)
{
    if(head == NULL)
    {
        head = newNode(data);
        return head;
    }

    if(head->data <= data)
        head->right = addNodeBST(head->right, data);
    else
        head->left = addNodeBST(head->left,data);
}
void inorderRecursive(node* head)
{
    if(head == NULL)
        return;

    inorderRecursive(head->left);
    cout << " " << head->data;
    inorderRecursive(head->right);

    return;
}

void inorderIterative(node *head)
{
    if(head == NULL)
    {
        cout << "head is null\n";
        return;
    }

    node* curr = head;
    stack<node*> inorder;
    cout << "\n";
    inorder.push(curr);
    curr = curr->left;
    while(!inorder.empty() || curr!=NULL)
    {
        while(curr!=NULL)
        {
            inorder.push(curr);
            curr = curr->left;
        }

        curr = inorder.top();
        inorder.pop();
        cout << " " << curr->data;

        curr = curr->right;
    }
    cout << "\n";
}
int main()
{
    int data;
    node* head = NULL;

    cout << " Enter the element to be added to the tree or 0 to exit\n";
    while(1)
    {
        cout << " ";
        cin >> data;

        if(!data)
            break;

        head = addNodeBST(head, data);
    }

    cout << " Tree constructed successfully\n\n";

    cout << " Recursive Inorder\n";
    inorderRecursive(head);

    cout << "\n Iterative Inorder\n";
    inorderIterative(head);

    return 0;
}
