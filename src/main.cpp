# include "../BitsetU32.hpp"

int main(void)
{
    BitsetU32 test(3);

    std::cout << test.getDigit() << '\n';
    test.setBit(2, 1);
    std::cout << test.getDigit() << '\n';
    return (0);
}