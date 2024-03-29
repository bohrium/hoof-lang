#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

#include "../preprocessor_tricks.h"

#include "../list.h"
#include "../cstring.h"

#define PRINT_LIST_NUMS(LIST) \
    printf(" ... len %d cap %d\n", LIST.len, LIST.cap);

void test_safe_operations();
void test_unsafe_operations();
void test_poly_nested();

void test_push_speed( void (*my_pusher)(IntList*, int) );
void test_getref_speed( int* (*my_getter)(IntList const*, int) );
void test_resize_speed();

int main(int argc, char const* const* argv)
{
    if ( argc>=2 ) {
        BREAKBLOCK {
            if ( argc!=2 ) { BARKLN("expected 1 arg", RED); return -1; }
            if ( cstr_eq(argv[1], "color"   ) ) { USECOLOR = 1; break; }
            if ( cstr_eq(argv[1], "no-color") ) { USECOLOR = 0; break; }
            BARKLN("arg must be `color` or `no-color`", RED); return -1;
        }
    }

    BARKLN("hi!", CYAN);

    { /* CORRECTNESS TESTS */
        BARKLN("\n# Safe Correctness", BLUE);
        test_safe_operations();

        // Proposition P: "Safe operations are defined in terms of unsafe ones".
        // Unless I forgot to maintain P, P is still true, so the previous test
        // also tests unsafe operations.  But we of course want to test the
        // interface without such assumptions about implementations.
        BARKLN("\n# Unsafe Correctness", BLUE);
        test_unsafe_operations();

        BARKLN("\n# Poly Correctness", BLUE);
        test_poly_nested();
    }

    { /* SPEED TESTS */
        BARKLN("\n# Unsafe Speed", BLUE);
        test_push_speed(il_push_unsafe);
        test_getref_speed(il_getref_unsafe);

        BARKLN("\n# Safe Speed", BLUE);
        test_push_speed(il_push);
        test_getref_speed(il_getref);

        BARKLN("\n# Resize Speed", BLUE);
        test_resize_speed();
    }

    BARKLN("\nbye!", CYAN);
    return 0;
}

/* -----  correctness tests  ----------------------------------------------- */

int const HALF = 6;

void test_safe_operations()
{
    IntList ily = il_init(2);

    FOR (i, 0, 2*HALF) {
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
    FOR (s, HALF, 3*HALF) {
        il_resize(&ily, s);
        printf("resize %d ...", s);
        PRINT_LIST_NUMS(ily);
    }
    FOR (i, -HALF, 3*HALF) {
        int* elptr = il_getref(&ily, i);
        if ( elptr )  { printf("getref idx %d val %d", i, *elptr); }
        else          { printf("getref idx %d val %s", i, "NULL"); }
        PRINT_LIST_NUMS(ily);
    }
    FOR (s, 0, 2*HALF) {
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

    FOR (i, 0, 2*HALF) {
        if ( ! il_is_empty(&ily) ) {
            int* elptr = il_top_unsafe(&ily);
            printf("top  val %d", *elptr);
        } else {
            printf("top ... is empty!");
        }
        PRINT_LIST_NUMS(ily);
        // NOTE : length ends up at HALF instead of 2*HALF
        int el = 2*i+1;
        if ( ! il_is_full(&ily) ) {
            il_push_unsafe(&ily, el);
            printf("push val %d", el);
        } else {
            printf("push ... is full!");
        }
        PRINT_LIST_NUMS(ily);
    }
    FOR (s, HALF, 2*HALF) {
        il_resize(&ily, s);
        printf("resize %d ...", s);
        PRINT_LIST_NUMS(ily);
    }
    FOR (i, 0, HALF) {
        int* elptr = il_getref_unsafe(&ily, i);
        printf("getref idx %d val %d", i, *elptr);
        PRINT_LIST_NUMS(ily);
    }
    FOR (s, 0, 2*HALF) {
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

void test_poly_nested()
{
    int const len = 1000;
    IntListList illy = ill_init(len);

    FOR (i, 0, len) { ill_push(&illy, il_init(5)); }

    FOR (i, 0, len) {
        if (i%10) { continue; }
        FOR (j, 0, (i/2)+1) {
            il_push(ill_getref(&illy, i), 2*j+1);
        }
    }

    int s=0;
    FOR (i, 0, len) {
        IntList ily = *ill_getref(&illy, i);
        FOR (j, 0, il_len(&ily)) {
            s += *il_getref(&ily, j);
        }
    }
    printf("sum is %d\n", s);

    FOR (i, 0, len) { il_free(ill_pop(&illy)); }

    ill_free(&illy);
}

/* -----  speed tests  ----------------------------------------------------- */

void test_push_speed( void (*my_pusher)(IntList*, int) )
{
    int const len = 10*1000*1000;

    IntList ily = il_init(len);

    START_CLOCK();
    FOR (i, 0, len) { (*my_pusher)(&ily, 2*i+1); }
    REPORT_CLOCK("[[TIME]] pushing");

    il_free(&ily);
}

void test_getref_speed( int* (*my_getter)(IntList const*, int) )
{
    int const len = 10*1000*1000;
    IntList ily = il_init(len);
    FOR (i, 0, len) { il_push(&ily, 2*i+1) ; }

    int s=0;

    START_CLOCK();
    FOR (i, 0, len) {
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
    FOR (s, 0, len) {
        ily.len = ily.cap; // <- ATTN : UNSAFE !
        il_resize(&ily, s);
    }
    REPORT_CLOCK("[[TIME]] resizing");

    il_free(&ily);
}

