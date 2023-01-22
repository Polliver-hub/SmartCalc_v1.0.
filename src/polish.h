/*!
\file
\brief Заголовочный файл с объявлениями функций связанных с компиляцией выржания
из инфискной в постфиксную нотацию
*/

#ifndef SRC_POLISH_H_
#define SRC_POLISH_H_
#define STACK_MAX_SIZE 300
#define MAX_INFIX_LENGTH 300

#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>

#define SUF -2   // недостаточно операндов в стеке
#define NCLB -4  // нет закр скобки

/**
 * @brief Преобразование выражений из инфиксной в обратную польскую нотацию
 * @param infix_record - входная строка.
 * @param polish_record - строка в обратной натации.
 */
void convert_to_polish_record(char *infix_record, char *polish_record);

/**
 * @brief Функция определения оператора.
 * @param c - входящий символ.
 * @result 1 - символ является оператором, 0 - символ не является оператором.
 */
int is_operator(char c);

/**
 * @brief Функция преобразования лексемы в односимвольный вид.
 * @param lexeme - указатель на лексему в стэке
 * @result возвращает символ.
 */
char get_op_name(char *lexeme);

/**
 * @brief Функция установки приоритета для операторов
 * @param op - оператор
 * @result возвращает целое число.
 */
int get_op_priority(char op);

/**
 * @brief Функция подсчета значения
 * @param polish_record - указатель на строку в обратном виде(после работы
 * convert_to_polish_record)
 * @param error - указатель на целое число, в которое будет записан код ошибки,
 * если она произойдет.
 * @param x - значение Х(аргумент).
 * @result возвращает результат подсчета в виде типа данных - дабл.
 */
double calculate_value(char *polish_record, double x, int *error);

#ifdef __cplusplus
}
#endif

#endif  // SRC_POLISH_H_
