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

int double_the_value(int v) {
    return v * 2;
}

int add_one(int v) {
    return v + 1;
}

static void list_can_map(void **state) {
    ACList *list = ACList_new();

    ACList_insert(list, 101);
    ACList_insert(list, 102);
    ACList_insert(list, 103);

    assert_int_equal(101, ACList_get(list, 0));
    assert_int_equal(102, ACList_get(list, 1));
    assert_int_equal(103, ACList_get(list, 2));

    ACList_map_in_place(list, double_the_value);
    assert_int_equal(202, ACList_get(list, 0));
    assert_int_equal(204, ACList_get(list, 1));
    assert_int_equal(206, ACList_get(list, 2));

    ACList_map_in_place(list, add_one);
    assert_int_equal(203, ACList_get(list, 0));
    assert_int_equal(205, ACList_get(list, 1));
    assert_int_equal(207, ACList_get(list, 2));


    ACList_free(list);
}


int choose_evens(int v) {
    return (v % 2) == 0;
}

static void list_can_filter(void **state) {
    ACList *list = ACList_new();

    ACList_insert(list, 101);
    ACList_insert(list, 102);
    ACList_insert(list, 103);

    assert_int_equal(101, ACList_get(list, 0));
    assert_int_equal(102, ACList_get(list, 1));
    assert_int_equal(103, ACList_get(list, 2));

    ACList_filter_in_place(list, choose_evens);
    assert_int_equal(102, ACList_get(list, 0));



    ACList_free(list);
}


static void list_can_find_index_of_nodes(void **state) {
    ACList *list = ACList_new();
    ACListNode *node1 = ACList_insert(list, 101);;
    ACListNode *node2 = ACList_insert(list, 102);
    ACListNode *node3 = ACList_insert(list, 103);

    assert_int_equal(0, ACList_index_of(list, node1));
    assert_int_equal(1, ACList_index_of(list, node2));
    assert_int_equal(2, ACList_index_of(list, node3));

    ACList_free(list);

}


static void list_can_remove_middle(void **state) {
    ACList *list = ACList_new();
    ACListNode *node = NULL;
    ACList_insert(list, 101);
    node = ACList_insert(list, 102);
    ACList_insert(list, 103);
    assert_int_equal(3, ACList_length(list));

    ACList_remove(list, node);
    assert_int_equal(2, ACList_length(list));

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
            cmocka_unit_test(list_can_map),
            cmocka_unit_test(list_can_remove_middle),
            cmocka_unit_test(list_can_find_index_of_nodes),
            cmocka_unit_test(list_can_filter),

            cmocka_unit_test(empty_stack_has_zero),
            cmocka_unit_test(stack_can_push_and_pop),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}