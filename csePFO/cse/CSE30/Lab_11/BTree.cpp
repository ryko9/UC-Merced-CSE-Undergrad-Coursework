#include <iostream>
#include "BTree.h"
using namespace std;

//constructor initializes empty tree

BTree::BTree()
{
	root = NULL; //if tree is empty, root points to NULL.
}

//destructor, calls destroy_tree

BTree::~BTree()
{
	destroy_tree();
}

Node* BTree::BTree_root()
{
	return root;
}

void BTree::destroy_tree(Node* leaf) //destroys from specified leaf
{
	if(leaf != NULL) //if the leaf isn't pointing to null, calls again for left and right, until all attached nodes are destroyed
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

/*compares value of key, the value we want to insert, to Node leaf's key value. If key is smaller, attempts to insert it in place of
  leaf's left child. If key is greater, attempts to insert it in place of leaf's right child.*/

void BTree::insert(int key, Node* leaf)
{

        //inserts at specific leaf in tree.

        if(leaf == NULL) //if there is nothing at leaf, create new node and insert key
        {
                leaf = new Node;
                leaf->key_value = key;
                leaf->left = NULL;
                leaf->right = NULL;
        }
        if(key < leaf->key_value) //if key has value less than node value, attempts to insert into left child
        {
                if(leaf->left != NULL) //if there is already a left child,
                {
                        insert(key, leaf->left); //calls again starting from left child
                }
                else //else if leaf->left = NULL, there is no left child, can insert
                {
                      leaf->left = new Node; //allocating memory
                      leaf->left->key_value = key; //inserting key into leaf->left's key_value
                      leaf->left->left = NULL; //leaf->left's left and right child are pointing to NULL.
                      leaf->left->right = NULL;
                }
        }
        else  //if the key has a greater value than node value, attempts to insert into right
        {
                if(leaf->right != NULL) //if there is already a right child
                {
                        insert(key, leaf->right); //calls again starting from right child
                }
                else //if left->right = NULL, there is no right child, can insert
                {
                        leaf->right = new Node;
                        leaf->right->key_value = key;
                        leaf->right->left = NULL;
                        leaf->right->right = NULL;
                }
        }
}

Node* BTree::search(int key, Node* leaf) //begins search at leaf
{
        if(leaf != NULL) //if leaf is valid
        {
                if(key == leaf->key_value)
                {
                        return leaf;
                }
                if(key < leaf->key_value) //if value is less,
                {
                        return search(key, leaf->left); //return call to left child
                }
                else
                        return search(key, leaf->right);//return call to right child
        }
        else
        {
                return NULL;
        }
}

void BTree::insert(int key) //inserts at root of tree.
{
        if(root == NULL) //if tree is empty
        {
                root = new Node; //creates new leaf and points root to it
                root->key_value = key;
                root->left = NULL;
                root->right = NULL;
        }
        else //if the tree is not empty, then we call insert
        {
                insert(key,root);
        }
}

Node* BTree::search(int key) //begins search at root
{
        return search(key, root);
}

void BTree::destroy_tree() //destroys entire tree
{
        destroy_tree(root); //starts from root.
}
