#ifndef MIPT_METAPROG_INHERITANCECONTAINER_H
#define MIPT_METAPROG_INHERITANCECONTAINER_H


/**
 * A simple inheritance container
 *
 * The user may implement other inheritance containers,
 * as long as they are of the same template interface, and satisfy the condition:
 *  *
 *  * InheritanceContainer must publicly inherit the second template parameter
 *  *
 * The element this container may hold is the first template parameter
 *
 *
 * This InheritanceContainer implements an "interface" to access instance of Element
 *
 * @tparam Element type whose instance is created
 * @tparam Root type to inherit this container from
 */
template<class Element, class Root>
struct InheritanceContainer
        : public Root
{
    Element e;
};


#endif //MIPT_METAPROG_INHERITANCECONTAINER_H
