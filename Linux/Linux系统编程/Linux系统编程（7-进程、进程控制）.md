# 进程相关概念
	程序：死的。只占用磁盘空间。		——剧本。

	进程：活的。运行起来的程序。占用内存、cpu等系统资源。	——戏。
	
### 一、虚拟内存映射MMU（虚拟内存和物理内存映射）

![CPU和MMU](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/CPU%E5%92%8CMMU.png)
![MMU](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/MMU.png)

### 二、PCB进程控制块：

在`/usr/src/linux-headers-3.16.0-30/include/linux/sched.h`中查看`struct task_struct`结构体定义。主要掌握如下：

* **进程id**：查看进程id`ps aux`

* **文件描述符表**：包含很多指向file结构体的指针

* **进程状态**：初始态、就绪态、运行态、挂起态、终止态。

* **当前进程工作目录位置**

* **umask掩码** （这个是进程的概念）

* 信号相关信息资源。

* 用户id和组id

* 会话和进程组

* 进程可以使用的资源上限

* 进程切换时需要保存和恢复的一些CPU寄存器

* 描述虚拟地址空间的信息

* 描述控制终端的信息

### 三、环境变量

* `LD_LIBRARY_PATH`：给动态链接库使用
* `PATH`：记录可执行文件位置
* `SHELL`：解析命令，值通常是`/bin/bash`
* `TERM`：当前终端类型
* `LANG`：语言
* `HOME`：家目录
* `env`：查看所有环境变量

# 进程控制

## 一、fork函数（创建子进程）

	pid_t fork(void)
	
	fork之后父进程先执行还是子进程先执行不确定，取决于内核所使用的调度算法。

	返回值：
	
		创建子进程。父子进程各自返回。父进程返回子进程pid。 子进程返回 0.
![fork函数原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/fork%E5%87%BD%E6%95%B0%E5%8E%9F%E7%90%86.png)

### 示例：循环创建n个子进程

```C
//loop_fork.c
int main(int argc, char* argv[])
{
        int i;
        pid_t pid;
        for(i=0; i<5; i++)	//出口1,父进程专用出口，循环期间，子进程不fork
        {
                if(fork() == 0) break;//出口2,子进程出口,i不自增
        }
        if(5 == i)	//父进程，从表达式2跳出
        {
                sleep(5);
                printf("I'm parent\n");
        }else	//子进程，从break跳出
        {
                sleep(i);
                printf("I'm %dth child\n",i+1);
        }
        return 0;
}
```

## 二、获取进程中相关id函数

1. getpid函数：获取当前进程ID`pid_t getpid();`

2. getppid函数：获取当前进程的父进程ID`pid_t getppid();`

3. getuid函数：

	* 获取当前进程实际用户ID`uid_t getuid();`
	
	* 获取当前进程有效用户ID`uid_t geteuid();`

4. getgid函数：
	
	* 获取当前进程使用用户组ID`gid_t getgid();`
	
	* 获取当前进程有效用户组ID`gid_t getegid();`

【注】区分一个函数是“系统函数”还是“库函数”：

*  是否访问内核数据结构
	
* 是否访问外部硬件资源 

## 三、进程共享（父子进程差异）

在刚使用`fork`创建子进程时，父子进程之间有哪些异同之处呢？

|父子相同处|父子不同处|
|----|----|
|**全局变量**、.data、.text、栈、堆、环境变量、用户ID、宿主目录、进程工作目录、信号处理方式|1.进程ID、2.fork返回值、3.父进程ID、4.进程运行时间、5.闹钟（定时器）、6.未决信号集|

【似乎】子进程复制了父进程0-3G用户空间内容，以及父进程的PCB，但pid不同。

【问题】真的每fork一个子进程都要将父进程的0-3G地址空间完全拷贝一份，然后再映射至物理内存吗？

【答】当然不是！父子进程间遵循**读时共享写时复制**的原则；这样的设计，无论子进程执行父进程的逻辑还是执行自己的逻辑都能节省内存开销。

【重点】父子进程共享：

1. **文件描述符** 

2. **mmap建立的映射区**

#### 示例1：编写程序测试，父子进程是否共享全局变量（父子进程不共享全局变量）

