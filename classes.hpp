#ifndef CLASSES
#define CLASSES

using namespace ::Meta;

#include<iostream>
#include<string>
#include"l.hpp"

// ClassWrapper - класс создающий семейство типа с индентификатором N, способный
// к кастингу к любому типу в иерархии
template<const int N>
struct ClassWrapper
{
    class A;
    class B;
    class C;

    // обозначает класс который последний в наследовании
    using family_tree = Meta::MeList::type_list<
        ClassWrapper<N>::C,
        Meta::MeList::type_list<
            ClassWrapper<N>::B,
            Meta::MeList::type_list<ClassWrapper<N>::A>
        >
    >;
    // Количество элементов в списке
    static constexpr int lvl = Meta::MeList::listSize<family_tree>;

    class A
    {
    public:
        static constexpr int lvli = 1;
        static constexpr int n = N;

    private:
        template<typename T, int Index, Meta::Array::atype Name>
        friend struct Meta::Core::methodsReview;
        using methods =
            typename Meta::Array::createArray<
                Meta::Array::atype("void f()"),
                Meta::Array::atype("void call_f()")
            >;

        template<int Index>
        using t = Meta::Core::getRType<
            Meta::Array::val_at<Index, methods>,
            N,
            ClassWrapper<N>::lvl,
            A::lvli,
            ClassWrapper<N>::family_tree
        >;
        template<int Index>
        t<Index> converse()
        {
            return (t<Index>)(*this);
        }

    public:
        // true implementation
        void call_f_() { f(); }
        void f_() { std::cout << "Hey from A\n\0"; }

        // method wrappers
        void call_f()
        {
            converse<1>().call_f_();
        }
        void f()
        {
            converse<0>().f_();
        }

        template<typename T>
        requires (T::lvli <= N)
        operator T() const
        {
            return T();
        }

        template<typename T>
        requires (T::lvli > N)
        operator T() const
        {
            throw std::exception::exception("not a base class of A");
        }
    };

    class B : public ClassWrapper<N>::A
    {
    public:
        static constexpr int lvli = ClassWrapper<N>::A::lvli + 1;

    private:
        template<typename T, int Index, Meta::Array::atype Name>
        friend struct Meta::Core::methodsReview;
        using methods =
            typename Meta::Array::createArray<
                Meta::Array::atype("void f()"),
                Meta::Array::atype("void c()"),
                Meta::Array::atype("void u()")
            >;

        template<int Index>
        using t = Meta::Core::getRType<
            Meta::Array::val_at<Index, methods>,
            N,
            ClassWrapper<N>::lvl,
            B::lvli,
            ClassWrapper<N>::family_tree
        >;
        template<int Index>
        t<Index> converse()
        {
            return (t<Index>)(*this);
        }

    public:
        // true implementation
        void u_() { std::cout << "unique method from B\n\0"; }
        void c_() { std::cout << "hey from B.c\n\0"; }
        void f_() { std::cout << "Hey from B\n\0"; }

        void c()
        {
            converse<1>().c_();
        }
        void u()
        {
            converse<2>().u_();
        }

        template<typename T>
        requires (T::lvli <= N)
        operator T() const
        {
            return T();
        }

        template<typename T>
        requires (T::lvli > N)
        operator T() const
        {
            throw std::exception::exception("not a base class of B");
        }
    };

    class C : public ClassWrapper<N>::B
    {
    public:
        static constexpr int lvli = ClassWrapper<N>::B::lvli + 1;
    private:
        template<typename T, int Index, Meta::Array::atype Name>
        friend struct Meta::Core::methodsReview;
        using methods =
            typename Meta::Array::createArray<
                Meta::Array::atype("void f()"),
                Meta::Array::atype("void c()")
            >;

        template<int Index>
        using t = Meta::Core::getRType<
            Meta::Array::val_at<Index, methods>,
            N,
            ClassWrapper<N>::lvl,
            C::lvli,
            ClassWrapper<N>::family_tree
        >;

        template<int Index>
        t<Index> converse()
        {
            return (t<Index>)(*this);
        }


    public:
        // true implementation
        void f_() { std::cout << "Hey from C\n\0"; }
        void c_() { std::cout << "hey from C.c\n\0"; }

        template<typename T>
        requires (T::lvli <= N)
        operator T() const
        {
            return T();
        }

        template<typename T>
        requires (T::lvli > N)
        operator T() const
        {
            throw std::exception::exception("not a base class of C");
        }
    };
};


#endif