#include "OOP1.hpp"


/*the default constructor*/
BitArray::BitArray() noexcept
{
	this->sizeint = 2;
	this->countbits = 0;
	this->countint = 0;
	this->bits = new unsigned int[this->sizeint];
	for (int i = 0; i < sizeint; i++)
	{
		this->bits[i] = 0;
	}
}
/*the destuctor*/
BitArray::~BitArray() noexcept
{
	this->sizeint = 0;
	this->countbits = 0;
	this->countint = 0;
	delete[] bits;
}
/*Constructs an array storing a specified number(num_bits) of bits.
The first sizeof(long) bits can be initialized using the value parameter.*/
BitArray::BitArray(int num_bits, unsigned long value) noexcept
{
	this->countbits = num_bits;
	this->countint = num_bits / 32;
	if (num_bits % 32)
	{
		countint++;
	}
	this->sizeint = this->countint;
	this->bits = new unsigned int[this->sizeint];
	this->bits[0] = value;
	for (int i = 1; i < this->sizeint; i++)
	{
		bits[i] = 0;
	}
}
/*the copying constructor*/
BitArray::BitArray(const BitArray& b)
{
	if (this == &b)
	{
		throw "error in the copying constructor: b=this";
	}
	this->sizeint = b.sizeint;
	this->countbits = b.countbits;
	this->countint = b.countint;
	this->bits = new unsigned int[this->sizeint];
	for (int i = 0; i < this->sizeint; i++)
	{
		this->bits[i] = b.bits[i];
	}
}
/*exchanges the values of two bit arrays
deep copying is taking place*/
void BitArray::swap(BitArray& b) noexcept
{
	if (this == &b)
	{
		return;
	}
	unsigned* tempints = new unsigned int[this->countint];
	for (int i = 0; i < this->countint; i++)
	{
		tempints[i] = this->bits[i];
	}
	delete[] this->bits;
	this->bits = new unsigned int[b.sizeint];
	for (int i = 0; i < b.countint; i++)
	{
		this->bits[i] = b.bits[i];
	}
	delete b.bits;
	b.bits = new unsigned int[this->sizeint];
	for (int i = 0; i < this->countint; i++)
	{
		b.bits[i] = tempints[i];
	}
	int temp;
	temp = this->countbits;
	this->countbits = b.countbits;
	b.countbits = temp;
	temp = this->countint;
	this->countint = b.countint;
	b.countint = temp;
	temp = this->sizeint;
	this->sizeint = b.sizeint;
	b.sizeint = temp;
	delete[] tempints;

}
/*operator =
causes an exception if the bit array is assigned to itself*/
BitArray& BitArray::operator=(const BitArray& b)
{
	if (this == &b)
	{
		throw "error in operator=, b=this";
	}
	delete[] this->bits;
	this->sizeint = b.sizeint;
	this->countint = b.countint;
	this->countbits = b.countbits;
	this->bits = new unsigned int[this->sizeint];
	for (int i = 0; i < this->countint; i++)
	{
		this->bits[i] = b.bits[i];
	}
	return *this;
}
/*Changes the size of the array and the size of the allocated memory.In case of expansion,
new elements are initialized with the value value.*/
void BitArray::resize(int num_bits, bool value) noexcept
{
	unsigned int* tempints = new unsigned int[this->countint];
	for (int i = 0; i < this->countint; i++)
	{
		tempints[i] = this->bits[i];
	}
	delete[] this->bits;
	this->sizeint = num_bits / 32;
	if (num_bits % 32 > 0)
	{
		this->sizeint++;
	}
	this->bits = new unsigned int[this->sizeint];
	for (int i = 0; i < this->countint; i++)
	{
		this->bits[i] = tempints[i];
	}
	delete[] tempints;
	if (value == false && num_bits > this->countbits)
	{
		for (int i = this->countbits % 32; i < 32; i++)
		{
			this->bits[this->countint] = this->bits[this->countint] & (~(1 << (31 - i)));
		}
		for (int i = this->countint; i < num_bits / 32; i++)
		{
			this->bits[i] = 0;
		}
		for (int i = 0; i < num_bits % 32; i++)
		{
			this->bits[num_bits / 32 + 1] = this->bits[num_bits / 32 + 1] & (~(1 << (31 - i)));
		}
		if (num_bits % 32 == 0)
		{
			this->bits[num_bits / 32] = 0;
		}
	}
	if (value == true && num_bits > this->countbits)
	{
		this->bits[this->countint] = 0;
		for (int i = this->countbits % 32; i < 32; i++)
		{
			this->bits[this->countint] = this->bits[this->countint] | (1 << (31 - i));
		}
		for (int i = this->countint; i < num_bits / 32; i++)
		{
			this->bits[i] = UINT32_MAX;
		}
		for (int i = 0; i < 32; i++)
		{
			this->bits[num_bits / 32 + 1] = this->bits[num_bits / 32 + 1] | (1 << (31 - i));
		}
		if (num_bits % 32 == 0)
		{
			this->bits[num_bits / 32] = UINT32_MAX;
		}

	}
	this->countbits = num_bits;
	this->countint = this->sizeint;
	return;

}
/*Clears the array, you can reuse the object*/
void BitArray::clear() noexcept
{
	delete[] this->bits;
	this->bits = new unsigned int[2];
	for (int i = 0; i < 2; i++)
	{
		this->bits[i] = 0;
	}
	this->countint = 0;
	this->countbits = 0;
	this->sizeint = 2;
}
/*Adds a new bit to the end of the array.If necessary, memory is redistributed.*/
void BitArray::push_back(bool bit) noexcept
{
	if (this->countbits % 32 == 0 || countint == 0)
	{
		if (this->countint + 1 > this->sizeint)
		{
			unsigned int* temp = new unsigned int[this->sizeint];
			for (int i = 0; i < countint; i++)
			{
				temp[i] = this->bits[i];
			}
			this->sizeint = this->sizeint + 4;
			delete[] this->bits;
			this->bits = new unsigned int[this->sizeint];
			for (int i = 0; i < countint; i++)
			{
				this->bits[i] = temp[i];
			}
			for (int i = this->countint; i < this->countint + 4; i++)
			{
				this->bits[i] = 0;
			}
			delete[] temp;
		}
		countint++;
	}
	this->countbits++;
	if (bit)
	{
		this->bits[this->countint - 1] = this->bits[this->countint - 1] | (1 << this->countbits % 32);
	}
	else
	{
		this->bits[this->countint - 1] = this->bits[this->countint - 1] & (~(1 << this->countbits % 32));
	}
}
/*The operator &=, only works on arrays of the same size.Throws an exception if the sizes are different*/
BitArray& BitArray::operator&=(const BitArray& b)
{
	if (this->countbits == b.countbits)
	{
		for (int i = 0; i < this->countint; i++)
		{
			this->bits[i] = this->bits[i] & b.bits[i];
		}
	}
	else
	{
		throw "error in operator&=, sizes are diferent";
	}
	return *this;
}
/*The operator |=, only works on arrays of the same size.Throws an exception if the sizes are different*/
BitArray& BitArray::operator|=(const BitArray& b)
{
	if (this->countbits == b.countbits)
	{
		for (int i = 0; i < this->countint; i++)
		{
			this->bits[i] = this->bits[i] | b.bits[i];
		}
	}
	else
	{
		throw "error in operator|=, sizes are diferent";

	}
	return *this;
}
/*The operator ^=, only works on arrays of the same size.Throws an exception if the sizes are different*/
BitArray& BitArray::operator^=(const BitArray& b)
{
	if (this->countbits == b.countbits)
	{
		for (int i = 0; i < this->countint; i++)
		{
			this->bits[i] = this->bits[i] ^ b.bits[i];
		}
	}
	else
	{
		throw "error in operator^=, sizes are diferent";
	}
	return *this;
}
/*operator <<=, bit shift to the left with zero padding*/
BitArray& BitArray::operator<<=(int n) noexcept
{
	unsigned int* tablenumbers = new unsigned int[32];
	tablenumbers[0] = UINT32_MAX;
	for (int i = 1; i < 32; i++)
	{
		tablenumbers[i] = tablenumbers[i - 1] ^ (1 << (32 - i));
	}
	BitArray b;
	b.countbits = this->countbits;
	b.countint = this->countint;
	b.sizeint = b.countint;
	b.bits = new unsigned int[b.sizeint];
	for (int i = 0; i < this->countint - n / 32; i++)
	{
		b.bits[i] = (this->bits[i + n / 32] & tablenumbers[n % 32]) << (n % 32);
		b.bits[i] = b.bits[i] | ((this->bits[i + n / 32 + 1] & (~tablenumbers[n % 32])) << (n % 32));
	}
	for (int j = 0; j < n % 32; j++)
	{
		b.bits[this->countint - n / 32 - 1] = b.bits[this->countint - n / 32 - 1] & (~(1 << j));
	}
	for (int i = this->countint - n / 32; i < this->countint; i++)
	{
		b.bits[i] = 0;
	}
	*this = b;
	delete[] tablenumbers;
	~b;
	return *this;
}
/*operator >>=, bit shift to the rigth with zero padding*/
BitArray& BitArray::operator>>=(int n) noexcept
{
	unsigned int* tablenumbers = new unsigned int[32];
	tablenumbers[0] = UINT32_MAX;
	for (int i = 1; i < 32; i++)
	{
		tablenumbers[i] = tablenumbers[i - 1] ^ (1 << i);
	}
	BitArray b;
	b.countbits = this->countbits;
	b.countint = this->countint;
	b.sizeint = b.countint;
	b.bits = new unsigned int[b.sizeint];
	for (int i = this->countint - 1; i >= n / 32; i--)
	{
		b.bits[i] = (this->bits[i - n / 32] & tablenumbers[n % 32]) >> (n % 32);
		b.bits[i] = b.bits[i] | ((this->bits[i - n / 32] & (~tablenumbers[n % 32])) >> (n % 32));
	}
	for (int j = 0; j < n % 32; j++)
	{
		b.bits[n / 32] = b.bits[n / 32] & (~(1 >> (31 - j)));
	}
	for (int i = n / 32 - 1; i >= 0; i--)
	{
		b.bits[i] = 0;
	}
	*this = b;
	delete[] tablenumbers;
	~b;
	return *this;
}
/*operator <<, bit shift to the left with zero padding*/
BitArray BitArray::operator<<(int n) const noexcept
{
	BitArray b(*this);
	b <<= n;
	return b;
}
/*operator >>, bit shift to the rigth with zero padding*/
BitArray BitArray::operator>>(int n) const noexcept
{
	BitArray b(*this);
	b >>= n;
	return b;
}
/*sets the bit with index i to val, throws an exception 
if i negative or is greater or than the number of bits in the bit array -1*/
BitArray& BitArray::set(int n, bool val)
{
	if (n < 0 || n >= this->countbits)
	{
		throw "error in set(int, bool): n is wrong";
	}
	if (val)
	{
		this->bits[n / 32] = this->bits[n / 32] | (1 << (31 - (n % 32)));
	}
	else
	{
		this->bits[n / 32] = this->bits[n / 32] & (~(1 << (31 - (n % 32))));
	}
	return *this;
}
/*Makes all bits true*/
BitArray& BitArray::set() noexcept
{
	for (int i = 0; i < this->countint; i++)
	{
		this->bits[i] = UINT32_MAX;
	}
	return *this;
}
/*sets the bit with index i to false, throws an exception
if i negative or is greater than the number of bits in the bit array -1 */
BitArray& BitArray::reset(int n)
{
	if (n < 0 || n >= this->countbits)
	{
		throw "error in reset(int): n is wrong";
	}
	this->bits[n / 32] = this->bits[n / 32] & (~(1 << (31 - (n % 32))));
	return *this;
}
/*Makes all bits false*/
BitArray& BitArray::reset() noexcept
{
	for (int i = 0; i < this->countint; i++)
	{
		this->bits[i] = 0;
	}
	return *this;
}
/*returns true if at least one bit is true, otherwise false, throws an exception if bit array is empty*/
bool BitArray::any() const 
{
	if (this->countbits == 0)
	{
		throw "error in any: bit array is empty";
	}
	for (int i = 0; i < this->countint; i++)
	{
		if (this->bits[i] > 0)
		{
			return true;
		}
	}
	return false;
}
/*returns true if all bits are false, otherwise false, throws an exception if bit array is empty*/
bool BitArray::none() const
{
	if (this->countbits == 0)
	{
		throw "error in none: bit array is empty";
	}
	for (int i = 0; i < this->countint; i++)
	{
		if (this->bits[i] > 0)
		{
			return false;
		}
	}
	return true;
}
/*Bit inversion*/
BitArray BitArray::operator~() const noexcept
{
	BitArray b;
	b.countint = this->countint;
	b.countbits = this->countbits;
	b.sizeint = this->sizeint;
	b.bits = new unsigned int[b.sizeint];
	for (int i = 0; i < this->countint; i++)
	{
		b.bits[i] = ~this->bits[i];
	}
	return b;
}
/*Returns the number of true bits in the bit array*/
int BitArray::count() const noexcept
{
	int count = 0;
	for (int i = 0; i < this->countint - 1; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (this->bits[i] & (1 << j))
			{
				count++;
			}
		}
	}
	if (this->countbits % 32 > 0)
	{
		for (int j = 0; j < this->countbits % 32; j++)
		{
			if (this->bits[this->countint - 1] & (1 << (31 - j)))
			{
				count++;
			}
		}
	}
	if (this->countbits % 32 == 0 && this->countbits > 0)
	{
		for (int j = 0; j < 32; j++)
		{
			if (this->bits[this->countint - 1] & (1 << (31 - j)))
			{
				count++;
			}
		}
	}
	return count;
}
/*Returns the value of the bit at the index i.Throws an exception if the index i is specified incorrectly :
negative or more than the number of bits in the bit array*/
bool BitArray::operator[](int i) const
{
	if (i > this->countbits - 1 || i < 0)
	{
		throw "error in operator[]: argument i is wrong";
	}
	else
	{
		if (this->bits[i / 32] & (1 << (i % 32)))
		{
			return true;
		}
	}
	return false;
}
/*Returns the number of bits in the bit array*/
int BitArray::size() const noexcept
{
	return this->countbits;
}
/*Returns true if the bit array is empty, otherwise false*/
bool BitArray::empty() const noexcept
{
	if (this->countbits == 0)
	{
		return true;
	}
	return false;
}
/*Returns the string representation of the array.The true bit corresponds to the character '1',
and the false bit corresponds to the character '0', the order from the highest to the lowest*/
std::string BitArray::to_string() const noexcept
{
	std::string str;
	for (int i = 0; i < this->countint - 1; i++)
	{
		for (int j = 31; j >= 0; j--)
		{
			if (this->bits[i] & (1 << j))
			{
				str.push_back('1');
			}
			else
			{
				str.push_back('0');
			}
		}
	}
	if (this->countbits % 32 > 0)
	{
		for (int j = 0; j < this->countbits % 32; j++)
		{
			if (this->bits[this->countint - 1] & (1 << (31 - j)))
			{
				str.push_back('1');
			}
			else
			{
				str.push_back('0');
			}
		}
	}
	if (this->countbits % 32 == 0 && this->countbits > 0)
	{
		for (int j = 0; j < 32; j++)
		{
			if (this->bits[this->countint - 1] & (1 << (31 - j)))
			{
				str.push_back('1');
			}
			else
			{
				str.push_back('0');
			}
		}
	}
	return str;
}
/*checks two bit arrays for equality, they are equal when the number of bits is the same,
and each bit of the first bit array is equal to each bit of the second, respectively*/
bool operator==(const BitArray& a, const BitArray& b) noexcept
{
	if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}
