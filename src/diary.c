#include "../include/diary.h"
#include "../include/interface.h"
#include <stdio.h>

// diary counter function

int diaryCount(string username) {
  string path;
  int count = -1;
  sprintf(path, "%s%s%s", PATH_INFO, username, EXTENSION_INF);
  file data = fopen(path, "r");
  if(data == NULL) {
    printf("Error reading %s.inf file\n", username);
    return count;
  }
  fscanf(data, "%d", &count);
  fclose(data);
  return count;
}

// writes to file
int ink(string username) {
  string path;
  string pathNew;
  char buffer[DIARY_SIZE];
  int count = 0;
 
  // diary object
  diary newDiary;
  printf("Name of the diary\n> ");
  fgets(newDiary.name, MAX_STRING_SIZE, stdin);
  printf("Title of the diary\n> ");
  fgets(newDiary.title, MAX_STRING_SIZE, stdin);
  printf("Tag\n> ");
  fgets(newDiary.tag, MAX_STRING_SIZE, stdin);
  printf("Day\n> ");
  fgets(newDiary.day, MAX_STRING_SIZE, stdin);
  printf("Add to favorites(y/n)\n> ");
  fgets(newDiary.favorites, MAX_STRING_SIZE, stdin);
  printf("Author\n> ");
  fgets(newDiary.author, MAX_STRING_SIZE, stdin);
  printf("Enter numeric date\n");
  printf("Day: ");
  scanf("%d", &newDiary.timestamp.day);
  printf("Month: ");
  scanf("%d", &newDiary.timestamp.month);
  printf("Year: ");
  scanf("%d", &newDiary.timestamp.year);
  

  count = diaryCount(username);
  if(count == -1) {
    count = 1;
  }
  else {
    count += 1;
  }
  // opening file 
  sprintf(path, "%s%s%s", PATH_DIARY, username, EXTENSION_TXT);
  sprintf(pathNew, "%s%d.%s%s", PATH_DIARY, count, username, EXTENSION_TXT);
  
  file entry = fopen(path, "a");
  if(entry == NULL) {
    printf("Error Creating New File\n");
    return FALSE;
  } 
  // writing to file
  fprintf(entry, "Name: %s", newDiary.name);
  fprintf(entry, "Title: %s", newDiary.title);
  fprintf(entry, "Tag: %s", newDiary.tag);
  fprintf(entry, "Day: %s", newDiary.day);
  fprintf(entry, "Added to favorites: %s", newDiary.favorites);
  fprintf(entry, "Author: %s", newDiary.author);
  fprintf(entry, "Date: %d/%d/%d\n", newDiary.timestamp.day, newDiary.timestamp.month, newDiary.timestamp.year);
  // fwrite(&newDiary, sizeof(newDiary), 1, entry);
  clearScreen(0);
  printf("Write below. Write :s to stop writing\n> ");
  while(TRUE) {
    if(fgets(buffer, DIARY_SIZE, stdin) == NULL)
      break;
    if(strcmp(buffer, ":s\n") == 0)
      break;
    fputs(buffer, entry);
  }
  fseek(entry, 0, SEEK_END);
  printf("Successfully wrote %ld bytes\n", ftell(entry));
  fclose(entry);
  rename(path, pathNew);
  generateList(username); // generating diary list
  return TRUE;
}

