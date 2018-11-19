#ifndef MIPT_METAPROG_GENLINEARF_H
#define MIPT_METAPROG_GENLINEARF_H

#include "TypeList.h"
#include "Fibonacci.h"


/**
 * A linear hierarchy generator.
 *
 * @tparam TypeList type list to get types from
 * @tparam remaining maximum number of types (from TypeList) this hierarchy must contain
 */
template<class TypeList, template <class, class> class InheritanceContainer, unsigned int remaining>
class GenLinearF;

template<class H, class T, template <class, class> class InheritanceContainer, unsigned int remaining>
class GenLinearF<TypeList<H, T>, InheritanceContainer, remaining>
        : public InheritanceContainer<H, GenLinearF<T, InheritanceContainer, remaining - 1> >
{};

template<class H, class T, template <class, class> class InheritanceContainer>
class GenLinearF<TypeList<H, T>, InheritanceContainer, 0>
{};

template<template <class, class> class InheritanceContainer, unsigned int remaining>
class GenLinearF<TypeNull, InheritanceContainer, remaining>
{};


#endif //MIPT_METAPROG_GENLINEARF_H
