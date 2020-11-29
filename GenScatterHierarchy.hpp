#include "type_list.hpp"

template <typename TL, template<class> typename Unit>
struct GenScatterHierarchy;

template <typename Atomic, template<class> typename Unit >
struct GenScatterHierarchy : public Unit<Atomic>
{
};

template <typename T1, typename T2, template<class> typename Unit>
struct GenScatterHierarchy <type_list<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit>
{
};

template <template<class> typename Unit>
struct GenScatterHierarchy <NullType, Unit>
{
};


template <typename T, typename TL, template<class> typename Unit>
Unit<T>&
Field(GenScatterHierarchy<TL, Unit>& obj)
{
    return obj;
}


template <typename TL, template<class> typename Unit>
Unit<typename TL::Head>&
Field_Helper(GenScatterHierarchy<TL, Unit>& obj, Int2Type<0>)
{
    GenScatterHierarchy<typename TL::Head, Unit>& temp = obj;
    return Field<typename TL::Head>(temp);
}

template <int i, typename TL, template<class> typename Unit>
Unit<typename TypeAt<TL,i>::Result>&
Field_Helper(GenScatterHierarchy<TL, Unit>& obj, Int2Type<i>)
{
    GenScatterHierarchy<typename TL::Tail, Unit>& temp = obj;
    return Field_Helper(temp, Int2Type<i-1>());
}


template<int i, typename TL, template<class> typename Unit>
Unit<typename TypeAt<TL,i>::Result>&
Field(GenScatterHierarchy<TL, Unit>& obj)
{
    return Field_Helper<i>(obj, Int2Type<i>());
}


