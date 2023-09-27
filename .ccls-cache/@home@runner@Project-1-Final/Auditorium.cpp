#include <climits>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Auditorium.h"
#include <cmath>

  /*
  Auditorium – Auditorium.h and Auditorium.cpp
o Members
  ▪ First (Node pointer)
    • Acts as head pointer of linked list
o Methods
  ▪ Constructor
    • Builds auditorium grid and fills in each node with a seat object based on file input
    • The first node in each row will connect to the first node in the row below it using
      the down pointer in the node
o Overloaded << operator
  ▪ create a string that contains the contents of each row in the theater
  ▪ traverses the grid and uses each node’s overloaded << operator
  ▪ inserts a newline at the end of each row
o You may add other methods as necessary to this class
  ▪ No direct access should be given to the grid inside the object
  ▪ Main should use auditorium methods to receive information and to provide data for changing the object
*/
  
// Default constructor
/*void*/ Auditorium::Auditorium() 
{ 
  head = nullptr;

}

//Constructor that builds the auditorium
//Parameter: string that holds the auditorium
Auditorium::Auditorium(std:: string totalAudiLine)
{
  int len = static_cast<int>(totalAudiLine.length()); //type casting char to int
  int numRows = 1; //counts the current number of rows we are on 
  char numCols = 'A'; // counts the current number of columns we are on
  for (int i =0; i<len; i++)
    {
      seatType = totalAudiLine.at(i); //takes each letter of the string containing the auditorium
      Node* new_node = new Node;
      Seat* new_seat = new Seat(numRows, numCols, seatType); // creates a new seat object
      new_node->data = seatType;
      new_node->payload = new_seat;

      if (i ==0 && seatType == 'X') //totalAudiLine conatins each row of the auditorium separated with an 'X'
      {
        //skip
      }
      else if (i == 1) //the first character in the auditorium
      {
        head = new_node;
      }
      else if (seatType == 'X')
      { 
        numRows++;
        numCols = 'A';
        insertNodeDown(totalAudiLine.at(i +1), numRows, numCols); //this fuction inserts a new node below when a new row is added
        i++;
      }
        
      else 
      { 
        insertNodeNext(seatType, numRows, numCols); // this function inserts the next node
        numCols++;
      }
    }
   
}

// Function to insert a new node.
//Parameter: data char, row, column
//Return Type: void
void Auditorium::insertNodeNext(char dataAudi, int row, int col)
{
    // Create the new Node.
    Node* newNode = new Node(dataAudi);
    char column = static_cast<char>(col); // converting int to char
    Seat* newSeat = new Seat(row, column, dataAudi);
    newNode->payload = newSeat;
  
    // Traverse till end of list
  Node* cur = head;
  
  while (cur->down != nullptr) 
  {
    // Update cur
    cur = cur->down;
  }
   
    while (cur->next != NULL) {
  
        // Update cur
        cur = cur->next;
    }
  
    // Insert at the last.
    cur->next = newNode;
  
}

// Function to insert a new node.
//Parameter: data char, row, column
//Return Type: void
void Auditorium::insertNodeDown(char dataAudi, int row, int col)
{
  Node* aNode = new Node(dataAudi);
  char column = static_cast<char>(col); // converting int to char
  Seat* newSeat = new Seat(row, column, dataAudi);
  aNode->payload = newSeat;
  
  Node* cur = head;
  
   // Traverse till end of list
  while (cur->down != nullptr) 
  {
     // Update cur
    cur = cur->down;
  }
  
  // Insert at the last.
      cur->down = aNode;

}

//Creates the file "A1.txt" and calls the overloaded << operator to print to the file
//Parameter: Nothing
//Return Type: void
void Auditorium::printAuditorium()
{  
    std::ofstream MyFile("A1.txt"); // creates file
    if (MyFile.good()) //Missing file check
    {
    std::cout << "File created" << std::endl;
    } 
    else 
    {
    std::cout << "File already exists" << std::endl;
    }

    MyFile << *this; // points to the auditorium

  MyFile.close(); // closes the file
  
}


