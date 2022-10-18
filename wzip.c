#include <stdio.h>
#include <string.h>

/*
 定义为全局变量，便于多个文件分批处理
 主要是考虑到上一文件的末尾字符与新文件的头一个字符相同的情况
*/
// 上次相同的字符
char lastC;
// 现在读取的字符
char curC;
// 上次相同字符数量
int num;

// 根据文件名压缩文件
int zipFile(int count, char *filename){
  FILE *file = fopen(filename, "r");
  if (file == NULL){
    printf("wzip: cannot open file\n");
    return 1;
  }
  // 只要第一次读的文件需要赋初值
  if (count == 1){
    lastC = getc(file);
    num = 1;
  }
  while((curC = getc(file)) != EOF) {
    if(curC == lastC) 
      num++;
    else{
      fwrite(&num, sizeof(int), 1, stdout);
      fwrite(&lastC, sizeof(char), 1, stdout);
      lastC = curC;
      num = 1;
    }
  }
  return 0;
}

int main(int argc,char **argv) {
  int i;
  if(argc <= 1) {
    printf("wzip: file1 [file2 ...]\n");
    return 1;
  }else {
    for (i = 1; i < argc; ++i){
      if (zipFile(i, argv[i]) == 1)
        return 1;
    }
    fwrite(&num, sizeof(int), 1, stdout);
    fwrite(&lastC, sizeof(char), 1, stdout);
  }
  return 0;
}


