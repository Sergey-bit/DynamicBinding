#include<iostream>
#include"l.hpp"
#include"classes.hpp"

int main(void)
{
    Class<A::__TR, A> obj1;
    Class<B::__TR, B> obj2;
    Class<C::__TR, C> obj3;

    // name of the method we wanna call
    static constexpr Meta::Array::atype val("f");

    // cast to A
    obj3.l = (A)obj3.l;

    // deduce closest type for executing func "val"
    using t = Meta::Core::getRType<val, obj3.v, family_tree>;

    // casting to the deduced type
    t p = (t)(obj3.l);
    p.f();

    return 0;
}