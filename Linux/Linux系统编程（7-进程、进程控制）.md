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

# 进程控制

## 一、fork函数（创建子进程）/getpid函数、getppid函数（获取进程ID）

	pid_t fork(void)
	
	fork之后父进程先执行还是子进程先执行不确定，取决于内核所使用的调度算法。

	返回值：创建子进程。父子进程各自返回。父进程返回子进程pid。 子进程返回 0.
	
	getpid();getppid();（获取进程ID）

![fork函数原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/fork%E5%87%BD%E6%95%B0%E5%8E%9F%E7%90%86.png)
	
### 示例：循环创建n个子进程

```C
//loop_fork.c
int main(int argc, char* argv[])
{
        int i;
        pid_t pid;
        for(i=0; i<5; i++)	//循环期间，子进程不fork
        {
                if(fork() == 0) break;
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

## 二、进程共享（父子进程差异）

![进程共享](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E5%85%B1%E4%BA%AB.png)

## 三、父子进程gdb调试

使用gdb调试的时候，gdb只能跟踪一个进程。可以在fork函数调用之前，通过指令设置gdb调试工具跟踪父进程或跟踪子进程。默认跟踪父进程。

`set follow-fork-mode child`命令设置gdb在fork之后跟踪子进程。

`set follow-fork-mode parent`设置跟踪父进程

注：一定要在fork函数调用之前设置才有效。

## 四、exec函数族：

![exec函数族](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F.png)

![exec函数族原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E5%8E%9F%E7%90%86.png)

### 示例1

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

### 特性

![exec函数特性](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E7%89%B9%E6%80%A7%EF%BC%881%EF%BC%89.png)
![exec函数特性](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E7%89%B9%E6%80%A7%EF%BC%882%EF%BC%89.png)

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

## 五、回收子进程

`ps ajx`查看父子进程

### 1.孤儿进程：

	父进程先于子进终止，子进程沦为“孤儿进程”，会被 init 进程领养。

### 2.僵尸进程：

	子进程终止，父进程尚未对子进程进行回收，在此期间，子进程残留资源（PCB）存放于内核中，变为“僵尸进程”。  kill 对其无效。


### 3.wait函数：

	pid_t wait(int *status)

	参数：（传出） 回收进程的状态。

	返回值：成功： 回收进程的pid

		失败： -1， errno
		
	父进程调用wait函数可以回收子进程退出资源， 阻塞回收任意一个。

		函数作用1：	阻塞等待子进程退出

		函数作用2：	清理子进程残留在内核的 pcb 资源

		函数作用3：	通过传出参数，得到子进程结束状态

	获取子进程正常终止值：

		WIFEXITED(status) --》 为真，说明正常终止 --》调用 WEXITSTATUS(status) --》 得到 子进程 退出值。

	获取导致子进程异常终止信号：

		WIFSIGNALED(status) --》 为真，说明异常终止 --》调用 WTERMSIG(status) --》 得到 导致子进程异常终止的信号编号。

#### 示例：使用wait回收子进程

### 4.waitpid函数：	指定某一个进程进行回收。可以设置非阻塞。			waitpid(-1, &status, 0) == wait(&status);

	pid_t waitpid(pid_t pid, int *status, int options)

	参数：
		pid：指定回收某一个子进程pid

			> 0: 回收指定pid的子进程

			-1：回收任意子进程（相当于wait）

			0：回收和当前调用waitpid一个组的任意子进程
			
			<-1(进程组号取反-1003)：回收指定进程组内的任意子进程

		status：（传出） 回收进程的状态。

		options：WNOHANG 指定回收方式为，设置为非阻塞状态。

	返回值：

		> 0 : 表成功回收的子进程 pid

		0 : 函数调用时， 参3 指定了WNOHANG， 并且，没有子进程结束。

		-1: 失败。errno

	总结：

		wait、waitpid	一次调用，回收一个子进程。

		想回收多个。while 

#### 示例：使用waitpid回收多个子进程

#### 作业：父进程fork3个子进程，三个子进程一个调用ps命令，一个调用自定义程序1（正常），一个调用自定义程序2（段错误）。父进程使用waitpid对其子进程进行回收。
