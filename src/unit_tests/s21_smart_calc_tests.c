#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_smart_calc.h"

#define STACK_DEPTH 500 /* Глубина стека */

START_TEST(test_sin) {
  char str[STACK_DEPTH];
  strcpy(str, "-sin(-2-3*1.55)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double b = -2 - 3 * 1.55;
  double a = -sin(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_asin) {
  char str[STACK_DEPTH];
  strcpy(str, "-asin(0.5)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 0.5;
  float a = -asin(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_cos) {
  char str[STACK_DEPTH];
  strcpy(str, "cos(x*2.1)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 2.1);
  ck_assert_ldouble_eq_tol(end, cos(2.1 * 2.1), ESP);
}
END_TEST

START_TEST(test_acos) {
  char str[STACK_DEPTH];
  strcpy(str, "acos(0.5)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 0.5;
  double a = acos(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_tan) {
  char str[STACK_DEPTH];
  strcpy(str, "tan(2.1)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 2.1;
  double a = tan(b);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_atan) {
  char str[STACK_DEPTH];
  strcpy(str, "atan(2.1)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 2.1;
  ck_assert_ldouble_eq_tol(end, atan(b), ESP);
}
END_TEST

START_TEST(test_sqrt) {
  char str[STACK_DEPTH];
  strcpy(str, "sqrt(21)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double b = 21;
  ck_assert_ldouble_eq_tol(end, sqrt(b), ESP);
}
END_TEST

START_TEST(test_ln) {
  char str[STACK_DEPTH];
  strcpy(str, "ln(2.1)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double a = log10f(2.1);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_log) {
  char str[STACK_DEPTH];
  strcpy(str, "log(2.1)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  double a = log(2.1);
  ck_assert_ldouble_eq_tol(end, a, ESP);
}
END_TEST

START_TEST(test_mod) {
  char str[STACK_DEPTH];
  strcpy(str, "10 mod 3+2");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, 3.0, ESP);
}
END_TEST

START_TEST(test_pow) {
  char str[STACK_DEPTH];
  strcpy(str, "2^(3^4)");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, pow(2, pow(3, 4)), ESP);
}
END_TEST

START_TEST(test_algorithm) {
  char str[STACK_DEPTH];
  strcpy(str,
         "15/(7-(1 + "
         "1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
         "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))");
  dijkstra_algorithm(str);
  double end = 0;
  operand(str, &end, 0);
  ck_assert_ldouble_eq_tol(end, -30.0721649484536082, ESP);
}
END_TEST

int main(void) {
  Suite *suite = suite_create("Core");
  TCase *tc = tcase_create("function");
  SRunner *sr = srunner_create(suite);
  suite_add_tcase(suite, tc);

  tcase_add_test(tc, test_algorithm);

  tcase_add_test(tc, test_pow);
  tcase_add_test(tc, test_mod);
  tcase_add_test(tc, test_cos);
  tcase_add_test(tc, test_sin);
  tcase_add_test(tc, test_tan);
  tcase_add_test(tc, test_acos);
  tcase_add_test(tc, test_asin);
  tcase_add_test(tc, test_atan);
  tcase_add_test(tc, test_sqrt);
  tcase_add_test(tc, test_ln);
  tcase_add_test(tc, test_log);

  srunner_run_all(sr, CK_VERBOSE);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}