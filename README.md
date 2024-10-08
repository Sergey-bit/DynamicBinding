# Содержание проекта
**main.cpp** - исолнительный файл с функцией main.</br>
**classes.hpp** - заголовочный файл с классами необходимыми для тестирования.</br>
**meta.hpp** - заголовочный файл с пространством имен Meta. Реализуется все важные структуры и using'и.</br>

# Описание файла main.cpp
Данный исполнительный файл содержит в себе функцию main

# Описание файла classes.hpp

## ClassWrapper
Все классы содержатся в структуре **ClassWrapper**. Объединяет все классы которые способны приводиться к друг другу. Имеет один template параметр: **int N**.
Он отвечает за то, каким изначально являлся тип до всяких cast'ов. Задается при объявлении переменной любого из классов. При касте в типе, к которому приводится экземпляр класса 
, значение N должно соответствовать значению N кастуемого экземпляра.

## family_tree `n lvl
**family_tree** представляет собой всю линию наследования. На данный момент задает только линию(не дерево). То есть наследование может быть только последовательным
и каждый класс может наследоваться только от одного другого</br></br>
**lvl** обозначает глубину family_tree. Другими словами размер списка типов family_tree.

## Структура классов
**lvli** - уровень на котором находится данный класс внезависимости от того, применялся к нему каст или нет</br>
Объявление **struct methodsReview** из пространства имен Meta::Core другом класса</br></br>
**t** - тип, к которому будет приводится класс в случае каста.</br></br>
**methods** - using declarations, которое представляет собой статический массив объявлений методов. Используются объявления для однозначного определения метода.</br></br>
**converse** - метод вызываемый перед вызованием любого метода. Кастует один класс в класс t (см. выше).</br></br>
**operator T()** - необходим для возможности преобразования типов родственников между собой. Представляет собой 2 метода. на первом стоит ограничение,
что тип к которому будет приводится экземпляр класса, являлся изначальным типом, либо его родителем. Второй обрабатывает остальные касты, которые не соответствуют условию для первого. Он ничего не возвращает так как
делает **Throw** ошибки.</br></br>
Дальше идут методы класса, которые определяются разработчким. Создаются в двух типах. 
> - первый представляет собой **имплементацию самого метода**, каким задумал его разраюотчик. Может вызываться только вторым типом
> - второй - **его wrapper**. Он кастует тип к тому, который необходим. То есть совершает динамическое связывание. Может вызываться кем-угодно.

# Описание файла meta.hpp
Реализация основной логики происходит в данном файле. Он состоит из пространства имен **Meta** (Metaprogramming), который делится на 4 других пространства имен: **Array**, **Logic**, **MeList** и **Core**.

## Пространство имен Meta::Array
Содержит логику, реализующую статический массив из строк размером 100 (тип aliased as atype) и методы необходимые для его управления: getSize, и т.к.

## Пространство имен Meta::Logic
Содержит все логические структуры, такие как True, False, or_Function, equalityI, и т.п. Также данное пространство имен содержит Ifs_array.</br></br>
**Ifs_array** реализуют логику If. Содержит 3 значние template: bool value, atype THEN, atype ELSE. Если value - true, тогда данная структура возвращает THEN, в противном случае ELSE.

## Пространство имен Meta::MeList
Данное пространство реализуют структуру данных для хранения массива типов и структуры для ее управлением.

## Пространство имен Meta::Core
Данное пространнство имен реализуют все необходимое для вывода типов.
> - Profile. Содержит тип, а также его индекс в линии наследования family_tree (индексы начинаются с 1)
> - rmpt (remove pointer type) - структура для избавления указателя в типе. Реализуются с помощью структур rmp. (**deprecated**)
> - Convertable - структура для проверки возможности каста типа A в тип B. (**deprecated**)
> - fullInheritance - структура для определения family_tree. Возвращает полную иерархическую линию, которая должна храниться в family_tree. (**deprecated**)
> - methodsReview - структура, котора опредляет если переданный тип содержит в с своем methods метод с переданным в него именем.
> - getRType (getRightType) - структура, возвращающий тип, к которому необходимо привести экземпляр класса. В template параметрах принимает имя метода, индекс в family_tree изначальной типа класса, размер family_tree и сам family_tree, представленный как type_list<T, type_list<...>>

### блок-схема структуры methodsReview
![image](https://github.com/user-attachments/assets/e6710715-7122-4418-a78b-0e89e486e754)

### блок-схема структуры getRType
![image](https://github.com/user-attachments/assets/1a50b907-c499-406f-8f1f-ac072282ae14)
