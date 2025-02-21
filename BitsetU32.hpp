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
        BitsetU32   operator+(const BitsetU32 &other) const;
        BitsetU32   operator*(const BitsetU32 &other) const;
        int         operator[](int index) const;
        ~BitsetU32();

        // correction & debug
        std::string getBinary(void) const;

        uint32_t    getDigit(void) const;
        void        setBit(int i, int value);
        int         getMSBIdx(void) const;
        BitsetU32   getGC(void) const;
    };

    std::ostream    &operator<<(std::ostream &o, const BitsetU32 &other);

#endif