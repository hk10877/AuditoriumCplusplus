#ifndef NODE_H
#define NODE_H
#include <string>
#include "Seat.h"

class Node {

  private:
  char data;
  Node* next;
  Node* down;
  Seat* payload;

  public:
  // Default constructor
  Node();
  

  // Parameterised Constructor
  Node(char data);

  char getNode(); //Accessor
  Node* getDown(){return down;}
  Node* getNext(){return next;}

  void setNode(char data);//{this->data = data;} //Mutator
  void setPayload(Seat* payload){this->payload = payload;}
  void setNext(Node* next){this->next = next;}
  void setDown(Node* down){this->down = down;}

//overloaded operator
  friend std::ostream& operator<<(std::ostream& ostr, const Node& obj);


};

#endif // NODE_H
