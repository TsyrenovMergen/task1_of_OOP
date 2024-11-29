#pragma once
#include <string>
#include <cstdlib>
#include <iostream>

class BitArray
{
	int sizeint;
	int countbits;
	int countint;
	unsigned int* bits;
public:
	BitArray() noexcept;
	~BitArray() noexcept;
	explicit BitArray(int num_bits, unsigned long value = 0) noexcept;
	BitArray(const BitArray& b);
	void swap(BitArray& b) noexcept;
	BitArray& operator=(const BitArray& b);
	void resize(int num_bits, bool value = false) noexcept;
	void clear() noexcept;
	void push_back(bool bit) noexcept;
	BitArray& operator&=(const BitArray& b);
	BitArray& operator|=(const BitArray& b);
	BitArray& operator^=(const BitArray& b);
	BitArray& operator<<=(int n) noexcept;
	BitArray& operator>>=(int n) noexcept;
	BitArray operator<<(int n) const noexcept;
	BitArray operator>>(int n) const noexcept;
	BitArray& set(int n, bool val = true);
	BitArray& set() noexcept;
	BitArray& reset(int n);
	BitArray& reset() noexcept;
	bool any() const;
	bool none() const;
	BitArray operator~() const noexcept;
	int count() const noexcept;
	bool operator[](int i) const;
	int size() const noexcept;
	bool empty() const noexcept;
	std::string to_string() const noexcept;
};

bool operator==(const BitArray& a, const BitArray& b) noexcept;
bool operator!=(const BitArray& a, const BitArray& b) noexcept;

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);