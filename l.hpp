#ifndef META
#define META

#include<exception>
#include<array>

namespace Meta
{
	namespace Array
	{
		using atype = std::array<char, 100>;
		static constexpr atype errval("");
	}
	namespace Logic
	{

	}
	namespace MeList
	{
		template<typename...>
		struct type_list { };

		using empty_list = typename type_list<>;

		template<typename List>
		struct counter
		{
			static constexpr int c = 1;
		};

		template<typename First, typename... Rest>
		struct counter<type_list<First, type_list<Rest...>>>
		{
			static constexpr int c = counter<type_list<Rest...>>::c + 1;
		};

		template<typename List, typename List1>
		struct either
		{
			using type = List;
		};

		template<typename List2>
		struct either<empty_list, List2>
		{
			using type = List2;
		};

		template<typename List, typename List2>
		using either_t = typename either<List, List2>::type;

		template<typename List>
		static constexpr int counter_v = counter<List>::c;

		template<typename list>
		struct list_size
		{
			static constexpr int s = 1;
		};

		template<typename T, typename... Rest>
		struct list_size<type_list<T, Rest...>>
		{
			static constexpr int s = 1 + list_size<type_list<Rest...>>::s;
		};

		template<typename T>
		static constexpr int listSize = list_size<T>::s;
	}
	namespace Core 
	{

		template<int N, typename LIST>
		struct profile
		{
			const int val = N;
			using type = LIST;
		};
	}

	namespace Logic
	{
		struct True
		{
			static constexpr bool hit = true;
		};

		struct False
		{
			static constexpr bool hit = false;
		};

		template<char a, char b>
		struct equalityC
		{
			static constexpr bool hit = false;
		};

		template<char a>
		struct equalityC<a, a>
		{
			static constexpr bool hit = true;
		};

		template<int a, int b>
		struct equalityI
		{
			static constexpr bool hit = false;
		};

		template<int a>
		struct equalityI<a, a>
		{
			static constexpr bool hit = true;
		};

		template<int Ind>
		concept includable = Ind < 31;

		template<Array::atype a, Array::atype b>
		struct equalityA
		{
			static constexpr bool hit = false;
		};

		template<Array::atype a>
		struct equalityA<a, a>
		{
			static constexpr bool hit = true;
		};

		template<bool a, bool b>
		struct orFunction
		{
			static constexpr bool val = true;
		};

		template<>
		struct orFunction<false, false>
		{
			static constexpr bool val = false;
		};
	
		template<bool True, typename THEN, typename ELSE>
		struct If_
		{
			using p = THEN;
		};

		template<typename THEN, typename ELSE>
		struct If_<false, THEN, ELSE>
		{
			using p = ELSE;
		};

		template<bool VALUE, typename THEN, typename ELSE>
		using If_t = typename If_<VALUE, THEN, ELSE>::p;

		template<bool True, Array::atype THEN, Array::atype ELSE>
		struct Ifs_
		{
			static constexpr Array::atype p = THEN;
		};

		template<Array::atype THEN, Array::atype ELSE>
		struct Ifs_<false, THEN, ELSE>
		{
			static constexpr Array::atype p = ELSE;
		};

		template<bool VALUE, Array::atype THEN, Array::atype ELSE>
		static constexpr Array::atype Ifs_array = Ifs_<VALUE, THEN, ELSE>::p;
	}
	namespace Array
	{
		template<atype name>
		struct element
		{
			static constexpr atype val = name;
		};

		template<class...>
		struct array {};

		using ertype = element<errval>;

		template<class Element>
		struct isErtype_
		{
			static constexpr bool hit = false;
		};

		template<>
		struct isErtype_<ertype>
		{
			static constexpr bool hit = true;
		};

		template<typename T>
		static constexpr bool IsErt = isErtype_<T>::hit;

		template<int N, int Ind, class First>
		struct at
		{
			static constexpr atype val = Logic::Ifs_array<N == Ind, First::val, errval>;
		};

