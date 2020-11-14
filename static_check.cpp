

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
    (void)sizeof(CompileTimeChecker<expr>(ERROR_##mssg())); \
}




void main()
{
    STATIC_CHECK(true, VOID_PTR_NOT_EQUAL_CHAR) ;
}


