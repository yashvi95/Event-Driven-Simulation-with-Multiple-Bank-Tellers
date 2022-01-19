#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <iomanip>
#include <functional>
#include "math.h"
#include "Event.h"
#include "Teller.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
/*Driver Code which will use the class Event to to organize the Customer Arrivals at a Bank,
with one one teller and processes the arrivals and then processes departure of the customer. Once the 
simulation ends, it will calculate the total transactions, the average time of the transactions 
for each customer and the avaerage wait time for each customer.*/
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


unsigned currentTime = 0; //Current time of the simulation
double waitTime = 0; //Keeps track of the wait time for each customer

//Function that checks the availability of the first available Teller
int chkAvailability (vector<Teller>& T)
{
   int tcurrent = 0;
   for(int i = 0; i<T.size(); i++)
     {
    if(T.at(i).getStatus() == true)
      {
         tcurrent = i;
         break;
      }
      else if( T.at(i).getStatus() == false){
        tcurrent = -1;
      }
     }
      return tcurrent;
}


// Processses an arrival event.
void processArrival(Event arrivalEvent, priority_queue<Event, vector<Event>, greater<Event>>& eventListPQueue, queue<Event>& bankQueue, vector<Teller>& T)
  {
     //Assigns the the first availble teller
     int tcurrent = 0;
     tcurrent = chkAvailability(T);
      
      // Remove this event from the event list
     eventListPQueue.pop();
     
     //Assign the customer's arrival event 
     Event customer = arrivalEvent;
     unsigned departureTime = 0;
     //Is the Bank Queue is empty and the Bank Teller is Available then calculates Departure time 
     //Adds the Departure event into the Bank Queue, and updates the BankTeller to be false
      if(bankQueue.empty() && tcurrent != -1)
      {
          cout<<left<< "Teller  "<< tcurrent+1 <<" processing   arrival event at time: ";
          cout<<right<< setw(4)<<customer.getTime() << setw(5) << customer.getDuration() <<endl;
          departureTime = currentTime + customer.getDuration();
          T.at(tcurrent).numTransaction(customer.getDuration());
          Event newDepartureEvent(Event::departure, departureTime, 0, tcurrent); 
          eventListPQueue.emplace(newDepartureEvent);
          T.at(tcurrent).updateStatus(false);
          
       }
       
      //Otherwise will add the customer to the BankQueue if the customer is not available
      else 
          bankQueue.emplace(customer);
  }

//Processes Departure Event
void processDeparture(Event departureEvent, priority_queue<Event, vector<Event>, greater<Event>>& eventListPQueue, queue<Event>& bankQueue, vector<Teller>& T) 
   {   
     // Remove this event from the event list
      eventListPQueue.pop();
      //Assigns the freeTeller to a local variable
      int freeTeller = departureEvent.getTeller();
      
      //Frees the Teller
      T.at(freeTeller).updateStatus(true); 
      
      cout<<left;
      cout<< "Teller  "<< freeTeller+1 <<" processing departure event at time:";
      cout<<right<< setw(5)<< departureEvent.getTime() <<endl;
     
       
       //If the Bank Queue is not empty, a New event is created for the next customer
       //Wait time is calculated for the next customer, the Customer is removed from the Bank Queue
       //A new Departure Event is created for the Next Customer and added to the Priority Queue
       if(!bankQueue.empty())
      {
         // Customer at front of line begins transaction
         Event nextcustomer = bankQueue.front();
      
        cout<<left<< "Teller  "<< freeTeller + 1 <<" processing   arrival event at time: ";
        cout<<right<< setw(4)<< departureEvent.getTime() << setw(5) << nextcustomer.getDuration() <<endl;
        
        //Calculates the waittime of the Next customer
         waitTime += (currentTime - nextcustomer.getTime());
         
         //Removes the customer from the Bankqueue
         bankQueue.pop();
         
         //Calculates the departure time and the assigns the new Departure Event for the customer
         unsigned departureTime = currentTime + nextcustomer.getDuration();
         Event newDepartureEvent(Event::departure, departureTime, 0, freeTeller); 
         
         //Assigns the Customer Information to the Teller
         T.at(freeTeller).numTransaction(nextcustomer.getDuration());
         //Updates the teller to unavailable
         T.at(freeTeller).updateStatus(false); 
         //Adds the Departure Event to the PriorityQueue
         eventListPQueue.emplace(newDepartureEvent);    
    }
    
   //Otherwise, if the BankQueue is empty then, the teller is available 
    }
      
 
 
 
