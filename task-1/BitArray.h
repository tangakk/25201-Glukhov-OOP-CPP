//
// Created by tangakk on 30.09.2026.
//

#ifndef CPP_BITARRAY_H
#define CPP_BITARRAY_H
#include <string>

using std::string;

class BitArray {
private:
    unsigned long *data;
    int num_bits;
    int capacity; //in bytes

    static constexpr size_t WORD_SIZE = sizeof(unsigned long) * 8;

    //Proxy class for [] overloading
    class ProxyBool {
    private:
        BitArray &bit_array;
        int index;

    public:
        ProxyBool(BitArray &bit_array, int index);
        ProxyBool& operator=(bool val);
        operator bool() const;
    };

    void clear_junk();
public:
    BitArray();

    ~BitArray();

    //Constructs BitArray with defined size.
    //First sizeof(long) bits can be initialized with value.
    explicit BitArray(int num_bits, unsigned long value = 0);

    BitArray(const BitArray &b);


    //Swaps two BitArrays.
    void swap(BitArray &b);

    BitArray &operator=(const BitArray &b);


    //Resizes the array to num_bits. New bits
    //can be set to value.
    void resize(int num_bits, bool value = false);

    //Clears BitArray.
    void clear();

    //Adds a bit to the end of the array. Resizes array if needed,
    void push_back(bool bit);


    //Bitwise operators.
    //Can only work with arrays of equal or greater size.
    //Otherwise will throw an exception.
    BitArray &operator&=(const BitArray &b);

    BitArray &operator|=(const BitArray &b);

    BitArray &operator^=(const BitArray &b);

    BitArray &operator<<=(int n);

    BitArray &operator>>=(int n);

    BitArray operator<<(int n) const;

    BitArray operator>>(int n) const;


    //Sets bit with index n to val.
    BitArray &set(int n, bool val = true);

    //Sets all bits to 1.
    BitArray &set();

    //Sets bit with index n to 0.
    BitArray &reset(int n);

    //Sets all bits to 0.
    BitArray &reset();

    //true if BitArray contains 1.
    bool any() const;

    //true if BitArray is not empty and all bits are 1.
    bool all() const;

    //true if BitArray doesn't contain 1.
    bool none() const;

    //Bitwise inversion
    BitArray operator~() const;

    //Counts bits set to 1.
    int count() const;

    //Can be used to set bit with index i.
    ProxyBool operator[](int i);

    //Returns bit with index i
    bool operator[](int i) const;

    //Returns size of BitArray.
    int size() const;

    //Returns true if BitArray is empty.
    bool empty() const;

    //Returns big-endian string representation of BitArray.
    string to_string() const;

    friend bool operator==(const BitArray &a, const BitArray &b);
};

bool operator==(const BitArray &a, const BitArray &b);

bool operator!=(const BitArray &a, const BitArray &b);

BitArray operator&(const BitArray &b1, const BitArray &b2);

BitArray operator|(const BitArray &b1, const BitArray &b2);

BitArray operator^(const BitArray &b1, const BitArray &b2);


#endif //CPP_BITARRAY_H
