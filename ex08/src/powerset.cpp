# include "../includes.hpp"

static void addSet(std::vector<std::vector<int32_t>> &mainVec, std::vector<int32_t> newSet, std::vector<int32_t> set, size_t size, size_t start)
{
    while (start < size)    
    {
        newSet.push_back(set[start]);
        mainVec.push_back(newSet);
        start++;
        addSet(mainVec, newSet, set, size, start);
        newSet.pop_back();
    }
}

std::vector<std::vector<int32_t>> powerset(std::vector<int32_t> set)
{
    // create it & add empty vec
    std::vector<std::vector<int32_t>> mainVec = {{}};
    std::vector<int32_t> newSet;

    // adding all possible variations in a recursive way
    addSet(mainVec, newSet, set, set.size(), 0);

    return (mainVec);
}