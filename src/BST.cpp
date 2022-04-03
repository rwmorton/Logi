//Logi includes
#include "BST.h"
#include "Stream.h"

//std includes
#include <iostream>

namespace Logi
{

BSTNode::BSTNode() : left{nullptr}, right{nullptr} {}

BSTNode::BSTNode(int key) : key(key), left{nullptr}, right{nullptr} {}

BSTNode::~BSTNode()
{
    std::cout << "deleting node with key = " << key << std::endl;
}

BST::BST() : _root{nullptr} {}

BST::~BST()
{
    if(_root) delete _root;
}

BSTNode* BST::root() const
{
    return _root;
}

BSTNode* BST::insert(BSTNode* root,int key)
{
    if(!root)
    {
        root = new BSTNode(key);
        return root;
    }

    if(key < root->key) root->left = insert(root->left,key);
    else root->right = insert(root->right,key);

    return root;
}

BSTNode* BST::search(BSTNode* root,int key) const
{
    if(root == nullptr || root->key == key) return root;

    return root->key < key ? search(root->right,key) : search(root->left,key);
}

const int BST::height(BSTNode* root) const
{
    int u{0},v{0};

    if(!root) return -1;

    u = height(root->left);
    v = height(root->right);

    return u>v ? u+1 : v+1;
}

void BST::inorder(BSTNode* root) const
{
    if(!root) return;

    inorder(root->left);

    std::cout << root->key << std::endl;

    inorder(root->right);
}

void BST::deleteTree(BSTNode* root)
{
    if(root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

} //namespace Logi
