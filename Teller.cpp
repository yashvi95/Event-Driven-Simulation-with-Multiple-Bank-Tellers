#include "Teller.h"
#include "Event.h"
#include <iostream>
using namespace std;


    Teller::Teller( )
    {
    }
    
    
    // Determines the number of Transactions of the Teller 
    unsigned Teller::getTransaction() const
    {
       return tTransaction;
    }
    
    // Determines if the Teller is Available
    bool Teller::getStatus() const
    {
       return tStatus;
    }
   
   //Determines the Transaction Duration for the Customer
    unsigned Teller::getTimeTransaction() const
    {
       return tTimeTransaction;
    }
   
    //Determines the Average transaction time for each Teller
    float Teller::getAverage() const
    {
       return tTimeTransaction/tTransaction;
    }
   
    //Updates the transaction for each Teller
    void Teller::numTransaction(unsigned duration)
    {
          tTransaction = tTransaction + 1;
          tTimeTransaction += duration;
    }
    
    //Updates the status for each Teller   
    void Teller::updateStatus(bool status)
    {
       tStatus = status;
    }
    
        
