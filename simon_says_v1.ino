//
// Simon Says
//
// Version 1.0
//

#include "pitches.h"

int speakerPin = 8; // The pin the speaker is on.
int startTune[] = {NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, 
                   NOTE_C4, NOTE_F4, NOTE_C4, NOTE_F4, 
                   NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, 
                   NOTE_G4};
int startDuration[] = {100, 200, 100, 200,
                       100, 400, 100, 100,
                       100, 100, 200, 100,
                       500};

int note[] = {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5};
int noteDuration[] = {100, 100, 100, 300, 100, 300};

int turn = 0; // turn counter
int buttonState = 0; // button state checker
int randomArray[100]; // store up to 100 inputs
int inputArray[100];

boolean buttonPin[] = {2, 3, 4, 5}; // Button pins
boolean ledPin[] = {9, 10, 11, 12}; // LED pins

void setup()
{
  // setup LED pins as outputs
  for(int x=0; x<4; x++)
  {
    pinMode(ledPin[x], OUTPUT);
  }
  
  // setup button pins as inputs with internal pullups
  for(int x=0; x<4; x++)
  {
    pinMode(buttonPin[x], INPUT);
    digitalWrite(buttonPin[x], HIGH); // enable internal pullup; buttons start in high position; logic reversed
  }
   
  randomSeed(analogRead(0)); // Add a generate "more randomness" with the randomArray for the output function
  for(int thisNote=0; thisNote<13; thisNote++)
  {
    // play the next note
    //speakerPin.play(startTune[thisNote]);
    tone(speakerPin, startTune[thisNote], startDuration[thisNote]);
    // Now flash LEDS depending on the note
    if (thisNote == 0 || thisNote == 2 || thisNote == 4 || thisNote == 6)
    {
      digitalWrite(ledPin[0], HIGH);
    }
    if (thisNote == 1 || thisNote == 3 || thisNote == 5 || thisNote == 7 || thisNote == 9 || thisNote == 11)
    {
      digitalWrite(ledPin[1], HIGH);
    }
    if (thisNote == 8 || thisNote == 12)
    {
      digitalWrite(ledPin[2], HIGH);
    }
    if (thisNote == 10)
    {
      digitalWrite(ledPin[3], HIGH);
    }
    delay(startDuration[thisNote]);
    // stop for the next note
    //speakerPin.stop();
    setAllLEDs(LOW);
    delay(25);
  }
  delay(1000);
}

void loop()
{
  for(int y=0; y<=99; y++)
  {
    // function for generatting the array to be matched by the player
    setAllLEDs(HIGH);
     
    // play intro tune
    for(int thisNote=0; thisNote<6; thisNote++)
    {
      // play the next note
      //speakerPin.play(note[thisNote]);
      tone(speakerPin, note[thisNote], noteDuration[thisNote]);
      // hold the note
      delay(noteDuration[thisNote]);
      // stop for the next note
      //speakerPin.stop();
      delay(25);
    }
    
    setAllLEDs(LOW);
    delay(1000);    
    
    for(int y=turn; y<=turn; y++)
    {
      // Limied by the turn variable
      randomArray[y] = random(1, 5); // Assign a random number (1-4) to this to randomArray[turn count]
      
      for(int x=0; x<=turn; x++)
      {
        for(int y=0; y<4; y++)
        {
          if(randomArray[x] == 1 && ledPin[y] == ledPin[0])
          {
            digitalWrite(ledPin[y], HIGH);
            tone(speakerPin, NOTE_G3, 100);
            delay(400);
            digitalWrite(ledPin[y], LOW);
            delay(100);
          }
          
          if(randomArray[x] == 2 && ledPin[y] == ledPin[1])
          {
            digitalWrite(ledPin[y], HIGH);
            tone(speakerPin, NOTE_A3, 100);
            delay(400);
            digitalWrite(ledPin[y], LOW);
            delay(100);
          }

          if(randomArray[x] == 3 && ledPin[y] == ledPin[2])
          {
            digitalWrite(ledPin[y], HIGH);
            tone(speakerPin, NOTE_B3, 100);
            delay(400);
            digitalWrite(ledPin[y], LOW);
            delay(100);
          }
          if(randomArray[x] == 4 && ledPin[y] == ledPin[3])
          {
            digitalWrite(ledPin[y], HIGH);
            tone(speakerPin, NOTE_C4, 100);
            delay(400);
            digitalWrite(ledPin[y], LOW);
            delay(100);
          }
        }
      }
    }
    input();
    //scoreDisplay.write(turn);
  } 
}

void setAllLEDs(bool state)
{
  // This function sets all the LEDs to the requested state
  for(int i=0; i<4; i++)
  {
    digitalWrite(ledPin[i], state);
  }
}

void input()
{
  //Function for allowing user input and checking input against the generated array
  
  for(int x=0; x<=turn;) // statement controlled by turn count
  {
    for(int y=0; y<4; y++)
    {
      buttonState = digitalRead(buttonPin[y]);
      
      // First button
      if (buttonState == LOW && buttonPin[y] == buttonPin[0])
      {
        // Checking for button push
        digitalWrite(ledPin[0], HIGH);
        tone(speakerPin, NOTE_G3, 100);
        delay(200);
        digitalWrite(ledPin[0], LOW);
        inputArray[x] = 1;
        delay(250);
        if (inputArray[x] != randomArray[x])
        {
          fail();
        }
        x++;
      }
      
      // Second Button
      if (buttonState == LOW && buttonPin[y] == buttonPin[1])
      {
        // Checking for button push
        digitalWrite(ledPin[1], HIGH);
        tone(speakerPin, NOTE_A3, 100);
        delay(200);
        digitalWrite(ledPin[1], LOW);
        inputArray[x] = 2;
        delay(250);
        if (inputArray[x] != randomArray[x])
        {
          fail();
        }
        x++;
      }

      // Third Button
      if (buttonState == LOW && buttonPin[y] == buttonPin[2])
      {
        // Checking for button push
        digitalWrite(ledPin[2], HIGH);
        tone(speakerPin, NOTE_B3, 100);
        delay(200);
        digitalWrite(ledPin[2], LOW);
        inputArray[x] = 3;
        delay(250);
        if (inputArray[x] != randomArray[x])
        {
          fail();
        }
        x++;
      }
      
      // Forth Button
      if (buttonState == LOW && buttonPin[y] == buttonPin[3])
      {
        // Checking for button push
        digitalWrite(ledPin[3], HIGH);
        tone(speakerPin, NOTE_C4, 100);
        delay(200);
        digitalWrite(ledPin[3], LOW);
        inputArray[x] = 4;
        delay(250);
        if (inputArray[x] != randomArray[x])
        {
          fail();
        }
        x++;
      }
    }
  }
  delay(500);
  turn++; // Increment the turn count
}

void fail()
{
  // Player failed to match the sequence
  for(int y=0; y<=2; y++)
  {
    // Flash lights for failure
    digitalWrite(ledPin[0], HIGH);
    digitalWrite(ledPin[1], HIGH);
    digitalWrite(ledPin[2], HIGH);
    digitalWrite(ledPin[3], HIGH);
    tone(speakerPin, NOTE_G3, 300);
    delay(200);
    digitalWrite(ledPin[0], LOW);
    digitalWrite(ledPin[1], LOW);
    digitalWrite(ledPin[2], LOW);
    digitalWrite(ledPin[3], LOW);
    tone(speakerPin, NOTE_C3, 300);
    delay(200);
  }
  delay(500);
  turn = -1; // Reset turn value so the game starts over without need for a reset button
}


