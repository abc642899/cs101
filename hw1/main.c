#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main() {
  FILE* fp;
  int slots = 0;
  time_t date = time(NULL);
  srand((unsigned)time(NULL));
  printf("　歡迎光臨長庚樂透彩購買機台\n　請問您要買幾組樂透彩（1－5）：");
  scanf("%d", &slots);
  if (slots < 1 || slots > 5) {
    main();
    return 0;
  };
  fp = fopen("lotto.txt","w+");
  fprintf(fp, "======== lotto649 =========\n");
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
  fprintf(fp, "======== csie@CGU =========\n");
  fclose(fp);
  printf("　以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", slots);
  return 0;
}
