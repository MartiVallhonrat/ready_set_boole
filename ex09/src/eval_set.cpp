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

static std::map<char, std::vector<int32_t>> checkVars(std::string &formula, std::vector<std::vector<int32_t>> sets)
{
    size_t formLen = formula.length();
    std::map<char, std::vector<int32_t>> result;
    for (size_t i = 0; i < formLen; i++)
    {
        if (std::isupper(formula[i]) && result.find(formula[i]) == result.end())
        {
            if (sets.empty())
                throw ErrorException("Invalid number of sets or vaiables provided");

            result[formula[i]] = sets.front();
            sets.erase(sets.begin());
        }
    }
    if (!sets.empty())
        throw ErrorException("Invalid number of sets or vaiables provided");

    return (result);
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

static std::vector<int32_t> getComplement(char variable, std::map<char, std::vector<int32_t>> sets)
{
    std::vector<int32_t> complement;

    for (t_mapvec it = sets.begin(); it != sets.end(); it++)
    {
        if (it->first != variable)
        {
            for (t_int32vec jt = it->second.begin(); jt != it->second.end(); jt++)
            {
                if (std::find(sets[variable].begin(), sets[variable].end(), *jt) == sets[variable].end())
                    complement.push_back(*jt);
            }
            
        }
    }
    
    return (complement);
}

static std::vector<int32_t> execPostorderNNF(TreeNode *node, std::map<char, std::vector<int32_t>> vars)
{
    if (node->left == nullptr || node->right == nullptr)
    {
        if (node->has_negative)
            node->set = getComplement(node->value, vars);
        return (node->set);
    }

    execPostorderNNF(node->left, vars);
    execPostorderNNF(node->right, vars);

    switch (node->value)
    {
        case '&':
        {
            for (t_int32vec it = node->left->set.begin(); it != node->left->set.end(); it++)
            {
                if (std::find(node->right->set.begin(), node->right->set.end(), *it) != node->right->set.end())
                    node->set.push_back(*it);
            }
            break;
        }
        case '|':
        {
            for (t_int32vec it = node->left->set.begin(); it != node->left->set.end(); it++)
            {
                if (std::find(node->set.begin(), node->set.end(), *it) == node->set.end())
                    node->set.push_back(*it);
            }
            for (t_int32vec it = node->right->set.begin(); it != node->right->set.end(); it++)
            {
                if (std::find(node->set.begin(), node->set.end(), *it) == node->set.end())
                    node->set.push_back(*it);
            }
            break;
        }
    };

    return (node->set);
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

TreeNode *createTree(std::string &formula, std::map<char, std::vector<int32_t>> vars)
{
    if (formula.empty())
        throw ErrorException("No input provided");
    // no negative in operators
    std::array<char, 6> operators = {'&', '|', '^', '>', '='};
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
        else if (vars.find(formula[i]) != vars.end())
        {
            TreeNode *newNode = new TreeNode(formula[i]);
            newNode->set = vars[formula[i]];
            numStack.push(newNode);
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

std::vector<int32_t> eval_set(std::string &formula, std::vector<std::vector<int32_t>> sets)
{
    std::map<char, std::vector<int32_t>> variables = checkVars(formula, sets);
    TreeNode *root = createTree(formula, variables);
    transformNNF(root);

    std::vector<int32_t> result = execPostorderNNF(root, variables);
    
    delete root;

    return (result);
}