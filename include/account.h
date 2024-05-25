#include "../include/globaldefs.h"
#include "../include/interface.h"
#define CREDENTIAL_SIZE 20
typedef struct usr {
  string name, password, recoveryKey;
} user;
int accountPresence();
int signup(char *username);
int login(char *username);
int dataValidation(string data, int id);
int input(char *data, int id);
// takes parameters a struct, a position and count, valid values for count are 1, 2 and valid values for pos are 0, 2
int checkExistence(user *userData, int pos, int count);
int recoverPass();
