#ifndef AUDITORIUM_H
 #define AUDITORIUM_H
 #include <string>
#include "Node.h"

class Auditorium 
{
  public:
  Node* head;
  std::string totalAudiLine;
  char seatType;

    
public: //public functions
    Auditorium(); //default constructor
    ~Auditorium(); //destructor
    Auditorium(std::string totalAudiLine); //constructors
    void insertNodeNext(char data, int row, int col);
    void insertNodeDown(char dataAudi, int row, int col);
    void printAuditorium();
    void displayPrintAuditorium();
    int getRows();
    int getCols();
    bool isAvailable(int row, char seat, int totalQ);
    void reserveSeatsInAuditorium(int row, char seat, int adultQ, int childQ, int seniorQ);
    void displayReport(); 
    std::string bestAvailable(int totalQuantity);
    friend std::ostream& operator<<(std::ostream& ostr, const Auditorium& obj);
    


}; 

#endif // AUDITORIUM_H



