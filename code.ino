#include <Stepper.h>

const int one_move = 2048;
const int speed = 17;
const int step = 1;

Stepper myStepper(one_move, 8, 10, 9, 11);

int position = 0;
const int X_pin = A0;
const int SW_pin = 2;

void setup()
{
    myStepper.setSpeed(speed);
    myStepper.step(step);
    Serial.begin(9600);
    pinMode(SW_pin, INPUT);
    digitalWrite(SW_pin, HIGH);
}

void loop()
{
    int sw = digitalRead(SW_pin);

    while (analogRead(X_pin) > 600)
    {
        myStepper.step(-one_move);
        position += one_move;
        if (position % 2048 == 0)
            position = 0;
    }

    while (analogRead(X_pin) < 300)
    {
        myStepper.step(one_move);
        position -= one_move;
        if (position % 2048 == 0)
            position = 0;
    }

    if (sw == 0)
    {
        if (position > 0 && position % 2048 != 0)
        {
            while (position != 0) 
            {
                myStepper.step(one_move);
                position -= one_move;
            }
        }
        if (position < 0 && position % 2048 != 0)
        {
            while (position != 0)
            {
                myStepper.step(-one_move);
                position += one_move;
            }
        }
    }
}