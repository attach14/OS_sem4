#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
const int size = 16384; // максимальный допустимый размер 

int main(int argc, char* argv[]){
    char buffer[size];
    int fd_input, fd_output;
    ssize_t read_bytes;
    if((fd_input = open(argv[1], O_RDONLY)) < 0){ // проверка, что файл с входным текстом получилось открыть
        printf("Can't open input file\n");
        return 0;
    }
    if((fd_output = open(argv[2], O_WRONLY)) < 0){ // проверка, что файл для записи получилось открыть
        printf("Can't open output file\n");
        return 0;
    }
    read_bytes = read(fd_input, buffer, size);
    if(read_bytes == -1){ // проверка, что размера буфера хватило для записи
        printf("Input file is too big\n");
        return 0;
    }
    size_t size = write(fd_output, buffer, read_bytes);
    // проверки, что файлы удалось закрыть
    if(close(fd_output) < 0){
        printf("Can't close output file\n");
        return 0;
    }
    if(close(fd_input) < 0){
        printf("Can't close input file\n");
        return 0;
    }
    printf("Ok\n");
    return 0;
}