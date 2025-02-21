# include "../BitsetU32.hpp"

int main(void)
{
    {
        std::cout << "Exercise 00 - Adder: " << '\n';
        
        BitsetU32 bitset1(3);
        BitsetU32 bitset2(10);
    
        std::cout << bitset1  << " + " << bitset2 << " = " << bitset1 + bitset2 << '\n';
    }
    {
        std::cout << "\n"
        << "Exercise 01 - Multiplier: " << '\n';

        BitsetU32 bitset1(3);
        BitsetU32 bitset2(10);
    
        std::cout << bitset1  << " * " << bitset2 << " = " << bitset1 * bitset2 << '\n';
    }
    {
        std::cout << "\n"
        << "Exercise 02 - Gray code: " << '\n';

        BitsetU32 bitset1(124);
        BitsetU32 bitset2 = bitset1.getGC();
    
        std::cout << bitset1 << ": " << bitset1.getBinary() << " ---> " << bitset2 << ": " << bitset2.getBinary() << '\n';
    }
    return (0);
}