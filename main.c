#include "include/aio.h"
int main() {
  char control;
  string username;
  int existingAccount, loginStat, signupStat, viewStat;
  // Main Loop
  while(TRUE) {
    interface(LOGO, TRUE);
    interface(LOGIN, FALSE);
    printf("> ");
    scanf(" %c", &control);
    // __fpurge(stdin);
    flushStream(); 
    if(control == 'l') {
      if(!accountPresence()) {
        printf("No account found\nPlease Signup\n");
        sleep(1);
        continue;
      }
      loginStat = login(username);
      if(loginStat == FALSE)
        printf("Login Failed\n");
    }
    else if(control == 's') {
      signupStat = signup(username);
      if(signupStat == FALSE)
        printf("Signup Failed\n");
    }
    else if(control == 'f') {
      //recoverPass();
      recoverPass();
    }
    else if(control == 'e') {
      break;
    }
    if(loginStat == TRUE || signupStat == TRUE) {
      while(TRUE) {

        interface(DIARY, TRUE);
        printf("> ");
        scanf(" %c", &control);
        flushStream();
        if(control == 'n') {
          ink(username);
        }
        else if(control == 'v') {
          while(TRUE) {
            interface(EDIT, TRUE);
            viewStat = viewDiary(username);
            if(viewStat == FALSE)
              break;
            printf("\nPress any key to continue...");
            getchar();
          }
        }
        else if(control == 'h') {
          interface(HELP, TRUE);
          printf("\nPress any key to continue...");
          getchar();
        }
        else if(control == 'o') {
          loginStat = FALSE;
          signupStat = FALSE;
          break;
        }
        else {
          printf("Wrong Input\n");
          continue;
        }
      }
    }
  }
  return 0;
}
