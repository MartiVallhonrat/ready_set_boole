# include "../BitsetU32.hpp"

BitsetU32::BitsetU32(): digit(0)
{
}

BitsetU32::BitsetU32(uint32_t new_digit): digit(new_digit)
{
}

BitsetU32::BitsetU32(const BitsetU32 &other)
{
    *this = other;
}

BitsetU32   &BitsetU32::operator=(const BitsetU32 &other)
{
    if (this != &other)
    {
        this->digit = other.digit;
    }

    return (*this);
}

// Reverse indexing
// Cant be changed, just to check
int    BitsetU32::operator[](int index)
{
    return ((this->digit >> index) & 1);
}

uint32_t   BitsetU32::getDigit(void) const
{
    return (this->digit);
}

// Reverse index again (i)
void    BitsetU32::setBit(int i, int value)
{
    if (value)
        this->digit = this->digit | (1 << i);
    else
        this->digit = this->digit & ~(1 << i);
}

BitsetU32::~BitsetU32()
{
}