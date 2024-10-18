#include <stdlib.h>
#include <string>
#include <iostream>

class BitArray
{
	int sizeint;
	int countbits;
	int countint;
	unsigned int* bits;
public:
	BitArray()
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
	~BitArray()
	{
		this->sizeint = 0;
		this->countbits = 0;
		this->countint = 0;
		delete[] bits;
	}
	//Конструирует массив, хранящий заданное количество бит.
	//Первые sizeof(long) бит можно инициализровать с помощью параметра value.
	explicit BitArray(int num_bits, unsigned long value = 0)
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
	BitArray(const BitArray& b)
	{
		this->sizeint = b.sizeint;
		this->countbits = b.countbits;
		this->countint = b.countint;
		this->bits = new unsigned int[this->sizeint];
		for (int i = 0; i < this->sizeint; i++)
		{
			this->bits[i] = b.bits[i];
		}
	}
	//Обменивает значения двух битовых массивов.
	void swap(BitArray& b)
	{
		int max=(this->countint>b.countint) ? this->countint:b.countint;
		unsigned int* tempbits=new unsigned int[max];
		for (int i = 0; i < this->countint; i++)
		{
			tempbits[i] = this->bits[i];
		}
		if (this->sizeint < b.countint)
		{
			this->sizeint = b.countint;
			delete[] this->bits;
			this->bits = new unsigned int[this->sizeint];
		}
		for (int i = 0; i < b.countint; i++)
		{
			this->bits[i] = b.bits[i];
		}
		if (b.sizeint < this->countint)
		{
			b.sizeint = this->countint;
			delete[] b.bits;
			b.bits = new unsigned int[b.sizeint];
		}
		for (int i = 0; i < this->countint; i++)
		{
			b.bits[i] = tempbits[i];
		}
		delete[] tempbits;
		int temp;
		temp = this->countbits;
		this->countbits = b.countbits;
		b.countbits = temp;
		temp = this->countint;
		this->countint = b.countint;
		b.countint = temp;
	}
	BitArray& operator=(const BitArray& b)
	{
		if (this->sizeint > 0)
		{
			delete[] this->bits;
		}
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
	//Изменяет размер массива. В случае расширения, новые элементы 
	//инициализируются значением value.
	void resize(int num_bits, bool value = false)
	{
		if (num_bits <= this->countbits)
		{
			this->countbits = num_bits;
			this->countint = num_bits / 32;
			if (num_bits % 32)
			{
				this->countint++;
			}
		}
		if (num_bits > this->countbits && num_bits <= this->sizeint * 32)
		{
			for (int i = this->countint; i < num_bits / 32; i++)
			{
				if (value)
				{
					this->bits[i] = UINT32_MAX;
				}
				else
				{
					this->bits[i] = 0;
				}
			}
			this->countbits = num_bits;
			this->countint = num_bits / 32;
			if (num_bits % 32)
			{
				this->countint++;
			}
		}
		if (num_bits>this->sizeint*32)
		{
			this->sizeint = num_bits / 32;
			if (num_bits % 32)
			{
				this->sizeint++;
			}
			unsigned int* temp = new unsigned int[this->sizeint];
			for (int i = 0; i < this->countint; i++)
			{
				temp[i] = this->bits[i];
			}
			for (int i = this->countint; i < num_bits / 32; i++)
			{
				if (value)
				{
					temp[i] = UINT32_MAX;
				}
				else
				{
					temp[i] = 0;
				}
			}
			this->countbits = num_bits;
			this->countint = this->sizeint;
			this->bits = new unsigned int[this->sizeint];
			for (int i = 0; i < this->countint; i++)
			{
				this->bits[i] = temp[i];
			}
			delete[] temp;
		}
	}
	//Очищает массив.
	void clear()
	{
		for (int i = 0; i < this->countint; i++)
		{
			this->bits = 0;
		}
		this->countint = 0;
		this->countbits = 0;
	}
	//Добавляет новый бит в конец массива. В случае необходимости 
	//происходит перераспределение памяти.
	void push_back(bool bit)
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
				this->sizeint = this->sizeint + 32;
				delete[] this->bits;
				this->bits = new unsigned int[this->sizeint];
				for (int i = 0; i < countint; i++)
				{
					this->bits[i] = temp[i];
				}
			}
			countint++;
		}
		this->countbits++;
		if (bit)
		{
			this->bits[this->countint-1] = this->bits[this->countint-1] | (1 <<this->countbits%32);
		}
		else
		{
			this->bits[this->countint-1] = this->bits[this->countint-1] & (~(1 << this->countbits%32));
		}
	}
	//Битовые операции над массивами.
	//Работают только на массивах одинакового размера.
	//Обоснование реакции на параметр неверного размера входит в задачу.
	BitArray& operator&=(const BitArray& b)
	{
		if (this->countbits == b.countbits)
		{
			for (int i = 0; i < this->countint-1; i++)
			{
				this->bits[i] = this->bits[i] & b.bits[i];
			}
			if (this->countbits % 32 > 0)
			{
				for (int j = 0; j < this->countbits % 32; j++)
				{
					this->bits[this->countint - 1] = (this->bits[this->countint - 1] & b.bits[b.countint - 1]) & (1 << (31 - j));
				}
			}
			if (this->countbits % 32 == 0 && this->countbits > 0)
			{
				this->bits[this->countint - 1] = this->bits[this->countint - 1] & b.bits[this->countint - 1];
			}
		}
		else
		{
			perror("bit arrays of different sizes");
		}
		return *this;
	}
	BitArray& operator|=(const BitArray& b)
	{
		if (this->countbits == b.countbits)
		{
			for (int i = 0; i < this->countint-1; i++)
			{
				this->bits[i] = this->bits[i] | b.bits[i];
			}
			if (this->countbits % 32 > 0)
			{
				for (int j = 0; j < this->countbits % 32; j++)
				{
					this->bits[this->countint - 1] = (this->bits[this->countint - 1] | b.bits[b.countint - 1]) & (1 << (31 - j));
				}
			}
			if (this->countbits % 32 == 0 && this->countbits > 0)
			{
				this->bits[this->countint - 1] = this->bits[this->countint - 1] | b.bits[this->countint - 1];
			}
		}
		else
		{
			perror("bit arrays of different sizes");
		}
		return *this;
	}
	BitArray& operator^=(const BitArray& b)
	{
		if (this->countbits == b.countbits)
		{
			for (int i = 0; i < this->countint-1; i++)
			{
				this->bits[i] = this->bits[i] ^ b.bits[i];
			}
			if (this->countbits % 32 > 0)
			{
				for (int j = 0; j < this->countbits%32; j++)
				{
					this->bits[this->countint - 1] = (this->bits[this->countint - 1] ^ b.bits[b.countint - 1]) & (1 << (31 - j));
				}
			}
			if (this->countbits % 32 == 0 && this->countbits > 0)
			{
				this->bits[this->countint - 1] = this->bits[this->countint - 1] ^ b.bits[this->countint - 1];
			}
		}
		else
		{
			perror("bit arrays of different sizes");
		}
		return *this;
	}
	//Битовый сдвиг с заполнением нулями.
	BitArray& operator<<=(int n)
	{
		unsigned int* tablenumbers1 = new unsigned int[32];
		unsigned int* tablenumbers2 = new unsigned int[32];
		tablenumbers1[0] = UINT32_MAX;
		tablenumbers2[31] = UINT32_MAX;
		for (int i = 1; i < 32; i++)
		{
			tablenumbers1[i] = tablenumbers1[i - 1] ^ (1 << (32 - i));
		}
		for (int i = 30; i >= 0; i--)
		{
			tablenumbers2[i] = tablenumbers2[i + 1] ^ (1 << (30 - i));
		}
		BitArray b;
		b.countbits = this->countbits;
		b.countint = this->countint;
		b.sizeint = b.countint;
		b.bits = new unsigned int[b.sizeint];
		for (int i = 0; i < this->countint - n / 32; i++)
		{
			b.bits[i] = (this->bits[i + n / 32] & tablenumbers1[n % 32]) << (n % 32);
			b.bits[i] = b.bits[i] | ((this->bits[i + n / 32 + 1] & tablenumbers2[n % 32]) << (n % 32));
		}
		for (int j = 0; j < n % 32; j++)
		{
			b.bits[this->countint - n / 32-1] = b.bits[this->countint - n / 32-1] & (~(1 << j));
		}
		for (int i = this->countint - n / 32; i < this->countint; i++)
		{
			b.bits[i] = 0;
		}
		*this = b;
		delete[] tablenumbers1;
		delete[] tablenumbers2;
		return *this;
	}
	BitArray& operator>>=(int n)
	{
		unsigned int* tablenumbers1 = new unsigned int[32];
		unsigned int* tablenumbers2 = new unsigned int[32];
		tablenumbers1[0] = UINT32_MAX;
		tablenumbers2[31] = UINT32_MAX;
		for (int i = 1; i < 32; i++)
		{
			tablenumbers1[i] = tablenumbers1[i - 1] ^ (1 << (32 - i));
		}
		for (int i = 30; i >= 0; i--)
		{
			tablenumbers2[i] = tablenumbers2[i + 1] ^ (1 << (30 - i));
		}
		BitArray b;
		b.countbits = this->countbits;
		b.countint = this->countint;
		b.sizeint = b.countint;
		b.bits = new unsigned int[b.sizeint];
		for (int i = this->countint-1; i>=n/32; i--)
		{
			b.bits[i] = (this->bits[i-n/32] & tablenumbers1[n % 32]) >> (n % 32);
			b.bits[i] = b.bits[i] | ((this->bits[i - n / 32] & tablenumbers2[n % 32]) >> (n % 32));
		}
		for (int j = 0; j < n % 32; j++)
		{
			b.bits[n/32] = b.bits[n/32] & (~(1 >> (31-j)));
		}
		for (int i = n/32-1; i>=0; i--)
		{
			b.bits[i] = 0;
		}
		*this=b;
		delete[] tablenumbers1;
		delete[] tablenumbers2;
		return *this;
	}
	BitArray operator<<(int n) const
	{
		unsigned int* tablenumbers1 = new unsigned int[32];
		unsigned int* tablenumbers2 = new unsigned int[32];
		tablenumbers1[0] = UINT32_MAX;
		tablenumbers2[31] = UINT32_MAX;
		for (int i = 1; i < 32; i++)
		{
			tablenumbers1[i] = tablenumbers1[i - 1] ^ (1 << (32-i));
		}
		for (int i = 30; i >= 0; i--)
		{
			tablenumbers2[i] = tablenumbers2[i + 1] ^ (1 << (30 - i));
		}
		BitArray b;
		b.countbits = this->countbits;
		b.countint = this->countint;
		b.sizeint = b.countint;
		b.bits = new unsigned int[b.sizeint];
		for (int i = 0; i < this->countint-n/32; i++)
		{
			b.bits[i] = (this->bits[i + n / 32]&tablenumbers1[n%32])<<(n%32);
			b.bits[i] = b.bits[i] | ((this->bits[i + n / 32 + 1] & tablenumbers2[n % 32]) << (n % 32));
		}
		for (int j =0; j<n%32; j++) 
		{
			b.bits[this->countint - n / 32-1] = b.bits[this->countint-n/32-1] & (~(1 << j));
		}
		for (int i = this->countint - n / 32; i<this->countint; i++)
		{
			b.bits[i] = 0;
		}
		delete[] tablenumbers1;
		delete[] tablenumbers2;
		return b;
	}
	BitArray operator>>(int n) const
	{
		unsigned int* tablenumbers1 = new unsigned int[32];
		unsigned int* tablenumbers2 = new unsigned int[32];
		tablenumbers1[0] = UINT32_MAX;
		tablenumbers2[31] = UINT32_MAX;
		for (int i = 1; i < 32; i++)
		{
			tablenumbers1[i] = tablenumbers1[i - 1] ^ (1 << (32 - i));
		}
		for (int i = 30; i >= 0; i--)
		{
			tablenumbers2[i] = tablenumbers2[i + 1] ^ (1 << (30 - i));
		}
		BitArray b;
		b.countbits = this->countbits;
		b.countint = this->countint;
		b.sizeint = b.countint;
		b.bits = new unsigned int[b.sizeint];
		for (int i =this->countint-1; i>n/32; i--)
		{
			b.bits[i] = (this->bits[i - n / 32] & tablenumbers1[n % 32]) >> (n % 32);
			b.bits[i] = b.bits[i] | ((this->bits[i - n / 32] & tablenumbers2[n % 32]) >> (n % 32));
		}
		for (int j = 0; j < n % 32; j++)
		{
			b.bits[n/32] = b.bits[n/32] & (~(1 >> (31-j)));
		}
		for (int i = n / 32-1; i>=0; i--)
		{
			b.bits[i] = 0;
		}
		delete[] tablenumbers1;
		delete[] tablenumbers2;
		return b;
	}
	//Устанавливает бит с индексом n в значение val.
	BitArray& set(int n, bool val = true)
	{
		if (val)
		{
			this->bits[n / 32] = this->bits[n / 32] | (1 << (31-(n % 32)));
		}
		else
		{
			this->bits[n / 32] = this->bits[n / 32] & (~(1 << (31-(n % 32))));
		}
		return *this;
	}
	//Заполняет массив истиной.
	BitArray& set()
	{
		for (int i = 0; i < this->countint - 1; i++)
		{
			this->bits[i] = UINT32_MAX;
		}
		if (this->countbits % 32 > 0)
		{
			for (int j = 0; j < this->countbits % 32; j++)
			{
				this->bits[this->countint - 1] = this->bits[this->countint - 1] | (1 << (31 - j));
			}
		}
		if (this->countbits % 32 == 0 && this->countbits > 0)
		{
			this->bits[this->countint - 1] = UINT32_MAX;
		}
		return *this;
	}
	//Устанавливает бит с индексом n в значение false.
	BitArray& reset(int n)
	{
		this->bits[n / 32] = this->bits[n / 32] & (~(1 << (31-(n % 32))));
		return *this;
	}
	//Заполняет массив ложью.
	BitArray& reset()
	{
		for (int i = 0; i < this->countint-1; i++)
		{
			this->bits[i] = 0;
		}
		if (this->countbits % 32 > 0)
		{
			for (int j = 0; j < this->countbits % 32; j++)
			{
				this->bits[this->countint - 1] = this->bits[this->countint - 1] & (~(1 << (31 - j)));
			}
		}
		if (this->countbits % 32 == 0 && this->countbits > 0)
		{
			this->bits[this->countint - 1] = 0;
		}
		return *this;
	}
	//true, если массив содержит истинный бит.
	bool any() const
	{
		for (int i = 0; i < this->countint-1; i++)
		{
			if (this->bits[i] > 0)
			{
				return true;
			}
		}
		if (this->countbits % 32 > 0)
		{
			for (int j = 0; j < this->countbits % 32; j++)
			{
				if (this->bits[this->countint - 1] & (1 << (31 - j)))
				{
					return true;
				}
			}
		}
		if (this->countbits % 32 == 0 && this->countbits > 0)
		{
			if (this->bits[this->countint - 1] > 0)
			{
				return true;
			}
		}
		return false;
	}
	//true, если все биты массива ложны.
	bool none() const
	{
		for (int i = 0; i < this->countint-1; i++)
		{
			if (this->bits[i] > 0)
			{
				return false;
			}
		}
		if (this->countbits % 32 > 0)
		{
			for (int j = 0; j < this->countbits % 32; j++)
			{
				if (this->bits[this->countint - 1] & (1 << (31 - j)))
				{
					return false;
				}
			}
		}
		if (this->countbits % 32 == 0 && this->countbits > 0)
		{
			if (this->bits[this->countint - 1] > 0)
			{
				return false;
			}
		}
		return true;
	}
	//Битовая инверсия
	BitArray operator~() const
	{
		BitArray b;
		b.countint = this->countint;
		b.countbits = this->countbits;
		b.sizeint = this->sizeint;
		b.bits = new unsigned int[b.sizeint];
		for (int i = 0; i < this->countint-1; i++)
		{
			b.bits[i] = ~this->bits[i];
		}
		if (this->countbits%32>0)
		{
			for (int j = 0; j < this->countbits % 32; j++)
			{
				if (this->bits[this->countint - 1] & (1 << (31 - j)))
				{
					b.bits[this->countint - 1] = b.bits[this->countint - 1] & (~(1 << (31 - j)));
				}
				else
				{
					b.bits[this->countint - 1] = b.bits[this->countint - 1] | (1 << (31 - j));
				}
			}
		}
		if (this->countbits % 32 == 0 && this->countbits > 0)
		{
			b.bits[this->countint - 1] = ~this->bits[this->countint - 1];
		}
		return b;
	}
	//Подсчитывает количество единичных бит.
	int count() const
	{
		int count = 0;
		for (int i = 0; i < this->countint-1; i++)
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
			for (int j = 0; j < this->countbits%32; j++)
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
	//Возвращает значение бита по индексу i.
	bool operator[](int i) const
	{
		if (i > this->countbits-1 || i < 0)
		{
			perror("wrong index");
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
	int size() const
	{
		return this->countbits;
	}
	bool empty() const
	{
		if (this->countbits==0)
		{
			return true;
		}
		return false;
	}
	//Возвращает строковое представление массива.
	std::string to_string() const
	{
		std::string str;
		for (int i = 0; i < this->countint-1; i++)
		{
			for (int j = 31; j>=0; j--)
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
		if (this->countbits % 32>0)
		{
			for (int j = 0; j < this->countbits%32; j++)
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
		if (this->countbits%32==0 && this->countbits>0)
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
};
bool operator==(const BitArray& a, const BitArray& b)
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
bool operator!=(const BitArray& a, const BitArray& b)
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
		perror("bit arrays of different sizes");
	}
	return b;
}
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
		perror("bit arrays of different sizes");
	}
	return b;
}
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
		perror("bit arrays of different sizes");;
	}
	return b;
}

