#ifndef CLASSES
#define CLASSES

using namespace ::Meta;

#include<iostream>
#include<string>
#include"l.hpp"

template<int N, typename T>
struct Class
{
    T l;
    static constexpr int v = N;
};

class A;
class B;
class C;

class A
{
public:
    using type_list = Meta::Core::type_list<A>;

public:
    static constexpr int __TR = Meta::Core::counter_v<type_list>;
    using methods =
        Meta::Array::createArray<
        Meta::Array::atype("f"), Meta::Array::atype("call_f")
        >;
    void call_f() { f(); }
    void f() { std::cout << "Hey from A\n\0"; }

    template<typename T> requires (std::is_base_of_v<T, C> ||
        std::is_base_of_v<C, T>)
    operator T() const
    {
        return T();
    }

private:
    template<typename T, int Index, Meta::Array::atype Name>
    friend struct Meta::Core::methodsReview;
};

class B : public A
{
public:
    using type_list = Meta::Core::type_list<B, typename A::type_list>;

public:
    static constexpr int __TR = Meta::Core::counter_v<type_list>;
    using methods = Meta::Array::createArray<Meta::Array::atype("f")>;

    void f() { std::cout << "Hey from B\n\0"; }

    template<typename T> requires (std::is_base_of_v<T, C> ||
        std::is_base_of_v<C, T>)
    operator T() const
    {
        return T();
    }

private:
    template<typename T, int Index, Meta::Array::atype Name>
    friend struct Meta::Core::methodsReview;
};

class C : public B
{
public:
    using type_list = Meta::Core::type_list<C, typename B::type_list>;

public:
    template<int N, typename T>
    void link(C)
    {

    }
    static constexpr int __TR = Meta::Core::counter_v<type_list>;
    using methods = Meta::Array::createArray<Meta::Array::atype("f")>;
    void f() { std::cout << "Hey from C\n\0"; }

    template<typename T> requires (std::is_base_of_v<T, C> ||
        std::is_base_of_v<C, T>)
    operator T() const
    {
        return T();
    }

private:
    template<typename T, int Index, Meta::Array::atype Name>
    friend struct Meta::Core::methodsReview;
};

using family_tree = typename C::type_list;

#endif