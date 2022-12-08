#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Uses getopt to parse the command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "cduf:s:")) != -1)
    {
        switch (opt)
        {
        case 'c':
        case 'd':
        case 'u':
            printf("Option: %c\n", opt);
            break;
        case 'f':
            printf("Option f with argument: '%s'\n", optarg);
            break;
        case 's':
            printf("Option s with argument: '%s'\n", optarg);
            break;
        case ':':
            printf("Option -%c requires an argument\n", optopt);
            break;
        case '?':
            printf("\n");
            printf("INVALID OPTION: -%c at index %d\n", optopt, optind);
            // Print out the help menu if the user passes an unknown option
            printf("Usage: %s [OPTION]... [INPUT-FILE]... [OUTPUT-FILE]...\n\n", argv[0]);
            printf("Options:\n");
            printf("  -c | --compress\t\tCompress the input file\n");
            printf("  -d | --decompress\t\tDecompress the input file\n");
            printf("  -u | --uncompress\t\tUncompress the input file\n");
            printf("  -f | --fields\t\t\tFields to check\n");
            printf("  -s | --string\t\t\tString to check\n\n");
            return 1;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        // First Arg is Input File
        if (i == optind)
        {
            printf("Input File: %s\n", argv[i]);
        }
        // Second Arg is Output File
        else if (i == optind + 1)
        {
            printf("Output File: %s\n", argv[i]);
        }
    }

    return 0;
}
