#ifndef TREENODE_HPP
# define TREENODE_HPP

# include <iostream> 
# include <vector>

class TreeNode
{
    private:
        void    deleteTree();
    
    public:
        char value;
        std::vector<int32_t> set;
        bool has_negative = false;
        TreeNode *left = nullptr;
        TreeNode *right = nullptr;
        
        TreeNode();
        TreeNode(const TreeNode &other);
        TreeNode(char new_value);
        ~TreeNode();

        TreeNode &operator=(const TreeNode &other);
};


#endif