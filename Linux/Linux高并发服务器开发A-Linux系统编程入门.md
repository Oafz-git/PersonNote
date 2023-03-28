# Linux系统编程入门

## 一、Linux开发环境的搭建

ssh生成本机公钥和私钥`ssh-keygen -t rsa`

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
![GCC常用参数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/GCC常用参数选项.png)

### 03/GCC编译常用参数

## 三、静态库
