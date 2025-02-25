# include "../BitsetU32.hpp"

int main(void)
{
    std::cout << "Exercise 02 - Gray code: " << '\n';

    BitsetU32 bitset1(42);
    BitsetU32 bitset2 = bitset1.getGC();
    
    std::cout << bitset1 << ": " << "(Binary: " << bitset1.getBinary() << ") ---> " << "(GrayCode: " << bitset2.getBinary() << ")\n";

    return (0);
}