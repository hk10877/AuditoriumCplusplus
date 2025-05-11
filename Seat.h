#ifndef SEAT_H
#define SEAT_H
#include <string>


class Seat
{
  private:
  int row;
  char seat;
  char ticketType;

  public:
  Seat(); //default constructor

  Seat(int row, char seat, char ticketType); //Overloaded constructor
  
  char getSeat(); //Accessor
  char* getTicketType() {return &ticketType;}
  int getRow() {return row;}
  
  void setRow(int row){this->row = row;}
  void setSeat(char seat); //Mutator
  void setTicketType(char ticketType){this->ticketType = ticketType;}

  friend std::ostream& operator<<(std::ostream& ostr, const Seat& obj);

};

#endif // SEAT_H
