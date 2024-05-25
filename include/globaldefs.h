#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include <stdio_ext.h>
#endif
#define DIARY_SIZE 1500
#define MAX_STRING_SIZE 200
#define TRUE 1
#define FALSE 0
#define NAME 100 
#define PASS 200 
#define REC 300
#define ERR_NAME 101     
#define ERR_PASS 201 
#define ERR_REC 301
#define RES 1000
#define LOGS 2000
#define LOGF 2001
#define SIGNS 3000
#define SIGNF 3001
#define INPUTS 4000
#define INPUTF 4001
#define LOGIN 301
#define DIARY 401
#define EDIT 501
#define LOGO 600
#define HELP 700
#define COMPONENT_SIZE 20
#define SPACING "    "
#define NEWLINE "\n"
#define DEFAULT_SLEEP 0 
#define PATH_INFO "data/"
#define PATH_DIARY "diary/"
#define EXTENSION_TXT ".txt"
#define EXTENSION_INF ".inf"
typedef char string[MAX_STRING_SIZE]; 
typedef FILE* file;
