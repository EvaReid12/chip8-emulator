#include "test.h"

int tests_run = 0;
int tests_failed = 0;

void
tests_summary(void)
{
    printf("\n========================================\n");

    printf("Tests  : %d\n", tests_run);
    printf("Passed : %d\n", tests_run - tests_failed);
    printf("Failed : %d\n", tests_failed);

    printf("========================================\n");
}