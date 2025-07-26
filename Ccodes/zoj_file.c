#include <stdio.h>
#include "FIO45.h"
extern void simulate_delay();
#define REPLACE_CHAR '#'

void file_char_replace(const char* file) {
    int size = 0;
    FILE* fp = fopen(file, "r");
    
    // Step 1: 获取文件原始长度
    if (fp != NULL) {
        fseek(fp, 0L, SEEK_END);
        size = ftell(fp);
        fclose(fp);
    } else {
        printf("Open file failed!\n");
        return;
    }

    /* Don't Delete!!!(start) */
    simulate_delay();
    /* Don't Delete!!!(end) */

    // Step 2: 扩展文件至两倍长度（追加相同数量的替换字符）
    fp = fopen(file, "a");
    if (fp != NULL) {
        for (int i = 0; i < size; i++) {
            fputc(REPLACE_CHAR, fp); // 追加 size 个字符
        }
        fclose(fp);
    } else {
        printf("Failed to open file for appending!\n");
        return;
    }

    // Step 3: 覆盖整个文件（替换所有字符为 REPLACE_CHAR）
    fp = fopen(file, "r+");
    if (fp != NULL) {
        fseek(fp, 0L, SEEK_SET); // 回到文件开头
        for (int i = 0; i < 2 * size; i++) {
            fputc(REPLACE_CHAR, fp); // 写入 2*size 个字符
        }
        fclose(fp);
    } else {
        printf("Failed to open file for writing!\n");
    }
}
