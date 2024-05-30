#include "../include/interface.h"

void border() {
  printf("--------------------------------------------------------\n");
}

void flushStream() {
  #ifdef __linux__
    __fpurge(stdin);
  #elif _WIN32
    // fflush(stdin);
    int c;
    do {
      c = getchar();
    }
    while(c != '\n' && c != EOF);
  #endif
}

void clearScreen(int duration) {
  sleep(duration);
  #ifdef __linux__
    system("clear");
  #elif _WIN32
    system("cls");
  #endif
}


void interface(int window, int clear) {
  string loginComponents[4] = {"Login(l)", "Sign Up(s)", "Forgot Password(f)", "Exit(e)"};
  string diaryComponents[5] = {"New Diary(n)", "View(v)", "Help(h)", "Logout(o)"};
  string editComponents[5] = {"Open(o)", "Search(/)", "Delete(d)", "Rewrite(r)", "Main Menu(m)"};
  if(clear == TRUE)
    clearScreen(DEFAULT_SLEEP);
  if(window == LOGIN) {
    for(int i = 0; i < 4; i++) {
      printf("%s%s", loginComponents[i], SPACING);
    }
    printf("%s", NEWLINE);
    border();
    printf(NEWLINE);
    return;
  }
  if(window == DIARY) {
    for(int i = 0; i < 5; i++) {
      printf("%s%s", diaryComponents[i], SPACING);
    }
    printf("%s", NEWLINE);
    border();
    printf(NEWLINE);
    return;
  }
  if(window == EDIT){
    for(int i = 0; i < 5; i++) {
      printf("%s%s", editComponents[i], SPACING);
    }
    printf("%s", NEWLINE);
    border();
    printf(NEWLINE);
    return;
  }
  if(window == LOGO) {
    printf("       __..._   _...__\n");
    printf("  _..-\"      `Y`      \"-._\n");
    printf("  \\ Day book  |           /\n");
    printf("  \\\\          |          //\n");
    printf("  \\\\\\         |         ///\n");
    printf("   \\\\\\ _..---.|.---.._ ///\n");
    printf("    \\\\`_..---.Y.---.._`//\n");
    printf("     '`               `'\n");
    printf(NEWLINE);
    return;
  }
  if(window == HELP) {
    printf("Help\n");
    border();
    printf("- Use the characters hinted within brackets (n) to navigate through the program.\n- You must have a username and password to use the program. If it's first time, sign up first.\n- Don't input string value on integer fields as that might result in undefined behavior\n- The diary files are stored in the diary folder with your username.\n- While writing a new diary, type :s on a newline to save the new diary file. If the program is not respoding, please restart it. ");
    printf(NEWLINE);
    printf("Day Book, version 1.0, dev: Roman Mia\n");
    printf(NEWLINE);
    return;

  }
}


void message(int id) {
  string name = "Enter username\n> ";
  string pass = "Enter password\n> ";
  string rec = "Enter recovery key\n> ";
  string restrictions = "Sign Up\nUsername must be strictly alphabetical\nPassword must not exceed 16 characters\nRecovery must be 5 digits\n\n";
  string errName = "Invalid username. Try again!\n";
  string errPass = "Invalid password. Try again!\n";
  string errRec = "Recovery key must be 5 digits. Try again!\n> ";
  string logs = "Login Successfull\n";
  string logf = "Login Failed\n";
  string signs = "Signup Successfull\n";
  string signf = "Signup Failed\n";
  string inputs = "Data submitted succesfully\n";
  string inputf = "Input failed\n";
  if(id == NAME) {
    printf("%s", name);
    return;
  }
  if(id == PASS) {
    printf("%s", pass);
    return;
  }
  if(id == REC) {
    printf("%s", rec);
    return;
  }
  if(id == ERR_NAME) {
    printf("%s", errName);
    return;
  }
  if(id == ERR_PASS) {
    printf("%s", errPass);
    return;
  }
  if(id == ERR_REC) {
    printf("%s", errRec);
    return;
  }
  if(id == RES) {
    printf("%s", restrictions);
    return;
  }
  if(id == LOGS) {
    printf("%s", logs);
    return;
  }
  if(id == LOGF) {
    printf("%s", logf);
    return;
  }
  if(id == SIGNS) {
    printf("%s", signs);
    return;
  }
  if(id == SIGNF) {
    printf("%s", signf);
    return;
  }
  if(id == INPUTF) {
    printf("%s", inputf);
    return;
  }
  if(id == INPUTS) {
    printf("%s", inputs);
    return;
  }
    
}

