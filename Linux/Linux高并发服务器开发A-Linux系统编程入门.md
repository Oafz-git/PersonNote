# Linux系统编程入门

## 一、Linux开发环境的搭建

### 01/工具

> 安装LINUX系统（虚拟机、云服务器）

1. 安装VMware Workstation（提取文件；`sudo`运行`.pl`文件）
2. 安装ssh服务端`sudo apt install openssh-server`
3. 安装`ifconfig`查询IP`sudo apt install net-tools`
4. `ens33`默认网卡名称
5. `oafz@oafz`第一个是用户名，第二个是主机名

> 安装XSHELL、XFTP（远程连接）
> 安装VScode

**配置远程信息：**

1. 主机名称`Host Ubuntu-18`
2. IP地址`HostName`
3. 用户名`User`

**配置免密登录：**

1. 在本机和LINUX下生成公钥、私钥`ssh-keygen -t rsa`,Linux的公钥和私钥默认生成到`~/.ssh`下
2. 发送公钥`ssh-copy-id`（暂时不能使用）
3. 在Linux上创建`authorized-keys`文件，将公钥拷入并保存

## 二、GCC介绍

### 01/什么是GCC

* GCC原名GNU C语言编译器（GNU C Compiler）
* GCC（GNU Compiler Collection，GNU编译器套件）是由GNU开发的编程语言译器。
  * 包括C/C++/Objective-C/Java/Ada/Go前端，也包括这些语言的库（如libstdc++、libgcj等）
* GCC不仅支持C的许多‘方言’，也可以区分不同的C语言标准；可以使用命令行选项来控制编译器在翻译源代码时应该遵循哪个C标准。例如，当使用命令行参数`-std=c99`启动GCC时，编译器支持C99标准
* 安装命令`sudo apt install gcc/g++`(版本>4.8.5,支持C++11)
* 查看版本`gcc/g++ -v/--version`

### 02/GCC工作流程

![GCC工作流程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/GCC工作流程.png)

### 03/gcc和g++的区别

* gcc和g++都是GNU（组织）的一个编译器
* **误区一：**gcc只能编译c代码，g++只能编译c++代码。两者都可以，注意：
  * 后缀为.c的，gcc把它当作是C程序，而g++当作是C++程序
  * 后缀为.cpp的，两者都会认为是C++程序，C++的语法规则更加严谨一些
  * 编译阶段，g++会调用gcc，对于C++代码，两者是等价的，但是因为gcc命令不能自动和C++程序使用的库链接，所以通常用g++来完成链接，为了统一，干脆编译/链接都用g++了，这就给人一种错觉，好像cpp程序只能用g++似的
* **误区二：**gcc不会定义`__cplusplus`宏，而g++会
  * 实际上，这个宏只是标志着编译器将会把代码按C还是C++语法来解释
  * 如上所述，如果后缀为.c，并采用gcc编译器，则该宏就是未定义的，否则，就是已定义的。
* **误区三：**编译只能为gcc，链接只能用g++
  * 严格来说，这句话不算错误，但它混淆了概念，应该这样说：编译可以用`gcc/g++`，而链接可以用`g++`或`gcc -lstdc++`
  * gcc命令不能自动和C++程序使用的库链接，所以通常使用g++来完成链接。但在编译阶段，g++会自动调用gcc，二者等价

### 04/GCC编译常用参数

|gcc编译选项|说明|
|:---:|:---:|
|-E|预处理指定的源文件，不进行编译|
|-S|编译指定的源文件，但是不进行汇编|
|-c|编译、汇编指定的源文件，但是不进行链接|
|-o|将文件编译成可执行文件|
|-I directory|指定include包含文件的搜索目录|
|-g|在编译的时候，生成调试信息，该程序可以被调试器调试|
|-D|在程序编译的时候，指定一个宏---相当于define，**用于进行调试**|
|-w|不生成任何警告信息|
|-wall|生成警告信息|
|-On|n的取值范围：0~3，编译器的优化选项的4个级别；-o0表示没有优化，-o1为缺省值，-o3优化级别最高**防止反汇编**|
|-l|在程序编译时，指定使用的库|
|-L|指定编译时，搜索库的路径|
|-fPIC/-fpic|生成与位置无关的代码|
|-shared|生成共享目标文件，通常用在建立共享库时|
|-std|指定C方言，如：-std=c99，gcc默认的方言是GNU C|