void generateList(string username) {
  string path, tempPath, filename, newFilename, diaryName, feed;
  int count;

  count = diaryCount(username);
  sprintf(newFilename, "temp.inf");
  sprintf(filename, "%s%s", username, EXTENSION_INF);
  sprintf(path, "%s%s%s", PATH_INFO, username, EXTENSION_INF);
  sprintf(tempPath, "%stemp%s", PATH_INFO, EXTENSION_INF);
  sprintf(diaryName, "%s%s", username, EXTENSION_TXT);
  
  if(count == -1) {
    count = 1;
    file inf = fopen(path, "w");
    if(inf == NULL) {
      printf("Error generating %s.inf file\n", username);
      return;
    }
    fprintf(inf, "%d\n", count);
    fprintf(inf, "%d.%s\n", count, diaryName);
    fclose(inf);
  }

  else {
    count += 1;
    file tempfile = fopen(tempPath, "w");
    file info = fopen(path, "r");
    if(tempfile == NULL || info == NULL) {
      printf("Error generating %s.inf file\n", username);
      return;
    }
    fprintf(tempfile, "%d\n", count);
    fgets(feed, MAX_STRING_SIZE, info);
    while(fgets(feed, MAX_STRING_SIZE, info) != NULL) {
      fprintf(tempfile, "%s", feed);
    }
    fprintf(tempfile, "%d.%s\n", count, diaryName);
    remove(path);
    rename(tempPath, path);
    fclose(tempfile);
    fclose(info);

  }
  return;
}
void openDiaryContent(string username, int index) {
  string pathFile;
  char lines[DIARY_SIZE];
  //__fpurge(stdin);
  flushStream();
  sprintf(pathFile, "%s%d.%s%s", PATH_DIARY, index, username, EXTENSION_TXT);
  file viewFile = fopen(pathFile, "r");
  if(viewFile == NULL) {
    printf("Error opening file\n");
    return;
  }
  printf("\n\n");
  while(fgets(lines, DIARY_SIZE, viewFile) != NULL) {
    printf("%s", lines);
  }
  printf("\n\n");
}
int viewDiary(string username) {
  int choice;
  string filename, pathInf, pathFile;
  string lines;
  char option;
  char diaryLines[DIARY_SIZE];
  int dcount = diaryCount(username);
  // Printing List of files
  sprintf(pathInf, "%s%s%s", PATH_INFO, username, EXTENSION_INF);
  file viewList = fopen(pathInf, "r");
  if(viewList == NULL) {
    printf("No record found\n");
    sleep(1);
    return FALSE;
  }
  printf("Diray List\n");
  border();
  fgets(lines, MAX_STRING_SIZE, viewList);
  while(fgets(lines, MAX_STRING_SIZE, viewList) != NULL) {
    printf("%s", lines);
  }
  // if(dcount )
  // Prompt for action
  printf("\nOption\n> ");
  scanf("%c", &option);
  if(option == 'o') {
    printf("Index\n> ");
    scanf("%d", &choice);
    openDiaryContent(username, choice);
    //__fpurge(stdin);
    flushStream();
    return TRUE;
    
  }
  if(option == '/') {
    searchDiary(username);
    return TRUE;
  }
  if(option == 'd') {
    deleteDiary(username);
    return TRUE;
  }
  if(option == 'm') {
    return FALSE;
  }
  return TRUE;
}

void deleteDiary(string username) {
  string path, pathInf, pathTemp;
  int choice, firstNum;
  string lines;
  printf("Enter diary index to delete\n> ");
  scanf("%d", &choice);
  sprintf(path, "%s%d.%s%s", PATH_DIARY, choice, username, EXTENSION_TXT);
  sprintf(pathInf, "%s%s%s", PATH_INFO, username, EXTENSION_INF);
  sprintf(pathTemp, "%stemp%s", PATH_INFO, EXTENSION_INF);
  if(remove(path) == 0) {
    printf("%d.%s%s deleted successfully\n", choice, username, EXTENSION_TXT);
    file update = fopen(pathInf, "r");
    file temp = fopen(pathTemp, "w");
    while(fgets(lines, MAX_STRING_SIZE, update) != NULL) {
      firstNum = atoi(&lines[0]);
      if(choice == firstNum && lines[1] == '.') 
        continue;
      else {
        fprintf(temp, "%s", lines);
      }
    }
    fclose(update);
    fclose(temp);
    remove(pathInf);
    rename(pathTemp, pathInf);

  }
  else {
    printf("Unable to delete file\n");
  }
  //__fpurge(stdin);
  flushStream();
}

int searchDiary(string username) {
  string pathDiary, phrase;
  char line[DIARY_SIZE];
  int index, lineNumber, found;
  lineNumber = 1;
  printf("Index of the file\n> ");
  scanf("%d", &index);
  printf("Phrase to search\n> ");
  //__fpurge(stdin);
  flushStream();
  fgets(phrase, MAX_STRING_SIZE, stdin);
  sprintf(pathDiary, "%s%d.%s%s", PATH_DIARY, index, username, EXTENSION_TXT);
  file search = fopen(pathDiary, "r");
  if(search == NULL) {
    printf("Error reading diary file\n");
    return FALSE;
  }
  openDiaryContent(username, index);

  while(fgets(line, DIARY_SIZE, search) != NULL) {
    char *pos = strstr(line, phrase);
    if(pos != NULL) {
      printf("Phrase found at line: %d\n", lineNumber);
      printf("%s", line);
      found = TRUE;
    }
    lineNumber++;
  }
  fclose(search);
  if(!found) {
    printf("Phrase Not Found\n");
    return FALSE;
  }
  return TRUE;
}
