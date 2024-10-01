#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <cstring> 
#include <algorithm>
#include <unordered_map> 
#include "Auditorium.h"
#include "Node.h"
#include "Seat.h"


std::string totalAudiLine; // Variable that will hold the string of the auditorium

//This class holds the orders of each customer
class Order
{
    private:
    int audiNumber;
    std::string startingSeat;
    std::string endingSeat;    
    int adultTickets;
    int childTickets;
    int seniorTickets;
    int totalTickets;
    std::vector<std::string> tickets;
    
    public:
    //Mutators
    void setAudiNumber(int audiNumber){this->audiNumber = audiNumber;}
    void setStartingSeat(std::string startingSeat){this->startingSeat = startingSeat;}
    void setEndingSeat(std::string endingSeat){this->endingSeat = endingSeat;}
    void setAdultTickets(int adultTickets){this->adultTickets = adultTickets;}
    void setChildTickets(int childTickets){this->childTickets = childTickets;}
    void setSeniorTickets(int seniorTickets){this->seniorTickets = seniorTickets;}
    
    //Accessors
    int getAudiNumber(){return audiNumber;}
    std::string getStartingSeat(){return startingSeat;}
    std::string getEndingSeat(){return endingSeat;}
    int getAdultTickets(){return adultTickets;}
    int getChildTickets(){return childTickets;}
    int getSeniorTickets(){return seniorTickets;}
    int getTotalTickets(){return adultTickets+childTickets+seniorTickets;}
    std::vector<std::string>* getTicketVector() { return &tickets; }
    
    //default constructor
    Order()
    {
        audiNumber = 0;
        startingSeat = "";
        endingSeat = "";
        adultTickets = 0;
        childTickets = 0;
        seniorTickets = 0;
    }
};


//This class contains the password and all the orders of each Customer
class Customer
{
    private:
    std::string password;
    std::vector<Order*> orders;
    
    public:
    
    //default constructor
    Customer()
    {
        password = "";
    }
    
    //Mutators
    void setPassword(std::string password){this->password = password;}
    void addOrder(Order* od){orders.push_back(od);}
    
    //Accessors
    std::string getPassword(){return password;}
    std::vector<Order*>* getOrderVector() { return &orders; }
};


