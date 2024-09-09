# 进程通信（IPC）

## 一、IPC概念

![IPC概念](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/IPC%E6%A6%82%E5%BF%B5.png)

## 二、常用方式及特征

在进程间完成数据传递需要借助操作系统提供特殊的方法，如：文件、管道、信号、共享内存、消息队列、套接字、命名管道等。随着计算机的蓬勃发展，一些方法由于自身缺陷被淘汰或弃用，现在常用的进程间通信方式有：

1. 管道（使用最简单）

2. 信号（开销最小）

3. 共享映射区（无血缘关系）

4. 本地套接字（最稳定）

# 管道

## 一、管道概念

管道是一种最基本的IPC机制，作用于有血缘关系的进程间，完成数据传递。调用**pipe系统函数**即可创建一个管道。

**特质：**

1. 其本质是一个**伪文件【实为内核缓冲区】**

2. 由**两个文件描述符引用**，一个表示读端，一个表示写端

3. 规定数据从管道的写端流入管道，从读端流出

**原理：**管道实为内核使用**环形队列**机制，借助**内核缓冲区（4k）实现**

**局限性：**

1. 数据**不能进程自己写，自己读**

2. 管道中数据**不可反复读取**，一旦读走，管道中不再存在

3. 采用**半双工通信方式**，数据只能在单方向上流动

4. 只能在有**公共祖先**的进程间使用管道

![管道原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AE%A1%E9%81%93%E5%8E%9F%E7%90%86.png)

## 二、pipe函数：创建，并打开管道。

	int pipe(int fd[2]);

	参数：	fd[0]: 读端。

		fd[1]: 写端。

	返回值： 成功： 0

		 失败： -1 errno

![管道创建](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AE%A1%E9%81%93%E5%88%9B%E5%BB%BA.png)

## 三、管道的读写行为：

	读管道：
		1. 管道有数据，read返回实际读到的字节数。

		2. 管道无数据：	1）无写端，read返回0 （类似读到文件尾）

				2）有写端，read阻塞等待。

	写管道：
		1. 无读端， 异常终止。 （SIGPIPE导致的）

		2. 有读端：	1） 管道已满， 阻塞等待

				2） 管道未满， 返回写出的字节个数。

### 示例：管道的读写
```C
int main(void)
{
    pid_t pid;
    char buf[1024];
    int fd[2];
    char *p = "test for pipe\n";
    
   if (pipe(fd) == -1) 
       sys_err("pipe");

   pid = fork();
   if (pid < 0) {
       sys_err("fork err");
   } else if (pid == 0) {
        close(fd[1]);//关闭写端
        int len = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);
   } else {
       close(fd[0]);//关闭读端
       write(fd[1], p, strlen(p));
       wait(NULL);
       close(fd[1]);
   }
    return 0;
}
```

## 四、wc命令

	常用于计算文件的行数、字数和字节数
	
	-l , --lines : 显示行数；

	-w , --words : 显示字数；

	-m , --chars : 显示字符数；

	-c , --bytes : 显示字节数；

	-L , --max-line-length : 显示最长行的长度；

### 示例：实现 ls | wc -l（父子通信、兄弟通信）

```C
//ls_wc_l.c
int main(void)
{
    int fd[2];
    pid_t  pid;
    int i;

    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error:");
        exit(1);
    }

    for (i = 0; i < 2; i++){
        pid = fork();
        if (pid == -1) {
            perror("pipe error:");  //ls | wc -l
            exit(1);
        }
        if (pid == 0)
            break;
    }

    if (i == 0) {  //兄  ls 
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    } else if (i == 1) { // 弟 wc -l 
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    } else if (i == 2) {  //父 
        close(fd[0]);
        close(fd[1]);
        for(i = 0; i < 2; i++)
            wait(NULL);
    }

    return 0;
}
```

## 五、管道缓冲区大小

### 1.`ulimit -a`命令
	
	查看当前系统中管道文件所对应的内核缓冲区大小
	
![ulimit_a命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ulimit_a%E5%91%BD%E4%BB%A4.png)

### 2.fpathconf()函数

	long fpathconf(int fd, int name);
	
	参数：
	
		fd：文件描述符，name：宏
	
	返回值：
	
		成功：返回管道大小；失败：-1，设置errno 

