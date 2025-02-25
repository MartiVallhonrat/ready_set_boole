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

BitsetU32   BitsetU32::operator+(const BitsetU32 &other) const
{
    BitsetU32 result;
    int bitThis;
    int bitOther;
    int bitCarry = 0;
    int bitResult;

    for (int i = 0; i < 32; i++)
    {
        bitThis = (*this)[i];
        bitOther = other[i];
        bitResult = bitThis ^ bitOther ^ bitCarry;
        result.setBit(i, bitResult); 

        if ((bitThis && bitOther) || (bitThis && bitCarry) || (bitOther && bitCarry))
            bitCarry = 1;
        else
            bitCarry = 0;
    }
    
    return (result);
}

BitsetU32   BitsetU32::operator*(const BitsetU32 &other) const
{
    BitsetU32 result;
    int otherDigit = other.getDigit();

    while (otherDigit--)
        result = result + this->digit;
    
    return (result);
}

// Reverse indexing
// Cant be changed, just to check
int    BitsetU32::operator[](int index) const
{
    return (index < 32 ? (this->digit >> index) & 1 : -1);
}

std::string BitsetU32::getBinary(void) const
{
    std::string binaryStr;
    
    for (int MSB = this->getMSBIdx(), idx = 0; MSB >= 0; MSB--, idx++)
    {
        binaryStr += (*this)[MSB] + '0'; 
    }
    return (binaryStr);
}

uint32_t   BitsetU32::getDigit(void) const
{
    return (this->digit);
}

void   BitsetU32::setDigit(uint32_t new_digit)
{
    this->digit = new_digit;
}

// Reverse index again (i)
void    BitsetU32::setBit(int i, int value)
{
    if (i < 32 && (value == 0 || value == 1))
    {
        if (value)
            this->digit = this->digit | (1 << i);
        else
            this->digit = this->digit & ~(1 << i);
    }
}

int BitsetU32::getMSBIdx() const
{
    if (this->digit == 0)
        return (-1);

    int idx = -1;
    for (int i = 1; i <= static_cast<int>(this->digit); i *= 2)
        idx++;

    return (idx);
}

BitsetU32    BitsetU32::getGC() const
{
    BitsetU32    grayCode;

    bool isFirst = true;
    for (int MSB = this->getMSBIdx(); MSB >= 0; MSB--)
    {
        if (isFirst)
        {
            grayCode.setBit(MSB, (*this)[MSB]);
            isFirst = false;
        }
        else
            grayCode.setBit(MSB, ((*this)[MSB + 1] ^ (*this)[MSB]));
    }

    return (grayCode);
}

BitsetU32::~BitsetU32()
{
}

std::ostream    &operator<<(std::ostream &o, const BitsetU32 &other)
{
    o << other.getDigit();
    return (o);
}
