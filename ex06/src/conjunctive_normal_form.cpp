# include "../includes.hpp"
# include "../TreeNode.hpp"

# include <exception>
# include <algorithm>
# include <array>
# include <stack>

static void getPostorderCommutative(TreeNode* node, std::string &literals, std::string &operands)
{
    if (node == nullptr)
        return;

    getPostorderCommutative(node->left, literals, operands);
    getPostorderCommutative(node->right, literals, operands);

    if (std::isupper(node->value))
    {
        literals += node->value;
        literals += (node->has_negative ? "!" : "");
    }
    else
        operands += node->value;
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

static void transformCNF(TreeNode* node)
{
    if (node->left == nullptr || node->right == nullptr)
        return;

    switch (node->value)
    {
        case '|':
        {
            TreeNode *get = nullptr;
            TreeNode *into = nullptr;
                
            if (node->left->value == '&')
            {
                get = node->right;
                into = node->left;
            }
            else if (node->right->value == '&')
            {
                get = node->left;
                into = node->right;
            }
            else
                break;

            node->value = '&';
            TreeNode *new_node1 = new TreeNode('|');
            new_node1->left = new TreeNode(*get);
            new_node1->right = into->left;
            into->left = nullptr;

            TreeNode *new_node2 = new TreeNode('|');
            new_node2->left = get;
            new_node2->right = into->right;
            into->right = nullptr;

            node->left = new_node1;
            node->right = new_node2;
            delete into;
            break;
        }
    }
    
    transformCNF(node->left);
    transformCNF(node->right);
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

std::string conjunctive_normal_form(std::string &formula)
{
    TreeNode *root = createTree(formula);
    
    transformNNF(root);
    transformCNF(root);
    std::string literals = "";
    std::string operands = "";
    getPostorderCommutative(root, literals, operands);
    // put operators to the end
    std::string formCNF = literals + operands;

    delete root;

    return (formCNF);
}