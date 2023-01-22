#ifndef SRC_POLISH_H_
#define SRC_POLISH_H_
#define STACK_MAX_SIZE 300
#define MAX_INFIX_LENGTH 300

#ifdef __cplusplus
extern "C" {
#endif
#include <string.h>

#define SOF -1   // стек переполнен
#define SUF -2   // недостаточно операндов в стеке
#define UNK -3   // неверное значение
#define NCLB -4  // нет закр скобки
#define EINF -5

int get_priority(char *op);
void convert_to_polish_record(char *infix_record, char *polish_record);
int is_operator(char c);
void split_to_lexeme(char *infix_record, char **lexeme);
char get_op_name(char *lexeme);
int get_op_priority(char op);
double calculate_value(char *polish_record, double x, int *error);

#ifdef __cplusplus
}
#endif

#endif  // SRC_POLISH_H_
