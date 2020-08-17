#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: ./recover image");
        return 1;
    }
    
    FILE *inp_file = fopen(argv[1], "r");
    
    if (inp_file == NULL) {
        printf("Usage: ./recover image");
        return 1;
    }

    unsigned char buffer[512];

    char filename[8];
    
    bool isopen = false;
    
    FILE *img;
    

    int img_num = 0;
    while (fread(buffer, sizeof buffer, 1, inp_file)) {

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0) {
            if (isopen) {
                fclose(img);

                isopen = false;
            }

            sprintf(filename, "%03i.jpg", img_num);
            
            img = fopen(filename, "w");

            fwrite(buffer, sizeof(buffer), 1, img);
            
            isopen = true;

            img_num++;
        }

        else {
            if (isopen) {

                fwrite(buffer, sizeof(buffer), 1, img);

            }
        }
    }

    fclose(inp_file);

    fclose(img);

    return 0;
}
