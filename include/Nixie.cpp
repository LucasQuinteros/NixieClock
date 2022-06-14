#include <Arduino.h>
class Nixie
{
  private:
    uint8_t Bit;
    uint Numero = 0;
  public:
    Nixie(uint8_t pin);
    ~Nixie();
    void display(uint Number);
};

  Nixie::Nixie(uint8_t pin)
  {
    Bit = pin;
    pinMode(Bit,OUTPUT);
    digitalWrite(Bit,HIGH);
  }

  Nixie::~Nixie()
  {

  }

  void Nixie::display(uint pulses){
        int Result;
        
        if( pulses >= Numero ){
            Result = pulses - Numero ; 
        }
        else
        {
            Result = pulses + (10 - Numero);
        }
        Numero = pulses;
        for (int i = 0; i < Result ; i++)
        {
          
          digitalWrite(Bit,LOW);
          delay(50);
          digitalWrite(Bit,HIGH);
        }
  }  