		template<int N, int Ind, class First>
		struct at<N, Ind, array<First>>
		{
			static constexpr atype val = Logic::Ifs_array<N == Ind, First::val, errval>;
		};

		template<int N, int Ind, class First, class... Rest>
		struct at<N, Ind, array<First, Rest...>>
		{
			static constexpr atype val = Logic::Ifs_array<N == Ind, First::val, at<N, Ind + 1, array<Rest...>>::val>;
		};

		template<int N, class... Array>
		static constexpr atype val_at = at<N, 0, Array...>::val;

		template<atype... vals>
		struct fillArray
		{
			using a = array<element<vals>...>;
		};

		template<atype... vals>
		using createArray = fillArray<vals...>::a;

		template<class... Rest>
		struct getSize_
		{
			static constexpr int s = 1;
		};

		template<class T, class... Rest>
		struct getSize_<array<T, Rest...>>
		{
			static constexpr int s = 1 + getSize_<array<Rest...>>::s;
		};

		template<class... Array>
		static constexpr int getSize = getSize_<Array...>::s;
	}
	namespace Core
	{
		inline constexpr bool more(int a, int b)
		{
			return a > b;
		}

		template<typename Ty>
		struct rmp
		{
			using t = Ty;
		};

		template<typename Ty>
		struct rmp<Ty*>
		{
			using t = Ty;
		};

		template<typename Ty>
		using rmpt = typename rmp<Ty>::t;

		template<class Fr, class To>
		concept Convertable =
			requires (rmpt<Fr>*t) { (rmpt<To>*)t; };

		template<typename...>
		struct fullInheritance
		{
			using type_trail = void;
		};

		template<int N1, typename List1, int N2, typename List2, typename... Rest>
		struct fullInheritance<profile<N1, List1>, profile<N2, List2>, Rest...>
		{
			using type_trail = fullInheritance<
				Logic::If_t<more(N1, N2), profile<N1, List1>, profile<N2, List2>>,
				Rest... >::type_trail;
		};

		template<int N1, typename List>
		struct fullInheritance<profile<N1, List>>
		{
			using type_trail = List;
		};

		template<typename T, int Index, Array::atype Name>
		struct methodsReview
		{
			static constexpr bool hit = Logic::If_t <
				more(Array::getSize<typename T::methods>, Index),
				Logic::If_t<
					Logic::equalityA<Name, Array::val_at<Index, typename T::methods>>::hit,
					typename Logic::True,
					methodsReview<T, Index + 1, Name>
				>,
				typename Logic::False
			>::hit;
		};

		template<typename T, Array::atype Name>
		static constexpr bool methodsReview_v = methodsReview<T, 0, Name>::hit;

		template<
			Array::atype Name,
			int Index, int StIndex, typename T>
		struct getRType_
		{
			using type = T;
		};

		template<
			Array::atype Name,
			int StIndex, int Index, typename T>
		struct getRType_<Name, StIndex, Index, MeList::type_list<T>>
		{
			using type = Logic::If_t<
				methodsReview_v<T, Name>,
				T,
				Array::ertype
			>;
		};

		template<
			Array::atype Name,
			int StIndex, int Index, typename T, typename... Rest>
		struct getRType_<Name, StIndex, Index, MeList::type_list<T, Rest...>>
		{
			using type = Logic::If_t<
				!more(Index, StIndex),
				Logic::If_t<
					methodsReview_v<T, Name>,
					T,
					typename getRType_<Name, StIndex, Index - 1, Rest...>::type
				>,
				typename getRType_<Name, StIndex, Index - 1, Rest...>::type
			>;
		};

		// StIndex - depth of the hierarchy, T - full hierarchy (from the root to leaves)
		// Index - level of initial hierarchy (determines initial type)
		// Name - the function we wanna call
		template<Array::atype Name, int Index, int StIndex, int curIndex, typename T>
		requires(!Array::IsErt<typename getRType_<Name, curIndex, StIndex, T>::type>)
		using getRType = getRType_<Name, Index, StIndex, T>::type;
	}
}

#endif