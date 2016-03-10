#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

#include <cmocka.h>

#include "aclist.h"
#include "acstack.h"



static void empty_stack_has_zero(void **state) {
    ACStack *stack = ACStack_new(10);

    assert_non_null(stack);
    assert_int_equal(10, ACStack_maxSize(stack));
    assert_int_equal(0, ACStack_currentSize(stack));
    ACStack_free(stack);
}

static void stack_can_push_and_pop(void **state) {
    ACStack *stack = ACStack_new(10);


    ACStack_push(stack, 0xDD);
    ACStack_push(stack, 0xEE);
    assert_int_equal(2, ACStack_currentSize(stack));

    assert_int_equal(0xEE, ACStack_peek(stack));
    assert_int_equal(2, ACStack_currentSize(stack));

    assert_int_equal(0xEE, ACStack_pop(stack));
    assert_int_equal(1, ACStack_currentSize(stack));
    assert_int_equal(0xDD, ACStack_peek(stack));

    ACStack_free(stack);
}

// ****************************************************************************

static void empty_list_has_length_zero(void **state) {
    ACList *list = ACList_new();

    assert_int_equal(0, ACList_length(list));
    ACList_free(list);
}
static void null_list_has_length_below_zero(void **state) {
    assert_int_equal(-1, ACList_length(NULL));
}

static void list_has_length_equal_to_number_of_adds(void **state) {
    ACList *list = ACList_new();

    ACList_insert(list, 101);
    ACList_insert(list, 102);
    ACList_insert(list, 102);
    ACList_insert(list, 102);

    assert_int_equal(4, ACList_length(list));

    ACList_free(list);
}

static void list_can_get_particular_values(void **state) {
    ACList *list = ACList_new();

    ACList_insert(list, 101);
    ACList_insert(list, 102);
    ACList_insert(list, 103);

    assert_int_equal(102, ACList_get(list, 1));

    ACList_free(list);
}

static void list_can_get_particular_values_invalid_idx(void **state) {
    ACList *list = ACList_new();

    ACList_insert(list, 101);
    ACList_insert(list, 102);
    ACList_insert(list, 103);

    assert_int_equal(-1, ACList_get(NULL, 0));
    assert_int_equal(-1, ACList_get(list, 3));

    ACList_free(list);
}


int main(void) {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(empty_list_has_length_zero),
            cmocka_unit_test(null_list_has_length_below_zero),
            cmocka_unit_test(list_has_length_equal_to_number_of_adds),
            cmocka_unit_test(list_can_get_particular_values),
            cmocka_unit_test(list_can_get_particular_values_invalid_idx),

            cmocka_unit_test(empty_stack_has_zero),
            cmocka_unit_test(stack_can_push_and_pop),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}