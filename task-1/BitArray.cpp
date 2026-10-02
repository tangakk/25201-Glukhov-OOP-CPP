#include "BitArray.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stdexcept>

using namespace std;

using std::copy;
using std::logic_error;

BitArray::BitArray() {
    this->capacity = 0;
    this->num_bits = 0;
    this->data = new unsigned long[this->capacity];
}

BitArray::~BitArray() {
    delete [] this->data;
}

BitArray::BitArray(int num_bits, unsigned long value) {
    if (num_bits < 0) num_bits = 0; //no you don't
    this->num_bits = num_bits;
    this->capacity = num_bits / sizeof(unsigned long) * 8 + (num_bits % (sizeof(unsigned long) * 8) != 0);
    this->data = new unsigned long[this->capacity];
    if (num_bits)
        this->data[0] = value;
}

BitArray::BitArray(const BitArray &b) {
    this->capacity = b.capacity;
    this->num_bits = b.num_bits;
    this->data = new unsigned long[this->capacity];
    copy(b.data, b.data + b.capacity, this->data);
}

void BitArray::swap(BitArray &b) {
    BitArray tmp(*this);
    *this = b;
    b = tmp;
}

BitArray &BitArray::operator=(const BitArray &b) {
    this->capacity = b.capacity;
    this->num_bits = b.num_bits;
    delete this->data;
    this->data = new unsigned long[this->capacity];
    copy(b.data, b.data + b.capacity, this->data);
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits >= this->num_bits) {
        int new_capacity = num_bits / (sizeof(unsigned long) * 8) + (num_bits % (sizeof(unsigned long) * 8) != 0);
        unsigned long *new_data = new unsigned long[new_capacity];
        copy(this->data, this->data + this->capacity, new_data);
        delete this->data;
        this->data = new_data;
        for (int i = this->num_bits; i % (sizeof(unsigned long) * 8) != 0; i++) {
            this->set(i, value);
        }
        for (int i = this->capacity; i < new_capacity; i++) {
            this->data[i] = value ? -1 : 0;
        }
        this->num_bits = num_bits;
        return;
    }

    throw logic_error("BitArray size cannot be reduced without clearing it first");
}

void BitArray::clear() {
    *this = BitArray();
}

void BitArray::push_back(bool bit) {
    //since this->num_bits always contains the size of an array
    //i can just do that:
    this->resize(this->num_bits + 1, bit);
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if (b.num_bits >= this->num_bits) {
        for (int i = 0; i < this->capacity; i++) {
            this->data[i] = this->data[i] & b.data[i];
        }
        return *this;
    }

    throw logic_error("Bitwise operations cannot be used on BitArrays of smaller size");
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if (b.num_bits >= this->num_bits) {
        for (int i = 0; i < this->capacity; i++) {
            this->data[i] = this->data[i] | b.data[i];
        }
        return *this;
    }

    throw logic_error("Bitwise operations cannot be used on BitArrays of smaller size");
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if (b.num_bits >= this->num_bits) {
        for (int i = 0; i < this->capacity; i++) {
            this->data[i] = this->data[i] ^ b.data[i];
        }
        return *this;
    }

    throw logic_error("Bitwise operations cannot be used on BitArrays of smaller size");
}

BitArray &BitArray::operator<<=(int n) {
    if (n <= 0) return *this;
    //oh i hate this
    if (n <= sizeof(unsigned long) * 8) {
        this->data[0] <<= n;
        for (int i = 1; i < this->capacity; i++) {
            unsigned long tmp = this->data[i] >> (sizeof(unsigned long) * 8 - n);
            this->data[i] <<= n;
            this->data[i - 1] |= tmp;
        }
    } else {
        int to_ashes = n / sizeof(unsigned long) * 8;
        for (int i = 0; i < this->capacity - to_ashes; i++) {
            this->data[i] = this->data[i + to_ashes];
        }
        for (int i = this->capacity - to_ashes; i < this->capacity; i++) {
            this->data[i] = 0;
        }
        *this <<= n % (sizeof(unsigned long) * 8);
    }
    this->clear_junk();
    return *this;
}

BitArray &BitArray::operator>>=(int n) {
    if (n <= 0) return *this;
    if (n <= sizeof(unsigned long) * 8) {
        this->data[this->capacity - 1] >>= n;
        for (int i = this->capacity - 2; i >= 0; i--) {
            unsigned long tmp = this->data[i] << (sizeof(unsigned long) * 8 - n);
            this->data[i] >>= n;
            this->data[i + 1] |= tmp;
        }
    } else {
        int to_ashes = n / sizeof(unsigned long) * 8;
        for (int i = this->capacity - to_ashes; i >= to_ashes; i--) {
            this->data[i] = this->data[i - to_ashes];
        }
        for (int i = 0; i < to_ashes; i++) {
            this->data[i] = 0;
        }
        *this >>= n % (sizeof(unsigned long) * 8);
    }
    this->clear_junk();
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray tmp(*this);
    tmp <<= n;
    return tmp;
}

