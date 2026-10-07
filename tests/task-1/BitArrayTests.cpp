#include "gtest/gtest.h"
#include "../../task-1/BitArray.h"
#include <iostream>

using namespace std;

TEST(BitArrayTests, test0) {
    BitArray a;
}

TEST(BitArrayTests, test1) {
    BitArray a(10, 0b1010101010);
    cout << a.to_string() << endl;
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(a[i], (i % 2 != 0));
    }
}

TEST(BitArrayTests, test2) {
    BitArray a(5, 0b11111);
    ASSERT_EQ(a[2], true);
    a.reset(2);
    ASSERT_EQ(a[2], false);
    a.set(2);
    ASSERT_EQ(a[2], true);
    a.set();
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(a[i], true);
    }
    a.reset();
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(a[i], false);
    }
}

TEST(BitArrayTests, test3) {
    BitArray a(5, 0b11111);
    BitArray b(5, 0b00000);
    ASSERT_NE(a, b);
    b = a;
    ASSERT_EQ(a, b);
    BitArray c(a);
    ASSERT_EQ(a, c);
    a.resize(sizeof(unsigned long) * 16, true);
    ASSERT_NE(a, b);
    b = a;
    ASSERT_EQ(a, b);
    b[10] = false;
    ASSERT_NE(a, b);
}

TEST(BitArrayTests, test4) {
    BitArray a(-1, 0b11111);
    ASSERT_EQ(a.size(), 0);
    ASSERT_EQ(a.empty(), true);
}

TEST(BitArrayTests, test5) {
    BitArray a(5, 0b10101);
    BitArray b(5, 0b11000);
    ASSERT_EQ(a.to_string(), "10101");
    a &= b;
    ASSERT_EQ(a.to_string(), "10000");
    a |= b;
    ASSERT_EQ(a.to_string(), "11000");
    a ^= b;
    ASSERT_EQ(a.to_string(), "00000");
    b = ~b;
    ASSERT_EQ(b.to_string(), "00111");

    a = BitArray(5, 0b10101);
    b = BitArray(5, 0b11000);
    ASSERT_EQ(a.to_string(), "10101");
    a = a&b;
    ASSERT_EQ(a.to_string(), "10000");
    a = a|b;
    ASSERT_EQ(a.to_string(), "11000");
    a = a^b;
    ASSERT_EQ(a.to_string(), "00000");
}

TEST(BitArrayTests, test6) {
    BitArray a(5, 0b10101);
    a <<= 2;
    ASSERT_EQ(a.to_string(), "10100");
    a >>= 2;
    ASSERT_EQ(a.to_string(), "00101");
    BitArray b(16, 0b0001'1010'0110'1111);
    ASSERT_EQ(b.to_string(), "0001101001101111");
    a = b << 10;
    ASSERT_EQ(a.to_string(), "1011110000000000");
    a = b >> 10;
    ASSERT_EQ(a.to_string(), "0000000000000110");
}

TEST(BitArrayTests, test7) {
    BitArray a(5, 0b11111);
    ASSERT_EQ(a.any(), true);
    ASSERT_EQ(a.all(), true);
    ASSERT_EQ(a.none(), false);
    ASSERT_EQ(a.count(), 5);
    a.reset();
    ASSERT_EQ(a.any(), false);
    ASSERT_EQ(a.all(), false);
    ASSERT_EQ(a.none(), true);
    BitArray b(sizeof(unsigned long) * 16, 1);
    ASSERT_EQ(b.any(), true);
    ASSERT_EQ(b.count(), 1);
    b.reset();
    ASSERT_EQ(b.all(), false);
}

TEST(BitArrayTests, test8) {
    BitArray a(5, 0b11111);
    BitArray b(5, 0b00000);
    a.swap(b);
    ASSERT_EQ(a.to_string(), "00000");
    ASSERT_EQ(b.to_string(), "11111");
}

TEST(BitArrayTests, test9) {
    BitArray a(5, 0b10101);
    a.push_back(true);
    ASSERT_EQ(a.size(), 6);
    ASSERT_EQ(a.to_string(), "110101");
    a.push_back(false);
    ASSERT_EQ(a.size(), 7);
    ASSERT_EQ(a.to_string(), "0110101");
    ASSERT_EQ(a[6], false);
    a.clear();
    ASSERT_EQ(a.size(), 0);
}

TEST(BitArrayTests, test10) {
    BitArray a(5, 0b10001);
    BitArray b(10, 0b01100);
    a |= b;
    ASSERT_EQ(a.size(), 5);
    ASSERT_EQ(a.to_string(), "11101");
    ASSERT_ANY_THROW(b&=a);
    ASSERT_ANY_THROW(b|=a);
    ASSERT_ANY_THROW(b^=a);
}

TEST(BitArrayTests, test11) {
    BitArray a(5, 0b00000);
    a.resize(10, true);
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.to_string(), "1111100000");
    ASSERT_ANY_THROW(a.resize(5));
    a.clear();
    a.resize(3, false);
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(a.to_string(), "000");
}

TEST(BitArrayTests, test12) {
    BitArray a(5, 0b11111);
    a[3] = 0;
    ASSERT_EQ(a.to_string(), "10111");
}

TEST(BitArrayTests, test13) {
    BitArray a;
    string s = "";
    for (int i = 0; i < sizeof(unsigned long) * 2; i++) {
        for (int j = 0; j < 8; ++j) {
            a.push_back(i % 2);
            s = (i % 2 ? "1" : "0") + s;
        }
    }
    ASSERT_EQ(a.to_string(), s);
    a <<= (sizeof(unsigned long) * 8+1);
    string new_s = s.substr(sizeof(unsigned long)*8+1, sizeof(unsigned long) * 8 - 1) + string(sizeof(unsigned long) * 8 + 1, '0');
    ASSERT_EQ(a.to_string(), new_s);

    a>>=(sizeof(unsigned long) * 8+1);
    new_s = string(sizeof(unsigned long) * 8 + 1, '0') + s.substr(sizeof(unsigned long)*8+1, sizeof(unsigned long) * 8 - 1);
    ASSERT_EQ(a.to_string(), new_s);
}

