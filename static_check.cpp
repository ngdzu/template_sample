

template <bool>
struct CompileTimeChecker
{
    CompileTimeChecker(...); // Don't need to define, we only use it inside of size_of
};

template<>
struct CompileTimeChecker<false> {}; // default ctor doesn't take any argument

#define STATIC_CHECK(expr, mssg) \
{   \
    class ERROR_##mssg{ }; \
    (void)sizeof( (CompileTimeChecker<expr>(ERROR_##mssg())) ); \
}

template<typename To, typename From>
To safe_reinterpret_cast(From a)
{
    STATIC_CHECK (sizeof(To) >= sizeof(From), NARROW_CAST );
    return reinterpret_cast<To>(a);
}


int main()
{
    STATIC_CHECK(sizeof(void*) == sizeof(long), VOID_PTR_NOT_EQUAL_CHAR) // no compile error for 64-bit system
    
    // char a = safe_reinterpret_cast<int>(23);
    // auto b = safe_reinterpret_cast<char>(8);
    int a = 2;
    auto c = safe_reinterpret_cast<double*>(&a);

    double b = 1.0;
    auto d = safe_reinterpret_cast<int*>(&b);

    return 0;
}