## 六、管道优劣

* 【优点】简单，相比信号，套接字实现进程间通信，简单很多

* 【缺点】

	1. 只能单向通信，双向通信需建立两个管道；
	
	2. 只能用于父子、兄弟进程（有共同祖先）间通信。

## 七、fifo管道【命名管道】

* 管道`pipe`只能用于**有血缘关系**的进程间，但通过**FIFO**，不相关的进程也能交换数据。

* `FIFO`是Linux基础文件类型中的一种，但FIFO文件在磁盘上没有数据块，仅仅用来标识内核中的一条通道；各进程可以打开这个文件进行`read/write`，实际上是在读写**内核通道**，这样就实现了进程间通信。

### 2.`mkfifo`命令及mkfifo函数
	
	命令：mkfifo 管道名
	
	库函数：int mkfifo(const char* pathname, mode_t mode);

#### 示例：实现无血缘关系进程间通信：

	读端，open fifo O_RDONLY
	写端，open fifo O_WRONLY

```C
//fifo_w.c
int main(int argc, char *argv[])
{
    int fd, i;
    char buf[4096];

    if (argc < 2) {
        printf("Enter like this: ./a.out fifoname\n");
        return -1;
    }
    fd = open(argv[1], O_WRONLY);       //打开管道文件
    if (fd < 0) 
        sys_err("open");

    i = 0;
    while (1) {
        sprintf(buf, "hello itcast %d\n", i++);

        write(fd, buf, strlen(buf));    // 向管道写数据
        sleep(1);
    }
    close(fd);

    return 0;
}
```

```C
//fifo_r.c
int main(int argc, char *argv[])
{
    int fd, len;
    char buf[4096];

    if (argc < 2) {
        printf("./a.out fifoname\n");
        return -1;
    }
    //int fd = mkfifo("testfifo", 644);
    //open(fd, ...);
    fd = open(argv[1], O_RDONLY);   // 打开管道文件
    if (fd < 0) 
        sys_err("open");
    while (1) {
        len = read(fd, buf, sizeof(buf));   // 从管道的读端获取数据
        write(STDOUT_FILENO, buf, len);
        sleep(3);           //多個读端时应增加睡眠秒数,放大效果.
    }
    close(fd);

    return 0;
}
```


# 共享内存映射:

## 一、文件实现进程间通信：（已过时）

	打开的文件是内核中的一块缓冲区。多个无血缘关系的进程，可以同时访问该文件。

## 二、存储映射概念

![存储映射](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AD%98%E5%82%A8%E6%98%A0%E5%B0%84.png)

## 三、mmap函数

	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);	//创建共享内存映射

	参数：
		addr： 	指定映射区的首地址。通常传NULL，表示让系统自动分配

		length：共享内存映射区的大小。（<= 文件的实际大小）

		prot：	共享内存映射区的读写属性。PROT_READ、PROT_WRITE、PROT_READ|PROT_WRITE

		flags：	标注共享内存的共享属性。MAP_SHARED（直接反应到物理磁盘）、MAP_PRIVATE（不反应到物理磁盘）

		fd:	用于创建共享内存映射区的那个文件的 文件描述符。

		offset：默认0，表示映射文件全部。偏移位置。需是 4k 的整数倍。

	返回值：

		成功：映射区的首地址。

		失败：MAP_FAILED (void*(-1))， errno

## 四、munmap函数

	int munmap(void *addr, size_t length);		释放映射区。

	addr：mmap 的返回值

	length：大小


### 使用注意事项：

![mmap注意事项](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/mmap%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9.png)

	1. 用于创建映射区的文件大小为 0，实际指定非0大小创建映射区，出 “总线错误”（7 SIGBUS）。

	2. 用于创建映射区的文件大小为 0，实际制定0大小创建映射区， 出 “无效参数”。

	3. 用于创建映射区的文件读写属性为，只读。映射区属性为 读、写。 出 “无效参数”。

	4. 创建映射区，需要read权限。当访问权限指定为 “共享”MAP_SHARED是， mmap的读写权限，应该 <=文件的open权限。	只写不行。

	5. 文件描述符fd，在mmap创建映射区完成即可关闭。后续访问文件，用 地址访问。

	6. offset 必须是 4096的整数倍。（MMU 映射的最小单位 4k ）

	7. 对申请的映射区内存，不能越界访问。 

	8. munmap用于释放的 地址，必须是mmap申请返回的地址。

	9. 映射区访问权限为 “私有”MAP_PRIVATE, 对内存所做的所有修改，只在内存有效，不会反应到物理磁盘上。

	10.映射区访问权限为 “私有”MAP_PRIVATE, 只需要open文件时，有读权限，用于创建映射区即可。


