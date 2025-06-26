#include <stdio.h>

/* " "中的内容是相对文件路径 */
// #include "aur_util.h"
/*
TODO: 添加那个%d之类的支持,或者识别类型并且自动编排
    添加变量显示支持,获取变量名称同时直接以"val : 3"的形式输出
 */
void println(char *str)
{
    printf("%s\n", str);
}
