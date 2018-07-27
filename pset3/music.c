// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // We use string - '0' to turn the number characters into numerator and denominator
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';
    //We multiply the numerator by 8 and denominator by 1 to get a whole digit calling out the octave
    return (numerator * 8) / (denominator * 1);

}

// Calculates frequency (in Hz) of a note

int frequency(string note)
{
    //The semitone will hold the distance from that note to the
    int semitone = 0;
    //The Octave will be used to hold the given octave
    int Octave = 0;
    //Type 1 = sharp note, type 0 = flat note
    int type = 1;
    char carrizo = note[0];

    //This code will immediately check whether flat or sharp
    if (strlen(note) == 2)
    {
        Octave = atoi(&note[1]);
    }
    else
    {
        Octave = atoi(&note[2]);
        if (note[1] == 'b')
        {
            type = 0;
        }
    }

    //Note A is checked for either A4 or Octave
    if (carrizo == 'A')
    {
        if (Octave == 4 && strlen(note) == 2)
        {
            return 440;
        }
        else if (Octave > 4)
        {
            semitone = (Octave - 4) * 12;
        }
        else if (Octave < 4)
        {
            semitone = -1 * ((4 - Octave) * 12);
        }
    }

    //Note B is checked separately from the other notes due to being at the end of the Octave. It is also checked for Octave
    else if (carrizo == 'B')
    {
        if (Octave == 4)
        {
            semitone = 2;
        }
        if (Octave > 4)
        {
            semitone = 2 + (12 * (Octave - 4));
        }
        else
        {
            semitone = - 1 * ((12 * (4 - Octave)) - 2);
        }
    }

    //All other notes get their semitone called out
    switch (carrizo)
    {
        case 'C':
            semitone = 9;
            break;
        case 'D':
            semitone = 7;
            break;
        case 'E':
            semitone = 5;
            break;
        case 'F':
            semitone = 4;
            break;
        case 'G':
            semitone = 2;
            break;
    }

    //The notes not A or B are checked for Octave and semitone is adjusted to either side of A4
    if (carrizo != 'B' && carrizo != 'A')
    {
        if (Octave > 4)
        {
            semitone = (12 - semitone) + (12 * (Octave - 5));
        }
        else if (Octave < 4)
        {
            semitone = -1 * (semitone + (12 * (4 - Octave)));
        }
        else
        {
            semitone = -1 * semitone;
        }
    }

    //If the note had a Sharp or Flat its semitone is adjusted one space up or down
    if (strlen(note) == 3)
    {
        if ((Octave > 4 && type == 1) || (Octave < 4 && type == 1) || (Octave == 4 && type == 1))
        {
            semitone++;
        }
        else if ((Octave > 4 && type == 0) || (Octave < 4 && type == 0) || (Octave == 4 && type == 0))
        {
            semitone--;
        }
    }

    //the exponent is floated, then 2 to the exponent multipled by 440 and rounded
    float expo = semitone / 12.0;
    return round(440 * pow(2, expo));


}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //boolean check for whether a black/empty string was passed to the function
    return !strlen(s);
}