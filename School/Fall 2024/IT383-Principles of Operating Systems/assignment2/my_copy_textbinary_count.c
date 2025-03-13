//Shane Stevens

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* args[]){
    if(argc != 3){
        printf("This program only works when 2 arguments are provided\n");
    }
    int numBytes = 1024;
    char* text = (char*)calloc(numBytes, sizeof(char));
    int bytesRead;
    int totalBytes = 0;
    int writeVal;
    int src = open(args[1], O_RDONLY);
    int dst = open(args[2], O_WRONLY | O_CREAT | O_TRUNC);
    if(src == -1 || dst == -1){
            printf("A error has occurred while opening the files");
            exit(-1);
        }
     bytesRead = read(src, text, numBytes);
    while(bytesRead != 0){
        if(bytesRead == -1){
            printf("A read error has occurred");
            exit(-1);
        }
        totalBytes+= bytesRead;
        writeVal = write(dst, text, bytesRead);
        if(writeVal == -1){
            printf("A write error has occurred");
            exit(-1);
        }
        bytesRead = read(src, text, numBytes);
    }
    char* byteText = (char*)calloc(100, sizeof(char));
    sprintf(byteText, "Total number of bytes: %d", totalBytes);
    writeVal = write(dst, byteText, strlen(byteText));
        if(writeVal == -1){
            printf("A write error has occurred");
            exit(-1);
        }
    printf("%s was copied to %s successfully.\n", args[1], args[2]);
    printf("%s\n", byteText);
    close(src);
    close(dst);
}