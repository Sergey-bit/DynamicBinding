#include<iostream>
#include"classes.hpp"

int main(void)
{
    ClassWrapper<2>::B obj1;
    ClassWrapper<1>::A obj2;
    ClassWrapper<3>::C obj3;

    // ((ClassWrapper<1>::C)obj1).f(); // Error. Каст изначального экземпляра класса А в С, где А - базовый класс
    ((ClassWrapper<1>::A)obj1).f(); // Ожидается результат из класс B
    ((ClassWrapper<3>::B)obj3).f(); // Ожидается результат из класс C

    // ((ClassWrapper<2>::A)obj3).u(); // Error. Каст в класс, который не имеет данного метода
    ((ClassWrapper<3>::C)obj3).u(); // Ожидается результат из класс B
    ((ClassWrapper<3>::B)obj3).c(); // Ожидается результат из класс C
    ((ClassWrapper<2>::B)obj1).c(); // Ожидается результат из класс B


    return 0;
}