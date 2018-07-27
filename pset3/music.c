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
    return (numerator * 8)/(denominator * 1);

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

    else if (carrizo == 'B')
    {
        if (Octave == 4)
        {
            semitone = 2;
        }
        if (Octave > 4)
        {
            semitone = 2 + (12*(Octave - 4));
        }
        else
        {
            semitone = - 1 * ((12*(4 - Octave)) - 2);
        }
    }

    else if (carrizo == 'C')
    {
        semitone = 9;
    }
    else if (carrizo == 'D')
    {
        semitone = 7;
    }
    else if (carrizo == 'E')
    {
        semitone = 5;
    }
    else if (carrizo == 'F')
    {
        semitone = 4;
    }
    else if (carrizo == 'G')
    {
        semitone = 2;
    }

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

    if (strlen(note) == 3)
    {
        if (Octave > 4 && type == 1)
        {
            semitone++;
        }
        else if (Octave > 4 && type == 0)
        {
            semitone--;
        }
        else if (Octave < 4 && type == 1)
        {
            semitone++;
        }
        else if (Octave < 4 && type == 0)
        {
            semitone--;
        }
        else if (Octave == 4)
        {
            if (type == 1)
            {
                semitone++;
            }
            else
            {
                semitone--;
            }
        }
    }

    float expo = semitone/12.0;
    return round(440 * pow(2, expo));


}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    return !strlen(s);
}
