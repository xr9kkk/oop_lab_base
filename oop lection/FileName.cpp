#include <iostream>
#include <fstream>
#include <functional>
#include <string>


class DArray
{
private:
	size_t size;
	int* array;
public:
	std::string to_string() const;
	void print(std::ostream& stream = std::cout) const;
	void set_size(size_t size);
};

int main()
{
	DArray arr;
	arr.print();
	setlocale(LC_ALL, "ru");
}

std::string DArray::to_string() const
{
	std::string result { " " };
	if (!array)
		result = "Array is empty!";
	else
	{
		for (size_t i{}; i < size; ++i)
		{
			result += std::to_string(array[i]) + ' ';
		}
	}
	return std::string();
}

void DArray::print(std::ostream& stream) const
{
	stream << to_string() << '\n';
}

void DArray::set_size(size_t size)
{
	this->size = size;
}
