/*
 * Stack module
 *
 * Has a stack class
 */
#ifndef __STACK_H_
#define __STACK_H_

#include <stdlib.h> // size_t
#include <string.h>

const size_t DEFAULT_CAP = 10;

template<class E>
class Stack {
private:
  E *items;
  size_t len;
  size_t cap;
  bool _zombie;
public:
  Stack() {
    len = 0;
    items = (E *) malloc(sizeof(E) * DEFAULT_CAP);
    if (items == NULL) {
      _zombie = true;
      return;
    }
    cap = DEFAULT_CAP;
    _zombie = false;
  }

  ~Stack() {
    if (!_zombie) {
      free(items);
    }
    _zombie = true;
  }

  bool push(const E &item) {
    if (_zombie) {
      return false;
    }
    if (len == cap) { // Out of space
      size_t newCap = cap + cap / 2;
      E *newItems = (E *) realloc(items, sizeof(E) * newCap);
      if (newItems == NULL) {
	return false;
      }
      items = newItems;
      cap = newCap;
    }
    items[len++] = item;
    return true;
  }

  E pop() {
    E ret;
    // If empty or zombie, you are not guaranteed to get anything meaningful back
    if (empty() || _zombie) {
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

  bool zombie() const {
    return _zombie;
  }
};

#endif // __STACK_H_