// Calculates the number of rows in the Auditorium
//Parameter: Nothing
//Return Type: integer
int Auditorium::getRows()
{  
  Node* horizontal = head;
  Node* vertical = head;
  int countRows = 0; // Variable to count the rows

  // Check for empty list.
  if (head == NULL) 
  {
      return 0;
  }

  // Traverse the list.
  while (vertical != nullptr)
  {
    while (horizontal != nullptr) 
    {
      horizontal = horizontal->next;
    }
    
    vertical = vertical->down; //go to the next row
    countRows++;
    horizontal = vertical; //setting horizontal to point to the starting of the next row
  }

  return countRows;
  
}


// Calculates the number of columns (seats) in the Auditorium
//Parameter: Nothing
//Return Type: integer
int Auditorium::getCols()
{  
    Node* horizontal = head;
    Node* vertical = head;
    int countCols = 0; // Variable to count the columns
  
    // Check for empty list.
    if (head == NULL) 
    {
        return 0;
    }
  
    // Traverse the list.
    while (vertical != nullptr)
    {
      countCols = 0;
      while (horizontal != nullptr) 
      {
        countCols++;
        horizontal = horizontal->next;
      }
      
      vertical = vertical->down; //go to the next row
      
      horizontal = vertical; //setting horizontal to point to the starting of the next row
    }
  
  return countCols;
  
}

//Displays the Auditorium with the reserved seats for the User
//Parameter: Nothing
//Return Type: void
void Auditorium::displayPrintAuditorium()
{  
  Node* horizontal = head;
  Node* vertical = head;

  // Check for empty list.
  if (head == NULL) 
  {
      std::cout << "List empty" << std::endl;
      return;
  }


  std::cout << "  ";

  //Numbers the seats with Alphabets
  for (char c = 'A'; c <  getCols() + 65; c++) 
    {
      std::cout << c;
    }

  std::cout << std::endl;
  int rowcount = 0;

  // Traverse the list.
  while (vertical != nullptr)
  {
    rowcount++;
    std::cout << rowcount << " ";
    
    while (horizontal != nullptr) 
    {
      // if the seat is already occupied by an adult, child, or senior, it replaces it with a '#'
      if (horizontal->data == 'A')
      {
        std::cout << '#';
      }

      else if (horizontal->data == 'C')
      {
        std::cout << '#';
      }

      else if (horizontal->data == 'S')
      {
        std::cout << '#';
      }
      
      else 
      {
        std::cout << horizontal->data;
      }  
      
      horizontal = horizontal->next;
      
    }
    
    vertical = vertical->down;
    horizontal = vertical;
    std::cout << std::endl;

    
  }
  std::cout << std::endl;
}


//Checks if the given seat is available for reservation
//Parameter: int row, char seat, int total quantity of tickets
//Return Type: boolean
bool Auditorium::isAvailable(int row, char seat, int totalQ) 
{
  int numSeat = seat - 65 + 1; // converts char to int

  Node* horizontal = head;
  Node* vertical = head;
  int countSeat = 0;
  int countRow = 0;
  Node* cur = head;
  
  // Check for empty list.
  if (head == NULL) 
  {
      return 0;
  }

  // Traverse the list.
  while ( countRow != row) // Checks if the program has reached the desired row
  {
    countSeat =0;
    while (countSeat != numSeat -1) // Checks if the program has reached the desired column
    { 
      horizontal = horizontal->next;
      countSeat++;
    }
    
    vertical = vertical->down;
    countRow++;

    cur = horizontal;
    horizontal = vertical;
    
  }
    while (totalQ > 0) //Makes sure that there are enough available quantity of seats
    {
      if (cur == nullptr)
      {
        return false;
      }
      
      if (cur ->getNode() != '.') // Checks if the specific seat is not empty
      {
        return false;
      }
      
      if (cur ->getNode() == '.') // Checks if the specific seat is empty
      {
        cur = cur ->next;
        totalQ--;

        if (totalQ == 0)
        {
          return true;
        }

      }
  
    }

     return false;

}


