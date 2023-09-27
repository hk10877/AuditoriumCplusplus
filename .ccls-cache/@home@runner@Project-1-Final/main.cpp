//Harshita Kumari NetID: hxk220066
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>
#include "Auditorium.h"
#include "Node.h"
#include "Seat.h"


std::string totalAudiLine; // Variable that will hold the string of the auditorium


int main() {
  

  std::cout << "Enter file name: " << std::endl;
  
  int row = 0;
  std::string name;

  std::cin >> name; //inputting the file name
  std::ifstream inputFile(name);
  if (inputFile.is_open()) // missing file check
  {
    std::string audiLine;
    
    //Reading in the file, replacing the newlines with 'X'
    while (getline(inputFile, audiLine))
    {
      row++;
      totalAudiLine += 'X';
      totalAudiLine += audiLine;
      
    }
  
    

    inputFile.close(); //close input file
  } 
  else 
  {
    std::cout << "Error: Unable to open the file." << std::endl;
  }

  Auditorium *auditorium = new Auditorium(totalAudiLine); //dynamic allocation of auditorium in the memory

  //Variables created for input vaildation
  char menuVaildating;
  int menu_input = 1;
  std::string askRow;
  std::string askSeatLetter;
  std::string adultTicketCount;
  std::string childTicketCount;
  std::string seniorTicketCount;
  int totalTickets;

  int correctAskRow;
  char correctSeatLetter;
  int childTicketQ;
  int seniorTicketQ;
  int adultTicketQ;
  
  //loop while condition is false
  while (menu_input != 2) { 
    std::cout << std::endl;
    std::cout << "Main Menu" << std::endl;
    std::cout << "1. Reserve Seats" << std::endl;
    std::cout << "2. Exit" << std::endl;
    

    std::cin >> menuVaildating;
    
    if (isdigit(menuVaildating))
    {
      menu_input = menuVaildating - '0'; //converting char to int

      if (menu_input == 1 || menu_input == 2)
      {
        //skip
      }
    
    }
    else{continue;}
    std::cout << std::endl;

    if (menu_input == 1) {
      auditorium -> displayPrintAuditorium();
      
      while (true) {
        std::cout << "Please enter Row Number: " << std::endl;
        std::cin >> askRow; 

        //vaildating row number
        std::istringstream checking(askRow);

        if (checking >> correctAskRow && checking.eof()) 
        {
        // Input is a valid integer
        
        } 
        else 
        {
        // Input is not an integer
          continue;
        }

          if (correctAskRow <= auditorium ->getRows() && correctAskRow > 0)
          {
            break;
          }
              

        std::cout << std::endl;
      }

     
      while (true) {
        std::cout << "Please enter Seat Letter: " << std::endl;
        std::cin >> askSeatLetter;
        
         //validating column number
        if (askSeatLetter.length() == 1 && std::isalpha(askSeatLetter[0]))
        {
        // Input is a single letter
          correctSeatLetter = askSeatLetter.at(0);
       } 
        else {
        // Input is not a single letter
        
    }

        //checking if char is in bounds
        if (correctSeatLetter >= 'A' && correctSeatLetter <= auditorium -> getCols() + 65) 
        {
          break;
        }
        std::cout << std::endl;
      }

      //
      while (true) {
        std::cout << "Please enter Adult Ticket Count: " << std::endl;
        std::cin >> adultTicketCount;
         //validating Adult Ticket Count
        std::istringstream checking(adultTicketCount);

        if (checking >> adultTicketQ && checking.eof()) 
        {
        // Input is a valid integer
        
        } 
        else 
        {
        // Input is not an integer
          continue;
        }
        
        if (adultTicketQ >= 0) // validating adult ticket count is in bounds
        { 
          break;
        }
        std::cout << std::endl;
      }

      while (true) {
        std::cout << "Please enter Child Ticket Count: " << std::endl;
        std::cin >> childTicketCount;

        //validating Child Ticket Count
        std::istringstream checking(childTicketCount);

        if (checking >> childTicketQ && checking.eof()) 
        {
        // Input is a valid integer
        
        } 
        else 
        {
        // Input is not an integer
          continue;
        }



        if (childTicketQ >= 0) // validating Child ticket count is in bounds
        {
          break;
        }
        std::cout << std::endl;
      }

      while (true) {
        std::cout << "Please enter Senior Ticket Count: " << std::endl;
        std::cin >> seniorTicketCount;
        
        //validating Senior Ticket Count
        std::istringstream checking(seniorTicketCount);

        if (checking >> seniorTicketQ && checking.eof()) 
        {
        // Input is a valid integer
        
        } 
        else 
        {
        // Input is not an integer
          continue;
        }
        
        if (seniorTicketQ >= 0) // validating Senior ticket count is in bounds
        {
          break;
        }
        std::cout << std::endl;
      }

      totalTickets = seniorTicketQ + childTicketQ + adultTicketQ;

      bool ret = false;

      ret = auditorium -> isAvailable(correctAskRow, correctSeatLetter, totalTickets);
      
      if (ret)  // seats are available
      {
        auditorium -> reserveSeatsInAuditorium(correctAskRow, correctSeatLetter, adultTicketQ,
                     childTicketQ, seniorTicketQ);
        std::cout << "Seats reserved." << std::endl;
        
      }
       else //seats are not available
       {
          std::string retBestAvail = auditorium -> bestAvailable(totalTickets);
          std::cout << std::endl;
          std::cout << "Recommended Seats" << std::endl;
         std::cout << retBestAvail << std::endl;

         if (retBestAvail == "*")
         {
           std::cout << "no seats available" <<std::endl;
           continue;
         }

          
        std::cout << "Please select alternate seats." <<std::endl;
        std::cout << "Enter Y to reserve or N to refuse:" << std::endl;
        char reserveAnotherSeats;
        std::cin >> reserveAnotherSeats;
        char seatLetter = retBestAvail[1];
        char rowChar = retBestAvail[0];
        int rowNumber = rowChar - '0'; // converts char to int

          if (reserveAnotherSeats == 'Y') 
          {
            auditorium -> reserveSeatsInAuditorium(rowNumber, seatLetter, adultTicketQ, childTicketQ, seniorTicketQ);
            
            std::cout << "Alternate seats reserved." << std::endl;
            

          } else if (reserveAnotherSeats == 'N') {
            std::cout << "Alternate seats refused and not reserved." << std::endl;
           
            continue;
          } else {
            std::cout << "Invalid input." << std::endl;
            std::cout << "No Reservations." << std::endl;
           
          }
         
       }
      
      
      
    }
  }
  auditorium ->displayReport(); 
  auditorium -> printAuditorium();
  auditorium -> ~Auditorium(); // deletes auditorium
 
} //end
