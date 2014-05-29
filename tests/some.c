#include <stdlib.h>
#include <check.h>

START_TEST(this_thing) {
    ck_assert_msg(0, "The tests are not implemented.");
}
END_TEST

Suite *money_suite(void) {
    Suite *s = suite_create ("Some Suit");

    /* Core test case */
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, this_thing);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char *argv[]) {
    int number_failed;

    Suite *s = money_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

