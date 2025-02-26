#ifndef TREENODE_HPP
# define TREENODE_HPP

# include <iostream> 

class TreeNode
{
    private:
        void    deleteTree();
    
    public:
        char value;
        bool has_negative = false;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        
        TreeNode();
        TreeNode(char new_value);
        ~TreeNode();
};


#endif