#ifndef TELLER_H_
#define TELLER_H_

class Teller
{

  public:
  
    Teller( );
    
    // Determines the number of Transactions of the Teller 
    unsigned getTransaction() const;
    
    // Determines if the Teller is Available
    bool getStatus() const;
    
    //Determines the Transaction Duration for the Customer
    unsigned getTimeTransaction() const;
    
    //Determines the Average transaction time for each Teller
    float getAverage() const;
    
    //Updates the transaction for each Teller
    void numTransaction(unsigned duration);
    
    //Updates the status for each Teller 
    void updateStatus(bool status);
    
    				 
  private:
    unsigned         tTransaction = 0;       // Number of Transactions
    float        tTimeTransaction = 0;       // Total Time of Transactions
    unsigned             tAverage = 0;      // Departure Time for Customer
    bool               tStatus = true;     // Status of Teller
    
};

#endif