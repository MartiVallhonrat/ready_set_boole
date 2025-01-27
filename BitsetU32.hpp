#ifndef BITSETU32_HPP
# define BITSETU32_HPP

# include <iostream>
# include <cstdint>

class BitsetU32
{
    private:
        uint32_t digit;

    public:
        BitsetU32();
        BitsetU32(uint32_t new_digit);
        BitsetU32(const BitsetU32 &other);
        BitsetU32   &operator=(const BitsetU32 &other);
        int         operator[](int index);
        ~BitsetU32();

        uint32_t    getDigit(void) const;
        void        setBit(int i, int value);
};

#endif