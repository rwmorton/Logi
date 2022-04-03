#ifndef __LOGI_BST_H__
#define __LOGI_BST_H__

//std includes
#include <vector>

namespace Logi
{

class BSTNode
{
    public:
        BSTNode();
        BSTNode(int key);
        ~BSTNode();
        int key;
        BSTNode* left;
        BSTNode* right;
};

class BST
{
    public:
        BST();
        ~BST();
        BSTNode* root() const;
        BSTNode* insert(BSTNode* root,int key);
        BSTNode* search(BSTNode* root,int key) const;
        const int height(BSTNode* root) const;
        void inorder(BSTNode* root) const;
        void deleteTree(BSTNode* root);
    private:
        BSTNode* _root;
};

} //namespace Logi

#endif //__LOGI_BST_H__
