#include "../include/account.h"

int accountPresence() {
  // string path;
  file account = fopen("data/usrdata.inf", "r");
  if(account == NULL ) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}
// data validation check if credentials are OK 
int dataValidation(string data, int id) {
  int length = strlen(data);
  if(id == NAME) {
    for(int i = 0; i < length; i++) {
      if(data[i] < 97 || data[i] > 122) {
        return FALSE;
      }
    }
  }
  if(id == PASS) {
    if(length > 12)
      return FALSE;
  }
  if(id == REC) {
    if(length > 5 || length < 5)
      return FALSE;
  }
  return TRUE;
}

// login funciton (if account already exists)
int login(char *username) {
  user tempUser, loginData;
  file account = fopen("data/usrdata.inf", "r");
  if(account == NULL) {
    return FALSE;
  }
  fscanf(account, "%s %s", loginData.name, loginData.password);
  input(tempUser.name, NAME);
  input(tempUser.password, PASS);
  if(checkExistence(&tempUser, 0, 2)) {
    strcpy(username, tempUser.name);
    return TRUE;
  }
  fclose(account);
  return FALSE;
}

// checks user data existence
int checkExistence(user *userData, int pos, int count) {
  string line;
  user testUser;
  file data = fopen("data/usrdata.inf", "r");
  if(data == NULL) {
    printf("Error checking username existence\n");
    return -1;
  }
  while(fgets(line, MAX_STRING_SIZE, data) != NULL) {
    sscanf(line, "%s %s %s", testUser.name, testUser.password, testUser.recoveryKey);
    if(pos == 0) {
      if(count == 2) {
        if(!strcmp(testUser.name, userData->name) && !strcmp(testUser.password, userData->password)) {
          return TRUE;
        } 
      }
      if(count == 1) {
        if(!strcmp(testUser.name, userData->name)) {
          return TRUE;
        }
      }
    }
    if(pos == 2) {
      if(!strcmp(testUser.recoveryKey, userData->recoveryKey)) {
        return TRUE;
      }
    }
  }
  return FALSE;
} 

// the signup function
int signup(char *username) {
  message(RES);
  string line; // to check if username already exists
  int filePermit = FALSE;
  file account = fopen("data/usrdata.inf", "a+");
  if(account == NULL) {
    return FALSE;
  }
  user newUser;
  int inputStat = 0;
  inputStat = input(newUser.name, NAME);
  if(!inputStat)
    return FALSE;
  inputStat = input(newUser.password, PASS);
  if(!inputStat)
    return FALSE;
  inputStat = input(newUser.recoveryKey, REC);
  if(!inputStat)
    return FALSE;
  if(checkExistence(&newUser, 0, 1)) {
    printf("Username already exists\n");
    return FALSE;
  }
  fprintf(account, "%s %s %s\n", newUser.name, newUser.password, newUser.recoveryKey);
  strcpy(username, newUser.name);
  fclose(account);

  return TRUE;
}

// input function for taking user credential input
int input(char *data, int id) {
  int errId = id + 1;
  int notCreated = TRUE;
  while(notCreated) {
    message(id);
    
    if(fgets(data, CREDENTIAL_SIZE, stdin) == NULL)
      return FALSE;
    if(data[strlen(data) - 1] == '\n') {
      data[strlen(data) - 1] = '\0';
    }
    if(!dataValidation(data, id)) {
      message(errId);
      continue;
    }
    notCreated = FALSE;
  }
  return TRUE;
}

