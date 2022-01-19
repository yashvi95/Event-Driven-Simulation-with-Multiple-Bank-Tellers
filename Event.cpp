// Event.cpp

#include "Event.h"
#include<queue>
#include <string>
#include <iostream>
using namespace std;


//This class Event performs a simulation for a Bank with one teller, according to the arrival times 
//of the customers. 
//This class will count the total number of transactions and keep track of their cumulative transaction times 
//and waiting times. These statistics are sufficient to compute the average transaction times 
//and the average waiting time after the last event has been processed.



/////////////////////////Class Implementation/////////////////////////////////////////////////////////////

//Constructor
Event::Event()
{
}
//Constructor, which assigns the evenType enum to the type, either arrival or departure
//Assigns the customer arrival time and the customer duration to the appropriate variables
Event::Event(eventType type , unsigned time , unsigned duration, int teller) 
{
   eType = type;
   eTime = time;
   eDuration = duration; 
   Teller = teller;
}

//Copy Constructor
Event::Event(const Event& otherEvent)
{
   eType = otherEvent.getType();
   eTime = otherEvent.getTime();
   eDuration = otherEvent.getDuration();
   Teller = otherEvent.getTeller();
}
 
    // Determines the type of the event, either arrival or departure
Event::eventType Event::getType() const{   
   return eType;
}
    
    // Determines the time of the event, the customer arrives
unsigned Event::getTime() const{
   return eTime;
}
    
    // Determines the duration of the (arrival) event of the customer
unsigned Event::getDuration() const{
   return eDuration;
}

int Event::getTeller() const{   
   return Teller;
}


// Events are ordered by their event time (occurance), but if the same time occurence occurs
//the departure event is greater than the arrival event and also orders the teller by ascending order

bool operator < ( const Event& lhs , const Event& rhs ){
       if((lhs.eTime == rhs.eTime) && (lhs.eType == rhs.eType)){
          return lhs.getTeller() < rhs.getTeller();
       }
          else if(lhs.eTime == rhs.eTime)
           {
              return lhs.getType() > rhs.getType();
           }
        else
         return lhs.getTime() < rhs.getTime();
}

// Events are ordered by their event time (occurance), but if the same time occurence occurs
//the departure event is greater than the arrival event and also orders the teller by ascending order

bool operator > ( const Event& lhs , const Event& rhs ){
      if((lhs.eTime == rhs.eTime) && (lhs.eType == rhs.eType)){
          return lhs.getTeller() > rhs.getTeller();
       }
          else if(lhs.eTime == rhs.eTime)
           {
              return lhs.getType() < rhs.getType();
           }
        else
         return lhs.getTime() > rhs.getTime();
}

    