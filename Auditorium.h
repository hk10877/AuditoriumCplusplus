#ifndef AUDITORIUM_H
#define AUDITORIUM_H
#include <string>
#include "Node.h"

class Auditorium 
{
  private:
  Node* head;
  std::string totalAudiLine;
  char seatType;

    
public: //public functions
    Auditorium(); //default constructor
    ~Auditorium(); //destructor
    Auditorium(std::string totalAudiLine); //constructors
    void insertNodeNext(char data, int row, int col);
    void insertNodeDown(char dataAudi, int row, int col);
    void printAuditorium(std::string fileName);
    void displayPrintAuditorium();
    int getRows();
    int getCols();
    bool isAvailable(int row, char seat, int totalQ);
    void reserveSeatsInAuditorium(int row, char seat, int adultQ, int childQ, int seniorQ);
    char unReserveSeatsInAuditorium(int row, char seat);
    std::string displayAdminReport(); 
    std::string bestAvailable(int totalQuantity);
    friend std::ostream& operator<<(std::ostream& ostr, const Auditorium& obj);
    


}; 

#endif // AUDITORIUM_H