int main()
{
   //Variable to store the arrival time of the customer
   unsigned arrivalTime = 0;
   //Variable to store the durationTime of the customer
   unsigned durationTime = 0;
   //Variable to store the transaction time of the customer
   double transactionTime = 0;
   //Variable to store the number of transactions occuring duirng the simulation
   double count = 0; 
   //Variable to Store TotalWaitLineLength
   unsigned totalwaitlength = 0;
   //Variable to Store MaxWaitLineLength
   unsigned maxwaitlength = 0;
   //Min Priority Queue to store the Events, Arrivals and Departures being processed 
   priority_queue<Event, vector<Event>, greater<Event>> eventListPQueue; 
   //A queue to store the customers in line waiting for the Bank Teller
   queue<Event> bankQueue; 
   //Event to store the departure Events
   Event departureEvent;
   //Local variable to store the imputed number of teller
   int numTellers = 0;
   //Vector of the Class Tellers, which will keep track of the Tellers availability and customer info
   vector<Teller> Tellers; 
   
   //Read in the Teller Numbers working
   cin >> numTellers;
   
   //Only accepts 1 - 10 tellers
   if(numTellers >= 1 || numTellers < 11)
   {
   //Resizes the Teller Vector to that Length
   Tellers.resize(numTellers);  
   }

   // Create and add arrival events to event list
   while(cin >> arrivalTime >> durationTime)
  {
     Event arrivalEvent(Event::arrival, arrivalTime, durationTime);
     eventListPQueue.push(arrivalEvent); 
     
  }
  
  cout << "<<< BEGIN SIMULATION ("<< numTellers <<" tellers) >>>"<<endl;
  
  // Event loop, which processes the Customers one at a time from the Queue 
  //and will process based on the type of the Event in the Priority Queue
  while(!eventListPQueue.empty())
  { 
     
      Event newEvent = eventListPQueue.top();
      currentTime = newEvent.getTime();
      transactionTime += newEvent.getDuration();
      
   if(newEvent.getType() == Event::arrival)
      {
         count++;
         totalwaitlength += bankQueue.size();
      
        if(bankQueue.size() > maxwaitlength)
          {
            maxwaitlength = bankQueue.size();
           }
         processArrival(newEvent, eventListPQueue , bankQueue, Tellers);    
          
      }
   else
      {
       processDeparture(newEvent , eventListPQueue , bankQueue, Tellers);
      
      }
       
  }
  
  cout<<"<<< END SIMULATION >>>"<<endl;
  cout<<endl;
  
  
  
  //Once the simulation ends, the average statistics are Calculated for the Simulation Statitistics
  cout<<">>> SIMULATION STATISTICS"<<endl;
  cout<<endl;
  
  cout<< "           Teller number:"<<right<< setw(8);
  for(int i = 1; i<=numTellers; i++)
  {
   if(i == numTellers){
      cout<< i <<"   ";
   }
   else
   cout<< i<<right<< setw(8);
  }
  cout<<right<< setw(6)<<"OVERALL"<< endl;
  
  
  cout << "  Transactions processed:" << right<< setw(8);
  for(int i = 0; i<Tellers.size(); i++)
  {
     if(i ==Tellers.size() - 1){
        cout << Tellers.at(i).getTransaction()<<right<<setw(8);
     }
        else
       cout<<Tellers.at(i).getTransaction()<<right<< setw(8);
  }
 
  cout<<right<< setw(10)<<count<<endl;
  
  cout<< "Average transaction time:" << right<< setw(8);
  for(int i = 0; i<Tellers.size(); i++)
  {
   
    cout<<fixed<<setprecision(2)
     << Tellers.at(i).getAverage()<<right<< setw(8);
  }

  cout <<right<< setw(10)<< fixed<<setprecision(2)<< (transactionTime/count)<< endl;
   
  cout<<endl;
 
  cout << right<< setw(25+(Tellers.size()*8)) << 
      "Maximum wait line length:"; 
  cout<<right<<setw(10) <<  fixed<< setprecision(2)<< maxwaitlength<<endl;
  
  cout << right<< setw(25+(Tellers.size()*8))
   <<"Average wait line length:";
   cout<<  right<<setw(10) <<  fixed<< setprecision(2)<< (totalwaitlength/count)<<endl;
  
  cout << right<< setw(25+(Tellers.size()*8))
   <<"Average wait time:";
  cout << right<< setw(10) << fixed<< setprecision(2)<< (waitTime/count)<< endl;
  cout<<endl;

   return 0;
}