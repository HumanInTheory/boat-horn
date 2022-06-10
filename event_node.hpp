#ifndef EVENT_NODE
#define EVENT_NODE

// Represents the various low-level actions
enum Event { NONE, ACTIVATE_BUZZER, ACTIVATE_HORN, SILENCE_BUZZER, SILENCE_HORN };

// Defines a node for a doubly-linked list
class EventNode {
public:
  unsigned int offsetDS;
  Event event;
  EventNode *prev, *next;
};

#endif
