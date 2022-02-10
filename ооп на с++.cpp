#include <iostream>
#include <cstdint>

// Первое задание 
//-------------------------------------------------------------------------------------------

class Power
{
private:
	int a;
	int b;

public:
	Power (int first = 1, int second = 1):
		a (first), b (second)
	{}

	void setVar(int first, int second)
	{
		a = first;
		b = second;
	}

	int calculate()
	{
		int result = 1;
		for (size_t i = 0; i < b; i++)
		{
			result *= a;
		}
		return result;
	}

	void print()
	{
		std::cout << "a:" << a << " b:" << b << " power:" << calculate() << std::endl;
	}
};

//-------------------------------------------------------------------------------------------
//Второе задание
//-------------------------------------------------------------------------------------------

class RGBA
{
private:
	std::uint8_t m_red = 0;
	std::uint8_t m_green = 0;
	std::uint8_t m_blue = 0;
	std::uint8_t m_alpha = 255;
public:
	RGBA ()
	{}

	RGBA(std::uint8_t first, std::uint8_t second, std::uint8_t third, std::uint8_t fourth) :
		m_red ( static_cast <uint16_t> (first)), m_green(static_cast <uint16_t> (second)), m_blue(static_cast <uint16_t> (third)), m_alpha(static_cast <uint16_t> (fourth))
	{}

	void print()
	{
		std::cout << "m_red:" << m_red << " m_green:" << m_green << " m_blue:" << m_blue << " m_alpha:" << m_alpha << std::endl;
	}
};

//-------------------------------------------------------------------------------------------
//Третье задание
//-------------------------------------------------------------------------------------------
class Stack
{
private:

	int m_array[10] = {1,2,3,4,5,6,7,8,9,19};
	int length = 10;

public:
	void reset()
	{
		for (size_t i = 0; i < 10; i++)
		{
			m_array[i] = 0;
		}
		length = 0;
	}

	void push(int a)
	{
		int check = 0;
		for (size_t i = 0; i < 10; i++)
		{
			if (m_array[i] == 0)
			{
				check++;
			}
		}
		if (check == 0)
		{
			std::cout << "Error" << std::endl;
		}
		else if (check > 0)
		{
			for (size_t i = 0; i < 10; i++)
			{
				if (m_array[i] == 0)
				{
					m_array[i] = a;
					length++;
					break;
				}

			}
		}
	}

	void pop()
	{
		int check2 = 0;
		for (size_t i = 0; i < 10; i++)
		{
			if (m_array[i] != 0)
			{
				check2++;
			}
		}

		if (check2 == 0)
		{
			std::cout << "Warning!" << std::endl;
		}

		else if (check2 > 0)
		{
			for (size_t i = 9; i >= 0; i--)
			{
				if (m_array[i] != 0)
				{
					m_array[i] = 0;
					length--;
					break;
				}
			}
		}
	}

	void print()
	{
		std::cout << "( ";
		for (size_t i = 0; i < 10; i++)
		{
			if (m_array[i] != 0)
			std::cout << m_array[i] << " ";
		}
		std::cout << ")" << std::endl;
		std::cout << "length:" << length << std::endl;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	// Первое задание
	std::cout << " Первое задание " << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
	Power stepen;
	stepen.print();
	stepen.setVar(2, 3);
	stepen.calculate();
	stepen.print();
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

	//Второе задание
	std::cout << " Второе задание " << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
	RGBA color;
	color.print();
	color = { 1, 2, 3, 4 };
	color.print();
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

	//Третье задание
	std::cout << " Третье задание " << std::endl;
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;
	Stack stack;
	stack.reset();
	stack.print();

	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();
	stack.print();
	std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

	return 0;
}