BitArray BitArray::operator>>(int n) const {
    BitArray tmp(*this);
    tmp >>= n;
    return tmp;
}

BitArray &BitArray::set(int n, bool value) {
    int index = n / (sizeof(unsigned long) * 8);
    if (value) {
        this->data[index] |= (1UL << (n % (sizeof(unsigned long) * 8)));
    } else {
        this->data[index] &= ~(1UL << (n % (sizeof(unsigned long) * 8)));
    }
    return *this;
}

BitArray &BitArray::set() {
    for (int i = 0; i < this->capacity; i++) {
        this->data[i] = -1;
    }
    return *this;
}

BitArray &BitArray::reset(int n) {
    return this->set(n, false);
}

BitArray &BitArray::reset() {
    for (int i = 0; i < this->capacity; i++) {
        this->data[i] = 0;
    }
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < this->capacity; i++) {
        if (this->data[i] != 0) {
            if (i != this->capacity - 1) {
                return true;
            }
            for (int j = i * sizeof(unsigned long) * 8; j != num_bits; j++) {
                if ((*this)[j]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool BitArray::all() const {
    for (int i = 0; i < this->capacity; i++) {
        if (this->data[i] == 0) {
            if (i != this->capacity - 1) {
                return false;
            }
            for (int j = i * sizeof(unsigned long) * 8; j != num_bits; j++) {
                if (!(*this)[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool BitArray::none() const {
    return !this->any();
}

BitArray BitArray::operator~() const {
    for (int i = 0; i < this->capacity; i++) {
        this->data[i] = ~this->data[i];
    }
    return *this;
}

int BitArray::count() const {
    int count = 0;
    for (int i = 0; i < this->capacity; i++) {
        if (i != this->capacity - 1) {
            int tmp = this->data[i];
            while (tmp > 0) {
                tmp &= (tmp - 1);
                count++;
            }
        } else {
            for (int j = i * sizeof(unsigned long) * 8; j < num_bits; j++) {
                count += (*this)[j];
            }
        }
    }
    return count;
}

BitArray::ProxyBool::ProxyBool(BitArray &bit_array, int index) : bit_array(bit_array), index(index) {
}

BitArray::ProxyBool &BitArray::ProxyBool::operator=(bool value) {
    this->bit_array.set(this->index, value);
    return *this;
}

BitArray::ProxyBool::operator bool() const {
    return static_cast<const BitArray>(this->bit_array)[this->index];
}

BitArray::ProxyBool BitArray::operator[](int i) {
    return ProxyBool(*this, i);
}

bool BitArray::operator[](int i) const {
    int index = i / (sizeof(unsigned long) * 8);
    unsigned long tmp = this->data[index];
    return (tmp >> (i % (sizeof(unsigned long) * 8))) & 1UL;
}

int BitArray::size() const {
    return this->num_bits;
}

bool BitArray::empty() const {
    return this->num_bits == 0;
}

string BitArray::to_string() const {
    string res = "";
    //i guess there's no better way to do that in c++17...
    for (int i = this->num_bits - 1; i >= 0; i--) {
        res += (*this)[i] ? "1" : "0";
    }
    return res;
}

bool operator==(const BitArray &a, const BitArray &b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.capacity; i++) {
        if (i != a.capacity - 1) {
            if (a.data[i] != b.data[i]) {
                return false;
            }
        }
        for (int j = i * sizeof(unsigned long) * 8; j < a.num_bits; j++) {
            if (a[j] != b[j]) return false;
        }
    }
    return true;
}

bool operator!=(const BitArray &a, const BitArray &b) {
    return !(a == b);
}

BitArray operator&(const BitArray &b1, const BitArray &b2) {
    BitArray res(b1);
    res &= b2;
    return res;
}

BitArray operator|(const BitArray &b1, const BitArray &b2) {
    BitArray res(b1);
    res |= b2;
    return res;
}

BitArray operator^(const BitArray &b1, const BitArray &b2) {
    BitArray res(b1);
    res ^= b2;
    return res;
}

void BitArray::clear_junk() {
    for (int i = (this->capacity) * sizeof(unsigned long) * 8 - 1; i >= num_bits; i--) {
        this->set(i, false);
    }
}
