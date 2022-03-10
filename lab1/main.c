#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define COUNTER_FILE = "counter.bin"

void init_file(){
    int write_array[1] = {0};
    FILE* tmpfp = fopen(COUNTER_FILE,"r");
    if (tmpfp == NULL){
        FILE* fp = fopen(COUNTER_FILE,"wb+");
        fwrite(write_array,sizeof(int),1,fp);
        fclose(fp);
    } else {
        fclose(tmpfp);
    }
}

int get_counter() {
    int read_array[1];
    FILE* fp = fopen(COUNTER_FILE,"rb");
    fread(read_array,sizeof(int),1,fp);
    fclose(fp);
    return read_array[0];
}

int slot(int arr[6]) {
  for (int i = 0; arr[4] == 0;) {
    int num = (rand() % 69) + 1, j = 0;
    for (int k = 0; k < i && j == 0; k++) (arr[k] == num) ? j = 1 : 0;
    if (j == 0) arr[i++] = num;
  };
  for (int i = 0; i < 4; i++) {
    int key = arr[i + 1], j = i;
    while (key < arr[j] && j >= 0) {
      arr[j + 1] = arr[j];
      j--;
    };
    arr[j + 1] = key;
  };
  arr[5] = (rand() % 10) + 1;
  return arr[6];
}

void set_counter(){
    int write_array[1];
    write_array[0] = counter;
    FILE* fp = fopen(COUNTER_FILE,"wb");
    fwrite(write_array,sizeof(int),1,fp);
    fclose(fp);
}

int main() {
  FILE* fp;
  int counter;
  init_file();
  counter = get_counter();
  printf("counter = %d\n", counter);
  int slots = 0;
  int op_id = 0;
  time_t date = time(NULL);
  srand((unsigned)time(NULL));
  printf("　歓迎光臨長庚楽透彩購買機台\n");
  printf("  請輸入操作人員ID:(0~5):");
  scanf("%d",&op_id);
  if (op_id < 0 || op_id > 5){
      main();
      return 0;
  };
  printf("　請問您要買幾組楽透彩（1－5）：");
  scanf("%d", &slots);
  if (slots < 1 || slots > 5) {
    main();
    return 0;
  };
  fp = fopen("lotto.txt","w+");
  fprintf(fp, "======== lotto649 ==========\n");
  fprintf(fp, "= %s =\n", strtok(ctime(&date), "\n"));
  for (int i = 0; i < 5; i++) {
    fprintf(fp, "[%d]：", i + 1);
    if (i < slots) {
      int arr[6] = {0};
      slot(arr);
      for (int j = 0; j < 6; j++) fprintf(fp, "%02d　%s", arr[j], (j == 5) ? "\n" : "");
    } else {
      for (int j = 0; j < 6; j++) fprintf(fp, "--　%s", (j == 5) ? "\n" : "");
    };
  };
  fprintf(fp, "=======* Op.%05d *=========\n",op_id);
  fprintf(fp, "======== csie@CGU ==========\n");
  fclose(fp);
  printf("　以為您購買的 %d 組楽透組合輸出至 lotto.txt\n", slots);
  set_counter(counter);
  return 0;
}
