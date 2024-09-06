# 系统调用

C标准函数和系统调用的关系：
![系统调用](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8.png)

# 文件IO

* **open函数/close函数**
* 错误处理函数errno
* **read函数/write函数（阻塞和非阻塞）**
* strace命令
* **fcntl函数**
* **lseek函数**
* **truncate函数**

## 一、open函数/close函数

	int open(char *pathname, int flags)			#include <unistd.h>

	参数：
		pathname: 欲打开的文件路径名

		flags：文件打开方式：									#include <fcntl.h>

			O_RDONLY|O_WRONLY|O_RDWR	O_CREAT|O_APPEND|O_TRUNC（截断）|O_EXCL（判断是否存在）|O_NONBLOCK（被阻塞） ....

	返回值：
		成功： 打开文件所得到对应的 文件描述符（整数）

		失败： -1， 设置errno	



	int open(char *pathname, int flags， mode_t mode)		123  775	

	参数：
		pathname: 欲打开的文件路径名

		flags：文件打开方式：	O_RDONLY|O_WRONLY|O_RDWR	O_CREAT|O_APPEND|O_TRUNC|O_EXCL|O_NONBLOCK ....

		mode: 参数3使用的前提， 参2指定了 O_CREAT（即创建文件时使用）。	取值8进制数，用来描述文件的 访问权限。 rwx    0664

			创建文件最终权限 = mode & ~umask

	返回值：
		成功： 打开文件所得到对应的 文件描述符（整数）

		失败： -1， 设置errno	
		
	常见错误：
		1.打开文件不存在
		2.以写方式打开只读文件（打开文件没有对应权限）
		3.以只写方式打开目录

	int close(int fd);


## 二、错误处理函数errno：

	errno表示操作系统的全局变量，可直接使用   #include<errno.h>
	
	char *strerror(int errnum); //翻译errno #include<string.h>
		printf("xxx error: %s\n", strerror(errno));
		
	void perror(const char *s); //相当strerror(errno)和printf的结合 #include<stdio.h>
	exit(1); #include<stdlib.h>

## 三、read函数/write函数

	ssize_t read(int fd, void *buf, size_t count);

	参数：
		fd：文件描述符

		buf：存数据的缓冲区

		count：缓冲区大小

	返回值：

		= 0：读到文件末尾；socket中，表示对端关闭。close（）

		> 0 读到的字节数。

		-1 设置 errno
			
			如果 errno == EINTR   被异常终端。 需要重启。慢速系统调用被中断。

			如果 errno == EAGIN 或 EWOULDBLOCK 说明不是read失败，而是read在以非阻塞方式读一个设备文件（网络文件），并且文件无数据。

			如果 errno == ECONNRESET  说明连接被 重置。 需要 close（），移除监听队列。

	ssize_t write(int fd, const void *buf, size_t count);

	参数：
		fd：文件描述符

		buf：待写出数据的缓冲区

		count：数据大小

	返回值：

		成功；	写入的字节数。

		失败：	-1， 设置 errno

* strace命令：跟踪函数调用
	
* 缓冲区：read、write函数常常被称为Unbuffered I/O，指的是无用户级缓冲区，但不保证不使用内核缓冲区
	
* 预读入缓输出机制（系统调用和库函数比较）
![预读入缓输出](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%A2%84%E8%AF%BB%E5%85%A5%E7%BC%93%E8%BE%93%E5%87%BA%E6%9C%BA%E5%88%B6.png)

### 示例：模仿cp命令

```C
// myCp.c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
        char buf[1024];
        int n = 0;
        int fd1 = open(argv[1], O_RDONLY);
        if(fd1 == -1)
        {
                perror("open argv1 error");
                exit(1);
        }
        int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC ,0777);
        if(fd2 == -1)
        {
                perror("open argv2 error");
                exit(1);
        }


        while(n = read(fd1, buf, 1024) != 0)
        {
                if(n == -1)
                {
                        perror("read error");
                        break;
                }

                write(fd2, buf, n);
        }

        close(fd1);
        close(fd2);
        return 0;
}
```
		

## 四、文件描述符：

![文件描述符](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E6%8F%8F%E8%BF%B0%E7%AC%A6.png)

	PCB进程控制块：本质 结构体。

	成员：文件描述符表。

	文件描述符：0/1/2/3/4。。。。/1023     最多打开1024个文件，表中可用的最小的。

	0 - STDIN_FILENO

	1 - STDOUT_FILENO

	2 - STDERR_FILENO

## 五、阻塞、非阻塞（设备文件、网络文件的属性）
	
	产生阻塞的场景。 读设备文件。读网络文件。（读常规文件无阻塞概念。）

	/dev/tty -- 终端文件。

### 示例：非阻塞方式读取终端文件

说明：循环定时10s，每2秒进行非阻塞读取并输出“try again”，10s内终端未输入数据为超时，输出“time out”

