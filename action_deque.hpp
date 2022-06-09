#ifndef ACTION_DEQUE
#define ACTION_DEQUE

#include "action_node.hpp"

// Defines a double-ended queue based on a linked list of ActionNode
class ActionDeque {
private:
  int dequeSize;
  ActionNode* front;
  ActionNode* rear;

public:
  ActionDeque();
  ~ActionDeque();

  void insertFront(unsigned int timeToPerform, Action action);
  void insertRear(unsigned int timeToPerform, Action action);

  void deleteFront();
  void deleteRear();

  unsigned int getFrontTime();
  unsigned int getRearTime();

  Action getFrontAction();
  Action getRearAction();

  bool isEmpty();
  int size();
  void erase();
};

#endif
