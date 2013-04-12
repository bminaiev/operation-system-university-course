#include <unistd.h>

char delim = ' ';
int buf_len = 4 * 1024;
char *buffer;

void do_main_part(int fr, int len) {
    write(1, buffer + fr, len);
}

int main(int argc, char ** argv) {
    int c;
    while ((c = getopt(argc, argv, "nzb:")) != -1) {
        switch (c)
        {
            case 'n':
                delim = '\n';
                break;
            case 'z':
                delim = 0;
                break;
            case 'b':
                buf_len = optarg;
                break;
            default:
                abort();
        }
    }



    buffer = (char *) malloc(buf_len);
    int eof = 0;
    int from = 0;
    while (1 - eof) {
        int r = read(0, buffer + from, buf_len - from);
        if (r == 0) {
            eof = 1;
            *(buffer + from) = delim;
            from++;
        }    
        from += r;
        while (1) {
            int i;
            int first_delim = -1;
            for (i = 0; i < from; i++) {
                if (*(buffer + i) == '\n') {
                    first_delim = i;
                    break;
                }
            }
            if (first_delim == -1) {
                break;
            }
            do_main_part(0, first_delim - 1);
            for (i = first_delim + 1; i < from; i++) {
                *(buffer + i - first_delim - 1) = *(buffer + i);
            }
            from -= first_delim - 1;
        }
        if (from == buf_len) {
            return 1;
        }
    }    
    free(buffer);
    return 0;
}
