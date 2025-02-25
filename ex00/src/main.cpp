# include "../BitsetU32.hpp"

int main(void)
{
    std::cout << "Exercise 00 - Adder: " << '\n';
        
    BitsetU32 bitset1(22);
    BitsetU32 bitset2(20);
    
    std::cout << bitset1  << " + " << bitset2 << " = " << bitset1 + bitset2 << '\n';
    
    return (0);
}