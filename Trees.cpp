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

node* inorderSuccesor(node* head)
{
    if(head == NULL)
        return NULL;

    node *temp = head;
    while(temp->left!=NULL)
        temp = temp->left;

    return temp;
}

node* removeNodeBST(node* head, int data)
{
    if(head == NULL)
    {
        cout << " Number not found\n";
        return head;
    }

    if(head->data == data)
    {
        cout << "\n Node Found \n";
        //removal code
        if(head->left == NULL && head->right == NULL)
        {
            cout << " No Child\n";
            free(head);
            return NULL;
        }
        else if(head->left != NULL && head->right == NULL)
        {
            cout << " Left child\n";
            node* temp = head->left;
            free(head);
            return temp;
        }
        else if(head->left == NULL && head->right != NULL)
        {
            cout << " Right child\n";
            node* temp = head->right;
            free(head);
            return temp;
        }
        else
        {
            cout << "both children\n";
            node* temp = inorderSuccesor(head->right);
            //cout << "Successor is " << temp->data << "\n";
            head->data = temp->data;
            head->right = removeNodeBST(head->right, temp->data);
        }
    }
    else if(head->data < data)
        head->right = removeNodeBST(head->right,data);
    else
        head->left = removeNodeBST(head->left,data);

        return head;
}
void inorderTraversal(node* head)
{
    if(head == NULL)
        return;

    inorderTraversal(head->left);
    cout << " " << head->data;
    inorderTraversal(head->right);

    return;
}
void preorderTraversal(node *head)
{
    if(head == NULL)
        return;

    cout << " " << head->data;
    preorderTraversal(head->left);
    preorderTraversal(head->right);

    return;
}
void postorderTraversal(node *head)
{
    if(head == NULL)
        return;

    postorderTraversal(head->right);
    postorderTraversal(head->left);
    cout << " " << head->data;

    return;
}

void levelorderTraversal(node* head)
{
    if(head == NULL)
        return;
    queue<node*> traversal;

    traversal.push(head);

    while(!traversal.empty())
    {
        node* temp = traversal.front();
        if(temp->left != NULL)
            traversal.push(temp->left);
        if(temp->right!= NULL)
            traversal.push(temp->right);

        traversal.pop();
        cout << " " << temp->data;
    }

    return;
}

void inorderTraversalWithoutRecursion(node* head)
{
    stack<node*> traversal;
    node* curr = head;

    while(!traversal.empty() || curr != NULL)
    {
        while(curr!= NULL)
        {
            traversal.push(curr);
            curr = curr->left;
        }


        curr = traversal.top();
        cout << curr->data << " ";
        traversal.pop();
        curr = curr->right;
    }

    cout << "\n";
}
int search(int inorder, int x, int n)
{
    for (int i = 0; i < n; i++)
      if (inorder[i] == x)
         return i;
    return -1;
}

// Prints postorder traversal from given inorder and preorder traversals
void printPostOrder(int in, int pre, int n)
{
   // The first element in pre[] is always root, search it
   // in in[] to find left and right subtrees
   int root = search(in, pre[0], n);

   // If left subtree is not empty, print left subtree
   if (root != 0)
      printPostOrder(in, pre.begin()+1, root);

   // If right subtree is not empty, print right subtree
   if (root != n-1)
      printPostOrder(in+root+1, pre.begin()+root+1, n-root-1);

   // Print root
   cout << pre[0] << " ";
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

    cout << " Tree constructed successfully\n";

    /*cout << " \n\nWhen there are no child, there is no issue simply free the node and inform the parent \n When there is one child copy it to the parent and free the parent node and inform grand parent\n";
    cout << " When node has both child then inorder predecessor (greatest element smaller than the number) or inorder successor(smallest element greater than the current node) is used\n";
    while(1)
    {
        preorderTraversal(head);
        cout << "\n";
        inorderTraversal(head);
        cout << "\n";
        postorderTraversal(head);
        cout << "\n";
        levelorderTraversal(head);
        cout << "\n";

        cout << " Enter element to be deleted\n or 0 to exit\n ";
        cin >> data;
        head = removeNodeBST(head, data);

        if(data == 0)
            break;
    }*/

    inorderTraversalWithoutRecursion(head);

    cout << "\n\n Since in preorder node comes first we know first element of array is the node and since in inorder entire left subtree comes befor the node and right subtree after the node, we can find children of the tree\n ";

    vector<int>inorder;
    vector<int> preorder;

    preorderArray(preorder, head);
    inorderArray(inorder,head);

    postorderFromInorderPreorder(inorder, preorder, preorder.size());

    return 0;
}
