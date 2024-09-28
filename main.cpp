#include<iostream>
#include"classes.hpp"

int main(void)
{
    ClassWrapper<2>::B obj1;
    ClassWrapper<1>::A obj2;
    ClassWrapper<3>::C obj3;

    // ((ClassWrapper<1>::C)obj1).f(); // Error. ���� ������������ ���������� ������ � � �, ��� � - ������� �����
    ((ClassWrapper<1>::A)obj1).f(); // ��������� ��������� �� ����� B
    ((ClassWrapper<3>::B)obj3).f(); // ��������� ��������� �� ����� C

    // ((ClassWrapper<2>::A)obj3).u(); // Error. ���� � �����, ������� �� ����� ������� ������
    ((ClassWrapper<3>::C)obj3).u(); // ��������� ��������� �� ����� B
    ((ClassWrapper<3>::B)obj3).c(); // ��������� ��������� �� ����� C
    ((ClassWrapper<2>::B)obj1).c(); // ��������� ��������� �� ����� B


    return 0;
}