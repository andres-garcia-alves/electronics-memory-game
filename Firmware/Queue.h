#include "Definitions.h"

#ifndef QUEUE_H
#define QUEUE_H

class Queue {
  private:
    stCommand _data[QUEUE_SIZE + 1];
    byte _front, _back, _count, _maxitems;
  public:
    Queue() { 
      _front = 0;
      _back = 0;
      _count = 0;
      _maxitems = QUEUE_SIZE;
    }
    void push(stCommand item);
    stCommand pop();
    byte count();
    void clear();
};

void Queue::push(stCommand item)
{
  if(_count < _maxitems) { // drops out when full
    _data[_back++] = item;
    ++_count;

    if (_back > _maxitems) // check wrap around
      _back -= (_maxitems + 1);
  }
}

stCommand Queue::pop() {
  if(_count <= 0) {
    return stCommand(); // returns empty

  } else {
    stCommand result = _data[_front];
    _front++;
    --_count;

    if (_front > _maxitems) // check wrap around
      _front -= (_maxitems + 1);

    return result;
  }
}

byte Queue::count() 
{
  return _count;
}

void Queue::clear() 
{
  _front = _back;
  _count = 0;
}

#endif
