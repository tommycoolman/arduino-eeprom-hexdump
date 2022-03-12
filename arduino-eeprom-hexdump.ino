#include <Wire.h>

#define chipAddress 80

void setup()
{
	Serial.begin(9600);
	Wire.begin();

	//writeTo(chipAddress, cellAddress, 128);
	unsigned cellAddress;

	for (int row = 0; row < 32; row++)
	{
		cellAddress = (16 * row);
		for (int offset = 0; offset < 16; offset++)
		{
			int x = readFrom(chipAddress, cellAddress + offset);
			printHex(x, 2);
			Serial.print(" ");
		}
		Serial.print(" | ");
		cellAddress = (16 * row);
		for (int offset = 0; offset < 16; offset++)
		{
			int x = readFrom(chipAddress, cellAddress + offset);
			if (x >= 16 && x <= 126)
			{
				Serial.write(x);
			}
			else
			{
				Serial.write(".");
			}
			Serial.print("");
		}
		Serial.println("|");
	}
}

void loop()
{
}

void writeTo(int chAddress, unsigned int ceAddress, byte wData)
{
	Wire.beginTransmission(chAddress);
	Wire.write((int)(ceAddress >> 8));
	Wire.write((int)(ceAddress & 0xFF));
	Wire.write(wData);
	Wire.endTransmission();

	delay(10);
}

byte readFrom(int chAddress, unsigned int ceAddress)
{
	Wire.beginTransmission(chAddress);
	Wire.write((int)(ceAddress >> 8));
	Wire.write((int)(ceAddress & 0xFF));
	Wire.endTransmission();

	Wire.requestFrom(chAddress, 1);

	byte rData = 0;
	if (Wire.available())
	{
		rData = Wire.read();
	}

	return rData;
}

void printHex(int num, int precision)
{
	char tmp[16];
	char format[128];

	sprintf(format, "%%.%dX", precision);

	sprintf(tmp, format, num);
	Serial.print(tmp);
}
