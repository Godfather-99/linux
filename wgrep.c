#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// 从STDIN读入内容并匹配单词
void grepStdin(char *word){
  char *input = (char *) malloc(sizeof(char) * 10000);
  while(fgets(input, 9999, stdin) != NULL) {
    if(strstr(input, word) != NULL) {
      printf("%s", input);
    }
  }
}

// 读取文件，找到包含单词的行并打印
int grepFile(char *word, char *filename){
  int cnt = 0;
  size_t len = 0;
  FILE *file = fopen(filename, "r");
  char *line;
  if(file==NULL){
    printf("wgrep: cannot open file\n");
    return 1;
  }else{
     while((cnt = getline(&line, &len, file)) != -1){
        if(strstr(line, word) != NULL){
          printf("%s", line);
        }
      }
   }
 fclose(file);
 return 0;
} 

int main(int argc, char **argv) {
  int i;
  if(argc <= 1){
    // 没有任何参数wgrep输出 wgrep: searchterm [file ...] 并返回1
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  }else if (argc == 2) {
    // 参数只有一个单词没有文件名则从STDIN读入内容
    grepStdin(argv[1]);
  }else{
    // 多个文件名 依次用参数单词匹配打印
    for(i = 2; i < argc; i++){
      if (grepFile(argv[1], argv[i]) == 1)
        return 1;
    }
  }
  return 0;
}
  
