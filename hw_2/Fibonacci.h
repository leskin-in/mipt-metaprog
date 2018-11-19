#ifndef MIPT_METAPROG_FIBONACCI_H
#define MIPT_METAPROG_FIBONACCI_H


/**
 * An at-compile-time fibonacci number calculator
 *
 * @tparam n fibonacci number index
 */
template<unsigned int n>
struct Fibonacci {
    enum {
        Result = Fibonacci<n-1>::Result + Fibonacci<n-2>::Result
    };
};

template<>
struct Fibonacci<0> {
    enum {
        Result = 1
    };
};

template<>
struct Fibonacci<1> {
    enum {
        Result = 1
    };
};


#endif //MIPT_METAPROG_FIBONACCI_H
