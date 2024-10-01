#include <iostream>
#include "Node.h"
#include "Seat.h"

/*

Node – Node.h and Node.cpp
o Members
▪ Next (Node pointer)
▪ Down (Node pointer)
▪ Payload (Seat object)
o Methods
▪ Default constructor
▪ Overloaded constructor
▪ Mutators
▪ Accessors
▪ Overloaded << operator  --left
  • will use the Seat’s overloaded << method --left

*/


  // Default constructor
  /*void*/ Node::Node()
  {
    data = 0;
    next = NULL;
    down = nullptr;
  }

  // Parameterised Constructor
  /*void*/ Node::Node(char data)
  {
    this->data = data;
    this->next = NULL;
    this->down = nullptr;
  }

//Accessor
  char Node::getNode()
  {
    return data;
  }

//Mutator
  void Node:: setNode(char data)
  {
    this->data = data;
    this->payload->setTicketType(data);
  }

//Overloaded constructor
  std::ostream& operator<<(std::ostream& ostr, const Node& obj){
    ostr << *obj.payload;
    return ostr;
  }


  

