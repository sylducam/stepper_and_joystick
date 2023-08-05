#include <Stepper.h>

const int one_move = 1000;
const int speed = 30;
const int step = 1;

Stepper myStepper(one_move, 8, 10, 9, 11);

int position = 0;
const int X_pin = A0;
const int SW_pin = 2;

void setup()
{
    myStepper.setSpeed(speed);
    myStepper.step(step);
    Serial.begin(19200);
    pinMode(SW_pin, INPUT);
    digitalWrite(SW_pin, HIGH);
}

void loop()
{
    int sw = digitalRead(SW_pin);

    while (analogRead(X_pin) > 600)
    {
        myStepper.step(step);
        position += step;
        if (position % 2048 == 0)
            position = 0;
    }

    while (analogRead(X_pin) < 300)
    {
        myStepper.step(-step);
        position -= step;
        if (position % 2048 == 0)
            position = 0;
    }
    if (sw == 0)
    {
        int new_position = position % 2048;
        if (position > 0)
        {
            if (new_position <= 1024)
            {
                while (position != 0)
                {
                    myStepper.step(-step);
                    if (position < 0)
                        position += step;
                    else
                        position -= step;
                    if (position % 2048 == 0)
                        position = 0;
                }
            }
            else
            {
                while (position != 0)
                {
                    myStepper.step(step);
                    position += step;
                    if (position % 2048 == 0)
                        position = 0;
                }
            }
        }
        else
        {
            if (new_position <= -1024)
            {
                while (position != 0)
                {
                    myStepper.step(-step);
                    position -= step;
                    if (position % 2048 == 0)
                        position = 0;
                }
            }
            else
            {
                while (position != 0)
                {
                    myStepper.step(step);
                    if (position < 0)
                        position += step;
                    else
                        position -= step;
                }
            }
        }
    }
}