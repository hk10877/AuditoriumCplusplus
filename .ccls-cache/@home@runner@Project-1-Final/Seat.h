#ifndef SEAT_H
#define SEAT_H
#include <string>


class Seat
{
  public:
  int row;
  char seat;
  char ticketType;

  Seat(); //default constructor

  Seat(int row, char seat, char ticketType); //Overloaded constructor
  
  char GetSeat(); //Accessor

  void SetSeat(char seat); //Mutator

  //std::string operator<<(Seat rhs);
  friend std::ostream& operator<<(std::ostream& ostr, const Seat& obj);

};

#endif // SEAT_H