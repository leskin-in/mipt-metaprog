#ifndef MIPT_METAPROG_GENSCATTERF_H
#define MIPT_METAPROG_GENSCATTERF_H

#include "TypeList.h"
#include "Fibonacci.h"
#include "GenLinearF.h"


/**
 * A scatter-linear hierarchy generator
 *
 * @warning This is a private implementation of scatter-linear hierarchy generator.
 * Use {@link GenScatterF} as an interface instead
 *
 * @tparam TypeList type list to get types from
 * @tparam InheritanceContainer a container with special functions
 * @tparam fib_index fibonacci number index (N) applicable to the direct child linear hierarchy
 */
template <class TypeList, template <class, class> class InheritanceContainer, unsigned int fib_index=0>
class _GenScatterF;

template <class H, class T, template <class, class> class InheritanceContainer, unsigned int fib_index>
class _GenScatterF<TypeList<H, T>, InheritanceContainer, fib_index>
        : public GenLinearF<TypeList<H, T>, InheritanceContainer, Fibonacci<fib_index>::Result>,
public _GenScatterF<typename TL_Slice<TypeList<H, T>, Fibonacci<fib_index>::Result >::Result, InheritanceContainer, fib_index + 1>
{};

template <template <class, class> class InheritanceContainer, unsigned int fib_index>
class _GenScatterF<TypeNull, InheritanceContainer, fib_index>
{};


/**
 * A scatter-linear hierarchy generator
 *
 * Each linear branch will contain at most fibonacci(N) elements,
 * where N is an index of linear branch.
 *
 * Total number of elements will be equal to the length of a given TypeList
 *
 * @tparam TypeList type list to get types from
 * @tparam InheritanceContainer a container with special functions (see InheritanceContainer.h)
 */
template <class TypeList, template <class, class> class InheritanceContainer>
using GenScatterF = _GenScatterF<TypeList, InheritanceContainer, 0>;


#endif //MIPT_METAPROG_GENSCATTERF_H