```C
//nonblock_timeout.c
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MSG_TRY "try again\n"
#define MSG_TIMEOUT "time out\n"

int main(void)
{
    char buf[10];
    int fd, n, i;

    fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);//以非阻塞方式打开终端文件，默认为阻塞方式
    if(fd < 0){
        perror("open /dev/tty");
        exit(1);
    }
    printf("open /dev/tty ok... %d\n", fd);

    for (i = 0; i < 5; i++){						//设置超时
        n = read(fd, buf, 10);
        if (n > 0) {                    //说明读到了东西
            break;
        }
        if (errno != EAGAIN) {          //EWOULDBLOCK，当以非阻塞方式读一个设备文件（网络文件），并且文件无数据时
            perror("read /dev/tty");
            exit(1);
        } else {
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            sleep(2);
        }
    }

    if (i == 5) {
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    } else {
        write(STDOUT_FILENO, buf, n);
    }

    close(fd);

    return 0;
}
```

## 六、fcntl函数：改变一个[已经打开]的文件的访问属性

	int fcntl(int fd, int cmd, ...); //改变一个[已经打开]的文件的访问属性；

	应用：
		int flgs = fcntl(fd,  F_GETFL);//获取文件属性

		flgs |= O_NONBLOCK//添加属性

		fcntl(fd,  F_SETFL, flgs);//设置属性

	获取文件状态： F_GETFL

	设置文件状态： F_SETFL
	
![位图](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BD%8D%E5%9B%BE.png)

### 示例：为stdin添加属性信息

说明：通过fcntl添加O_NONBLOCK属性

```C
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(void)
{
	char buf[10];
	int flags, n;

	flags = fcntl(STDIN_FILENO, F_GETFL); //获取stdin属性信息
	if(flags == -1){
		perror("fcntl error");
		exit(1);
	}
	flags |= O_NONBLOCK;
	int ret = fcntl(STDIN_FILENO, F_SETFL, flags);//为stdin添加属性信息
	if(ret == -1){
		perror("fcntl error");
		exit(1);
	}

tryagain:
	n = read(STDIN_FILENO, buf, 10);
	if(n < 0){
		if(errno != EAGAIN){		
			perror("read /dev/tty");
			exit(1);
		}
		sleep(3);
		write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
		goto tryagain;
	}
	write(STDOUT_FILENO, buf, n);

	return 0;
}
```

## 七、lseek函数：修改文件偏移量（读写位置）

	off_t lseek(int fd, off_t offset, int whence);//修改文件偏移量（读写位置）

	参数：
		fd：文件描述符

		offset： 偏移量

		whence：起始偏移位置： SEEK_SET/SEEK_CUR/SEEK_END

	返回值：

		成功：较起始位置偏移量（文件头的位置）

		失败：-1 errno

### 示例：

#### 1. 文件的“读”、“写”使用同一偏移位置。

```C
int main(int argc, char* argv[])
{
        char msg[] = "It's a for lseek.txt";
        int fd, n;
        char buf;
        fd = open("lseek.txt", O_RDWR|O_CREAT|O_TRUNC, 0664);
        if(fd < 0)
        {
                perror("open error");
                exit(1);
        }
        n = write(fd,msg,strlen(msg));

        lseek(fd, 0, SEEK_SET);//重置光标到文件开始位置
        while(n = read(fd, &buf, 1))
        {
                if(n == -1)
                {
                        perror("read error");
                        exit(1);
                }
                write(STDOUT_FILENO, &buf, n);
        }

        close(fd);
        return 0;
}
```

#### 2. 使用lseek获取文件大小：返回值即大小

```C
int main(void)
{
	int fd;

	fd = open("lseek.txt", O_RDONLY | O_CREAT, 0664);
	if(fd < 0){
		perror("open lseek.txt error");
		exit(1);
	}

	int len = lseek(fd, 0, SEEK_END);
	if(len == -1){
		perror("lseek error");
		exit(1);
	}
	printf("len of msg = %d\n", len);//返回文件大小

	off_t cur = lseek(fd, -10, SEEK_SET);//无效参数
	printf("--------| %ld\n", cur);
	if(cur == -1){
		perror("lseek error");
		exit(1);
	}
}
```

#### 3. 使用lseek拓展文件大小：要想使文件大小真正拓展，必须引起IO操作，没有添加字符的会有“文件空洞”

```C
len = lseek(fd, 999, SEEK_SET);//拓展文件大小
if(len == -1){
	perror("lseek seek_set error");
	exit(1);
}
  int ret = write(fd, "a", 1);
if(ret == -1){
	perror("write error");
	exit(1);
}
```

#### 4.使用 truncate 函数，直接拓展文件。	int ret = truncate("dict.cp", 250);

```C
int ret = truncate("lseek.txt", 1500);//拓展文件大小
//int ret = ftruncate(fd, 1000);
if(ret == -1){
	perror("ftrun error");
	exit(1);
}
printf("len of file = %d\n", ret);

close(fd);
return 0;
}
```

## 八、od命令

	od -tcx filename //查看文件的16进制表示形式
	od -tcd filename //查看文件的10进制表示形式

![od命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/od.png)

## 九、传入传出参数

	传入参数：

		1. 指针作为函数参数。

		2. 同常有const关键字修饰。

		3. 指针指向有效区域， 在函数内部做读操作。

	传出参数：

		1. 指针作为函数参数。

		2. 在函数调用之前，指针指向的空间可以无意义，但必须有效。

		3. 在函数内部，做写操作。

		4。函数调用结束后，充当函数返回值。

	传入传出参数：

		1. 指针作为函数参数。

		2. 在函数调用之前，指针指向的空间有实际意义。

		3. 在函数内部，先做读操作，后做写操作。

		4. 函数调用结束后，充当函数返回值。





	




























