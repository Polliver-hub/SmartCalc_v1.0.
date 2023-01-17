#ifndef SRC_POLISH_H_
#define SRC_POLISH_H_
#define MAX_INFIX_LENGTH 100

#ifdef __cplusplus
extern "C" {
#endif

// struct polish_element {
//     double value;
//     char op;
//     // struct polish_element *next;
// };

int get_priority(char *op);
void convert_to_polish_record(char* infix_record, char* polish_record);
int is_operator(char c);
void split_to_lexeme(char* infix_record, char **lexeme);
char get_op_name(char *lexeme);
int get_op_priority(char op);
double calculate_value(char *polish_record, double x);

#ifdef __cplusplus
}
#endif

#endif  // SRC_POLISH_H_
