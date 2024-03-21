#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

float calculate_index(int characters, int words, int sentence);
float coleman_liau_index(string input);
void reading_level(float index);

// ----------------------------------------------------------------------------------------------------------------------

int main()
{
    // Get the index number as a float
    float number = coleman_liau_index(get_string("Input a string: "));

    // Print the results
    reading_level(number);
}

// ----------------------------------------------------------------------------------------------------------------------

float coleman_liau_index(string input)
// Takes a string and sums the total chars, words and sentences found.
// Calls the function to calcuate the index value.
{
    int total_characters = 0;
    int total_words = 0;
    int total_sentences = 0;
    int length = strlen(input);

    char previous_character;

    // Sums the total characters, words and sentences contained within the input string.
    for (int i = 0; i < length; i++)
    {
        // Increase word count using space as a terminator
        if (input[i] == ' ')
        {
            // Account for white space and punctuation
            if (previous_character != '.' && previous_character != '?' && previous_character != '!')
            {
                total_words++;
            }
        }
        // Increase word and sentence count using punctuation as a terminator
        else if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            total_words++;
            total_sentences++;
        }
        // Increase character count ignoring white space and characters we haven't already account
        // for.
        else if (input[i] != '\n' && input[i] != '\t' && input[i] != '\'' && input[i] != ',')
        {
            total_characters++;
        }
        // Record the current character so we can check against the logic on the next iteration of
        // the loop.
        previous_character = input[i];
    }

    // Check for non fullstop terminated sentences at the end of the input. Treat that as a
    // sentence.
    if (previous_character != '.' && previous_character != '?' && previous_character != '!')
    {
        total_words++;
        total_sentences++;
    }

    return calculate_index(total_characters, total_words, total_sentences);
}

// ----------------------------------------------------------------------------------------------------------------------

float calculate_index(int characters, int words, int sentence)
// Takes the character, word and sentence counts and returns the reading level as a float.
{
    // Constant values used in the calculation
    float const VALUE_1 = 0.0588;
    float const VALUE_2 = 0.296;
    float const VALUE_3 = 15.8;

    // Cast ints to floats to prevent data loss - calculate average values per word
    float characters_per_word = (float)characters / (float)words;
    float words_per_sentence = (float)sentence / (float)words;

    // calclate the average values per 100 words
    float l_value = characters_per_word * 100;
    float s_value = words_per_sentence * 100;

    return VALUE_1 * l_value - VALUE_2 * s_value - VALUE_3;
}

// ----------------------------------------------------------------------------------------------------------------------

void reading_level(float index)
// Prints the result to the user
{
    // Round the index to the nearest whole number
    int rounded_index = (int)index;
    float remainder = index - rounded_index;
    if (remainder >= 0.5)
    {
        rounded_index++;
    }

    // Report the results
    if (rounded_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded_index < 16)
    {
        printf("Grade %i\n", rounded_index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}
