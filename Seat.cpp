#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Seat.h"

/*
Seat – Seat.h and Seat.cpp
o Members
  ▪ Row (integer)
  ▪ Seat (character)
  ▪ Ticket type (character)
o Methods
  ▪ Default constructor
  ▪ Overloaded constructor
    • Parameters: row, seat, ticket type
  ▪ Mutators
  ▪ Accessors
  ▪ Overloaded << operator
    • acts like toString in Java
    • returns a formatted string containing the ticket type

*/

//Default constructor
/*void*/ Seat::Seat() {
  row = 1;
  seat = 'A';
  ticketType = 'A';
}

//Overloaded constructor
//Parameters: row, seat, ticket type
/*void*/ Seat::Seat(int row, char seat, char ticketType) {
  this->row = row;
  this->seat = seat;
  this->ticketType = ticketType;
}

char Seat::getSeat() { return this->seat; } //Accessor

void Seat::setSeat(char seat) { this->seat = seat; }  //Mutator

//Overloaded << operator
std::ostream& operator<<(std::ostream& ostr, const Seat& obj){
    ostr << obj.ticketType;
    return ostr;
  }