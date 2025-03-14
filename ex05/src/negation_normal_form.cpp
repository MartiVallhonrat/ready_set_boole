# include "../includes.hpp"
# include "../TreeNode.hpp"

# include <exception>
# include <algorithm>
# include <array>
# include <stack>

static void getPostorder(TreeNode* node, std::string &formula)
{
    if (node == nullptr)
        return;

    getPostorder(node->left, formula);
    getPostorder(node->right, formula);

    formula += node->value;
    formula += (node->has_negative ? "!" : "");
}

static void transformNNF(TreeNode* node)
{
    if (node->left == nullptr || node->right == nullptr)
        return;

    switch (node->value)
    {
        case '>':
        {
            node->value = '|';
            node->left->has_negative = !node->left->has_negative;
            break;
        }
        case '=':
        {
            node->value = '|';
            
            TreeNode *new_node1 = new TreeNode('&');
            new_node1->left = node->left;
            new_node1->right = node->right;
            TreeNode *new_node2 = new TreeNode('&');
            new_node2->left = new TreeNode(*node->left);
            new_node2->right = new TreeNode(*node->right);
            // apply negatives after copy both nodes
            new_node2->left->has_negative = !new_node2->left->has_negative;
            new_node2->right->has_negative = !new_node2->right->has_negative;

            node->left = new_node1;
            node->right = new_node2;
            break;
        }
        case '^':
        {
            node->value = '|';
            
            TreeNode *new_node1 = new TreeNode('&');
            new_node1->left = new TreeNode(*node->left);
            new_node1->right = new TreeNode(*node->right);;
            new_node1->right->has_negative = !new_node1->right->has_negative;

            TreeNode *new_node2 = new TreeNode('&');
            new_node2->left = node->left;
            new_node2->right = node->right;
            new_node2->left->has_negative = !new_node2->left->has_negative;

            node->left = new_node1;
            node->right = new_node2;
            break;
        }
    }
    if (node->has_negative)
    {
        node->has_negative = !node->has_negative;
        switch (node->value)
        {
            case '|':
                node->value = '&';
                node->left->has_negative = !node->left->has_negative;
                node->right->has_negative = !node->right->has_negative;
                break;
            
            case '&':
                node->value = '|';
                node->left->has_negative = !node->left->has_negative;
                node->right->has_negative = !node->right->has_negative;
                break;
        }
    }

    transformNNF(node->left);
    transformNNF(node->right);
}

static void handleError(std::stack<TreeNode*> numStack, std::string errStr)
{
    while (!numStack.empty())
    {
        TreeNode *tmp = numStack.top();
        numStack.pop();
        if (tmp != nullptr)
            delete tmp;
    }
    throw ErrorException(errStr);
}

TreeNode *createTree(std::string &formula)
{
    if (formula.empty())
        throw ErrorException("No input provided");
    // no negative in operators
    std::array<char, 5> operators = {'&', '|', '^', '>', '='};
    size_t formLen = formula.length();
    
    std::stack<TreeNode*> numStack;
    TreeNode *root = nullptr;
    
    for (size_t i = 0; i < formLen; i++)
    {
        if (std::find(operators.begin(), operators.end(), formula[i]) != operators.end())
        {
            if (numStack.empty())
                handleError(numStack, "Invalid number of operators");
            TreeNode *fromStackRight = numStack.top();
            numStack.pop();
    
            if (numStack.empty())
            {
                numStack.push(fromStackRight);
                handleError(numStack, "Invalid number of operators");
            }
            TreeNode *fromStackLeft = numStack.top();
            numStack.pop();
    
            root = new TreeNode(formula[i]);
            root->left = fromStackLeft;
            root->right = fromStackRight;
    
            numStack.push(root);
        }
        else if (std::isupper(formula[i]))
        {
            numStack.push(new TreeNode(formula[i]));
        }
        else if (formula[i] == '!')
        {
            if (numStack.empty())
                handleError(numStack, "Invalid number of numbers");
    
            root = numStack.top();
            numStack.pop();
            root->has_negative = true;
            numStack.push(root);
        }
        else
            handleError(numStack, "Invalid Input");
    }
    
    root = numStack.top();
    numStack.pop();
    if (!numStack.empty())
    {
        numStack.push(root);
        handleError(numStack, "Invalid number of values");
    }    
    return (root);

}

std::string negation_normal_form(std::string &formula)
{
    std::string formulaNNF = "";

    TreeNode *root = createTree(formula);
    
    transformNNF(root);
    getPostorder(root, formulaNNF);

    delete root;

    return (formulaNNF);
}