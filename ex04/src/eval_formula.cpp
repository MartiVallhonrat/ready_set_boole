# include <exception>
# include <algorithm>
# include <array>
# include <stack>

# include "../includes.hpp"
# include "../TreeNode.hpp"

// testing
static void printPostorder(TreeNode* node)
{
    if (node == nullptr)
        return;

    printPostorder(node->left);

    printPostorder(node->right);

    std::cout << node->value << (node->has_negative ? "!" : "") << " ";
}

static char execPostorder(TreeNode *node)
{
    if (node->left == nullptr || node->right == nullptr)
        return (0);

    execPostorder(node->left);
    execPostorder(node->right);

    switch (node->value)
    {
        case '&':
            node->value = (node->left->value - '0') & (node->right->value - '0');
            node->value = (node->value + '0');
            break;
        case '|':
            node->value = (node->left->value - '0') | (node->right->value - '0');
            node->value = (node->value + '0');
            break;               
        case '^':
            node->value = (node->left->value - '0') ^ (node->right->value - '0');
            node->value = (node->value + '0');
            break;
        case '>':
            node->value = (!(node->left->value - '0')) | (node->right->value - '0');
            node->value = (node->value + '0');
            break;
        case '=':
            node->value = (node->left->value - '0') == (node->right->value - '0');
            node->value = (node->value + '0');
            break;
    };
    if (node->has_negative)
        node->value = (node->value == '0' ? '1' : '0');

    return (node->value);
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
    std::array<char, 6> operators = {'&', '|', '^', '>', '='};
    std::array<char, 2> values = {'0', '1'};
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
        else if (std::find(values.begin(), values.end(), formula[i]) != values.end())
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

bool eval_formula(std::string &formula)
{
    TreeNode *root = createTree(formula);

    // DEBUGGING
    // printPostorder(root);
    
    int result = (execPostorder(root) - '0');
    
    delete root;
    
    return (result);
}