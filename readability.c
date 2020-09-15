// Reading grade check
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int text_length = strlen(text);
    float letters = 0;
    float words = 1;
    float sentences = 0;

    for (int i = 0; i < text_length; i++)
    {
        // Check for space
        if (text[i] == 32)
        {
            words++;
        }
        // check for fullstop or questionmark
        else if (text[i] == 46 || text[i] == 63)
        {

            sentences++;
        }
        else if ((text[i] > 64 && text[i] < 90) || (text[i] > 96 && text[i] < 123))
        {
            letters++;
        }
    }

    // Average letters per 100 words
    float l = 100 / words * letters;
    // Average sentences per 100 words
    float s = 100 / words * sentences;

    // The Coleman-Liau index
    float index = 0.0588 * l - 0.296 * s - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        int grade = roundf(index);
        printf("Grade %i\n", grade);
    }
}