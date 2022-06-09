#ifndef ACTION_NODE
#define ACTION_NODE

// Represents the various low-level actions
enum Action { NONE, ACTIVATE_BUZZER, ACTIVATE_HORN, SILENCE_BUZZER, SILENCE_HORN };

// Defines a node for a doubly-linked list
class ActionNode {
public:
  unsigned int decisecondsToPerform;
  Action action;
  ActionNode *prev, *next;
};

#endif