## 三、静态库和动态库

### 01/什么是库

![静态库和动态库链接的区别](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/静态库和动态库链接的区别.png)

* 库文件是计算机上的一类文件，可以简单的把库文件看成一种**代码仓库**，它提供给使用者一些可以拿来用的变量、函数或类
* 库是特殊的一种程序，编写库的程序和编写一般的程序区别不大，只是**库不能单独运行**。
* **静态库和动态库（共享库）的区别：**静态库在程序的链接阶段被复制到了程序中；动态库在*链接阶段*没有被复制到程序中，而是程序在运行时有系统*动态加载*到内存中供程序调用
* **库的好处：**1.代码保密；2.方便部署和分发

### 02/静态库的制作

![静态库的制作过程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/静态库制作过程.png)

* ***命名规则：***
  >***Linux***: libxxx.a  
  >>lib: 前缀（固定）  
  >>xxx: 库的名字，自己起  
  >>.a: 后缀（固定）  
  >
  >***Windows***: libxxx.lib

* ***静态库的制作：***
  1. gcc获得.o文件
  2. 将.o文件打包，使用`ar`工具`archive`

  `ar rcs libxxx.a xxx.o xxx.o`
    > r - 将文件插入备存文件中  
    > c - 建立备存文件  
    > s - 索引  
  
* ***静态库的使用***

```shell
gcc main.c -o app -I 头文件目录 -l 库的名称 -L 库的位置
```

* ***静态库的优点和缺点***
  > 优点：
  >> 静态库被打包到应用程序中加载速度快
  >> 发布程序无需提供静态库，移植方便
  >
  >缺点：
  >> 消耗系统资源，浪费内存
  >> 更新、部署、发布麻烦
  
![静态库的优缺点](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/静态库的优缺点.png)

### 03/动态库（共享库）的制作

* ***命名规则：***
  > ***Linux***: libxxx.so--在Linux下是个可执行文件
  >>lib: 前缀（固定）  
  >>xxx: 库的名字，自己起  
  >>.so: 后缀（固定）  
  >***Windows***: libxxx.dll

* ***动态库的制作：***

![动态库制作过程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/动态库制作过程.png)

  1. gcc得到.o文件，得到和位置无关的代码`gcc -c -fpic/-FPIC a.c b.c`
  2. gcc得到动态库`gcc -shared a.o b.o -o libcalc.so`

* ***动态库的使用：***

```shell
gcc main.c -o main -I include/ -L 动态库路径 -l calc
```

* ***动态库加载失败的原因：（工作原理）***
  * 静态库：GCC进行链接时，会把静态库中代码打包到可执行程序中
  * 动态库：GCC进行链接时，动态库的代码不会被打包到可执行程序中
  * 程序启动之后，动态库会被动态加载到内存中，通过`ldd 可执行程序`（list dynamic dependencies）命令检查动态库依赖关系
  * 如何定位共享文件呢？
    > 当系统加载可执行代码时，能够知道其所依赖的库的名字，但还需要知道绝对路径。此时就需要系统的**动态载入器**来获取该**绝对路径**。对于elf格式的可执行程序，是有ld-linux.so来完成的，它先后搜索elf文件的**DT_RPATH段**-->**环境变量LD_LIBRARY_PATH**-->**/etc/ld.so.cache文件列表**-->**/lib/,/usr/lib**目录找到库文件后将其载入内存

* ***解决动态库加载失败的问题***

> **方法一：配置环境变量LD_LIBRARY_PATH：**

* `env`查看所有环境变量
* `echo $LD_LIBRARY_PATH`查看某一个环境变量
* `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:路径`设置环境变量（临时）
  * `$`获取环境变量；`:`分割环境变量
* `vim ~/.bashrc`设置环境变量（用户级）
  * `. .bashrc`或`source .bashrc`使环境变量生效
