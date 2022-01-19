// Event.h by bjuliano@csuchico.edu

#ifndef EVENT_H_
#define EVENT_H_

class Event
{

  public:
  
    enum eventType { undefined , arrival , departure };
  
    Event( );
    Event(eventType type , unsigned time , unsigned duration = 0, int teller = -1 );
    Event( const Event& otherEvent );
  
    // Determines the type of the event
    eventType getType() const;
    
    // Determines the time of the event
    unsigned getTime() const;
    
    // Determines the duration of the (arrival) event
    unsigned getDuration() const;
    
    int  getTeller() const;
    // Events are ordered by their event time (occurance)
    friend bool operator<( const Event& lhs , const Event& rhs );
    friend bool operator>( const Event& lhs , const Event& rhs );
    				 
  private:
  
    eventType     eType;       // type of event
    unsigned      eTime;      // time of event occurance
    unsigned  eDuration;      // duration, if event is an arrival event
    int          Teller=0;
};

#endif