```C
int main(int argc, char* argv[])
{
        int var = 100;
        pid_t pid;
        pid = fork();
        if(pid == -1)
        {
                perror("fork error");
                exit(1);
        }

        if(pid == 0)
        {
                printf("child: &var:%x, var=%d\n", &var, var);
                //var = 200;
                printf("child: &var:%x, var=%d\n", &var, var);
        }
        else if(pid > 0)
        {
                printf("parent: &var:%x, var=%d\n", &var, var);
                var = 300;
                printf("parent: &var:%x, var=%d\n", &var, var);
        }

        return 0;
}
```

## 四、父子进程gdb调试

使用gdb调试的时候，gdb只能跟踪一个进程。可以在fork函数调用之前，通过指令设置gdb调试工具跟踪父进程或跟踪子进程。默认跟踪父进程。

`set follow-fork-mode child`命令设置gdb在fork之后跟踪子进程。

`set follow-fork-mode parent`设置跟踪父进程

**注：一定要在fork函数调用之前设置才有效。**

## 五、exec函数族

* fork创建子进程后执行的是和父进程相同的程序（但可能执行不同的代码分支），子进程往往要调用一种exec函数以执行另一个程序。

* 当调用一个exec函数时，该进程的**用户空间代码**和**数据**完全被新程序替换，从新程序的启动例程开始执行。

* 调用exec**并不创建新进程**，所以调用exec前后该进程的id并未改变。

* 将当前进程的`.text/.data`替换为所要加载的程序的`.text/.data`，然后让进程从新的.text第一条指令开始执行，但进程ID不变，**换核不换壳**

![exec函数族原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E5%8E%9F%E7%90%86.png)

* 六种exec函数

	   int execl(const char *path, const char *arg, ...);
	   int execlp(const char *file, const char *arg, ...);
	   int execle(const char *path, const char *arg,..., char * const envp[]);
	   int execv(const char *path, char *const argv[]);
	   int execvp(const char *file, char *const argv[]);
	   int execvpe(const char *file, char *const argv[],char *const envp[]);

* 【特性】exec函数一旦调用成功即执行新的程序，**不返回**；**只有在失败才会返回，错误值-1**；所以通常我们直接在exec函数调用后直接调用perror()和exit()，无需if判断。

	* `l(list)`：命令行参数列表
	
	* `p(path)`：搜索file时使用path变量
	
	* `v(vector)`：使用命令行参数数组
	
	* `e(environment)`：使用命令行参数数组，不使用进程原有的环境变量，设置新加载程序运行的环境变量
	
事实上，只有`execve`是真正的系统调用，其它五个函数最终都调用`execve`，所以`execve`在man手册第2节，其它函数在man函数第3节。这些函数之间的关系如下

![exec函数特性](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E7%89%B9%E6%80%A7%EF%BC%882%EF%BC%89.png)

### 示例1:execlp/execl函数的使用

```C
//fork_exec()
int main(int argc, char* argv[])
{
        pid_t pid = fork();             //创建子进程
        if(pid == -1)
        {
                perror("fork error");
        } else if(pid == 0) //子进程
        {
                execlp("ls", "ls", "-l", "-d", NULL);//NULL为哨兵，表示结尾
                //execl("./a.out","./a.out", NULL);
                //execl("/bin/ls", "ls", "-l", NULL);
                
              	//char *argv[] = {"ls", "-l", "-h", NULL};
              	//execvp("ls", argv);
                
                perror("execlp error");//只有execlp执行出错时才会执行，否则不执行
                exit(1);
        } else if(pid > 0)//父进程
        {       
                printf("I'm parent: %d\n", getpid());
        }
        
        return 0;
}
```

### 示例2：将当前系统中的进程信息，打印到文件中

```C
//exec_ps.c 
int main(int argc, char* argv[])
{
        int fd;
        fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC, 0644);
        if(fd < 0)
        {
                perror("open ps.out error");
                exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        close(fd);
        return 0;
}
```

## 六、回收子进程

`ps ajx`查看父子进程

### 1.孤儿进程：

父进程先于子进终止，子进程沦为**孤儿进程**，会被**init进程**领养。

### 2.僵尸进程：

子进程终止，父进程尚未对子进程进行回收，在此期间，子进程残留资源（PCB）存放于内核中，变为**僵尸进程**；  kill 对其无效。