int main() 
{
    //Reading Auditorium 1 from A1.txt
      int row1 = 0;
      std::ifstream inputFile1("A1.txt");
      if (inputFile1.is_open()) // missing file check
      {
        std::string audiLine;
        
        //Reading in the file, replacing the newlines with 'X'
        while (getline(inputFile1, audiLine))
        {
          row1++;
          totalAudiLine += 'X';
          totalAudiLine += audiLine;
          
        }
        inputFile1.close(); //close input file
      } 
      else 
      {
        std::cout << "Error: Unable to open the file." << std::endl;
      }    
      
      Auditorium *auditorium1 = new Auditorium(totalAudiLine); //dynamic allocation of auditorium in the memory
      totalAudiLine = "";
      
      //Reading Auditorium 2 from A2.txt
      int row2 = 0;
      std::ifstream inputFile2("A2.txt");
      if (inputFile2.is_open()) // missing file check
      {
        std::string audiLine;
        
        //Reading in the file, replacing the newlines with 'X'
        while (getline(inputFile2, audiLine))
        {
          row2++;
          totalAudiLine += 'X';
          totalAudiLine += audiLine;
          
        }
        inputFile2.close(); //close input file
      } 
      else 
      {
        std::cout << "Error: Unable to open the file." << std::endl;
      }    
      
      Auditorium *auditorium2 = new Auditorium(totalAudiLine); //dynamic allocation of auditorium in the memory
      
      //Reading Auditorium 3 from A3.txt
      totalAudiLine = "";
      int row3 = 0;
      std::ifstream inputFile3("A3.txt");
      if (inputFile3.is_open()) // missing file check
      {
        std::string audiLine;
        
        //Reading in the file, replacing the newlines with 'X'
        while (getline(inputFile3, audiLine))
        {
          row3++;
          totalAudiLine += 'X';
          totalAudiLine += audiLine;
          
        }
        inputFile3.close(); //close input file
      } 
      else 
      {
        std::cout << "Error: Unable to open the file." << std::endl;
      }    
      
      Auditorium *auditorium3 = new Auditorium(totalAudiLine); //dynamic allocation of auditorium in the memory
      
      //Creates the hashmap in which all the usernames and passwords of the Customer are saved
      std::unordered_map<std::string, Customer*> hashmap;
      std::string userLine;
      std::string username;
      std::string password;
      std::ifstream inputFileUser("userdb.dat");
      if (inputFileUser.is_open()) // missing file check
      {
          while((getline(inputFileUser, userLine)))
          {
              std::stringstream ss(userLine);
              
              ss >> username;
              ss >> password;
              
              Customer* cust = new Customer(); //Creates a new customer object
              cust->setPassword(password);
              hashmap[username] = cust;
          }
      }
      else
      {
          std::cout << "Couldn't open file!" << std::endl;
      }
  
  std::string userOptionInput; //Options for the admin
  
  while(userOptionInput != "3") //while the admin doesn't exit
  {
      std::cout << "Enter your username: " << std::endl;
      std::string yourUsername;
      std::cin >> yourUsername;
      
      int countPassTimes =0;
      bool passwordIsRight = false;
      while (passwordIsRight != true)
      {
          std::cout << "Enter your password: " << std::endl;
          std::string yourPassword;
          std::cin >> yourPassword;
          
          //Vaildating password for the username
          auto search = hashmap.find(yourUsername);
            if (search != hashmap.end()) 
            {
                if(hashmap[yourUsername]->getPassword() == yourPassword)
                {
                    std::cout << "vaild" << std::endl;
                    passwordIsRight = true;
                }
                else{
                    std::cout << "Invalid password" << std::endl;
                    if (countPassTimes == 2) //three times password is asked
                    {
                        break;
                    }
                    
                    countPassTimes++;
                }
            } 
            else 
            {
                std::cout << " Invalid password" << std::endl;
                if (countPassTimes == 2) //three times password is asked
                {
                    break;
                    continue;
                }
                
                countPassTimes++;
            }
          }
          
          if(countPassTimes == 2)
          {
              continue;
          }
      

      bool adminWantsToStayInMainMenu = true;
      bool exittheprogram = false;
      
      //Code for the Admin Logging
      // Admin has a different main menu than the regular customer
      if(yourUsername == "admin")
      {
          while(adminWantsToStayInMainMenu == true){
          std::cout << "Admin Main Menu" << std::endl;
          std::cout << "1. Print Report" << std::endl;
          std::cout << "2. Logout" << std::endl;
          std::cout << "3. Exit" << std::endl;
          
          //Vaildating if the user enters right data
          std::cout << "Choose an option from 1 to 3: " << std::endl;
          std::cin >> userOptionInput;
          if (userOptionInput == "1" || userOptionInput == "2" || userOptionInput == "3")
          {
              
          }
          else{
              continue;
          }
          
          //Admin wants to print report
          if(userOptionInput =="1")
          {
              //Variables to store values from the string returned by displayAdminReport() in the Auditorium class
              std::string periodString;
              std::string totalReservedString;
              std::string adultQString;
              std::string childQString;
              std::string seniorQString;
              std::string totalSalesString;
              
              int period = 0;
              int totalReserved = 0;
              int adultQuant = 0;
              int childQuant = 0;
              int seniorQuant = 0;
              double totalSales = 0;
              
              //These variables help to store the totals for each kind of tickets and seats
              int periodTotal = 0;
              int totalReservedTotal = 0;
              int adultQTotal = 0;
              int childQTotal = 0;
              int seniorQTotal = 0;
              double totalSalesTotal = 0;
              
              std::string rep;
              
              //Calculating all the totals for Auditorium 1
              std::cout << "Auditorium 1    ";
              rep = auditorium1->displayAdminReport();
              std::stringstream s(rep);
              s >> periodString;
              s >> totalReservedString;
              s >> adultQString;
              s >> childQString;
              s >> seniorQString;
              s >> totalSalesString;
              
              period = stoi(periodString);
              totalReserved = stoi(totalReservedString);
              adultQuant = stoi(adultQString);
              childQuant = stoi(childQString);
              seniorQuant = stoi(seniorQString);
              totalSales = stod(totalSalesString);
              
              periodTotal += period;
              totalReservedTotal+= totalReserved;
              adultQTotal+= adultQuant;
              childQTotal+= childQuant;
              seniorQTotal+= seniorQuant;
              totalSalesTotal+= totalSales;
              
              //Setting all the variables back to zero
              periodString = "";
              totalReservedString = "";
              adultQString = "";
              childQString = "";
              seniorQString = "";
              totalSalesString = "";
              
              period = 0;
              totalReserved = 0;
              adultQuant = 0;
              childQuant = 0;
              seniorQuant = 0;
              totalSales = 0;
              
              //Calculating all the totals for Auditorium 2
              std::cout << "Auditorium 2    ";
              rep = auditorium2->displayAdminReport();
              std::stringstream s2(rep);
              s2 >> periodString;
              s2 >> totalReservedString;
              s2 >> adultQString;
              s2 >> childQString;
              s2 >> seniorQString;
              s2 >> totalSalesString;
              
              period = stoi(periodString);
              totalReserved = stoi(totalReservedString);
              adultQuant = stoi(adultQString);
              childQuant = stoi(childQString);
              seniorQuant = stoi(seniorQString);
              totalSales = stod(totalSalesString);
              
              periodTotal += period;
              totalReservedTotal+= totalReserved;
              adultQTotal+= adultQuant;
              childQTotal+= childQuant;
              seniorQTotal+= seniorQuant;
              totalSalesTotal+= totalSales;
              
              //Setting all the variables back to zero
              periodString = "";
              totalReservedString = "";
              adultQString = "";
              childQString = "";
              seniorQString = "";
              totalSalesString = "";
              
              period = 0;
              totalReserved = 0;
              adultQuant = 0;
              childQuant = 0;
              seniorQuant = 0;
              totalSales = 0;
              
              //Calculating all the totals for Auditorium 3
              std::cout << "Auditorium 3    ";
              rep = auditorium3->displayAdminReport();
              std::stringstream s3(rep);
              s3 >> periodString;
              s3 >> totalReservedString;
              s3 >> adultQString;
              s3 >> childQString;
              s3 >> seniorQString;
              s3 >> totalSalesString;
              
              period = stoi(periodString);
              totalReserved = stoi(totalReservedString);
              adultQuant = stoi(adultQString);
              childQuant = stoi(childQString);
              seniorQuant = stoi(seniorQString);
              totalSales = stod(totalSalesString);
              
              periodTotal += period;
              totalReservedTotal+= totalReserved;
              adultQTotal+= adultQuant;
              childQTotal+= childQuant;
              seniorQTotal+= seniorQuant;
              totalSalesTotal+= totalSales;
              
              //printing the total for all the orders
              std::cout << "Total" << "          ";
              std::cout << periodTotal <<"   " << totalReservedTotal <<"   " << adultQTotal;
              std::cout <<"   "<< childQTotal <<"   "<< seniorQTotal <<"   $"<< std::fixed << std::setprecision(2) << totalSalesTotal << std::endl;
  
              
          }
          
          //Admin wants to Logout
          else if(userOptionInput =="2")
          {
              adminWantsToStayInMainMenu = false;
              continue;
          }
          
          //Admin exits the programs and all the data from the 3 auditoriums is written into 3 files
          else if(userOptionInput =="3")
          {
              auditorium1->printAuditorium("A1Final.txt");
              auditorium2->printAuditorium("A2Final.txt");
              auditorium3->printAuditorium("A3Final.txt");
              adminWantsToStayInMainMenu = false;
              exittheprogram = true;
              break;
          }
          
          //Input Vaildation message
          else
          {
              std::cout << "Invaid input" << std::endl;
          }
        }
        if (adminWantsToStayInMainMenu == false && exittheprogram == true)
        {
            break;
        }
        if (adminWantsToStayInMainMenu == false)
        {
            continue;
        }
          
      }
      
      //Display main menu for the regular customer
      bool userWantsToStayInMainMenu = true;
      while(userWantsToStayInMainMenu == true)
      {
          std::cout << "Main Menu" << std::endl;
          std::cout << "1. Reserve Seats" << std::endl;
          std::cout << "2. View Orders" << std::endl;
          std::cout << "3. Update Order" << std::endl;
          std::cout << "4. Display Receipt" << std::endl;
          std::cout << "5. Log Out" << std::endl;
          
          std::cout << "Choose an option from 1 to 5: " << std::endl;
          
          std::string userMainMenuInput;
          std::cin >> userMainMenuInput;
          
          //Reserve Seats in a auditorium
          if (userMainMenuInput == "1")
          {
              std::cout << "Reserve Seats" << std::endl;
              int userAudiChoice;
              std::cout << "1. Auditorium 1" << std::endl;
              std::cout << "2. Auditorium 2" << std::endl;
              std::cout << "3. Auditorium 3" << std::endl;
              std::cout << "Choose an Auditorium from 1 to 3: " << std::endl;
              std::cin >> userAudiChoice;
              
              //Displays the auditoirum according to the choice of the user
              if (userAudiChoice == 1)
              {
                  std::cout << "Here is Auditorium 1" << std::endl;
                  auditorium1->displayPrintAuditorium();
              }
              else if (userAudiChoice == 2)
              {
                  std::cout << "Here is Auditorium 2" << std::endl;
                  auditorium2->displayPrintAuditorium();
              }
              else if (userAudiChoice == 3)
              {
                  std::cout << "Here is Auditorium 3" << std::endl;
                  auditorium3->displayPrintAuditorium();
              }
              else
              {
                  std::cout << "Wrong input" << std::endl;
              }
              
              //Creates a new order that will be added to the order vector of the customer class
              Order* order = new Order;
              order->setAudiNumber(userAudiChoice);
              hashmap[yourUsername]->getOrderVector()->push_back(order); // Pushs the object into the vector
             
              //variables for input validation
              std::string askRow;
              std::string askSeatLetter;
              std::string adultTicketCount;
              std::string childTicketCount;
              std::string seniorTicketCount;
              int totalTickets;
            
              //Variables to store the actual value of the user's input
              int correctAskRow;
              char correctSeatLetter;
              int childTicketQ;
              int seniorTicketQ;
              int adultTicketQ;
              
              //Ask user for row number
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
                  //Checking if the input is in bounds
                  if (userAudiChoice == 1)
                  {
                      if (correctAskRow <= auditorium1 ->getRows() && correctAskRow > 0)
                      {
                        break;
                      }
                  }
                  if (userAudiChoice == 2)
                  {
                      if (correctAskRow <= auditorium2 ->getRows() && correctAskRow > 0)
                      {
                        break;
                      }
                  }
                  if (userAudiChoice == 3)
                  {
                      if (correctAskRow <= auditorium3 ->getRows() && correctAskRow > 0)
                      {
                        break;
                      }
                  }
                std::cout << std::endl;
              }
        
              //Ask user for seat letter
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
                if (userAudiChoice == 1)
                  {
                      if (correctSeatLetter >= 'A' && correctSeatLetter <= auditorium1 -> getCols() + 65-1) 
                        {
                          break;
                        }
                  }
                  if (userAudiChoice == 2)
                  {
                      if (correctSeatLetter >= 'A' && correctSeatLetter <= auditorium2 -> getCols() + 65-1) 
                        {
                          break;
                        }
                  }
                  if (userAudiChoice == 3)
                  {
                      if (correctSeatLetter >= 'A' && correctSeatLetter <= auditorium3 -> getCols() + 65-1) 
                        {
                          break;
                        }
                  }
                
                std::cout << std::endl;
              }
        
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
        
              auto vectSize = hashmap[yourUsername]->getOrderVector()->size();
              totalTickets = seniorTicketQ + childTicketQ + adultTicketQ;
              
              //Selecting the auditorium in which we will make changes
              Auditorium* audiSelected = new Auditorium();
              if(userAudiChoice == 1)
              {
                  audiSelected = auditorium1;
                  
              }
              
              else if(userAudiChoice == 2)
              {
                  audiSelected = auditorium2;
              }
              
              else if(userAudiChoice == 3)
              {
                  audiSelected = auditorium3;
              }
              
              else
              {
                  std::cout << "Invaild Auditorium number." << std::endl;
              }
              
              
              bool ret = false;
              ret = audiSelected -> isAvailable(correctAskRow, correctSeatLetter, totalTickets);
              
              if (ret)  // seats are available
              {
                audiSelected -> reserveSeatsInAuditorium(correctAskRow, correctSeatLetter, adultTicketQ,
                             childTicketQ, seniorTicketQ);
                
                //Making changes to the order object accordingly             
                std::string startingS = std::to_string(correctAskRow); 
                startingS += correctSeatLetter;
                std::string endingS = std::to_string(correctAskRow);
                int endletter = correctSeatLetter + totalTickets;
                char endString = static_cast<char>(endletter);
                endingS += endString;
                hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setAdultTickets(adultTicketQ);
                hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setChildTickets(childTicketQ);
                hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setSeniorTickets(seniorTicketQ);
                hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setStartingSeat(startingS);
                hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setEndingSeat(endingS);
                
                std::cout << "Seats reserved." << std::endl;
                audiSelected->displayPrintAuditorium();
                
              }
               else //seats are not available
               {
                  std::string retBestAvail = audiSelected -> bestAvailable(totalTickets); //Calls bestAvailable fuction for the whole Auditorium
                  std::cout << std::endl;
                  std::cout << "Recommended Seats" << std::endl;
                  std::cout << retBestAvail << std::endl;

                  //if there are no Recommended seats
                  if (retBestAvail == "*")
                  {
                   std::cout << "no seats available" <<std::endl;
                   hashmap[yourUsername]->getOrderVector()->erase(hashmap[yourUsername]->getOrderVector()->begin() + vectSize-1);
                   continue;
                  }
        
                  //Ask the user if they want to reserve the Recommended seats
                  std::cout << "Please select alternate seats." <<std::endl;
                  std::cout << "Enter Y to reserve or N to refuse:" << std::endl;
                  char reserveAnotherSeats;
                  std::cin >> reserveAnotherSeats;
                  char seatLetter = retBestAvail[1];
                  char rowChar = retBestAvail[0];
                  int rowNumber = rowChar - '0'; // converts char to int
        
                  //Use wants to reserve the Recommended seats
                  if (reserveAnotherSeats == 'Y') 
                  {
                    std::cout << "Please select alternate seats." <<std::endl;
                    //Calls the reserve seats function from the Auditorium class
                    audiSelected->reserveSeatsInAuditorium(rowNumber, seatLetter, adultTicketQ, childTicketQ, seniorTicketQ);
                    
                    std::cout << "Alternate seats reserved." << std::endl;
                    //Making changes to the order vector
                    hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setAdultTickets(adultTicketQ);
                    hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setChildTickets(childTicketQ);
                    hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setSeniorTickets(seniorTicketQ);
                    hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setStartingSeat(retBestAvail.substr(0,2));
                    hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->setEndingSeat(retBestAvail.substr(5));
        
                  } else if (reserveAnotherSeats == 'N') {
                      hashmap[yourUsername]->getOrderVector()->erase(hashmap[yourUsername]->getOrderVector()->begin() + vectSize-1);//delete the order object
                    std::cout << "Alternate seats refused and not reserved." << std::endl;
                   
                    continue;
                  } else {
                    std::cout << "Invalid input." << std::endl;
                    std::cout << "No Reservations." << std::endl;
                   
                  }
                 
               }
              
              //Adding the newly reserved seats to the orders vector
              for(int j = 0; j < hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->getTotalTickets() ; j++)
               {
                   char startRow = hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->getStartingSeat().at(0);
                   char startSeat = hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->getStartingSeat().at(1);
                   char start = static_cast<char>(startSeat + j);
                   std::string startRowString(1, startRow);
                   std::string startString(1, start);
                   std::string theSeat = startRowString+startString;
                   hashmap[yourUsername]->getOrderVector()->at(vectSize-1)->getTicketVector()->push_back(theSeat);
               }
          }
          
          
          //View orders for regular customer
          else if (userMainMenuInput == "2")
          {
              std::cout << "View Orders" << std::endl;
              //view Orders
              /*Auditorium 1, 2A,2B
                1 adult, 1 child, 0 senior*/
                
                //if there are no orders
                if(hashmap[yourUsername]->getOrderVector()->size() == 0)
                {
                    std::cout << "No orders" << std::endl;
                }
                
                for ( unsigned int i = 0; i<hashmap[yourUsername]->getOrderVector()->size(); i++)
                {
                   std::cout << "Auditorium " << hashmap[yourUsername]->getOrderVector()->at(i)->getAudiNumber()<< ", " ;
                   std::vector<std::string>* vectorcopy = hashmap[yourUsername]->getOrderVector()->at(i)->getTicketVector();
                   std::sort(vectorcopy->begin(), vectorcopy->end());
                   
                   //Printing the seats from the tickets vector
                   for(unsigned int it = 0; it<vectorcopy->size(); it++)
                   {
                       if(it == vectorcopy->size()-1)
                       {
                           std::cout << vectorcopy->at(it) << std::endl;
                       }
                       else
                       {
                           std::cout << vectorcopy->at(it) << ",";
                       }
                   }
                   //Printing out the quantity for each ticket type
                   std::cout << hashmap[yourUsername]->getOrderVector()->at(i)->getAdultTickets() << " adult, ";
                   std::cout << hashmap[yourUsername]->getOrderVector()->at(i)->getChildTickets() << " child, ";
                   std::cout << hashmap[yourUsername]->getOrderVector()->at(i)->getSeniorTickets() << " senior" << std::endl;
                }
          }
          
          
          //Update order for regular customer
          else if (userMainMenuInput == "3")
          {
              std::cout << "Update Order" << std::endl;
                std::string updateChoice;
                std::string numberOrderString;
                int numberOrder;
                bool cond = false;
                bool userEntersTheRightOrderNumber = false;
                
                //Displaying the menu for the number of orders
                for (unsigned int i = 0; i<hashmap[yourUsername]->getOrderVector()->size(); i++)
                    {
                       std::cout << i+1 << ". Order " << i+1 << std::endl;
                    }
                    
                    if(hashmap[yourUsername]->getOrderVector()->size() == 0)
                    {
                        cond = true;
                        userEntersTheRightOrderNumber = true;
                        std::cout << "No orders" << std::endl;
                    }
                    
                    //Input Vaildation
                    while(userEntersTheRightOrderNumber == false)
                    {
                       if(hashmap[yourUsername]->getOrderVector()->size() != 0)
                        {
                            std::cout << "Choose the order which you want to update: " << std::endl;
                            std::cin >> numberOrderString;
                            std::istringstream checking(numberOrderString);
        
                            if (checking >> numberOrder && checking.eof()) 
                            {
                            // Input is a valid integer
                                if (numberOrder <= static_cast<int>(hashmap[yourUsername]->getOrderVector()->size()))
                                {
                                  userEntersTheRightOrderNumber = true;
                                }
                            
                            } 
                            else 
                            {
                            // Input is not an integer
                              continue;
                            }
                            
                            
                        } 
                    }

                //Ask the user if they want to add, delete, or cancel the order
                while(!cond)
                {
                    std::cout << "1. Add tickets to order" << std::endl;
                    std::cout << "2. Delete tickets from order" << std::endl;
                    std::cout << "3. Cancel Order" << std::endl;
            
                    std::cout << "Choose from 1 to 3 to update your order: " << std::endl;
                    std::cin >> updateChoice;
                    
                    //Add tickets to the order
                    if(updateChoice =="1")
                    {
                        std::cout << "Add tickets to your order" << std::endl;
                        
                        int audiNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAudiNumber();
                          if (audiNum == 1)
                          {
                              auditorium1->displayPrintAuditorium();
                          }
                          else if (audiNum == 2)
                          {
                              auditorium2->displayPrintAuditorium();
                          }
                          else
                          {
                              auditorium3->displayPrintAuditorium();
                          }
                          
                          //Steping the user through the reservation process
                          std::string rowFromUser;
                          std::string seatFromUser;
                          std::string adultFromUser;
                          std::string childFromUser;
                          std::string seniorFromUser;
                          int totalTicketsFromUser;
                        
                          int correctAskRowFromUser;
                          char correctSeatLetterFromUser;
                          int childTicketQFromUser;
                          int seniorTicketQFromUser;
                          int adultTicketQFromUser;
                          
                          while (true) {
                            std::cout << "Please enter Row Number: " << std::endl;
                            std::cin >> rowFromUser; 
                            std::istringstream checking(rowFromUser);
                            if (checking >> correctAskRowFromUser && checking.eof()) {}
                            else 
                            { // Input is not an integer
                              continue;
                            }
                            //checking if integer is in bounds
                              if (audiNum == 1)
                              {
                                  if (correctAskRowFromUser <= auditorium1 ->getRows() && correctAskRowFromUser > 0)
                                  {
                                    break;
                                  }
                              }
                              if (audiNum == 2)
                              {
                                  if (correctAskRowFromUser <= auditorium2 ->getRows() && correctAskRowFromUser > 0)
                                  {
                                    break;
                                  }
                              }
                              if (audiNum == 3)
                              {
                                  if (correctAskRowFromUser <= auditorium3 ->getRows() && correctAskRowFromUser > 0)
                                  {
                                    break;
                                  }
                              }
                            std::cout << std::endl;
                          }
                    
                         
                          while (true) {
                            std::cout << "Please enter Seat Letter: " << std::endl;
                            std::cin >> seatFromUser;
                            if (seatFromUser.length() == 1 && std::isalpha(seatFromUser[0]))
                            {
                            // Input is a single letter
                              correctSeatLetterFromUser = seatFromUser.at(0);
                            } 
                            else {
                            // Input is not a single letter
                            }
                    
                            //checking if char is in bounds
                            if (audiNum == 1)
                              {
                                  if (correctSeatLetterFromUser >= 'A' && correctSeatLetterFromUser <= auditorium1 -> getCols() + 65-1) 
                                    {
                                      break;
                                    }
                              }
                              if (audiNum == 2)
                              {
                                  if (correctSeatLetterFromUser >= 'A' && correctSeatLetterFromUser <= auditorium2 -> getCols() + 65-1) 
                                    {
                                      break;
                                    }
                              }
                              if (audiNum == 3)
                              {
                                  if (correctSeatLetterFromUser >= 'A' && correctSeatLetterFromUser <= auditorium3 -> getCols() + 65-1) 
                                    {
                                      break;
                                    }
                              }
                            
                            std::cout << std::endl;
                          }
                    
                          //
                          while (true) {
                            std::cout << "Please enter Adult Ticket Count: " << std::endl;
                            std::cin >> adultFromUser;
                             //validating Adult Ticket Count
                            std::istringstream checking(adultFromUser);
                    
                            if (checking >> adultTicketQFromUser && checking.eof()) 
                            {
                            // Input is a valid integer
                            
                            } 
                            else 
                            {
                            // Input is not an integer
                              continue;
                            }
                            
                            if (adultTicketQFromUser >= 0) // validating adult ticket count is in bounds
                            { 
                              break;
                            }
                            std::cout << std::endl;
                          }
                    
                          while (true) {
                            std::cout << "Please enter Child Ticket Count: " << std::endl;
                            std::cin >> childFromUser;
                    
                            //validating Child Ticket Count
                            std::istringstream checking(childFromUser);
                    
                            if (checking >> childTicketQFromUser && checking.eof()) 
                            {
                            // Input is a valid integer
                            
                            } 
                            else 
                            {
                            // Input is not an integer
                              continue;
                            }
                    
                    
                    
                            if (childTicketQFromUser >= 0) // validating Child ticket count is in bounds
                            {
                              break;
                            }
                            std::cout << std::endl;
                          }
                    
                          while (true) {
                            std::cout << "Please enter Senior Ticket Count: " << std::endl;
                            std::cin >> seniorFromUser;
                            
                            //validating Senior Ticket Count
                            std::istringstream checking(seniorFromUser);
                    
                            if (checking >> seniorTicketQFromUser && checking.eof()) 
                            {
                            // Input is a valid integer
                            
                            } 
                            else 
                            {
                            // Input is not an integer
                              continue;
                            }
                            
                            if (seniorTicketQFromUser >= 0) // validating Senior ticket count is in bounds
                            {
                              break;
                            }
                            std::cout << std::endl;
                          }
                          totalTicketsFromUser = seniorTicketQFromUser + childTicketQFromUser + adultTicketQFromUser;
                          
                          //Reserving the seat if seat is available for reservation
                          bool ret = false;
                          if(hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAudiNumber() == 1)
                          {
                              std::cout << "here " << std::endl;
                              ret = auditorium1 -> isAvailable(correctAskRowFromUser, correctSeatLetterFromUser, totalTicketsFromUser);
                              std::cout << "ret " << ret << std::endl;
                              if (ret)
                              {
                                  auditorium1 -> reserveSeatsInAuditorium(correctAskRowFromUser, correctSeatLetterFromUser, adultTicketQFromUser, childTicketQFromUser, seniorTicketQFromUser);
                                  cond = true;
                              }
                          }
                          else if(hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAudiNumber() == 2)
                          {
                              ret = auditorium2 -> isAvailable(correctAskRowFromUser, correctSeatLetterFromUser, totalTicketsFromUser);
                              if (ret)
                              {
                                  auditorium2 -> reserveSeatsInAuditorium(correctAskRowFromUser, correctSeatLetterFromUser, adultTicketQFromUser, childTicketQFromUser, seniorTicketQFromUser);
                                  cond = true;
                              }
                          }
                          else // ==3
                          {
                              ret = auditorium3 -> isAvailable(correctAskRowFromUser, correctSeatLetterFromUser, totalTicketsFromUser);
                              if (ret)
                              {
                                  auditorium3 -> reserveSeatsInAuditorium(correctAskRowFromUser, correctSeatLetterFromUser, adultTicketQFromUser, childTicketQFromUser, seniorTicketQFromUser);
                                  cond = true;
                              }
                          }
                          
                          //No seats available, best available is not offered
                          if (ret == false)
                          {
                              std::cout << "no seats available" << std::endl;
                          }

                          //Making changes to the order object in the order vector
                          if (ret)
                          {
                              
                              int ad = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAdultTickets();
                              int ch = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getChildTickets();
                              int sen = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getSeniorTickets();
                              
                              for(int p = 0; p< totalTicketsFromUser; p++)
                              {
                                  std::string rowNum = std::to_string(correctAskRowFromUser);
                                   char startSeat = correctSeatLetterFromUser;
                                   char start = static_cast<char>(startSeat + p);
                                   std::string startString(1, start);
                                   std::string theSeat = rowNum+startString;
                                   hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getTicketVector()->push_back(theSeat);
                                  
                              }
                              hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setAdultTickets(ad + adultTicketQFromUser);
                              hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setChildTickets(ch + childTicketQFromUser);
                              hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setSeniorTickets(sen + seniorTicketQFromUser);
                          }
                        }             
                          
                    
                    //User wants to delete tickets
                    else if(updateChoice =="2")
                    {
                        std::cout << "Deleting tickets from order" << std::endl;
                        std::string rowChoice;
                        std::string seatChoice;
                        int correctRow;
                        char correctSeat;
                        
                        int audiNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAudiNumber();
                        
                        //Asking user for row and seat Number
                        while (true) {
                            std::cout << "Please enter Row Number: " << std::endl;
                            std::cin >> rowChoice; 
                            std::istringstream checking(rowChoice);
                            if (checking >> correctRow && checking.eof()) {}
                            else 
                            { // Input is not an integer
                              continue;
                            }
                    
                              if (audiNum == 1) //Checking if int is in bounds
                              {
                                  if (correctRow <= auditorium1 ->getRows() && correctRow > 0)
                                  {
                                    break;
                                  }
                              }
                              if (audiNum == 2)
                              {
                                  if (correctRow <= auditorium2 ->getRows() && correctRow > 0)
                                  {
                                    break;
                                  }
                              }
                              if (audiNum == 3)
                              {
                                  if (correctRow <= auditorium3 ->getRows() && correctRow > 0)
                                  {
                                    break;
                                  }
                              }
                            std::cout << std::endl;
                          }
                    
                         
                          while (true) {
                            std::cout << "Please enter Seat Letter: " << std::endl;
                            std::cin >> seatChoice;
                            if (seatChoice.length() == 1 && std::isalpha(seatChoice[0]))
                            {
                            // Input is a single letter
                              correctSeat = seatChoice.at(0);
                            } 
                            else {
                            // Input is not a single letter
                            }
                    
                            //checking if char is in bounds
                            if (audiNum == 1)
                              {
                                  if (correctSeat >= 'A' && correctSeat <= auditorium1 -> getCols() + 65-1) 
                                    {
                                      break;
                                    }
                              }
                              if (audiNum == 2)
                              {
                                  if (correctSeat >= 'A' && correctSeat <= auditorium2 -> getCols() + 65-1) 
                                    {
                                      break;
                                    }
                              }
                              if (audiNum == 3)
                              {
                                  if (correctSeat >= 'A' && correctSeat <= auditorium3 -> getCols() + 65-1) 
                                    {
                                      break;
                                    }
                              }
                            
                            std::cout << std::endl;
                          }
                        
                        //Removing ticket from ticket vector  
                        std::string rowToDelete = std::to_string(correctRow);
                        std::string seatToDelete = std::string(1,correctSeat);
                        std::string toDelete = rowToDelete+seatToDelete;
                        bool ifItemExists = false;
                        std::vector<std::string>* ticketscopy = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getTicketVector();
                        
                        int adultNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAdultTickets();
                        int childNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getChildTickets();
                        int seniorNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getSeniorTickets();
                        char chararcter;
                        
                        //Calling the unReserveSeatsInAuditorium function of the auditorium class to remove the reservation
                        for (unsigned int d =0; d<hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getTicketVector()->size(); d++)
                        {
                            if(hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getTicketVector()->at(d) == toDelete)
                            {
                                ticketscopy->erase(ticketscopy->begin() + d);
                                ifItemExists = true;
                                 if (audiNum == 1)
                                 {
                                     chararcter = auditorium1->unReserveSeatsInAuditorium(correctRow, correctSeat);
                                     cond = true;
                                 }
                                 if (audiNum == 2)
                                 {
                                     chararcter = auditorium2->unReserveSeatsInAuditorium(correctRow, correctSeat);
                                     cond = true;
                                 }
                                 if (audiNum == 3)
                                 {
                                     chararcter = auditorium3->unReserveSeatsInAuditorium(correctRow, correctSeat);
                                     cond = true;
                                 }
                                 
                                 //Reducing the ticket count for each ticket removed
                                    if (chararcter == 'A') 
                                    {
                                        adultNum--;
                                        hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setAdultTickets(adultNum);
                                    }
                                    
                                     if (chararcter == 'C') 
                                     {
                                         childNum--;
                                         hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setChildTickets(childNum);
                                     }
                                     
                                     if (chararcter == 'S') 
                                     {
                                         seniorNum--;
                                         hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setSeniorTickets(seniorNum);
                                     }
                            }
                        }
                        if (ifItemExists == false)
                        {
                            std::cout << "Item does not exist" << std::endl;
                        }
                        
                        if(ifItemExists == true && hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAdultTickets() == 0 && hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getChildTickets() == 0 && hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getSeniorTickets() == 0)
                        {
                            hashmap[yourUsername]->getOrderVector()->erase(hashmap[yourUsername]->getOrderVector()->begin() + numberOrder-1);
                        }
                        
                    }
                    
                    //User wants to cancel the order
                    else if(updateChoice =="3")
                    {
                        std::cout << "Cancel your order" << std::endl;
                        
                        //Remove the ticket from the tickets vector
                        std::vector<std::string>* ticketscopyCancellation = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getTicketVector();
                        std::string ticketToDelete;
                        std::string rowOfTicketToDeleteString;
                        std::string seatOfTicketToDeleteString;
                        int rowOfTicketToDelete;
                        char seatOfTicketToDelete;
                        char chararcter;
                        
                        //Reduce the number of tickets for each type
                        int adultNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAdultTickets();
                        int childNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getChildTickets();
                        int seniorNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getSeniorTickets();
                        int audiNum = hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->getAudiNumber();
                        
                        //Un reserve the seats in each auditorium
                        for(unsigned int c = 0; c < ticketscopyCancellation->size(); c++)
                        {
                            ticketToDelete = ticketscopyCancellation->at(c);
                            rowOfTicketToDeleteString = ticketToDelete.at(0);
                            seatOfTicketToDeleteString = ticketToDelete.at(1);
                            
                            rowOfTicketToDelete = stoi(rowOfTicketToDeleteString);
                            seatOfTicketToDelete = seatOfTicketToDeleteString.at(0);
                            
                            if (audiNum == 1)
                            {
                                chararcter = auditorium1->unReserveSeatsInAuditorium(rowOfTicketToDelete, seatOfTicketToDelete);
                                
                            }
                            if (audiNum == 2)
                            {
                                chararcter = auditorium2->unReserveSeatsInAuditorium(rowOfTicketToDelete, seatOfTicketToDelete);
                                
                            }
                            if (audiNum == 3)
                            {
                                chararcter = auditorium3->unReserveSeatsInAuditorium(rowOfTicketToDelete, seatOfTicketToDelete);
                                
                            }
                            
                            if (chararcter == 'A') {adultNum--;hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setAdultTickets(audiNum);}
                            if (chararcter == 'C') {childNum--;hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setChildTickets(childNum);}
                            if (chararcter == 'S') {seniorNum--;hashmap[yourUsername]->getOrderVector()->at(numberOrder-1)->setSeniorTickets(seniorNum);}
                        }
                        int num = numberOrder-1;
                        //Finally delete the order from the vector
                        hashmap[yourUsername]->getOrderVector()->erase(hashmap[yourUsername]->getOrderVector()->begin() + num);
                        std::cout << "Your Order has been Canceled" << std::endl;
                        cond = true;
                        
                    }
                    else
                    {
                        std::cout << "Wrong Input! Please enter the input for updating again" << std::endl;
                        continue;
                    }
                }
          }
          
          //display orders for regular customer
          else if (userMainMenuInput == "4")  
          {
              std::cout << "Display report" << std::endl;
              double customerTotal = 0;
              for (unsigned int i = 0; i<hashmap[yourUsername]->getOrderVector()->size(); i++)
                {
                   //Display each order
                   std::cout << "Auditorium " << hashmap[yourUsername]->getOrderVector()->at(i)->getAudiNumber()<< ", " ;
                   std::vector<std::string>* vectorcopy = hashmap[yourUsername]->getOrderVector()->at(i)->getTicketVector();
                   std::sort(vectorcopy->begin(), vectorcopy->end());

                   for(unsigned int it = 0; it<vectorcopy->size(); it++)
                   {
                       if(it == vectorcopy->size()-1)
                       {
                           std::cout << vectorcopy->at(it) << std::endl;
                       }
                       else
                       {
                           std::cout << vectorcopy->at(it) << ",";
                       }
                   }

                   int adultQ = hashmap[yourUsername]->getOrderVector()->at(i)->getAdultTickets();
                   int childQ = hashmap[yourUsername]->getOrderVector()->at(i)->getChildTickets();
                   int seniorQ = hashmap[yourUsername]->getOrderVector()->at(i)->getSeniorTickets();
                   
                   std::cout << adultQ << " adult, ";
                   std::cout << childQ << " child, ";
                   std::cout << seniorQ << " senior" << std::endl;
                    
                    //Display the order total for each order
                    double totalSales = 10 * adultQ + 5 * childQ + 7.5 * seniorQ;
                    customerTotal += totalSales;
                    std::cout << "Order Total: $" << std::fixed << std::setprecision(2) << totalSales << std::endl;
                }
                //final cost for the customer
                std::cout << "Customer Total: $" << std::fixed << std::setprecision(2) << customerTotal << std::endl;
          }
          
          //Logout for regular customer
          else if (userMainMenuInput == "5")
          {
              std::cout << "Logging out..." << std::endl;
              break;
          }
          else
              {
                  std::cout << " Invalid Input! Choose from the options in the Main Menu" << std::endl;
                  continue;
              }
          }
      
      }
    //Calling the destructor
    auditorium1 -> ~Auditorium(); // deletes auditorium1
    auditorium2 -> ~Auditorium(); // deletes auditorium2
    auditorium3 -> ~Auditorium(); // deletes auditorium3

} //end
