#ifndef EVENT_DEQUE
#define EVENT_DEQUE

#include "event_node.hpp"

// Defines a double-ended queue based on a linked list of EventNode
class EventDeque {
private:
  int dequeSize;
  EventNode* front;
  EventNode* rear;

public:
  EventDeque();
  ~EventDeque();

  void insertFront(unsigned int offsetDS, Event event);
  void insertRear(unsigned int offsetDS, Event event);

  void deleteFront();
  void deleteRear();

  EventNode* getFront();
  EventNode* getRear();

  bool isEmpty();
  int size();
  void erase();
};

#endif