* `sudo vim /etc/profile`设置环境变量（系统级）
  * `. /etc/profile`或`source /etc/profile`使环境变量生效

> **方法二：修改`/etc/ld.so.cache`文件列表**

使用`vim /etc/ld.so.conf`添加路径，然后使用`sudo ldconfig`生效

> **方法三：将动态库文件放到`/lib/`或`/usr/lib`目录下**

* ***动态库的优缺点***

> 优点：
>> 可以实现进程间资源共享（共享库）
>> 更新、部署、发布简单
>> 可以控制何时加载动态库
>
> 缺点：
>> 加载速度比动态库慢
>> 发布程序时需要提供依赖的动态库

![动态库的优缺点](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/动态库的优缺点.png)

## 四、Makefile

### 01/什么是Makefile

* 一个工程中的源文件不计其数，其按类型、功能、模块分别放在若干个目录中，Makefile文件定义了一系列的规则来指定哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至更复杂的功能操作，就像shell脚本一样，也可以执行操作系统的命令。  
* Makefile好处是“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，提高开发效率。  make是一个解释Makefile文件中指令的命令工具。`sudo apt install make`

### 02/命名

`makefile / Makefile`

### 03/一个规则

> 目标:依赖
>（一个tab缩进）Shell命令
> 如：add.o:add.c
> (一个tab缩进) gcc -Wall -g -c add.c -o add.o
>>目标：最终要生成的目标文件（伪目标除外）
>>依赖：目标文件由哪些文件生成
>>命令：通过执行该命令由依赖文件生成目标
>
>ALL:a.out #ALL-->指定终极目标
>>Makefile中的其它规则一般都是为第一条规则服务的（如果第一条规则没有包含某个子规则，那么子规则不会执行）

```Makefile
app:sub.c add.c mult.c div.c main.c
  gcc sub.c add.c mult.c div.c main.c -o app
```

### 04/工作原理

* 命令在执行之前，检查规则中的依赖条件是否存在
  * 如存在，执行命令
  * 如不存在，向下检查其它规则，检查有没有一个规则是用来生成这个依赖的，如果找到了，则执行改规则中命令
* 检查更新，在执行规则中的命令时，会比较目标和依赖文件的时间
  * 如果依赖的时间比目标的时间晚，需要重新生成目标
  * 如果依赖的时间比目标的时间早，目标不需要更新，对应规则中的命令不需要被执行

```Makefile
#比第一种效率高：不会将每个文件都重新编译，只会重新链接
app:sub.o add.o mult.o div.o main.o
  gcc sub.o add.o mult.o div.o main.o -o app

sub.o:sub.c
  gcc -c sub.c -o sub.o

add.o:add.c
  gcc -c add.c -o add.o

mult.o:mult.c
  gcc -c mult.c -o mult.o

div.o:div.c
  gcc -c div.c -o div.o

main.o:main.c#会比较main.o和main.c的更新时间
  gcc -c main.c -o main.o
```

### 05/变量

* 自定义变量  
  * 变量名 = 变量值   `var = hello`
* 预定义变量
  * `AR` - 归档维护程序的名称，默认值为`ar`
  * `CC` - C编译器的名称，默认值为`cc`
  * `CXX` - C++编译器的名称，默认值为`g++`
* 自动变量（智能类规则的命令中使用）
  * `$@` - 目标的完整名称
  * `$<` - 第一个依赖文件的名称
  * `$^` - 所有的依赖文件，如果将该变量应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则。
* 获取变量的值
  * `$(变量名)`

### 06/模式匹配

`%.o:%.c`

* %: 通配符，匹配一个字符串
* 两个%匹配同一个字符串

```Makefile
src = sub.o add.o mult.o div.o main.o
target = app
$(target):$(src)
  $(CC) $(src) -o $(target)

%.o:%.c#这是通过第一条规则向这里查找的
  $(CC) -c $< -o $@
```

### 07/函数

`$(wildcard PATTERN...)`

* 功能：获取指定目录下指定类型的文件列表
* 参数：PATTERN指的是某个或多个目录下的对应的某种类型的文件，如果有多个目录，一般使用空格间隔
* 返回：得到的若干个文件的文件列表，文件名之间使用空格间隔
  * `$(wildcard *.c ./sub/*.c)`
  * 返回格式 `a.c b.c c.c d.c`

