# include "../TreeNode.hpp"

TreeNode::TreeNode(): value('0')
{
}

TreeNode::TreeNode(char new_value): value(new_value)
{
}

TreeNode::~TreeNode()
{
    this->deleteTree();
}

void    TreeNode::deleteTree()
{
    if (this->left != nullptr)
    {
        this->left->deleteTree();
        delete this->left;
        this->left = nullptr;
    }
    if (this->right != nullptr)
    {
        this->right->deleteTree();
        delete this->right;
        this->right = nullptr;
    }
}