//Reserves the seats requested in the auditorium
//Parameter: int row, char seat, int adult quantity of tickets, int child quantity of tickets, int senior quantity of tickets 
//Return Type: void
void Auditorium::reserveSeatsInAuditorium(int row, char seat, int adultQ, int childQ, int seniorQ) 
{
  int numSeat = seat - 65 + 1; // converts char to int

  Node* horizontal = head;
  Node* vertical = head;
  int countSeat = 0;
  int countRow = 0;
  Node* cur = head;
  int totalQ = adultQ + childQ + seniorQ;
  
    // Check for empty list.
    if (head == NULL) 
    {
        std::cout << "List empty" << std::endl;
    }
  
    // Traverse the list.
    while ( countRow != row) // Checks if the program has reached the desired row
    {
      countSeat =0;
      while (countSeat != numSeat -1) // Checks if the program has reached the desired column
      { 
        horizontal = horizontal->next;
        countSeat++;
      }
      
      vertical = vertical->down;
      countRow++;

      cur = horizontal;
      horizontal = vertical;

    }
  
      while (totalQ > 0) //Makes sure that all the rquested seats are reserved
      {
        if (cur == nullptr)
        {
          //skip
        }

        //reserves the desired seats
        if (adultQ > 0)
        {
          cur ->setNode('A');
          adultQ--;
        }

        else if (childQ > 0)
        {
          cur ->setNode('C');
          childQ--;
        }

        else //(seniorQ > 0)
        {
          cur ->setNode('S');
          seniorQ--;
        }

        
          cur = cur ->next;
          totalQ--;
          
      }
      
    }

//Displays the recipt for the reservation
//Parameter: Nothing
//Return Type: void
void Auditorium::displayReport() 
{

  int adultQ = 0;
  int seniorQ = 0;
  int childQ = 0;
  int period = 0;

  

  Node* horizontal = head;
  Node* vertical = head;
  
    // Check for empty list.
    if (head == NULL) 
    {
        std::cout << "List empty" << std::endl;
        return;
    }

  //counts the number of tickets to be purchased
    while (vertical != nullptr)
    {
      while (horizontal != nullptr) 
      {
        if (horizontal->data == 'A')
        {
          adultQ++;
        }

        else if (horizontal->data == 'C')
        {
          childQ++;
        }

        else if (horizontal->data == 'S')
        {
          seniorQ++;
        }

        else
        {
          period++;
        }
        
        horizontal = horizontal->next;
      }
      
      vertical = vertical->down;
      horizontal = vertical;

    }

  int totalSeats = adultQ + seniorQ + childQ + period;
  int totalTickets = adultQ + seniorQ + childQ;

  double totalSales = 10 * adultQ + 5 * childQ + 7.5 * seniorQ;

  std::cout << "Total Seats:	" << totalSeats << std::endl;
  std::cout << "Total Tickets:	" << totalTickets << std::endl;
  std::cout << "Adult Tickets:	" << adultQ << std::endl;
  std::cout << "Child Tickets:	" << childQ << std::endl;
  std::cout << "Senior Tickets:	" << seniorQ << std::endl;
  std::cout << "Total Sales:	$" << std::fixed << std::setprecision(2) << totalSales << std::endl;
  
}




