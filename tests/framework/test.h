#ifndef TEST_H
#define TEST_H

#include <stdio.h>

extern int tests_run;
extern int tests_failed;

void tests_summary(void);

#define TEST(name) void name(void)

#define RUN_TEST(test)                    \
    do                                    \
    {                                     \
        printf("Runnning %-30s", #test);  \
        tests_run++;                      \
        test();                           \
    } while(0)                            

#define PASS()                            \
    do                                    \
    {                                     \
        printf("\033[32mPASS\033[0m\n");  \
        return;                           \
    } while(0)                            

#define FAILED(msg)                       \
    do                                    \
    {                                     \
        tests_failed++;                   \
        printf("\033[31mFAIL\033[0m\n");  \
        printf("    %s\n", msg);          \
        return;                           \
    } while (0);                          

#define ASSERT_EQ(value, reference)                           \
    do                                                        \
    {                                                         \
        if ((value) != (reference))                           \
        {                                                     \
            tests_failed++;                                   \
            printf("\033[31mFAIL\033[0m\n");                  \
            printf("    %s:%d\n", __FILE__, __LINE__);        \
            printf("    Expected : %d\n", (reference));       \
            printf("    Actual   : %d\n", (value));           \
            return;                                           \
        }                                                     \
    } while (0)

#endif