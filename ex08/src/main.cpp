# include "../includes.hpp"

static std::string printSet(std::vector<int32_t> set)
{
    std::string strSet = "{";
    for (t_int32vec it = set.begin(); it != set.end(); it++)
    {
        strSet += (*it + '0');
        if (it + 1 != set.end())
            strSet += ", ";
    }
    strSet += "}";

    return (strSet);
}

static std::string printGroup(std::vector<std::vector<int32_t>> set)
{
    std::string strSet = "{";
    for (t_vecint32vec it = set.begin(); it != set.end(); it++)
    {
        strSet += printSet(*it);
        if (it + 1 != set.end())
            strSet += ", ";
    }
    strSet += "}";

    return (strSet);
}

int main(void)
{
    std::cout << "Exercise 08 - Powerset: " << '\n';

    std::vector<int32_t> set = {1, 2, 3};

    try
    {
        std::cout << "powerset(\"" << printSet(set) << "\") ---> " << printGroup(powerset(set)) << '\n';
    }
    catch(std::exception  &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
        
    return (0);
}