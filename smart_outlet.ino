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

#define	LED	13	//LED on if at least one relay is activated
#define	Relay_A	8	//Relay: Channel A
#define	Relay_B 7	//Relay: Channel B

//Global State of each channel
bool	state_A	= LOW;
bool	state_B = LOW;

void	setup() 
{
	pinMode(LED, OUTPUT);
	pinMode(Relay_A, OUTPUT);
	pinMode(Relay_B, OUTPUT);

	Serial.begin(9600);
	while (!Serial)		//Wait until serial is available
	;
}

void	loop()
{
	char	data;
    
	if (Serial.available() > 0)			//If something is sent to serial
	{
      		data = Serial.read();			//Store here what was sent
		if (data == 'a' || data == 'A')		//See if it was asked to on/off channel A
		{
			state_A = not state_A;
			digitalWrite(Relay_A, state_A);
		}
		else if (data == 'b' || data == 'B')	//See if it was asked to on/off channel B
		{
			state_B = not state_B;
			digitalWrite(Relay_B, state_B);
		}
	}
	if (state_A == HIGH || state_B == HIGH)		//If one, or both, channel is ON, turn LED ON
		digitalWrite(LED, HIGH);
	else
		digitalWrite(LED, LOW);
	delay(100);
}
