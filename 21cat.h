#include <ctype.h> /* проверка и изменение некоторых символов */
#include <fcntl.h> /* open()*/
#include <getopt.h>/* обработка аргументов командной строки */
#include <stdio.h>       /* ввод-вывод */
#include <stdlib.h>      /* очистка памяти malloc, free, exit */
#include <string.h>      /* строки */
#include <unistd.h>      /* read(), write() close() */
#define BUFFER_SIZE 1024 // Определение размера буфера для чтения данных
/* Функция для вывода строки с учетом указанных флагов */