`$(patsubst <pattern>,<replacement>,<text>)`

* 功能：查找`<text>`中的单词（单词以“空格”、“Tab”或“回车”、“换行”分隔）是否符合模式`<pattern>`，如果匹配的话，则以`<replacement>`替换。
* 参数：`<pattern>`可以包括通配符`%`，表示任意长度的子串。如果`<replacement>`中也包含`%`，那么，`<replacement>`中的这个`%`将是`<pattern>`中的那个`%`所代表的子串。（可以用`\`来转义，以`\%`来表示真实含义的`%`字符）
* 返回：函数返回被替换过后的字符串
  * `$(patsubst %.c, %.o, x.c bar.c)`
  * 返回值格式：`x.o bar.o`

```Makefile
src=$(wildcard ./*.c)#add.c sub.c main.c mult.c div.c
obj=$(patsubst %.c, %.o, $(src))
target = app
$(target):$(obj)
  $(CC) $(obj) -o $(target)

%.o:%.c
  $(CC) -c $< -o $@

.PHONY:clean#伪目标：使clean不会当前目录的clean文件比较
clean:
  rm $(obj) -f#删除生成的.o文件（make clean）
```

## 五、GDB调试

### 01/什么是GDB

* GDB是由GNU软件系统社区提供的调试工具，同GCC配套组成了一套完整的开发环境，GDB是Linux和许多类UNIX系统中的标准开发环境
* 一般来说，GDB主要帮助你完成四个方面的功能
  1. 启动程序，可以按照自定义的要求随心所欲的运行程序
  2. 可让被调试的程序在所指定的调置的断点处停住（断点可以是条件表达式）
  3. 当程序被停住时，可以检查此时程序中所发生的事
  4. 可以改变程序，将一个BUG产生的影响修正从而测试其他BUG

### 02/准备工作

`gcc -g -Wall program.c -o program`

* `-o`在为调试而编译时，我们会关掉编译器的优化选项`-o`
* `-Wall`在尽量不影响程序行为的情况下选项打开所有warning，也可以发现许多问题，避免一些不必要的BUG
* `-g`调试选项，在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证gdb能找到源文件

### 03/GDB-启动、退出、查看代码

* 启动和退出
  * `gdb 可执行程序`
  * `quit`
* 给程序设置参数/获取设置参数
  * `set args 10 20`
  * `show args`
* GDB使用帮助
  * `help`
* 查看当前文件代码
  * `list/l` （从默认位置显示）
  * `list/l 行号` （从指定的行显示）
  * `list/l 函数名` （从指定的函数显示）
* 查看非当前文件代码
  * `list/l 文件名:行号`
  * `list/l 文件名:函数名`
* 设置显示的行数
  * `show list/listsize`
  * `set list/listsize 行数`

### 04/GDB命令-断点操作

* 设置断点
  * `b/break 行号`
  * `b/break 函数名`
  * `b/break 文件名:行号`
  * `b/break 文件名:函数`
* 查看断点
  * `i/info b/break`
* 删除断点
  * `d/del/delete 断点编号`
* 设置断点无效
  * `dis/disable 断点编号`
* 设置断点生效
  * `ena/enable 断点编号`
* 设置条件断点（一般用在循环的位置）
  * `b/break 10 if i ==5`

### 05/GDB命名-调试命令

* 运行GDB程序
  * `start`（程序停在第一行）
  * `run`（遇到断点才停）
* 继续运行，到下一个断点停
  * `c/continue`
* 向下执行一行代码（不会进入函数体）
  * `n/next`
* 变量操作
  * `p/print 变量名`（打印变量值）
  * `ptype 变量名`（打印变量类型）
* 向下单步调试（遇到函数进入函数体）
  * `s/step`
  * `finish`（跳出函数体）
* 自动变量操作
  * `display num`（自动打印指定变量的值）
  * `i/info display`
  * `undisplay 编号`
* 其它操作
  * `set var 变量名 = 变量值`
  * `until`（跳出循环）
 