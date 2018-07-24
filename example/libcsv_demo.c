#include <rtthread.h>
#include <rtdevice.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

/* libcsv */
#include "libcsv.h"

/* optparse */
#include "optparse.h"

#define PROGRAM_NAME "csvcheck"
#define AUTHORS "Robert Gamble"

static struct optparse_long longopts[] =
{
    {"delimiter", 'd',          OPTPARSE_REQUIRED},
    {"quote",     'q',          OPTPARSE_REQUIRED},
    {"help",      CHAR_MAX + 1, OPTPARSE_NONE},
    {NULL,        0,            OPTPARSE_NONE}
};

/* The name this program was called with */
char *program_name;

/* The delimiter character */
char delimiter = CSV_COMMA;

/* The delimiter argument */
char *delimiter_name;

/* The quote character */
char quote = CSV_QUOTE;

/* The quote argument */
char *quote_name;

void usage(int status)
{
  if (status != RT_EOK)
    fprintf (stderr, "Try `%s --help for more information.\n", program_name);
  else {
    printf("\
Usage: %s [OPTION]... [FILE]...\n\
Determine if file(s) are properly formed CSV files and display the position\n\
of the first offending byte if not.\n\
\n\
", program_name);
    printf("\
  -d, --delimiter=DELIM   use DELIM as the delimiter instead of comma\n\
  -q, --quote=QUOTE_CHAR  use QUOTE_CHAR as the quote character instead of\n\
                          double quote\n\
      --help              display this help and exit\n\
");
  }
}

void check_file(char *filename)
{
    size_t pos = 0;
    char buf[1024];
    struct csv_parser p;
    FILE *fp;
    size_t bytes_read;
    size_t retval;

    if (csv_init(&p, CSV_STRICT | CSV_STRICT_FINI) != 0)
    {
        fprintf(stderr, "Failed to initialize csv parser\n");
        return; 
    }
    csv_set_delim(&p, delimiter);
    csv_set_quote(&p, quote);

    if (filename == NULL || !strcmp(filename, "-"))
    {
        fp = stdin;
    }
    else
    {
        fp = fopen(filename, "rb");
        if (fp == NULL)
        {
            fprintf(stderr, "Failed to open file %s: %s\n", filename, strerror(errno));
            csv_free(&p);
            return;
        }
    }

    while ((bytes_read = fread(buf, 1, 1024, fp)) > 0)
    {
        if ((retval = csv_parse(&p, buf, bytes_read, NULL, NULL, NULL)) != bytes_read)
        {
            if (csv_error(&p) == CSV_EPARSE)
            {
                printf("%s: malformed at byte %lu\n", filename ? filename : "stdin", (unsigned long)pos + retval + 1);
                goto end;
            }
            else
            {
                printf("Error while processing %s: %s\n", filename ? filename : "stdin", csv_strerror(csv_error(&p)));
                goto end;
            }
        }
        pos += 1024;
    }

    if (csv_fini(&p, NULL, NULL, NULL) != 0)
        printf("%s: missing closing quote at end of input\n", filename ? filename : "stdin");
    else
        printf("%s well-formed\n", filename ? filename : "data is");

end:
    fclose(fp);
}

int csvcheck(int argc, char *argv[])
{
    int optc;
    int option_index;
    program_name = argv[0]; 
    struct optparse options;
    
    if(argc == 1)
    {
        usage(RT_EOK);
        return RT_EOK; 
    }

    optparse_init(&options, argv);
    while ((optc = optparse_long(&options, longopts, &option_index)) != -1)
    {
        switch (optc)
        {
        case 'd':
            delimiter_name = options.optarg;
            if (strlen(delimiter_name) > 1)
                printf("delimiter must be exactly one byte long\n");
            else
                delimiter = delimiter_name[0];
            break;

        case 'q':
            quote_name = options.optarg;
            if (strlen(quote_name) > 1)
                printf("delimiter must be exactly one byte long\n");
            else
                quote = quote_name[0];
            break;

        case CHAR_MAX + 1:
            /* --help */
            usage(RT_EOK);
            return RT_EOK; 

        default:
            usage(RT_ERROR);
            return RT_ERROR; 
        }
    } 

    if (options.optind < argc)
    {
        while (options.optind < argc)
        {
            check_file(argv[options.optind++]);
        }
    }
    else
    {
        /* Process from stdin */
        check_file(NULL);
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(csvcheck, The command to check CSV files format based on the libcsv.); 
