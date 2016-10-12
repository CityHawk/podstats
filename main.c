#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <zlib.h>
#include <errno.h>
#include <string.h>
#include <regex.h>
#include "sortstruct.h"

#define LENGTH 0x1000
static regex_t regex;

static obj oo[100];

void add_result(char *result) {
    o_add(oo, result);
}

void parse_string(char *s) {
    int reti;
    regmatch_t pmatch[2];
    size_t nmatch = 2;

    reti = regexec(&regex, s, nmatch, pmatch, 0);
    if (!reti) {
        char *result;
        result = (char*)malloc(pmatch[0].rm_eo - pmatch[0].rm_so);
        strncpy(result, s+pmatch[0].rm_so, pmatch[0].rm_eo - pmatch[0].rm_so);
        /* printf("%s\n", result); */
        add_result(result);
        free(result);
    } else if (reti == REG_NOMATCH) {
        ;;
    } else {
        char msgbuf[100];
        regerror(reti, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        exit(1);
    }
}

void parse_init(void) {
    int reti;
    reti = regcomp(&regex, "pip[0-9][0-9].mp3", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    gzFile file;
    char buffer[LENGTH];
    int err;

    if (argc < 2)
        exit(1);

    struct dirent *ep;
    DIR *dp;
    dp = opendir(argv[1]);
    parse_init();

    if (dp != NULL) {
        while ((ep = readdir(dp))) {
            if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
                continue;
            char file_name[256];
            char *out=NULL;
            sprintf(file_name, "%s/%s", argv[1], ep->d_name);
            file = gzopen(file_name, "r");
            if (!file) {
                fprintf (stderr, "gzopen of '%s' failed: %s.\n", ep->d_name, strerror (errno));
                exit (EXIT_FAILURE);
            }
            while (!gzeof(file)) {
                if ((out = gzgets(file, buffer, 1024)) != NULL) {
                    parse_string(out);
                } else {
                    if (!gzeof(file)) {
                        const char * error_string;
                        error_string = gzerror(file, &err);
                        fprintf (stderr, "Error %s: %s.\n", ep->d_name, error_string);
                        break;
                    }
                }
            }
            gzclose(file);
        }
        closedir(dp);
    }
    sort_by_name(oo);
    o_print(oo);
    return 0;
}
