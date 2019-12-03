#ifndef FIBIN_FIBIN_2_H
#define FIBIN_FIBIN_2_H

#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <cstring>


struct True {
    constexpr static bool val = true;
};
struct False {
    constexpr static bool val = false;
};

// A type for Fib<...>
template<u_int64_t v, typename = void>
struct Fib {
    constexpr static u_int64_t val = Fib<v-1>::val + Fib<v-2>::val;
};

// A type for Fib<0>
template<typename F>
struct Fib<0, F> {
    constexpr static u_int64_t val = 0;
};

// A type for Fib<1>
template<typename F>
struct Fib<1, F> {
    constexpr static u_int64_t val = 1;
};


/* The syntax contains eleven expression types:
 * Lit for literals, two types: Fib and True/False,
 * Var for variable names
 * Ref for variable references,
 * Let for joining Var with its value (which could be Lit but also Lambda),
 * Lambda terms for anonymous functions,
 * Invoke for function applications,
 * If for conditionals,
 * Eq for equal,
 * Inc1 for increasing an argument by Fib<1> = 1,
 * Inc1 for increasing an argument by Fib<10> = 55,
 * and Sum for addition at least 2 arguments.
 *  */

template <typename T>
struct Lit {} ;

constexpr u_int32_t length(const char* nam) {

    u_int32_t len = 0;
    for (size_t i = 0; nam[i] != '\0'; i++) {
        len++;
    }
    return len;
}

