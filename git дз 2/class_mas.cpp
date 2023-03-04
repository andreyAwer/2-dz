#include <limits>
#include <iostream>

template <typename unknown_type>
//почему мы обычно вместо логичного и понятного
//названия типа используем имя 'T'?и не только мы
class List
{
public:
    unknown_type *list_values;
    //будущий массив
    //неизвестный тип будет понятен при создании обьекта

    unsigned long long size;
    //возможность хранить размер массива
    //вне зависимости от его значения

    List(float) = delete;
    List(double) = delete;
    List(long double) = delete;
    List(signed char) = delete;
    List(signed short) = delete;
    List(signed int) = delete;
    List(signed long) = delete;
    List(signed long long) = delete;
    //запрет существования конструктора с signed параметром внутри
    //запрет существования конструктора с нецелочисленным параметром внутри

    List(auto fill_list)
    {
        size = fill_list;
        //сохранение информации о размере массива

        list_values = new unknown_type[fill_list];
        while (fill_list)
        {
            std::cin >> list_values[--fill_list];
        }
    }
    //после проверки того что параметр не является нецелочисленным
    //или что он не может гипотетически быть отрицательным
    //создаётся массив размера параметра

    ~List()
    {
        delete[] list_values;
    }

    unknown_type bigest()
    {
        unknown_type bigest = std::numeric_limits<unknown_type>::min();

        signed long long size_copy = size;
        // size_copy меняет значение
        // size не меняет значение поскольку
        //с его неизменчивым значением работают функции

        while (size_copy)
        {
            bigest = list_values[--size_copy] > bigest ? list_values[size_copy] : bigest;
        }
        return bigest;
    }
    //шаблонная функция

    unknown_type smalest()
    {
        unknown_type smalest = std::numeric_limits<unknown_type>::max();

        unsigned long long size_copy = size;
        // size_copy меняет значение
        // size не меняет значение поскольку
        //с его неизменчивым значением работают функции

        while (size_copy)
        {
            smalest = list_values[--size_copy] < smalest ? list_values[size_copy] : smalest;
        }
        return smalest;
    }
    //шаблонная функция

    void change(unsigned long long element, unknown_type value)
    //неорицательное положительное целочисленное число является элементом массива
    {
        if (element > size)
        {
            return;
        }
        //функция ничего не делает если номер элемента для заполнения больше размера массива

        element -= (bool)element;
        // 0 и 1 приравниваются
        //остальные числа равны самим себе -1
        //можно заполнять элемент самого большого массива,при максимальном значении element
        //с стиль приведения поскольку задание старое

        list_values[element] = value;
    }

    void sort()
    {
        unsigned long long size_copy = size;
        bool swapped;
        unknown_type memory;
        while (size_copy--)
        {
            swapped = false;

            for (int i = 0; i < size_copy; ++i)
            {
                if (list_values[i] > list_values[i + 1])
                {
                    memory = list_values[i];
                    list_values[i] = list_values[i + 1];
                    list_values[i + 1] = memory;
                    swapped = true;
                }
            }

            if (!swapped)
            {
                for (int t = 0; t < size; ++t)
                {
                    std::cout << list_values[t];
                }
                return;
            }
        }
    }
    //сортировка массива

    void binary_find(std::string binary)
    {
        unknown_type value = 0.8;
        //тип должен быть целочисленный

        if (binary.length() > sizeof(unknown_type) * 8 || binary[0] != '1' || value)
        {
            return;
        }
        //если гипотетическое двоичное число-строка больше
        //чем максимальная вместительность unknown_type,
        //если первый знак бинарного числа не равен 1,
        //если unknown_type не целочисленный тип,
        //функция не будет работать

        for (char t = 0; binary[t]; ++t)
        {
            if (binary[t] != '0' && binary[t] != '1')
            {
                return;
            }
            //если в двоичной записи встречается не 0 и не 1
            //функция прекращается

            else if (binary[t] == '0')
            {
                value *= 2;
            }
            else if (binary[t] == '1')
            {
                value *= 2;
                value += 1;
            }
        }

        for (unsigned long long tt = 0; tt < size; ++tt)
        {
            if (list_values[tt] == value)
            {
                std::cout << value << ' ' << tt << ' ';
                //последний пробел для возможности
                //красивого вывода нескольких элементов
            }
        }
    }
};
int main()
{

    List<double> test_object(4u);
    std::cout << test_object.bigest() << ' ';
    std::cout << test_object.smalest() << ' ';
    test_object.change(0ull, 99);
    // 1 и 0 одинаковы
    std::cout << test_object.bigest() << ' ';
    test_object.change(1ull, 5);
    // 1 и 0 одинаковы
    std::cout << test_object.bigest() << ' ';

    test_object.change(2ull, 4);
    std::cout << test_object.bigest() << ' ';

    test_object.change(3ull, 6);
    std::cout << test_object.bigest() << ' ';

    test_object.change(4ull, 7);
    std::cout << test_object.bigest() << ' ';

    test_object.change(5ull, 8);
    //не сработало
    std::cout << test_object.bigest() << ' ';

    // 5 4 6 7 значения массива

    std::cout << '\n';
    test_object.sort();
    std::cout << '\n';

    test_object.binary_find("10");
    //не подходящий тип test_object

    List<unsigned short int> test_object_2(4u);
    test_object_2.binary_find("01");
    //первый символ строки не '1'

    List<unsigned short int> test_object_3(4u);
    test_object_3.binary_find("10000000000000000");
    //тип short не помещается в такое длинное двоичное число

    test_object_3.change(3, 0b10010101ull);
    test_object_3.binary_find("10010101");
}