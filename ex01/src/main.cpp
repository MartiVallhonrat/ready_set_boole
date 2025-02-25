# include "../BitsetU32.hpp"

int main(void)
{
    std::cout << "Exercise 01 - Multiplier: " << '\n';

    BitsetU32 bitset1(7);
    BitsetU32 bitset2(6);
    
    std::cout << bitset1  << " * " << bitset2 << " = " << bitset1 * bitset2 << '\n';

    return (0);
}