constexpr u_int32_t Var(const char* nam) {

    size_t len = length(nam);
    assert(len >= 1 && len <= 6);

    for (size_t i = 0; i < len; i++) {
        char c = nam[i];
        assert((c >= '0' && c <= '9') ||
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z'));
    }

    u_int32_t value = 0;
    for (size_t j = 0; j < len; j++) {
        size_t i = len - 1 - j;
        char c = nam[i];
        //hash
        //there are 36 signs: 0,...,9, a,...,z
        //theirs ids are      0,...,9,10,...,35
        //there are max 6 positions, each with base 36^pos_id
        if (c >= 'a' && c <= 'z') {
            value *= 36;
            value = value + c - 'a' + 10;
        }
        else if (c >= 'A' && c <= 'Z') {//lowercase
            value *= 36;
            value = value + c - 'A' + 10;
        }
        else if (c >= '0' && c <= '9') {
            value *= 36;
            value = value + c - '0';
        }
    }
    return value;
}

template <u_int32_t Var>
struct Ref {};

template <u_int32_t Var, typename Value, typename Expr>
struct Let {};

template<u_int32_t Var, typename Body>
struct Lambda {};

template<typename Fun, typename Arg>
struct Invoke {};

template<typename Cond, typename Then, typename Else>
struct If {};

template <typename T1, typename T2>
struct Eq {};

template<typename Arg>
struct Inc1 {};

template<typename Arg>
struct Inc10 {};

template <typename Arg1, typename Arg2, typename... Args>
struct Sum {};

template <u_int64_t v>
struct Calc {
    constexpr static u_int64_t val = v;
};



/* Environments are structures that map (variable) names to values.
 * Environments are paired with expressions to give meanings to free
 * variables. */

// EmptyEnv is the empty environment.
struct EmptyEnv;

// Bindings<Name,Value,Env> is a type than encodes the environment Env
// extended with a binding for Name => Value.
template<u_int32_t Name, typename Value, typename Env>
struct Binding {};

// EnvLookup<Name,Env> :: result looks up the value of Name in Env.
template<u_int32_t Name, typename Env>
struct FindVar {};

template<u_int32_t Name>
struct FindVar<Name, EmptyEnv> {}; // Name not found.

// Found variable - it's value is Value and the "new" type is result
template<u_int32_t Name, typename Value, typename Env>
struct FindVar<Name, Binding<Name, Value, Env> > {
    Value typedef result;
};

// Haven't found the variable - go recursively to the previous layer
// and check has it been binded to Environment there
template<u_int32_t Name, u_int32_t Name2, typename Value2, typename Env>
struct FindVar<Name, Binding<Name2, Value2, Env> > {
    typename FindVar<Name, Env>::result typedef result;
};

//
//  EVAL
//

// Values:
template<typename Lam, typename Env>
struct Closure {};

// Eval<Exp,Env> :: result is the value of expression Exp in
// environment Env.
template<typename Exp, typename Env>
struct Eval {};

// Inv<Proc,Value> :: result is the value of applying Proc to Value.
template<typename Fun, typename Value, typename Env>
struct Inv {};

template <u_int64_t v, typename Env>
struct Eval<Calc<v>, Env> {
    Calc<v> typedef result;
};

// Literals evaluate to themselves:
template<typename T, typename Env>
struct Eval<Lit<T>, Env> {
    T typedef result;
};

//Lit<T>
template <u_int64_t n, typename Env>
struct Eval<Lit<Fib<n>>, Env> {
    Fib<n> typedef result;
};

// Variable references are looked up in the current environment:
template<u_int32_t name, typename Env>
struct Eval<Ref<name>, Env> {
    typename Eval<typename FindVar<name, Env>::result, Env>::result typedef result;
};


// Lambda terms evaluate into closures:
template<u_int32_t name, typename Body, typename Env>
struct Eval<Lambda<name, Body>, Env> {
    //Closure<Lambda<name, Body>, Env> typedef result;
};

// Applications apply the value of the function expression to the
// value of the argument expression:
template<typename Fun, typename Arg, typename Env>
struct Eval<Invoke<Fun, Arg>, Env> {
    typename Inv<Fun, Env, Lit<typename Eval<Arg, Env>::result>>::result typedef result;
};

// Transition to the body of the lambda term inside the closure:
template<u_int32_t name, typename Body, typename Env, typename Value>
struct Inv<Lambda<name, Body>, Env, Value> {
    typename Eval<Body, Binding<name, Value, Env> >::result typedef result;
};

// Branch true:
template<typename Then, typename Else, typename Env>
struct Eval<If<True, Then, Else>, Env> {
    typename Eval<Then, Env>::result typedef result;
};

// Branch false:
template<typename Then, typename Else, typename Env>
struct Eval<If<False, Then, Else>, Env> {
    typename Eval<Else, Env>::result typedef result;
};

// Evaluate the condition:
template<typename Cond, typename Then, typename Else, typename Env>
struct Eval<If<Cond, Then, Else>, Env> {
    typename Eval<If<typename Eval<Cond, Env>::result, Then, Else>, Env>::result
    typedef result;
};

template<typename T1, typename Env>
struct Eval<Eq<T1, T1>, Env> {
    True typedef result;
};

template<u_int64_t v1, u_int64_t v2, typename Env>
struct Eval<Eq< Lit<Fib<v1>>, Lit<Fib<v2>>>, Env> {
    False typedef result;
};

template<u_int64_t v1, typename Env>
struct Eval<Eq< Lit<Fib<v1>>, Lit<Fib<v1>>>, Env> {
    True typedef result;
};

template<typename T1, typename T2, typename Env>
struct Eval<Eq<T1, T2>, Env> {
    typename Eval<Eq< Lit<typename Eval<T1, Env>::result>,
                      Lit<typename Eval<T2, Env>::result>>,
                      Env>:: result typedef result;
};

//Sum<Arg> |Args| = 2
template <typename Arg1, typename Arg2, typename Env>
struct Eval<Sum<Arg1, Arg2>, Env> {
    Calc<Eval<Arg1, Env>::result::val +
         Eval<Arg2, Env>::result::val> typedef result;
};

//Sum<Args> |Args| > 2
template <typename Arg1, typename Arg2, typename... Args, typename Env>
struct Eval<Sum<Arg1, Arg2, Args...>, Env> {
    typename Eval<Sum<Arg1, typename
             Eval<Sum<Arg2, Args...>, Env>::result>, Env>::result typedef result;
};

//Inc1<Arg>
template <typename Arg, typename Env>
struct Eval<Inc1<Arg>, Env> {
    typename Eval<Sum<Arg, Lit<Fib<1>>>, Env>::result typedef result;
};

//Inc1<Arg>
template <typename Arg, typename Env>
struct Eval<Inc10<Arg>, Env> {
    typename Eval<Sum<Arg, Lit<Fib<10>>>, Env>::result typedef result;
};

template <u_int32_t name, typename Value, typename Expr, typename Env>
struct Eval<Let<name, Value, Expr>, Env> {
    typename Eval<Expr, Binding<name, Value, Env>>::result typedef result;
};

template <typename ValueType>
class Fibin {
public:

    template<typename Expr>
    constexpr static ValueType eval() {
        ValueType result = Eval<Expr, EmptyEnv>::result::val;
        return result;
    }
};

#endif //FIBIN_FIBIN_2_H
