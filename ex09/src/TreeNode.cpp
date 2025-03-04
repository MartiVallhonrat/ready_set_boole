# include "../TreeNode.hpp"

TreeNode::TreeNode(): value('0')
{
}

TreeNode::TreeNode(const TreeNode &other)
{
    *this = other;
}

TreeNode::TreeNode(char new_value): value(new_value)
{
}

TreeNode::~TreeNode()
{
    this->deleteTree();
}

TreeNode &TreeNode::operator=(const TreeNode &other)
{
    this->value = other.value;
    this->has_negative = other.has_negative;
    this->set = other.set;
       
    if (other.left == nullptr)
        this->left = other.left;
    else
        this->left = new TreeNode(*other.left);
        
    if (other.right == nullptr)
        this->right = other.right;
    else
        this->right = new TreeNode(*other.right);

    return (*this);
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