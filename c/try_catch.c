    // 文件名: try_catch.c

    #include <stdio.h>

    #define TRY int __ret__ = 0;

    #define CATCH           \
        __exeception:       \
        if (__ret__ == 0)   \
        {                   \
            goto __finally; \
        }                   \
        switch (__ret__)

    #define FINALLY __finally:

    #define FINALLY_WITHOUT_CATCH \
        __exeception:

    #define CASE(error, content) \
        case (error):            \
        {                        \
            {content} break;     \
        }

    #define OTHER(content)   \
        default:             \
        {                    \
            {content} break; \
        }

    #define THROW(ret)   \
        __ret__ = (ret); \
        goto __exeception

    #define EXEC(func)    \
        __ret__ = (func); \
        if (__ret__ != 0) \
        goto __exeception

    int func0()
    {
        return 0;
    }

    int func1()
    {
        return 1;
    }

    int func2()
    {
        return 2;
    }

    int func3()
    {
        return 3;
    }

    int test_exec(int (*func)())
    {
        TRY
        {
            EXEC(func());
        }
        CATCH
        {
            CASE(1,
                printf("line:%d catch: %d ...\n", __LINE__, __ret__);)
            CASE(2,
                printf("line:%d catch: %d ...\n", __LINE__, __ret__);)
            OTHER(
                printf("line:%d catch: %d ...\n", __LINE__, __ret__);)
        }
        FINALLY
        {
            printf("Finally ret: %d ...\n", __ret__);
        }
        return __ret__;
    }

    int test_throw(int value)
    {
        TRY
        {
            THROW(value);
        }
        CATCH
        {
            CASE(1,
                printf("line:%d catch: %d ...\n", __LINE__, __ret__);)
            CASE(2,
                printf("line:%d catch: %d ...\n", __LINE__, __ret__);)
            OTHER(
                printf("line:%d catch: %d ...\n", __LINE__, __ret__);)
        }
        FINALLY
        {
            printf("Finally ret: %d ...\n", __ret__);
        }
        return __ret__;
    }

    int test_finally(int (*func)())
    {
        TRY
        {
            EXEC(func());
        }
        FINALLY_WITHOUT_CATCH
        {
            printf("Finally ret: %d ...\n", __ret__);
        }
        return __ret__;
    }

    int main(int argc, char const *argv[])
    {
        printf("test_exec ...\n");
        test_exec(func0);
        test_exec(func1);
        test_exec(func2);
        test_exec(func3);

        printf("\ntest_throw ...\n");
        test_throw(0);
        test_throw(1);
        test_throw(2);
        test_throw(3);

        printf("\ntest_finally ...\n");
        test_finally(func1);

        return 0;
    }
