#include <iostream>
#include <type_traits>
#include "fibin.h"

template<unsigned n>
using L = Lit<Fib<n>>;
using FB = Fibin<int>;

void test_fib() {

    static_assert(0 == Fibin<int>::eval<L<0>>());
    static_assert(1 == Fibin<int>::eval<L<1>>());
    static_assert(1 == Fibin<int>::eval<L<2>>());
    static_assert(2 == Fibin<int>::eval<L<3>>());
    static_assert(3 == Fibin<int>::eval<L<4>>());
    static_assert(5 == Fibin<int>::eval<L<5>>());
    static_assert(8 == Fibin<int>::eval<L<6>>());
    static_assert(13 == Fibin<int>::eval<L<7>>());
    static_assert(21 == Fibin<int>::eval<L<8>>());
    static_assert(34 == Fibin<int>::eval<L<9>>());
    static_assert(55 == Fibin<int>::eval<L<10>>());
    static_assert(89 == Fibin<int>::eval<L<11>>());
    static_assert(144 == Fibin<int>::eval<L<12>>());
    static_assert(233 == Fibin<int>::eval<L<13>>());
    static_assert(377 == Fibin<int>::eval<L<14>>());
    static_assert(610 == Fibin<int>::eval<L<15>>());
    static_assert(987 == Fibin<int>::eval<L<16>>());
    static_assert(1597 == Fibin<int>::eval<L<17>>());
    static_assert(2584 == Fibin<int>::eval<L<18>>());
    static_assert(4181 == Fibin<int>::eval<L<19>>());
    static_assert(6765 == Fibin<int>::eval<L<20>>());
    static_assert(10946 == Fibin<int>::eval<L<21>>());
    static_assert(17711 == Fibin<int>::eval<L<22>>());
    static_assert(28657 == Fibin<int>::eval<L<23>>());
    static_assert(46368 == Fibin<int>::eval<L<24>>());
    static_assert(75025 == Fibin<int>::eval<L<25>>());
    static_assert(121393 == Fibin<int>::eval<L<26>>());
    static_assert(196418 == Fibin<int>::eval<L<27>>());
    static_assert(317811 == Fibin<int>::eval<L<28>>());
    static_assert(514229 == Fibin<int>::eval<L<29>>());


    static_assert(0 == Fibin<uint8_t>::eval<L<0>>());
    static_assert(1 == Fibin<uint8_t>::eval<L<1>>());
    static_assert(1 == Fibin<uint8_t>::eval<L<2>>());
    static_assert(2 == Fibin<uint8_t>::eval<L<3>>());
    static_assert(3 == Fibin<uint8_t>::eval<L<4>>());
    static_assert(5 == Fibin<uint8_t>::eval<L<5>>());
    static_assert(8 == Fibin<uint8_t>::eval<L<6>>());
    static_assert(13 == Fibin<uint8_t>::eval<L<7>>());
    static_assert(21 == Fibin<uint8_t>::eval<L<8>>());
    static_assert(34 == Fibin<uint8_t>::eval<L<9>>());
    static_assert(55 == Fibin<uint8_t>::eval<L<10>>());
    static_assert(89 == Fibin<uint8_t>::eval<L<11>>());
    static_assert(144 == Fibin<uint8_t>::eval<L<12>>());
    static_assert(233 == Fibin<uint8_t>::eval<L<13>>());
    static_assert(121 == Fibin<uint8_t>::eval<L<14>>());
    static_assert(98 == Fibin<uint8_t>::eval<L<15>>());
    static_assert(219 == Fibin<uint8_t>::eval<L<16>>());
    static_assert(61 == Fibin<uint8_t>::eval<L<17>>());
    static_assert(24 == Fibin<uint8_t>::eval<L<18>>());
    static_assert(85 == Fibin<uint8_t>::eval<L<19>>());
    static_assert(109 == Fibin<uint8_t>::eval<L<20>>());
    static_assert(194 == Fibin<uint8_t>::eval<L<21>>());
    static_assert(47 == Fibin<uint8_t>::eval<L<22>>());
    static_assert(241 == Fibin<uint8_t>::eval<L<23>>());
    static_assert(32 == Fibin<uint8_t>::eval<L<24>>());
    static_assert(17 == Fibin<uint8_t>::eval<L<25>>());
    static_assert(49 == Fibin<uint8_t>::eval<L<26>>());
    static_assert(66 == Fibin<uint8_t>::eval<L<27>>());
    static_assert(115 == Fibin<uint8_t>::eval<L<28>>());
    static_assert(181 == Fibin<uint8_t>::eval<L<29>>());
}