### mmap函数的保险调用方式：

	1. fd = open（"文件名"， O_RDWR）;

	2. mmap(NULL, 有效文件大小， PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);


### 示例1：父子进程使用 mmap 进程间通信：

	父进程 先 创建映射区。 open（O_RDWR） mmap(MAP_SHARED);

	指定 MAP_SHARED 权限

	fork() 创建子进程。

	一个进程读， 另外一个进程写。

```C
//fork_mmap.c
int var = 100;
int main(void)
{
    int *p;
    pid_t pid;

    int fd;
    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    ftruncate(fd, 4);

    //p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(p == MAP_FAILED){		//注意:不是p == NULL
        perror("mmap error");
        exit(1);
    }
    close(fd);					//映射区建立完毕,即可关闭文件

    pid = fork();				//创建子进程
    if(pid == 0){
       *p = 7000;               // 写共享内存
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    } else {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, var);     // 读共享内存
        wait(NULL);

        int ret = munmap(p, 4);				//释放映射区
        if (ret == -1) {
            perror("munmap error");
            exit(1);
        }
    }

    return 0;
}
```


### 示例2：无血缘关系进程间 mmap 通信：  				【会写】

	两个进程 打开同一个文件，创建映射区。

	指定flags 为 MAP_SHARED。

	一个进程写入，另外一个进程读出。

	【注意】：无血缘关系进程间通信。mmap：数据可以重复读取。

					fifo：数据只能一次读取。


```C
//mmap_r.c
struct STU {
    int id;
    char name[20];
    char sex;
};

int main(int argc, char *argv[])
{
    int fd;
    struct STU student;
    struct STU *mm;

    if (argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        sys_err("open error");
    mm = mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap error");
    close(fd);//注意：生成文件描述符后就可以关闭文件了
    while (1) {
        printf("id=%d\tname=%s\t%c\n", mm->id, mm->name, mm->sex);
        sleep(2);
    }
    munmap(mm, sizeof(student));

    return 0;
}
```
```C
//mmap_w.c
struct STU {
    int id;
    char name[20];
    char sex;
};
int main(int argc, char *argv[])
{
    int fd;
    struct STU student = {10, "xiaoming", 'm'};
    char *mm;

    if (argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    ftruncate(fd, sizeof(student));

    mm = mmap(NULL, sizeof(student), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap");
    close(fd);
    while (1) {
        memcpy(mm, &student, sizeof(student));
        student.id++;
        sleep(1);
    }
    munmap(mm, sizeof(student));

    return 0;
}

```

## 五、mmap匿名映射

**只能用于血缘关系进程间通信**
	
	p = (int *)mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
		
		len大小随意
	
* `/dev/zero`空白文件：会不断产生空字节，无限的空字节流

* `/dev/null`黑洞文件：不会满
	
### 示例1：使用MAP_ANONYMOUS和MAP_ANON宏

```C
int main(void)
{
	int *p;
	pid_t pid;
	
	p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);  //MAP_ANONYMOUS
	if(p == MAP_FAILED){		//注意:不是p == NULL
		perror("mmap error");
		exit(1);
	}

	pid = fork();				//创建子进程
	if(pid == 0){
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	munmap(p, 4);				//释放映射区

	return 0;
}
```

### 示例2：没有宏的情况

```C
int main(void)
{
	int *p;
	pid_t pid;
	
	int fd;
	fd = open("/dev/zero", O_RDWR);

	p = mmap(NULL, 400, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

	if(p == MAP_FAILED){		//注意:不是p == NULL
		perror("mmap error");
		exit(1);
	}

	pid = fork();				//创建子进程
	if(pid == 0){
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	munmap(p, 4);				//释放映射区

	return 0;
}
```


















	
	

	

	



	