### 3.wait函数：

	pid_t wait(int *status)

	参数：（传出） 回收进程的状态。

	返回值：成功： 回收进程的pid

		失败： -1， errno
		
	父进程调用wait函数可以回收子进程退出资源， 阻塞回收任意一个。

		函数作用1：	阻塞等待子进程退出

		函数作用2：	清理子进程残留在内核的 pcb 资源

		函数作用3：	通过传出参数，得到子进程结束状态

	获取子进程正常终止值（状态）：

		WIFEXITED(status) --》 为真，说明正常终止 --》调用 WEXITSTATUS(status) --》 得到 子进程 退出值。

	获取导致子进程异常终止信号（状态）：

		WIFSIGNALED(status) --》 为真，说明异常终止 --》调用 WTERMSIG(status) --》 得到 导致子进程异常终止的信号编号。

#### 示例：使用wait回收子进程

```C
int main(void)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if(pid == -1){
		perror("fork error");
		exit(1);
	} else if(pid == 0){		//son
		printf("I'm process child, pid = %d\n", getpid());
#if 1
		execl("./abnor", "abnor", NULL);
		perror("execl error");
		exit(1);
#endif
		sleep(1);				
		exit(10);
	} else {
		//wpid = wait(NULL);	//传出参数
		wpid = wait(&status);	//传出参数

		if(WIFEXITED(status)){	//正常退出
			printf("I'm parent, The child process "
					"%d exit normally\n", wpid);
			printf("return value:%d\n", WEXITSTATUS(status));

		} else if (WIFSIGNALED(status)) {	//异常退出
			printf("The child process exit abnormally, "
					"killed by signal %d\n", WTERMSIG(status));
										//获取信号编号
		} else {
			printf("other...\n");
		}
	}

	return 0;
}
```

### 4.waitpid函数：	指定某一个进程进行回收。可以设置非阻塞。			

	pid_t waitpid(pid_t pid, int *status, int options)
	
	waitpid(-1, &status, 0) == wait(&status);

	参数：
		pid：指定回收某一个子进程pid

			> 0: 回收指定pid的子进程

			-1：回收任意子进程（相当于wait）

			0：回收和当前调用waitpid一个组的任意子进程
			
			<-1(进程组号取反-1003)：回收指定进程组内的任意子进程

		status：（传出） 回收进程的状态。

		options：WNOHANG 指定回收方式为，设置为非阻塞状态。设置为0 默认为阻塞回收

	返回值：

		> 0 : 表成功回收的子进程 pid

		0 : 函数调用时， 如果参3指定了WNOHANG， 并且，没有子进程结束时，返回0。

		-1: 失败。errno

	总结：

		wait、waitpid	一次调用，回收一个子进程。

		想回收多个。while 

#### 示例1：非阻塞回收

```C
int main(void)
{
	pid_t pid, pid2, wpid;
	int flg = 0;

	pid = fork();
	pid2 = fork();

	if(pid == -1){
		perror("fork error");
		exit(1);
	} else if(pid == 0){		//son
		printf("I'm process child, pid = %d\n", getpid());
		sleep(5);				
		exit(4);
	} else {					//parent
		do {
			wpid = waitpid(pid, NULL, WNOHANG);//非阻塞回收
            		//wpid = wait(NULL);
			printf("---wpid = %d--------%d\n", wpid, flg++);
			if(wpid == 0){
				printf("NO child exited\n");
				sleep(1);		
			}
		} while (wpid == 0);		//子进程不可回收

		if(wpid == pid){		//回收了指定子进程
			printf("I'm parent, I catched child process,"
					"pid = %d\n", wpid);
		} else {
			printf("other...\n");
		}
	}
	return 0;
}
```

#### 示例2：使用waitpid回收多个子进程

```C
int main(int argc, char *argv[])
{
	int n = 5, i;				
	pid_t p, q;

	if(argc == 2){	
		n = atoi(argv[1]);
	}
    	q = getpid();

	for(i = 0; i < n; i++)	 {
        p = fork();
		if(p == 0) {
			break;			
        } 
    }

	if(n == i){  // parent
		sleep(n);
		printf("I am parent, pid = %d\n", getpid());
        for (i = 0; i < n; i++) {
            p = waitpid(0, NULL, WNOHANG);
            printf("wait  pid = %d\n", p);
        }
	} else {
		sleep(i);
		printf("I'm %dth child, pid = %d\n", 
				i+1, getpid());
	}
	return 0;
}
```

#### 作业：父进程fork3个子进程，三个子进程一个调用ps命令，一个调用自定义程序1（正常），一个调用自定义程序2（段错误）。父进程使用waitpid对其子进程进行回收。
