#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char title[100];
char content[5000];
void print_box(char* title, char* content);
//实现自适应文本框的关键在于计算每行文本的显示长度。
// 这里使用了一个函数 get_display_length 来计算字符串的长度。
// 这个函数会遍历字符串中的每个字符，如果字符是一个三字节的UTF-8字符（假设为中文），则长度加2；
// 如果字符是一个单字节字符（假设为英文），则长度加1。

int get_display_length(char* str) {
    int length = 0;
    while (*str) {
        if (*str == '\t') {  // 制表符
            length += 4;  // 假设一个制表符等于4个空格
            str += 1;
        }
        else if ((*str & 0x80) == 0) {  // 单字节UTF-8字符
            length += 1;
            str += 1;
        }
        else if ((*str & 0xE0) == 0xC0) {  // 双字节UTF-8字符
            length += 2;
            str += 2;
        }
        else if ((*str & 0xF0) == 0xE0) {  // 三字节UTF-8字符
            length += 2;
            str += 3;
        }
    }
    return length;
}


//然后，使用 print_with_padding 和 print_with_padding2 函数来打印内容和标题。
// 这两个函数会根据文本框的宽度和当前行的长度，计算出需要添加的空格数量，以确保文本在文本框中居中显示。
void print_with_padding(char* str, int padding) {
    int length = get_display_length(str);
    printf("* %s", str);
    for (int i = 0; i < padding - length + 3; i++) {  //可修改这个+3改变内容右侧*的缩进
        printf(" ");
    }
    printf("*\n");
}

void print_with_padding2(char* str, int padding) {
    int length = get_display_length(str);
    printf("* ");
    for (int i = 0; i < (padding - length) / 2 + 1; i++) {
        printf(" ");
    }
    printf("%s", str);
    for (int i = 0; i < (padding - length + 1) / 2 + 2; i++) {  //可修改这个+2改变标题右侧*的缩进
        printf(" ");
    }
    printf("*\n");
}

//在 print_box 函数中，首先计算标题的长度，然后遍历内容中的每一行，找出最长的一行。这样就可以得到文本框的宽度。
//最后，print_box 函数会打印出上边框、标题、分隔线、内容和下边框，从而形成一个完整的文本框。
// 这个文本框的宽度会自动适应标题和内容中最长的一行，实现了自适应的效果。
void print_box(char* title, char* content) {
    int max_line_length = get_display_length(title);
    char* content_copy = strdup(content);  // 创建内容的副本
    char* line = strtok(content_copy, "\n");

    // 计算最长行的长度
    while (line) {
        int line_length = get_display_length(line);
        if (line_length > max_line_length) {
            max_line_length = line_length;
        }
        line = strtok(NULL, "\n");
    }

    free(content_copy);  // 释放副本的内存
    content_copy = strdup(content);  // 创建一个新的副本
    line = strtok(content_copy, "\n");

    // 打印上边框
    for (int i = 0; i < max_line_length + 6; i++) {
        printf("*");
    }
    printf("\n");

    // 打印标题
    print_with_padding2(title, max_line_length);  // 使用print_with_padding函数打印标题

    // 打印分隔线
    for (int i = 0; i < max_line_length + 6; i++) {
        printf("=");
    }
    printf("\n");

    // 打印内容
    while (line) {
        print_with_padding(line, max_line_length);
        line = strtok(NULL, "\n");
    }

    // 打印下边框
    for (int i = 0; i < max_line_length + 6; i++) {
        printf("*");
    }
    printf("\n");

    free(content_copy);  // 释放副本的内存
}


int main(){
    printf("\n");
    sprintf(title, "功能演示.vol.1");
    strcat(content, "1.第一项功能\n");
    strcat(content, "2.第二项功能\n");
    strcat(content, "3.第三项功能\n");
    strcat(content, "4.第四项功能\n");
    strcat(content, "5.第五项功能\n");
    print_box(title, content);      //strcat函数的使用,将字符串连接到content中,代码排版整洁
    system("pause");

    printf("\n");
    sprintf(title, "功能演示.vol.2");
    sprintf(content, "1.第一项功能\n");
    sprintf(content, "%s2.第二项功能\n", content);
    sprintf(content, "%s3.第三项功能\n", content);
    sprintf(content, "%s4.第四项功能\n", content);
    sprintf(content, "%s5.第五项功能\n", content);
    sprintf(content, "%s6.第六项功能\n", content);
    sprintf(content, "%s7.第七项功能\n", content);
    sprintf(content, "%s当前系统时间: %s", content, __TIME__);
    print_box(title, content);      //sprintf函数的使用,将字符串连接到content中,可以在sprintf中使用变量
    system("pause");

    int i;
    printf("\n");
    sprintf(title, "Hello Everyone");
    sprintf(content, "你好,世界!         薇薇安         爱丽丝          奈奈子           艾莉           尤莉雅\n");//空四个空格，学号/性别空六个空格
    for (i = 0; i < 10; i++) {
        sprintf(content, "%s%-16s%-16s%-16s%-16s%-16s%s\n", content,"Hello World", "Hello Vivian","Hello Alice","Hello Nanako","Hello Ely","Hello Yuliya");
    }
    print_box(title, content);      //sprintf函数的使用,实现循环打印的功能
    system("pause");

    return 0;
}
