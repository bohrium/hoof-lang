#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#define ELEMENT_TYPE        int
#define LIST_TYPE_NAME      IntList
#define LIST_METHOD_PREFIX  il
#define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
#include "list.template.c"
#undef ELEMENT_TYPE
#undef LIST_TYPE_NAME
#undef LIST_METHOD_PREFIX
#undef EXPAND_FACTOR

#define ELEMENT_TYPE        int*
#define LIST_TYPE_NAME      IntPtrList
#define LIST_METHOD_PREFIX  ipl
#define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
#include "list.template.c"
#undef ELEMENT_TYPE
#undef LIST_TYPE_NAME
#undef LIST_METHOD_PREFIX
#undef EXPAND_FACTOR

#define ELEMENT_TYPE        IntList
#define LIST_TYPE_NAME      IntListList
#define LIST_METHOD_PREFIX  ill
#define EXPAND_FACTOR       1.272 /* sqrt( phi ) , just for fun */
#include "list.template.c"
#undef ELEMENT_TYPE
#undef LIST_TYPE_NAME
#undef LIST_METHOD_PREFIX
#undef EXPAND_FACTOR

#define FOR(VAR, START, END) for (int VAR=START; VAR!=END; ++VAR)
#define PRINT_LIST_NUMS(LIST) printf(" ... len %d cap %d\n", LIST.len, LIST.cap);

void test_safe_operations();
void test_unsafe_operations();
void test_push_speed( void (*my_pusher)(IntList*, int) );
void test_getref_speed( int* (*my_getter)(IntList const*, int) );

void test_resize_speed();

int main()
{
    printf("hi!\n");

    printf("\n#SAFE CORRECTNESS\n");
    test_safe_operations();

    // Proposition P: "Safe operations are defined in terms of unsafe ones".
    // Unless I forgot to maintain P, P is still true, so the previous test
    // also tests unsafe operations.  But we of course want to test the
    // interface without such assumptions about implementations.
    printf("\n#UNSAFE CORRECTNESS\n");
    test_unsafe_operations();

    printf("\n#UNSAFE SPEED\n");
    test_push_speed(il_push_unsafe);
    test_getref_speed(il_getref_unsafe);

    printf("\n#SAFE SPEED\n");
    test_push_speed(il_push);
    test_getref_speed(il_getref);

    printf("\n#RESIZE SPEED\n");
    test_resize_speed();

    printf("\nbye!\n");
    return 0;
}

int const HALF = 6;

void test_safe_operations()
{
    IntList ily = il_init(2);

    FOR(i, 0, 2*HALF) {
        int* elptr = il_top(&ily);
        if ( elptr )  { printf("top  val %d", *elptr); }
        else          { printf("top  val %s", "NULL"); }
        PRINT_LIST_NUMS(ily);
        //
        int el = 2*i+1;
        il_push(&ily, el);
                        printf("push val %d", el);
        PRINT_LIST_NUMS(ily);
    }
    FOR(s, HALF, 3*HALF) {
        il_resize(&ily, s);
        printf("resize %d ...", s);
        PRINT_LIST_NUMS(ily);
    }
    FOR(i, -HALF, 3*HALF) {
        int* elptr = il_getref(&ily, i);
        if ( elptr )  { printf("getref idx %d val %d", i, *elptr); }
        else          { printf("getref idx %d val %s", i, "NULL"); }
        PRINT_LIST_NUMS(ily);
    }
    FOR(s, 0, 2*HALF) {
        int* elptr = il_pop(&ily);
        if ( elptr )  { printf("pop val %d", *elptr); }
        else          { printf("pop val %s", "NULL"); }
        PRINT_LIST_NUMS(ily);
    }

    il_free(&ily);
}

void test_unsafe_operations()
{
    IntList ily = il_init(HALF);

    FOR(i, 0, 2*HALF) {
        if ( ! il_is_empty(&ily) ) {
            int* elptr = il_top_unsafe(&ily);
            printf("top  val %d", *elptr);
        } else {
            printf("top ... is empty!");
        }
        PRINT_LIST_NUMS(ily);
        //
        int el = 2*i+1;
        if ( ! il_is_full(&ily) ) {
            il_push_unsafe(&ily, el);
            printf("push val %d", el);
        } else {
            printf("push ... is full!");
        }
        PRINT_LIST_NUMS(ily);
    }
    FOR(s, HALF, 2*HALF) {
        il_resize(&ily, s);
        printf("resize %d ...", s);
        PRINT_LIST_NUMS(ily);
    }
    FOR(i, 0, 2*HALF) {
        int* elptr = il_getref_unsafe(&ily, i);
        printf("getref idx %d val %d", i, *elptr);
        PRINT_LIST_NUMS(ily);
    }
    FOR(s, 0, 2*HALF) {
        if ( ! il_is_empty(&ily) ) {
            int* elptr = il_pop_unsafe(&ily);
            printf("pop val %d", *elptr);
        } else {
            printf("pop ... is empty!");
        }
        PRINT_LIST_NUMS(ily);
    }

    il_free(&ily);
}



void test_push_speed( void (*my_pusher)(IntList*, int) )
{
    int const len = 10*1000*1000;

    IntList ily = il_init(len);

    START_CLOCK();
    FOR(i, 0, len) { (*my_pusher)(&ily, 2*i+1); }
    REPORT_CLOCK("[[TIME]] pushing");

    il_free(&ily);
}

void test_getref_speed( int* (*my_getter)(IntList const*, int) )
{
    int const len = 10*1000*1000;
    IntList ily = il_init(len);
    FOR(i, 0, len) { il_push(&ily, 2*i+1) ; }

    int s=0;

    START_CLOCK();
    FOR(i, 0, len) {
        *my_getter(&ily, i) -= 2;
        s += *my_getter(&ily, i);
    }
    REPORT_CLOCK("[[TIME]] getting");

    printf("sum is %d\n", s);

    il_free(&ily);
}

void test_resize_speed()
{
    int const len = 20*1000;
    IntList ily = il_init(len);
    il_resize(&ily, 2);

    int ss = 0;
    START_CLOCK();
    FOR(s, 0, len) {
        ily.len = ily.cap; // <- ATTN : UNSAFE !
        il_resize(&ily, s);
    }
    REPORT_CLOCK("[[TIME]] resizing");

    il_free(&ily);
}

