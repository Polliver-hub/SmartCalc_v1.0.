#include "polish.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

void convert_to_polish_record(char *infix_record, char *polish_record) {
  struct stack *operators = NULL;
  char output_queue[MAX_INFIX_LENGTH * 2];
  strcpy(output_queue, "");
  char str[MAX_INFIX_LENGTH * 2];
  strcpy(str, "");
  int prev = 0;  // 1 - цифра, 2 - оператор, 3 - символ
  for (char *ptr = infix_record; *ptr != '\0'; ptr++) {
    int len = strlen(str);
    if ((*ptr > 47 && *ptr < 58) || *ptr == '.') {
      if (prev == 1 || prev == 0) {
        str[len] = *ptr;
        str[len + 1] = '\0';
      } else {
        str[len] = ' ';
        str[len + 1] = *ptr;
        str[len + 2] = '\0';
      }
      prev = 1;
    } else if (*ptr == 'x' || is_operator(*ptr)) {
      str[len] = ' ';
      str[len + 1] = *ptr;
      str[len + 2] = '\0';
      prev = 2;
    } else if (*ptr != ' ') {
      if (prev == 3 || prev == 0) {
        str[len] = *ptr;
        str[len + 1] = '\0';
      } else {
        str[len] = ' ';
        str[len + 1] = *ptr;
        str[len + 2] = '\0';
      }
      prev = 3;
    }
  }
  char *lexeme = strtok(str, " ");
  while (lexeme) {
    double num = atof(lexeme);
    if (num) {
      strcat(output_queue, lexeme);
      strcat(output_queue, " ");
    } else if (strcmp(lexeme, "x") == 0) {
      strcat(output_queue, lexeme);
      strcat(output_queue, " ");
    } else if (strcmp(lexeme, "0") == 0) {
      strcat(output_queue, lexeme);
      strcat(output_queue, " ");
    } else {
      char op = get_op_name(lexeme);
      if (op == '(') {
        operators = push(operators, op);
      } else if (op == ')') {
        while (operators->op != '(') {
          int len = strlen(output_queue);
          output_queue[len] = operators->op;
          output_queue[len + 1] = ' ';
          output_queue[len + 2] = '\0';
          operators = pop(operators);
        }
        operators = pop(operators);
      } else {
        while (operators != NULL &&
               get_op_priority(operators->op) >= get_op_priority(op)) {
          int len = strlen(output_queue);
          output_queue[len] = operators->op;
          output_queue[len + 1] = ' ';
          output_queue[len + 2] = '\0';
          operators = pop(operators);
        }
        operators = push(operators, op);
      }
    }
    lexeme = strtok(NULL, " ");
  }
  while (operators != NULL) {
    int len = strlen(output_queue);
    output_queue[len] = operators->op;
    output_queue[len + 1] = ' ';
    output_queue[len + 2] = '\0';
    operators = pop(operators);
  }
  strcpy(polish_record, output_queue);
}

int is_operator(char c) {
  char *operators = "+-m*/()^";
  return strchr(operators, c) ? 1 : 0;
}

char get_op_name(char *lexeme) {
  char res = '\0';
  if (strcmp(lexeme, "+") == 0) res = '+';
  if (strcmp(lexeme, "-") == 0) res = '-';
  if (strcmp(lexeme, "m") == 0) res = 'm';
  if (strcmp(lexeme, "*") == 0) res = '*';
  if (strcmp(lexeme, "/") == 0) res = '/';
  if (strcmp(lexeme, "(") == 0) res = '(';
  if (strcmp(lexeme, ")") == 0) res = ')';
  if (strcmp(lexeme, "sin") == 0) res = 's';
  if (strcmp(lexeme, "asin") == 0) res = 'S';
  if (strcmp(lexeme, "cos") == 0) res = 'c';
  if (strcmp(lexeme, "acos") == 0) res = 'C';
  if (strcmp(lexeme, "tan") == 0) res = 't';
  if (strcmp(lexeme, "atan") == 0) res = 'T';
  if (strcmp(lexeme, "sqrt") == 0) res = 'q';
  if (strcmp(lexeme, "ln") == 0) res = 'l';
  if (strcmp(lexeme, "log") == 0) res = 'L';
  if (strcmp(lexeme, "^") == 0) res = '^';
  return res;
}

int get_op_priority(char op) {
  int priority = 0;
  if (op == '^') priority = 10;
  if (op == '*' || op == '/') priority = 5;
  if (op == 'm') priority = 4;
  if (op == '+' || op == '-') priority = 2;
  if (op == 's' || op == 'S' || op == 'c' || op == 'C' || op == 't' ||
      op == 'T' || op == 'g' || op == 'q' || op == 'l' || op == 'L')
    priority = 6;
  return priority;
}

double calculate_value(char *polish_record, double x, int *error) {
  struct stack *nums = NULL;
  int scount = 0;
  int bracketOP = 0;
  int bracketCL = 0;
  char polish_record_copy[MAX_INFIX_LENGTH];
  strcpy(polish_record_copy, polish_record);
  char *lexeme = strtok(polish_record_copy, " ");
  while (lexeme && *error == 0) {
    if (strchr("(", *lexeme) != NULL) {
      bracketOP++;
    }
    if (strchr(")", *lexeme) != NULL) {
      bracketCL++;
    }
    if ((strchr("+*/m^", *lexeme) != NULL && scount < 2) ||
        (strchr("-sScCtTqLl", *lexeme) != NULL && scount < 1)) {
      *error = SUF;
    } else {
      double num = atof(lexeme);
      if (num) {
        nums = push(nums, 'd');
        nums->value = num;
      } else if (strcmp(lexeme, "x") == 0) {
        nums = push(nums, 'd');
        nums->value = x;
      } else if (strcmp(lexeme, "0") == 0) {
        nums = push(nums, 'd');
        nums->value = 0;
      } else {
        char op = *lexeme;
        double a, b;
        switch (op) {
          case '+':
            a = nums->value;
            nums = pop(nums);
            b = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = a + b;
            break;
          case '-':
            b = nums->value;
            nums = pop(nums);
            a = nums ? nums->value : 0;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = a - b;
            break;
          case 'm':
            b = nums->value;
            nums = pop(nums);
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = fmod(a, b);
            break;
          case '*':
            a = nums->value;
            nums = pop(nums);
            b = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = a * b;
            break;
          case '/':
            b = nums->value;
            nums = pop(nums);
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = a / b;
            break;
          case '^':
            b = nums->value;
            nums = pop(nums);
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = pow(a, b);
            break;
          case 's':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = sin(a);
            break;
          case 'S':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = asin(a);
            break;
          case 'c':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = cos(a);
            break;
          case 'C':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = acos(a);
            break;
          case 't':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = tan(a);
            break;
          case 'T':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = atan(a);
            break;
          case 'l':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = log(a);
            break;
          case 'L':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = log10(a);
            break;
          case 'q':
            a = nums->value;
            nums = pop(nums);
            nums = push(nums, 'd');
            nums->value = sqrt(a);
            break;
        }
      }
      lexeme = strtok(NULL, " ");
    }
    scount++;
  }
  if ((bracketOP + bracketCL) % 2 != 0 && bracketOP != bracketCL) {
    *error = NCLB;
  }
  double y = nums ? nums->value : 0;
  destroy_stack(nums);
  return y;
}
