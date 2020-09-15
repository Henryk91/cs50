# Task Spec https://cs50.harvard.edu/x/2020/psets/4/recover/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define BLOCK 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check that there are one argument for the name of the file.
    if (argc != 2)
    {
        printf("Recover only needs one argument (file name).\n");
        return 1;
    }

    // Open Memory card (raw file)
    FILE *file = fopen(argv[1], "r");
    if (file)
    {
        // Allocate memory for one BLOCK of memory and read from infile

        BYTE *buffer = malloc(BLOCK);
        int file_count = 0;
        int startedFile = 0;
        if (buffer == NULL)
        {
            return 3;
        }

        FILE *image;
        int byte_count = 1;

        // Open Memory card
        do
        {
            // Read 512 bytes into buffer
            byte_count = fread(buffer, BLOCK, byte_count, file);

            // Check if file header has jpg start values
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                ((buffer[3] & 0xf0) == 0xe0))
            {

                // if alerady found JPEG
                if (startedFile == 1)
                {
                    // Need to close previos pic before starting new one
                    fclose(image);
                }

                // Create new image file
                // JPG name should be saved as ###.jpg starting at 000.jpg
                // sprintf(filename, "%03i.jpg", 2); (%03i means print int with 3 digets)

                char filename[8];
                sprintf(filename, "%03i.jpg", file_count);
                image = fopen(filename, "w");

                if (image == NULL)
                {
                    printf("Outfile is null.\n");
                    fclose(image);
                    free(buffer);
                    fclose(file);
                    return 3;
                }

                // Write to file add file to file count
                fwrite(buffer, BLOCK, byte_count, image);
                startedFile = 1;
                file_count++;
            }
            else if (startedFile == 1)
            {
                // if file is open write buffer data to file
                fwrite(buffer, BLOCK, byte_count, image);
            }


            if (byte_count != 1)
            {
                // At end of .raw file so save data and close image file
                fwrite(buffer, BLOCK, byte_count, image);
                fclose(image);
            }

            // Repeat until end of card:
        }
        while (byte_count != 0);

        // Free buffer memory close file and stop program
        free(buffer);
        fclose(file);
        return 0;
    }
    else
    {
        printf("No file with given name found.\n");
        return 1;
    }
}
