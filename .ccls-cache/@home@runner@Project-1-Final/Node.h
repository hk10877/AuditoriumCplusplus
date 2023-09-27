#ifndef NODE_H
 #define NODE_H
 #include <string>
#include "Seat.h"

class Node {
public:
  char data;
  Node* next;
  Node* down;
  Seat* payload;

  // Default constructor
  Node();
  

  // Parameterised Constructor
  Node(char data);

  char getNode(); //Accessor

  void setNode(char data); //Mutator

//overloaded operator
  friend std::ostream& operator<<(std::ostream& ostr, const Node& obj);


};

#endif // NODE_H