//Incase the seats that the user wants is not available for reservation, this function returns the best seats availble for reservation according to the center of the auditorium
//Parameters: Total Quantity of seats to be reserved
//Return: Formatted string of the line of seats available for reservation
std::string Auditorium::bestAvailable(int totalQuantity) 
{
  //find the midpoint of the auditorium
  int rowTrack = 1;
  int colTrack =0;
  
  double midCol; // midpoint of the number of seats

  if (getCols() % 2 == 0) 
  {
    midCol = (getCols() / 2.0) + 0.5;
  } 
  else 
  {
    midCol = (getCols() + 1) / 2;
  }

  double midRow; // midpoint of the number of rows

  if (getRows() % 2 == 0) 
  {
    midRow = (getRows() / 2.0) + 0.5;
  } 
  else 
  {
    midRow = (getRows() + 1) / 2;
  }

  
  double minDist = INT_MAX; //minimum distance from teh center of the auditorium
  std::string temp; // varaible that will return the value of this function

  Node* horizontal = head;
  Node* vertical = head;
  Node* ptr = head;
  
  int xCoord = 0;
  int yCoord = 0;
  int copyOfColTrack = 0;
  int additionalSeats = 0;
  

  // Traverse the list.
    while (vertical != nullptr)
    {
      while (horizontal != nullptr) 
      {
        colTrack++; //keeps track on the column number

        if (horizontal-> getNode() == '.')
        {
            bool cond = true; 
            ptr = horizontal;
            copyOfColTrack = colTrack;
          
            for (int i = 0; i < totalQuantity -1; i++) // checks if there are empty seats in a row
              {
                if (ptr->next == nullptr)
                {
                  cond = false;
                  break;
                }
                ptr = ptr->next;
                copyOfColTrack++;
                
                if (ptr->getNode() != '.')
                {
                  cond = false;
                   break;
                }
                else {cond = true;}
              }
            if (cond == true)
            {
              //using the distance formula
              double y = fabs((colTrack + (totalQuantity -1)/2.0) - midCol);
              double x = fabs(rowTrack - midRow);
    
              double dist = sqrt(pow(x,2) + pow(y, 2));

              if (dist == minDist) //Case in which distance is Tied. The row closer to the middle row is selected
              {
                double rowdist = fabs(midRow - rowTrack);
                double rowdist2 = fabs(midRow - xCoord);

                if (rowdist < rowdist2)
                {
                  minDist = dist;
                  xCoord = rowTrack;
                  yCoord = colTrack;
                  additionalSeats = copyOfColTrack;
                }
                
              }

              //replaces values for smaller distance
              if (dist < minDist)
              {
                minDist = dist;
                xCoord = rowTrack;
                yCoord = colTrack;
                additionalSeats = copyOfColTrack;
              }
            }
          
          
        }
        horizontal = horizontal->next;
        
      }
      rowTrack++;
      colTrack =0;

      //std::cout << std::endl;
      
      vertical = vertical->down;
      
      
      horizontal = vertical;
  
    }


  char seatChar1 = static_cast<char>(yCoord + 65 - 1); // converts int to char
  char seatChar2 = static_cast<char>(additionalSeats + 65 - 1); // converts int to char

  std::string startingSeat = std::string(1,seatChar1);
  std::string endingSeat = std::string(1,seatChar2);
  std::string rowString = std::to_string(xCoord);

  if (xCoord == 0)
  {
    temp = "*";
  }

  //Prints according to the following format
  //<row><starting seat> - <row><ending seat>
  // Example: 3D – 3F
  else
  {
    temp = rowString + startingSeat + " - " + rowString + endingSeat;
  }
  
  return temp;
  
}



//Auditorim Destructor- deletes the auditorium when program is terminated
Auditorium::~Auditorium()
    {
      Node* horizontal = head;
      Node* vertical = head;
      Node* prev = head;
  
      // Check for empty list.
      if (head == NULL) 
      {
          std::cout << "List empty" << std::endl;
          return;
      }
    
      // Traverse the list.
      while (vertical != nullptr)
      {
        while (horizontal != nullptr) 
        {
          prev = horizontal;
          horizontal = horizontal->next;  
          delete prev; // deletes the nodes
        }
        
        vertical = vertical->down;
        horizontal = vertical;
        
      }
      //The Auditorium is deleted
    }


// Overloaded << operator
// create a string that contains the contents of each row in the theater
// traverses the grid and uses each node’s overloaded << operator
// inserts a newline at the end of each row
std::ostream& operator<<(std::ostream& ostr, const Auditorium& obj){
   Node* horizontal = obj.head;
    Node* vertical = obj.head;
  
    // Check for empty list.
    if (obj.head == NULL) 
    {
        std::cout << "List empty" << std::endl;
        return ostr;
    }
  
    // Traverse the list.
    while (vertical != nullptr)
    {
      while (horizontal != nullptr) 
      {
        ostr << *horizontal;
        horizontal = horizontal->next;        
      }
      
      vertical = vertical->down;
      horizontal = vertical;
      if (vertical != nullptr)
      {
        ostr << std::endl;
      }
      
    }
    return ostr;
}

//end