/*Checks two bit arrays for inequality, they are not equal when the number of bits is different
or at least one bit of the first array is not equal to the bit of the second*/
bool operator!=(const BitArray& a, const BitArray& b) noexcept
{
	if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] != b[i])
			{
				return true;
			}
		}
		return false;
	}
	return true;
}
/*The operator &, makes a bitwise conjunction, only works on arrays of the same size.
Throws an exception if the sizes are different*/
BitArray operator&(const BitArray& b1, const BitArray& b2) 
{
	BitArray b;
	if (b1.size() == b2.size())
	{
		b = b1;
		b &= b2;
	}
	else
	{
		throw "error in operator&: sizes of bitarrays are diferent";
	}
	return b;
}
/*The operator |, makes a bitwise disjunction, only works on arrays of the same size.
Throws an exception if the sizes are different*/
BitArray operator|(const BitArray& b1, const BitArray& b2)
{
	BitArray b;
	if (b1.size() == b2.size())
	{
		b = b1;
		b|= b2;
	}
	else
	{
		throw "error in operator|: sizes of bitarrays are diferent";
	}
	return b;
}
/*The operator ^,  makes a bitwise inversion, only works on arrays of the same size.
Throws an exception if the sizes are different*/
BitArray operator^(const BitArray& b1, const BitArray& b2)
{
	BitArray b;
	if (b1.size() == b2.size())
	{
		b = b1;
		b^= b2;
	}
	else
	{
		throw "error in operator^: sizes of bitarrays are diferent";
	}
	return b;
}
