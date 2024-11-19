#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <functional>

class DArray;

DArray task_only_odd(const DArray& DA);

class DArray
{
private:
    size_t size, max_size;
    int* array;
    void destroy() { if (array) delete[] array; array = nullptr; size = 0; }
    static inline size_t counter{};
    size_t number{};
    friend void change(DArray& arr, std::function<void(int&)> action);
    friend std::ostream& operator << (std::ostream& stream, const DArray& arr);

public:
    DArray() {}
    DArray(size_t max_size);
    DArray(size_t max_size, size_t size, int A, int B);
    DArray(size_t max_size, std::istream& stream);
    //--------------------------------------------------------------------
    DArray(const DArray& other);
    DArray& operator=(const DArray& other);
    DArray(DArray&& tmp);
    DArray& operator=(DArray&& tmp);
    //--------------------------------------------------------------------

    std::string to_string() const;

    void print(std::ostream& stream = std::cout) const;
    void set_size(size_t size)
    {
        this->size = size;
    }
    int get_elem(size_t index) const;
    void set_elem(size_t index, int elem) const;
    size_t get_size()const { return size; }
    size_t get_max_size() const { return max_size; }
    size_t get_number() const { return number; }
    ~DArray() { destroy(); }
    static void print_count()
    {
        std::cout << "Created " << counter << " objects \n";
    }
    DArray operator +(const DArray& arr) const;
    int operator [] (size_t index) const;
    bool operator()() const
    {
        bool result{ true };
        size_t i{};
        while (i < size - 1 && result)
            if (array[i] * array[i + 1] < 0)
                ++i;
            else
                result = false;
        return result;
    }
    DArray& operator () (std::function<void(int&)>);

};


int main()
{
    DArray DA1(100, 10,-100,100);
    DA1.print();
    

    DArray DA_2 = DA1;
    DA_2.print();

    DArray DA_3(7);
    DA_3 = DA1;
    DA_3.print();

    DArray DA_odd = task_only_odd(DA1);
    DA_odd.print();

    DA_3 = task_only_odd(DA1);


    DArray::print_count();

}

DArray task_only_odd(const DArray& DA)
{
    size_t cnt{}, size = DA.get_size();
    DArray result(DA.get_max_size());
    for (size_t i{}; i < size; ++i)
    {
        int x = DA.get_elem(i);
        if (x % 2)
        {
            result.set_elem(cnt, x);
            ++cnt;
        }
    }
    result.set_size(cnt);
    return result;
}

DArray::DArray(size_t max_size)
{
    array = new int[max_size];
    number = ++counter;
}

DArray::DArray(size_t max_size, size_t size, int A, int B)
{
    srand(GetTickCount());
    array = new int[max_size];
    this->size = size < max_size ? size : max_size;
    for (size_t i{}; i < this->size; ++i)
        array[i] = A + rand() % (B - A);
    number = ++counter;

}

DArray::DArray(size_t max_size, std::istream& stream)
{
    array = new int[max_size];
    stream >> size;
    for (size_t i{}; i < size; ++i)
        stream >> array[i];
    number = ++counter;

}

DArray::DArray(const DArray& other) : max_size(other.max_size), size(other.size)
{
    std::cout << "Copy constructor\n";
    array = new int[max_size];
    for (size_t i{}; i < size; ++i)
    {
        array[i] = other.array[i];
    }
    number = ++counter;
}

DArray& DArray::operator=(const DArray& other)
{
    if (this != &other)
    {
        std::cout << "Copy operator (assigment) \n";
        destroy();
        max_size = other.max_size;
        size = other.size;
        array = new int[max_size];
        for (size_t i{}; i < size; ++i)
        {
            array[i] = other.array[i];
        }
        number = ++counter;
    }
    return *this;
}

DArray::DArray(DArray&& tmp) : max_size(tmp.max_size), size(tmp.size), array(tmp.array), number(tmp.number)
{
    std::cout << "Move constructot\n";
    tmp.array = nullptr;
}

DArray& DArray::operator=(DArray&& tmp)
{
    if (this != &tmp)
    {
        std::cout << "Move operator (assigment)\n";
        destroy();
        max_size = tmp.max_size;
        size = tmp.size;
        array = tmp.array;
        number = tmp.number;
        tmp.array = nullptr;
    }
    return *this;
}

std::string DArray::to_string() const
{
    std::string result = "";
    if (!array)
        result = "Array is empty";
    else
    {
        for (size_t i{}; i < size; ++i)
            result += std::to_string(array[i]) + ' ';
    }
    return result;
}

void DArray::print(std::ostream& stream) const
{
    stream << to_string() << '\n';
}

int DArray::get_elem(size_t index) const
{
    int result{};
    if (index >= 0 && index < size)
        result = array[index];

    return result;
}

void DArray::set_elem(size_t index, int elem) const
{
    
    if (index >= 0 && index < size)
        array[index] = elem;
}

DArray DArray::operator+(const DArray& arr) const
{
    DArray result(max_size);
    size_t size_arr{ arr.get_size() };
    size_t size_result = size < size_arr ? size: size_arr;
    result.set_size(size_result);
    for (size_t i{}; i < size_result; ++i)
    {
        result.array[i] = array[i] + arr.array[i];
    }
    return result;
}

int DArray::operator[](size_t index) const
{
    int result{};
    if (index >= 0 && index < size)
        result = array[index];
    return result;
}

DArray& DArray::operator()(std::function<void(int&)>action)
{
    for (size_t i{}; i < size; ++i)
        action(array[i]);
    return *this;
}

void change(DArray& arr, std::function<void(int&)> action)
{
    for (size_t i{}; i < arr.get_size(); ++i)
    {
        action(arr.array[i]);
    }
}

std::ostream& operator << (std::ostream& stream, const DArray& arr) {
    return stream;
}


DArray operator+(const DArray& arr1, const DArray& arr2)
{
    DArray result(arr1.get_max_size());
    size_t size_arr1{ arr1.get_size() }, size_arr2{ arr2.get_size() };
    size_t size_result = size_arr1 < size_arr2 ? size_arr1 : size_arr2;
    result.set_size(size_result);
    for (size_t i{}; i < size_result; ++i)
    {
        result.set_elem( i, arr1.get_elem(i) + arr2.get_elem(i));
    }
    return result;
}