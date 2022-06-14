#include <time.h>
#include <Arduino.h>
extern "C"
{
  #include "user_interface.h"
}
#define TiempoEnTicks 60

os_timer_t myTimer;
bool tickOccured;
bool espera = true;

int timezone = 5;
int dst = 0;
int acum = 0;

String Mes(int x){
	switch(x){
		case 0:
		return "Ene";
		break;
		
		case 1:
		return "Feb";
		
		break;
		
		case 2:
		return "Mar";
		
		break;

		case 3:
		return "Abr";

		break;
		
		case 4:
		return "May";

		break;
		
		case 5:
		return "Jun";
		
		break;
		
		case 6:
		return "Jul";

		
		break;
		
		case 7:
		return "Ago";

		break;
		
		case 8:
		return "Sep";

		break;
		
		case 9:
		return "Oct";
	
		break;
		
		case 10:
		return "Nov";
		
		break;
		
		case 11:
		return "Dic";			
	    break;

		default:
		return "None";
		}
	
}


String Tiempolocal(){
	  time_t now = time(nullptr);//creo timer
	  struct tm * timeinfo; //en lib time
	  time(&now);
      timeinfo = localtime(&now);  //en lib time
	  String hora = String(timeinfo->tm_hour);
	  if (hora.toInt()<=9) hora= "0"+hora;
	  String minutos = String(timeinfo->tm_min);
	  if (minutos.toInt()<=9) minutos= "0"+minutos;
	  String seg = String(timeinfo->tm_sec);
	  if (seg.toInt()<=9) seg= "0"+seg;
	  String dia = String(timeinfo->tm_mday);
	  String mes = Mes(timeinfo->tm_mon);
	  String anio = String((1900+timeinfo->tm_year)%100);
	  	  
	  //return (dia+mes+anio+" "+ hora +":"+ minutos +":"+ seg);
	  return(hora +":"+ minutos +":"+ seg);
}
void timerCallback(void *pArg) {

	  acum++;
      tickOccured = true;
	  if(acum>=TiempoEnTicks){
		espera = true;
		acum = 0;
	  }	  
	  
	  
		  
} // End of timerCallback

void user_init(void) {
 /*
  os_timer_setfn - Define a function to be called when the timer fires

void os_timer_setfn(
      os_timer_t *pTimer,
      os_timer_func_t *pFunction,
      void *pArg)

Define the callback function that will be called when the timer reaches zero. The pTimer parameters is a pointer to the timer control structure.

The pFunction parameters is a pointer to the callback function.

The pArg parameter is a value that will be passed into the called back function. The callback function should have the signature:
void (*functionName)(void *pArg)

The pArg parameter is the value registered with the callback function.
*/

      os_timer_setfn(&myTimer, timerCallback, NULL);

/*
      os_timer_arm -  Enable a millisecond granularity timer.

void os_timer_arm(
      os_timer_t *pTimer,
      uint32_t milliseconds,
      bool repeat)

Arm a timer such that is starts ticking and fires when the clock reaches zero.

The pTimer parameter is a pointed to a timer control structure.
The milliseconds parameter is the duration of the timer measured in milliseconds. The repeat parameter is whether or not the timer will restart once it has reached zero.

*/

      os_timer_arm(&myTimer, 1000, true);
} // End of user_init