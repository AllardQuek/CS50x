// Helper functions for music

#include <cs50.h>
#include <math.h> //for pow and round
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //take as input as a string a fraction and convert it to some integral number of eighths.
    //ASSUME that duration will only be passed a string formatted as X/Y, where X and Y is a positive decimal digit, and Y is a power of 2.
    //minus '0' works based on ASCII chart, getting the string, e.g '4', to be cast into the int 4. ASCII: 48;0 49;1 50;2 51;3 52;4
    int numerator = fraction[0] - '0'; //where fraction[0] gives numerator as a string
    int denominator = fraction[2] - '0'; //OR int numerator = atoi(&fraction[0]); where & is a pointer giving the ADDRESS where for e.g, char '4', is being stored
    int dur;

    dur = numerator * (8 / denominator);
    return dur;

}

// Calculates frequency (in Hz) of a note as an int, by taking input note of type string.
int frequency(string note)
{
    //freq of some note is 2n/12 × 440, where n is no. of semitones from that note to A4.
    //Only implement support initially ONLY for A0 through A8. Ensure that frequency returns the expected values for those notes, as by running notes or using debug50 or eprintf. Compare your function’s output against your own calculations on paper or on a calculator.
    //Then add support for # and b but still only for A0 through A8 (i.e., A#0 through A#8 and Ab0 through Ab8). Then add support for B, C and beyond.
    int n = strlen(note);
    double freq = 0.0; //initialize value of double to 0.0

    //note[0] note name, note[1] if it exists is accidental
    //note[n-1]; //octave no.

    //for all octaves of A to G
    //pow takes inputs of type DOUBLE, must use 2.0 and 12.0 instead of just in 2 and 12!
    //freq = 440 x (no. of semitones the note is from A4) * (no. of octaves note is from 4th octave)
    switch (note[0])
    {
        case 'A':
            freq = 440 * pow(2.0, (note[n - 1] - '0' - 4));
            break;
        case 'B':
            freq = 440 * pow(2.0, (2.0 / 12.0)) * pow(2.0, (note[n - 1] - '0' - 4));
            break;
        case 'C':
            freq = 440 * pow(2.0, (-9.0 / 12.0)) * pow(2.0, (note[n - 1] - '0' - 4));
            break;
        case 'D':
            freq = 440 * pow(2.0, (-7.0 / 12.0)) * pow(2.0, (note[n - 1] - '0' - 4));
            break;
        case 'E':
            freq = 440 * pow(2.0, (-5.0 / 12.0)) * pow(2.0, (note[n - 1] - '0' - 4));
            break;
        case 'F':
            freq = 440 * pow(2.0, (-4.0 / 12.0)) * pow(2.0, (note[n - 1] - '0' - 4));
            break;
        case 'G':
            freq = 440 * pow(2.0, (-2.0 / 12.0)) * pow(2.0, (note[n - 1] - '0' - 4));
            break;
    }

    //Account for accidentals; #/b
    if (note[1] == '#')
        freq = freq * pow(2.0, (1.0 / 12.0));

    else if (note[1] == 'b')
        freq = freq * pow(2.0, (-1.0 / 12.0));


    return round(freq);
}

// Determines whether a string represents a rest (return true/false)
bool is_rest(string s)
{
    //If user inputs only a line ending, returns "", not NULL. Returns NULL upon error or no input whatsoever (i.e., just EOF, which is ctrl-d).
    // if the 0th character in the string is null terminator, NOT //(strcmp(s, "\n"))
    if (s[0] == '\0')
        return true;

    return false;
}
