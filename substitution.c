// Encryption with Key
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool duplicateCheck(string key);

int main(int argc, string argv[])
{

    string key;
    // Check that there are 2 args for key and name
    if (argc == 2)
    {
        key = argv[1];
        int text_length = strlen(key);
        if (text_length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        if (duplicateCheck(key))
        {
            return 1;
        }
    }
    else
    {
        // Not enough args
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Get text to encrypt
    string text = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int j = 0, n = strlen(text); j < n; j++)
    {
        // Check if character to encrypt was an uppercase letter
        bool input_is_upper = false;
        int val;

        if (text[j] > 64 && text[j] <= 90)
        {
            // Get new value from key
            val = text[j] - 64;
            input_is_upper = true;
        }
        else if (text[j] > 95)
        {
            // Get new value from key
            val = text[j] - 96;
        }
        else
        {
            // Is not a letter
            val = 0;
        }

        if (val)
        {
            char enc = key[val - 1];
            bool key_is_upper = false;
            // Check if key character was an uppercase letter
            if (enc < 96)
            {
                // Key is upper case
                key_is_upper = true;
            }


            if (input_is_upper)
            {
                if (!key_is_upper)
                {
                    // Convert to upper case
                    printf("%c", enc - 32);
                }
                else
                {
                    printf("%c", enc);
                }
            }
            else
            {
                if (!key_is_upper)
                {
                    // Key isnt upper case
                    printf("%c", enc);
                }
                else
                {
                    // Convert to lower case
                    printf("%c", enc + 32);
                }
            }
        }
        else if (val == 0)
        {
            printf("%c", text[j]);
        }

    }
    printf("\n");
    return 0;
}



bool duplicateCheck(string key)
{
    // Checks for duplicates and non letters
    int key_length = strlen(key);
    for (int i = 0; i < key_length; i++)
    {
        if (key[i] < 65 || key[i] > 122 || (key[i] < 96 && key[i] > 90))
        {
            printf("Key must only contain letters.\n");
            return true;
        }

        for (int j = 0; j <= key_length; j++)
        {
            if (key[i] == key[j] && i != j)
            {
                printf("Key must not contain duplicates.\n");
                return true;
            }
        }
    }
    return false;
}