template<uint64_t n>struct W {using w = Sum<Lit<Fib<6>>,typename W<n-8>::w>;};
template<>struct W<0>{using w = Lit<Fib<0>>;};
template<>struct W<1>{using w = Lit<Fib<1>>;};
template<>struct W<2>{using w = Lit<Fib<3>>;};
template<>struct W<3>{using w = Lit<Fib<4>>;};
template<>struct W<4>{using w = Inc1<Lit<Fib<4>>>;};
template<>struct W<5>{using w = Lit<Fib<5>>;};
template<>struct W<6>{using w = Inc1<Lit<Fib<5>>>;};
template<>struct W<7>{using w = Inc1<Inc1<Lit<Fib<5>>>>;};

template<uint64_t n>
using SquareN = 
Lambda<
    Var("f"),
    Lambda<
        Var("n"),
        If<
            Eq<
                typename W<n*2-1>::w,
                Ref<Var("n")>
            >,
            Ref<Var("n")>,
            Sum<
                Ref<Var("n")>,
                Invoke<
                    Ref<Var("f")>,
                    Sum<
                        Ref<Var("n")>,
                        Lit<Fib<3>>>>>>>>;




int main(){


    static_assert( Fibin<int>::eval<
            Let<
                    Var("x"),
                    Lit<Fib<5>>,
                    Let<
                            Var("y"),
                            Ref<Var("x")>,
                            Let<
                                    Var("x"),
                                    Lit<Fib<3>>,
                                    Ref<Var("y")>
                            >
                    >
            >
    >() == 5);


    using f1 = Lambda<Var("x"), Inc10<Ref<Var("x")>>>;
    using f2 = Lambda<Var("f"), Sum<Invoke<Ref<Var("f")>, Lit<Fib<1>>>, Lit<Fib<1>>>>;

    static_assert( Fibin<int>::eval<Invoke<f2, f1>>() == 57 );

    static_assert( Fibin<int>::eval<
            If <
                    Eq<
                            Lit<Fib<7>>,
                            Sum<Lit<Fib<6>>, Lit<Fib<5>>>
                    >,
                    Lit<Fib<1>>,
                    Lit<Fib<0>>
            >
    > () == 1);


    static_assert(Fibin<int>::eval<Let<
            Var("const"),
            Lit<Fib<1>>,
            Let<
                    Var("f"),
                    Lambda<
                            Var("x"),
                            Sum<
                                    Ref<Var("const")>,
                                    Ref<Var("x")>
                            >
                    >,
                    Let<
                            Var("const"),
                            Lit<Fib<2>>,
                            Invoke<
                                    Ref<Var("f")>,
                                    Lit<Fib<0>>
                            >
                    >
            >
    >>() == 1);

    static_assert(Fibin<int>::eval<Let<
            Var("X"),
            Lit<Fib<0>>,
            Invoke<
                    Lambda<
                            Var("X"),
                            Ref<Var("X")>
                    >,
                    Lit<Fib<1>>
            >
    >>() == 1);

    static_assert(Fibin<uint64_t>::eval<Invoke<Let<Var("x"), Lit<Fib<0>>, Lambda<Var("x"), Ref<Var("x")>>>, Lit<Fib<1>>>>() == 1);

    test_fib();

    static_assert(FB::eval<If<Lit<False>, Lit<Fib<10>>, Lit<Fib<11>>>>() == 89);
    static_assert(FB::eval<If< Eq<L<1>, L<2>>, L<10>, L<11> >>() == 55);
    static_assert(FB::eval<If< Eq<L<1>, L<3>>, L<10>, L<11> >>() == 89);
    static_assert(Fibin<uint8_t>::eval<If< Eq<L<32>, L<5>>, L<10>, L<11> >>() == 55);

    static_assert(FB::eval<If<If<Lit<False>, Lit<True>, Lit<False>>, Lit<Fib<2>>, Lit<Fib<3>>>>() == 2);
    static_assert(FB::eval<Sum<Lit<Fib<6>>, Lit<Fib<3>>>>() == 10);
    static_assert(FB::eval<Sum<L<6>, L<3>>>() == 10);
    static_assert(FB::eval<Sum<L<6>, L<3>, L<3>>>() == 12);
    static_assert(FB::eval<Sum<L<6>, L<3>, L<3>, L<6>>>() == 20);
    static_assert(FB::eval<Sum<L<4>, L<4>>>() == 6);
    static_assert(FB::eval<Inc1<L<4>>>() == 4);
    static_assert(FB::eval<Inc10<L<4>>>() == 58);
    

	//using Variable as bool
	static_assert(5 == Fibin<int16_t>::eval< Let<Var("true"), Lit<True>,
	        If<Ref<Var("true")>, L<5>, L<3> > >
	        >());

	//summing two Variables
	static_assert(57 == Fibin<int16_t>::eval<Let<Var("A"), L<10>,
	        Let<Var("asffss"), L<3>, Sum<Ref<Var("A")>, Ref<Var("asffss")>>>>>());



	// Testing: if False then Fib(0) else Fib(1)
	static_assert(1 == Fibin<uint8_t>::eval<If<Lit<False>, Lit<Fib<0>>, Lit<Fib<1>>>>());

	// Testing: let z = Fib(0) in {z + Fib(1)}
	static_assert(1 == Fibin<int16_t>::eval< Let<Var("z"), L<0>, Inc1<Ref<Var("Z")>> >>());


	// Testing: let z = Fib(0) in {z + Fib(1)}
	static_assert(1 == Fibin<int16_t>::eval< Let<Var("z"), L<0>, Inc1<Ref<Var("Z")>> >>());

    using Scoping = 
    Let<
        Var("const"),
        Lit<Fib<9>>,
        Let<
            Var("f"),
            Lambda<
                Var("x"),
                Sum<
                    Ref<Var("const")>,
                    Ref<Var("x")>
                >
            >,
            Let<
                Var("const"),
                Lit<Fib<10>>,
                Invoke<
                    Ref<Var("f")>,
                    Lit<Fib<0>>
                >
            >
        >
    >;

    static_assert(34 == Fibin<int>::eval<Scoping>());



    static_assert(2 == Fibin<uint>::eval<Invoke<Let<Var("x"), Lit<Fib<1>>, Lambda<Var("x"), Ref<Var("x")> > >, Lit<Fib<3>> > >());

    using FunctionComparison =
    Let<
        Var("f"),
        Lambda<
            Var("x"),
            Ref<Var("x")>
        >,
        If<
            Eq<
                Ref<Var("f")>,
                Ref<Var("F")>
            >,
            L<10>,
            L<11>
        >
    >;
    static_assert(55 == FB::eval<FunctionComparison>());

/*
    using Ycombinator =
    Lambda<
        Var("f"),
        Invoke<
            Lambda<
                Var("x"),
                Invoke<
                    Ref<Var("x")>,
                    Ref<Var("x")>
                >
            >,
            Lambda<
                Var("x"),
                Invoke<
                    Ref<Var("f")>,
                    Lambda<
                        Var("args"),
                        Invoke<
                            Invoke<
                                Ref<Var("x")>,
                                Ref<Var("x")>
                            >,
                            Ref<Var("args")>>>>>>>;

    uint64_t a = Fibin<uint64_t>::eval<Invoke<
            Invoke<Ycombinator, SquareN<45>>,
            Lit<Fib<1>>>>();

    std::cout << a << "\n";

   static_assert(
        Fibin<uint64_t>::eval<Invoke<
            Invoke<Ycombinator, SquareN<45>>,
            Lit<Fib<1>>
        >>() == 2025);

    static_assert(
        Fibin<uint64_t>::eval<Invoke<
            Invoke<Ycombinator, SquareN<103>>,
            Lit<Fib<1>>
        >>() == 103*103);
*/
	// Prints out to std::cout: "Fibin doesn't support: PKc"
	Fibin<const char*>::eval<Lit<Fib<0>>>();

}
