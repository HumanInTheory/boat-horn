#include "action_deque.hpp"

#include <Arduino.h>

// Creates an ActionDeque with NULL references and a size of zero
ActionDeque::ActionDeque() {
  front = rear = NULL;
  dequeSize = 0;
}

// Erases every ActionNode before destructing
ActionDeque::~ActionDeque() {
  erase();
}

bool ActionDeque::isEmpty() {
  return ( front == NULL );
}

int ActionDeque::size() {
  return dequeSize;
}

// Inserts a new node based on data into the front
void ActionDeque::insertFront( unsigned int decisecondsToPerform, Action action ) {
  // Create node
  ActionNode* newNode = new ActionNode();
  newNode->decisecondsToPerform = decisecondsToPerform;
  newNode->action = action;

  // Define front and rear pointers if ActionDeque is empty
  // Otherwise make new node front and set its next reference to the previous front
  if ( isEmpty() ) {
    front = rear = newNode;
  }
  else {
    newNode->next = front;
    front->prev = newNode;
    front = newNode;
  }

  dequeSize++;
}

// Inserts a new node based on data into the rear
void ActionDeque::insertRear( unsigned int decisecondsToPerform, Action action ) {
  // Create node
  ActionNode* newNode = new ActionNode();
  newNode->decisecondsToPerform = decisecondsToPerform;
  newNode->action = action;

  // Define front and rear pointers if ActionDeque is empty
  // Otherwise make new node rear and set its prev reference to the previous rear
  if ( isEmpty() ) {
    front = rear = newNode;
  }
  else {
    newNode->prev = rear;
    rear->next = newNode;
    rear = newNode;
  }

  dequeSize++;
}

// Deletes the node refenced by front, replacing the reference with the next node
void ActionDeque::deleteFront() {
  if ( !isEmpty() ) {
    ActionNode* temp = front;
    front = front->next;

    // If only 1 node present
    if (front == NULL) {
      rear == NULL;
    }
    else {
      front->prev = NULL;
    }

    delete temp;

    dequeSize--;
  }
}

// Deletes the node refenced by rear, replacing the reference with the prev node
void ActionDeque::deleteRear() {
  if ( !isEmpty() ) {
    ActionNode* temp = rear;
    rear = rear->prev;

    // If only 1 node present
    if (rear == NULL) {
      front == NULL;
    }
    else {
      rear->next = NULL;
    }

    delete temp;

    dequeSize--;
  }
}

// Returns the time offset of the front action in deciseconds
unsigned int ActionDeque::getFrontTime() {
  if( isEmpty() ) {
    return -1;
  }
  else {
    return front->decisecondsToPerform;
  }
}

// Returns the time offset of the rear action in deciseconds
unsigned int ActionDeque::getRearTime() {
  if( isEmpty() ) {
    return -1;
  }
  else {
    return rear->decisecondsToPerform;
  }
}

// Returns the enum of the front action
Action ActionDeque::getFrontAction() {
  if( isEmpty() ) {
    return Action::NONE;
  }
  else {
    return front->action;
  }
}

// Returns the enum of the rear action
Action ActionDeque::getRearAction() {
  if( isEmpty() ) {
    return Action::NONE;
  }
  else {
    return rear->action;
  }
}

// Iterates through the list, deleting each ActionNode
void ActionDeque::erase() {
  rear = NULL;

  while ( front != NULL ) {
    ActionNode* temp = front;
    front = front->next;
    delete front;
  }

  dequeSize = 0;
}
