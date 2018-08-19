#include<bits/stdc++.h>

using namespace std;

struct trieNode
{
    map <char, trieNode*> children;
    bool eow;
};

typedef struct trieNode trieNode;

trieNode *createNode()
{
    trieNode *newNode = new trieNode;

    newNode->eow = false;

    return newNode;
}

void insertNode(trieNode *root, string key)
{
    map<char,trieNode*>::iterator it;
    trieNode *head = root;

    for(long i=0; i<key.length(); i++)
    {
        it = head->children.find(key[i]);
        if(it == head->children.end())
        {
            pair <char, trieNode*> newLink;
            newLink = std::make_pair(key[i],createNode());
            head->children.insert(newLink);
        }
        head = head->children[key[i]];
    }
    head->eow = true;
}

bool searchString(trieNode *root, string key)
{
    trieNode *head = root;

    for(long i=0; i<key.length(); i++)
    {
        if(head->children.find(key[i]) == head->children.end())
            return false;
        head = head->children[key[i]];
    }

    if(head->eow && head!=NULL)
        return true;
    else
        return false;
}

void deleteString(trieNode *root, string key)
{


}

int main()
{
    long noOfStrings;
    string *keyArray, searchElement;

    cout << " Enter the number of string you want to enter: ";
    cin >> noOfStrings;

    keyArray = new string[noOfStrings];

    for(long i=0; i<noOfStrings; i++)
    {
        cout << " ";
        fflush(stdin);
        cin >> keyArray[i];
    }

    trieNode* root = createNode();

    for(long i=0; i<noOfStrings; i++)
        insertNode(root, keyArray[i]);


    cout << "\n Enter the String to be searched ";
    cin >> searchElement;

    if(searchString(root, searchElement))
        cout << "\n String found";
    else
        cout << "\n String not found";

    return 0;
}
