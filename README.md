# strenc
C++源码级字符串混淆库/工具

## 使用方法
1. 在独立文件中声明需要混淆的字符串常量，如：
```txt
STR_NAME
my name is jeff
STR_PASSWORD
my password is 123456
```

将上述内容保存到`sample.strenc`文件中。

2. 使用strenctool工具生成`sample.h`文件：
```sh
strenctool sample.strenc
```

3. 引用字符串
```c++
#include "sample.h"

printf("%s", STR_NAME);     // my name is jeff
printf("%s", STR_PASSWORD); // my password is 123456
```