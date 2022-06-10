#include "event_deque.hpp"

#include <Arduino.h>

// Creates an ActionDeque with NULL references and a size of zero
EventDeque::EventDeque() {
  front = rear = NULL;
  dequeSize = 0;
}

// Erases every ActionNode before destructing
EventDeque::~EventDeque() {
  erase();
}

bool EventDeque::isEmpty() {
  return ( front == NULL );
}

int EventDeque::size() {
  return dequeSize;
}

// Inserts a new node based on data into the front
void EventDeque::insertFront( unsigned int offsetDS, Event event ) {
  // Create node
  EventNode* newNode = new EventNode();
  newNode->offsetDS = offsetDS;
  newNode->event = event;

  // Define front and rear pointers if EventDeque is empty
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
void EventDeque::insertRear( unsigned int offsetDS, Event event ) {
  // Create node
  EventNode* newNode = new EventNode();
  newNode->offsetDS = offsetDS;
  newNode->event = event;

  // Define front and rear pointers if EventDeque is empty
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
void EventDeque::deleteFront() {
  if ( !isEmpty() ) {
    EventNode* temp = front;
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
void EventDeque::deleteRear() {
  if ( !isEmpty() ) {
    EventNode* temp = rear;
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
EventNode* EventDeque::getFront() {
  return front;
}

// Returns the time offset of the rear action in deciseconds
EventNode* EventDeque::getRear() {
  return rear;
}

// Iterates through the list, deleting each ActionNode
void EventDeque::erase() {
  rear = NULL;

  while ( front != NULL ) {
    EventNode* temp = front;
    front = front->next;
    delete front;
  }

  dequeSize = 0;
}
