#include <stdio.h>
#include<stdlib.h>

// 解压缩文件并输出到STDOUT
int unzipFile(char *filename) {
  FILE *file = fopen(filename, "rb");
  char c;
  int num, j;
  if(file == NULL){
    printf("wunzip: cannot open file\n");
    return 1;
  } 
  while(fread(&num, sizeof(int), 1, file) != 0 && fread(&c, sizeof(char), 1, file) != 0){
    for(j = 0;j < num; j++) {
      putc(c, stdout);
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  int i;
  if(argc <= 1) {
    printf("wunzip: file1 [file2 ...]\n");
    return 1;
  } 
  for(i = 1; i < argc; i++) {
    if (unzipFile(argv[i]) == 1)
      return 1;
  }
  return 0;
}
