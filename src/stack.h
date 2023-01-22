/*!
\file
\brief Заголовочный файл с объявлениями функций для работы со стэком
*/

#ifndef SRC_STACK_H_
#define SRC_STACK_H_

// Описание стpуктуpы(элемента стека)
struct stack {
  char op;
  double value;
  struct stack *prev;
};

/* Функции */

/**
 * @brief Инициализация стэка, выделение памяти.
 * @param op - символ
 * @return Возвращает указатель на первый элемент стэка
 */
struct stack *init_stack(char op);

/**
 * @brief добавляем элемент в стэк
 * переменная a возвpащает указатель на последний элемент стека
 * @param head - стек
 * @param op - символ
 * @return Возвращает указатель на добавленный элемент стэка
 */
struct stack *push(struct stack *head, char op);

/**
 * @brief Удаляет последний символ стека.
 * Возвpащает удаляемый символ.
 * Изменяет указатель на веpшину стека
 * @param head - стек
 * @param a - символ с веpшины стека
 * @return Возвращает указатель на предыдущий элемент в стэке
 */
struct stack *pop(struct stack *head);

/**
 * @brief Удаляет стэк. Чистит память.
 * @param head - стек
 * @param a - символ с веpшины стека
 */
void destroy_stack(struct stack *root);

#endif  // SRC_STACK_H_
