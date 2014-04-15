/*
 * Stack module
 *
 * Has a stack class
 */
#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h> // size_t, abort
#ifdef GROUND_TEST
#include <iostream> // std::cerr
#else
#include <Arduino.h> // Serial
#endif

const size_t DEFAULT_CAP = 10;

void panicOOM() {
#ifdef GROUND_TEST
  std::cerr << "PANIC: Out of memory.\n";
#else
  if (Serial) {
    Serial.println("PANIC: Out of memory");
  }
#endif
  abort();
}

void *xmalloc(size_t size) {
  void *ret = malloc(size);
  if (ret == NULL) {
    panicOOM();
  }
  return ret;
}

void *xrealloc(void *ptr, size_t size) {
  void *ret = realloc(ptr, size);
  if (ret == NULL) {
    panicOOM();
  }
  return ret;
}

template<class E>
class Stack {
private:
  E *items;
  size_t len;
  size_t cap;
public:
  Stack() {
    len = 0;
    items = (E *) xmalloc(sizeof(E) * DEFAULT_CAP);
    cap = DEFAULT_CAP;
  }

  ~Stack() {
    for (int i = 0; i < len; i++) {
      items[i].~E();
    }
    free(items);
  }

  void push(const E &item) {
    if (len == cap) { // Out of space
      size_t newCap = cap + cap / 2;
      E *newItems = (E *) xrealloc(items, sizeof(E) * newCap);
      items = newItems;
      cap = newCap;
    }
    items[len++] = item;
  }

  E pop() {
    E ret;
    // If empty, you are not guaranteed to get anything meaningful back
    if (empty()) {
      return ret;
    }
    ret = items[len - 1];
    items[len - 1].~E();
    len--;
    return ret;
  }

  bool empty() const {
    return len == 0;
  }
};

#endif // __STACK_H_
