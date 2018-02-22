/********************************************************/
/*							*/
/*							*/
/*	smart_outlet.ino				*/
/*							*/
/*	By: rFeijoo <goldcard99@hotmail.com>		*/
/*							*/
/*	Created: 2018/02/19 17:54:37			*/
/*	Updated: 2018/02/21 22:02:42			*/
/*							*/
/********************************************************/

#include <IRremote.h>

#define	LED	13					//LED on if at least one relay is activated
#define	Relay_A	8					//Relay: Channel A
#define	Relay_B 7					//Relay: Channel B
#define IR_Led	5					//Infra Red LED

IRsend	irsend;

//Global State of each channel
bool	state_A	= LOW;
bool	state_B = LOW;
bool	stat_TV = LOW;

void	setup() 
{
	pinMode(LED, OUTPUT);
	pinMode(Relay_A, OUTPUT);
	pinMode(Relay_B, OUTPUT);

	Serial.begin(9600);
	while (!Serial)					//Wait until serial is available
	;
}

void	loop()
{
	int	data;
    
	if (Serial.available() > 0)			//If something is sent to serial
	{
      		data = Serial.read();			//Store what was sent
		if (data == 1)				//TV ON/OFF
		{
			stat_TV = not stat_TV;
			irsend.sendNEC(0xBD807F, 32);
		}
		else if (data == 2)			//TV Vol Up
			irsend.sendNEC(0xBD30CF, 32);
		else if (data == 3)			//TV Vol Down
			irsend.sendNEC(0xBD08F7, 32);
		else if (data == 4)			//TV MUTE
			irsend.sendNEC(0xBD20DF, 32);
		else if (data == 5)			//Channel A ON/OFF
		{
			state_A = not state_A;
			digitalWrite(Relay_A, state_A);
		}
		else if (data == 6)			//Channel B ON/OFF
		{
			state_B = not state_B;
			digitalWrite(Relay_B, state_B);
		}
	}
	if (state_A || state_B || stat_TV)		//If one of the electronics is turned on, LED will be ON
		digitalWrite(LED, HIGH);
	else
		digitalWrite(LED, LOW);
	delay(100);
}