int main()
{
	using namespace std;
	string str;
	string str2;
	BitArray b(32, UINT32_MAX);
	bool a = b.any();
	cout << a << '\n';
	b = ~b;
	str = b.to_string();
	cout << str << '\n';
	bool n = b.none();
	cout << n << '\n';
	BitArray b2(b);
	b ^= b2;
	bool e = b.empty();
	cout << e << '\n';
	b.set();
	str = b.to_string();
	cout << str << '\n';
	int c = b.count();
	cout << c << '\n';
	b.reset();
	str = b.to_string();
	cout << str << '\n';
	b.resize(64, true);
	str = b.to_string();
	cout << str << '\n';
	b>>=1;
	str = b.to_string();
	cout << str << '\n';
	b.push_back(false);
	str = b.to_string();
	cout << str << '\n';
	b.swap(b2);
	str = b.to_string();
	str2 = b2.to_string();
	cout << "swap"<<"\n";
	cout << str << '\n';
	cout << str2 << '\n';
	b2.set(1, true);
	str2 = b2.to_string();
	cout << str2 << '\n';
	b2.reset(60);
	str2 = b2.to_string();
	cout << str2 << '\n';;
	cout << "new op\n";
	int s = b2.size();
	b.resize(s, true);
	BitArray b3;
	b3 = b & b2;
	string str3;
	str3 = b3.to_string();
	cout << str3 << "\n";
	BitArray b4(b3);
	b4 = ~b4;
	string str4 = b4.to_string();
	cout << str4 << "\n";
	b |= b4;
	str = b.to_string();
	cout << str << "\n";
	b = b ^ b2;
	str = b.to_string();
	cout << str << "\n";
	b = b & b3;
	str = b.to_string();
	cout << str << "\n";
	b = b3 | b4;
	str = b.to_string();
	cout << str << "\n";
	bool eq = b == b;
	cout << eq << "\n";
	eq = b == b2;
	cout << eq << "\n";
	bool el = b[3];
	cout << el << "\n";
	str = b.to_string();
	cout << str << "\n";
	b.clear();
	b3 >>= 4;
	b2 = b3 << 3;
	return 0;
}