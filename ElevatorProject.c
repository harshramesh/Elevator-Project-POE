/*
Copyright (c) 2014, Antonio
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific 
prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma config(Sensor, dgtl1,  Shaft,          sensorRotation)
#pragma config(Sensor, dgtl3,  First,          sensorTouch)
#pragma config(Sensor, dgtl4,  Second,         sensorTouch)
#pragma config(Sensor, dgtl5,  Third,          sensorTouch)
#pragma config(Sensor, dgtl6,  O1,             sensorLEDtoVCC)
#pragma config(Sensor, dgtl7,  U1,             sensorLEDtoVCC)
#pragma config(Sensor, dgtl8,  D2,             sensorLEDtoVCC)
#pragma config(Sensor, dgtl9,  O2,             sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, U2,             sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, D3,             sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, O3,             sensorLEDtoVCC)
#pragma config(Motor,  port1,  Elev,           tmotorVex393, openLoop)

#define ledOn turnLEDOn
#define ledOff turnLEDOff
#define sens SensorValue

void moveElev(int floorNum, int direction);
void lights(int floorNum);

int floorTo = 1, curFloor = 1;

task main()
{
while(true)
{
	if(curFloor == 1)
	{
		
		while(!(sens[First] || sens[Second] || sens[Third]));
		floorTo = (sens[First]) ? 1 : (sens[Second]) ? 2 : 3;
	
	}
	else
	{
		
		ClearTimer(T1);
		while(!(sens[First] || sens[Second] || sens[Third]))
			if(time1[T1] > 30000) break;
		if(time1[T1] > 30000) floorTo = 1;
		else floorTo = ((sens[First]) ? 1 : (sens[Second]) ? 2 : 3);
	
	}
	
	moveElev(floorTo, (floorTo > curFloor) ? -1 : (floorTo < curFloor) ? 1 : 0);
	curFloor = floorTo;

}
}

void moveElev(int floorNum, int direction)
{

	int floorVal = /*TODO ShaftEncoder Stuff*/0;
	while(SensorValue[Shaft] != floorVal)
	{

		startMotor(Elev, 30 * direction);

	}

	stopMotor(Elev);
	lights(floorNum);

}

void lights(int floorNum)
{

	if(floorNum < 3)
	{

		ledOff(O3);
		ledOn(D3);

	}
	else
	{
		
		ledOff(D3);
		ledOn(O3);
	
	}
	
	if(floorNum > 2)
	{

		ledOff(O2);
		ledOff(D2);
		ledOn(U2);

	}
	else if(floorNum < 2)
	{

		ledOff(O2);
		ledOff(U2);
		ledOn(D2);

	}
	else
	{
		
		ledOff(U1);
		ledOff(D2);
		ledOn(O1);
	
	}
	if(floorNum > 1)
	{

		ledOff(O1);
		ledOn(U1);

	}
	else
	{
		
		ledOff(U1);
		ledOn(O1);
	
	}

}
