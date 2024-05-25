#include "globaldefs.h"
// declaration of diary object
struct tmsp {
  int day;
  int month;
  int year;
};

typedef struct diary {
  string index;
  string name;
  string title;
  string tag;
  string day;
  string favorites;      
  string author;
  struct tmsp timestamp; 
} diary;

int edit();
int view();
void help();
int logout();
int search();
int ink(string author);
int viewDiary(string username);
void inf();
void generateList(string filename);
void deleteDiary(string filename);
int searchDiary(string username);
