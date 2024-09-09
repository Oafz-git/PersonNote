# 信号

## 一、信号的概念

### 1.信号共性：

	简单、不能携带大量信息、满足条件才发送。

### 2.信号的特质：

	信号是软件层面上的“中断”。一旦信号产生，无论程序执行到什么位置，必须立即停止运行，处理信号，处理结束，再继续执行后续指令。

**【注】所有信号的产生及处理全部都是由【内核】完成的。**

### 3.信号相关的概念：

* **产生信号：**

	1. 按键产生：`Ctrl+c`、`Ctrl+z`、`Ctrl+\`
	
	2. 系统调用产生：`kill`、`raise`、`abort`
	
	3. 软件条件产生：**定时器alarm**
	
	4. 硬件异常产生：**非法访问内存（段错误）**、**除0（浮点数例外）**、**内存对齐出错（总线错误）**
	
	5. 命令产生：`kill`

* **未决：** 产生与递达之间状态，主要由于阻塞（屏蔽）导致该状态

* **递达：** 产生并且送达到进程。直接被内核处理掉。

* **信号处理方式：**
 
	*	执行默认处理动作
	* 忽略
	* 捕捉（自定义）
	
* **阻塞信号集（信号屏蔽字）：**  本质：位图。用来记录信号的屏蔽状态。一旦被屏蔽的信号，在解除屏蔽前，一直处于未决态。
	
*	**未决信号集：** 本质：位图。
	
	* 用来记录信号的处理状态。	
	* 该信号集中的信号，表示，已经产生，但尚未被处理的状态。
		
![信号屏蔽字和未决信号集](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E5%B1%8F%E8%94%BD%E5%AD%97%E5%92%8C%E6%9C%AA%E5%86%B3%E4%BF%A1%E5%8F%B7%E9%9B%86.png)

### 4.信号四要素（先确定4要素）及常规信号一览表：

**四要素：** 编号、名称、对应事件、默认处理动作。

![信号](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7.png)

**常规信号一览表：**

`man 7 signal`查看帮助文档，也可查看`/usr/src/linux-headers-3.16.0.30/arch/s390/include/uapi/asm/signal.h`

![信号一览表-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-1.png)
![信号一览表-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-2.png)
![信号一览表-3](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-3.png)

**总结：**

![信号总结](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E6%80%BB%E7%BB%93.png)

## 二、信号的产生

### 1.kill命令和kill()函数（发送信号）：

	int kill（pid_t pid, int signum）

	参数：
		pid: 	> 0:发送信号给指定进程

			= 0：发送信号给跟调用kill函数的那个进程处于同一进程组的进程。

			< -1: 取绝对值，发送信号给该绝对值所对应的进程组的所有组员。

			= -1：发送信号给，有权限发送的所有进程。

		signum：待发送的信号，使用宏

	返回值：
		成功： 0

		失败： -1 errno

**【kill权限】**

* **进程组** 每个进程都属于一个进程组，进程组是一个或多个进程集合，它们相互关联，共同完成一个实体任务；每个进程组都有一个进程组长，默认进程组ID与进程组长ID相同

* **权限保护** root用户可以发送信号给任意用户，普通用户是不能向系统用户发送信号的：

	* `kill -9 (root用户的pid)`是不可以的；
	
	* 同样，普通用户也不能向其它普通用户发送信号，终止其进程。只能向自己创建的进程发送信号；
	
	* **普通用户的基本规则：发送者实际或有效用户ID == 接收者实际或有效用户ID**

#### 示例：循环创建5个子进程，父进程用kill函数终止任意一子进程

```C++
int main(void)
{
	int i;				//默认创建5个子进程

	for(i = 0; i < N; i++)	//出口1,父进程专用出口
		if(fork() == 0)
			break;			//出口2,子进程出口,i不自增

    if (i == 3) {
        sleep(1);
        printf("-----------child ---pid = %d, ppid = %d\n", getpid(), getppid());
        kill(getppid(), SIGKILL);

    } else if (i == N) {
        printf("I am parent, pid = %d\n", getpid());
        while(1);
    }

	return 0;
}
```

### 2.软件条件产生信号（alarm、setitimer）

	unsigned int alarm(unsigned int seconds);
	
		参数：
			seconds：定时秒数

		返回值：上次定时剩余时间。

			无错误现象。
		
		注意：
	
			与进程状态无关，使用自然计时法。
	
			每个进程都有且只有唯一一个定时器。

			定时发送SIGALRM（14）给当前进程，默认动作：终止进程。
			
			alarm（0）； 取消闹钟，返回旧闹钟余下秒数

**time命令（优化IO）：**  查看程序执行时间。  实际时间 = 用户时间 + 内核时间 + 等待时间(获取设备)  --》 优化瓶颈 IO

![time命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/time%E5%91%BD%E4%BB%A4.png)

#### 示例：使用alarm计数计算机1s能数多少个数，输入至文件中

```C
int main(int argc, char* argv[])
{
        int a = 0, fd;
        alarm(1);
        fd = open("temp",O_RDWR|O_CREAT|O_TRUNC,0664);
        if(fd == -1)
        {
                perror("open error");
                exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        while(1)
        {
                printf("%d\n", a++);
        }
        return 0;
}
```

	setitimer函数：

		int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);

		设置定时器。可代替alarm函数，精度微妙us，可以实现周期定时

		参数：
			which：	ITIMER_REAL： 采用自然计时。---> SIGALRM

				ITIMER_VIRTUAL: 采用用户空间计时  ---> SIGVTALRM

				ITIMER_PROF: 采用内核+用户空间计时 ---> SIGPROF
		
			new_value：定时秒数

		           	类型：struct itimerval {

               					struct timeval {
               						time_t      tv_sec;         /* seconds */
               						suseconds_t tv_usec;        /* microseconds */

           					}it_interval;---> 周期定时秒数

               				 	struct timeval {
               						time_t      tv_sec;         
               						suseconds_t tv_usec;        

           					}it_value;  ---> 第一次定时秒数  
           			 	};

			old_value：传出参数，上次定时剩余时间。
			
		返回值：
			成功： 0

			失败： -1 errno
	
		e.g.
			struct itimerval new_t;	
			struct itimerval old_t;	

			new_t.it_interval.tv_sec = 0;
			new_t.it_interval.tv_usec = 0;
			new_t.it_value.tv_sec = 1;
			new_t.it_value.tv_usec = 0;

			int ret = setitimer(&new_t, &old_t);  定时1秒

#### 示例1：使用setitimer函数实现alarm函数，重复计算机1秒数数程序。

```C
unsigned int my_alarm(unsigned int sec)
{
	struct itimerval it, oldit;
    int ret;

	it.it_value.tv_sec = sec;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 0;
	it.it_interval.tv_usec = 0;

	ret = setitimer(ITIMER_REAL, &it, &oldit);
    if (ret == -1) {
        perror("setitimer");
        exit(1);
    }
	return oldit.it_value.tv_sec;
}

int main(void)
{
	int i;
	my_alarm(1);  //alarm(sec);

	for(i = 0; ; i++)
		printf("%d\n", i);

	return 0;
}
```

#### 示例2：捕捉setitimer信号
```C
int main(void)
{
	struct itimerval it, oldit;

	signal(SIGALRM, myfunc);   //注册SIGALRM信号的捕捉处理函数。

	it.it_value.tv_sec = 2;
	it.it_value.tv_usec = 0;

	it.it_interval.tv_sec = 5;
	it.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &it, &oldit) == -1){
		perror("setitimer error");
		return -1;
	}

	while(1);

	return 0;
}
```


### 3.其他几个发信号函数：

	int raise(int sig);

	void abort(void);


## 三、信号集操作函数(阻塞信号集)

![信号集操作函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%9B%86%E6%93%8D%E4%BD%9C%E5%87%BD%E6%95%B0.png)

### 1.自定义set

	sigset_t set;  自定义信号集。

	sigemptyset(sigset_t *set);	清空信号集

	sigfillset(sigset_t *set);	全部置1

	sigaddset(sigset_t *set, int signum);	将一个信号添加到集合中

	sigdelset(sigset_t *set, int signum);	将一个信号从集合中移除

	sigismember（const sigset_t *set，int signum); 判断一个信号是否在集合中。 在--》返回1， 不在--》返回0

### 2.设置信号屏蔽字和解除屏蔽：

	int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

		how:	SIG_BLOCK:	设置阻塞（位或）

			SIG_UNBLOCK:	取消阻塞（取反后再位与）

			SIG_SETMASK:	用自定义set替换mask。（覆盖）

		set：	自定义set

		oldset：旧有的 mask。

### 3.查看未决信号集：

	int sigpending(sigset_t *set);
	
	参数：

		set： 传出的 未决信号集。
		
`ctrl-d`不是发送信号，是写入EOF

#### 示例：信号集操作函数练习

```C
void printset(sigset_t *ped)
{
	int i;
	for(i = 1; i < 32; i++){
		if((sigismember(ped, i) == 1)){
			putchar('1');
		} else {
			putchar('0');
		}
	}
	printf("\n");
}

int main(void)
{
	sigset_t set, oldset, ped;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
#if 0
	sigaddset(&set, SIGQUIT); 
	sigaddset(&set, SIGKILL);	//阻塞被忽略
	sigaddset(&set, SIGSEGV);
	sigfillset(&set);
#endif
	sigprocmask(SIG_BLOCK, &set, &oldset);	

	while(1){
		sigpending(&ped);       //获取未决信号集
		printset(&ped);
		sleep(1);
	}
```

## 四、信号捕捉

### 1.signal()函数
	
**注册**一个信号捕捉函数：该函数由ANSI定义，由于历史原因在不同版本的UNIX和不同版本的LINUX中可能有不同的行为，应尽量避免使用它。

![signal函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/signal%E5%87%BD%E6%95%B0.png)	

#### 示例：signal函数的使用

```C
//signal.c
void do_sig(int a)
{
    printf("Hi, SIGINT, how do you do !\n");
}

int main(void)
{
    if (signal(SIGINT, do_sig) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while (1) {
        printf("---------------------\n");
        sleep(1);
    }

    return 0;
}
```

### 2.sigaction()函数 （重点！！！）

![sigaction函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/sigaction%E5%87%BD%E6%95%B0.png)

	参数：
		act：传入参数，新的处理方式
		
		oldact：传出参数，旧的处理方式，默认传NULL

![struct_sigaction](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_sigaction.png)

	sa_handler：
	
		指定信号捕捉后的处理函数名（即注册函数）。
	
		也可赋值为SIG_IGN（表忽略）或SIG_DFL（表执行默认动作）
	
	sa_mask：
	
		* 调用信号处理函数时，所要屏蔽的信号集合（信号屏蔽字）。
		
		* 注意：仅在处理函数被调用期间屏蔽生效，是临时性设置。
	
	sa_flags：
		
		* 通常设置为0，表默认属性（本信号默认屏蔽）
		
		设置被信号中断后系统调用是否重启。SA_INTERRURT不重启，SA_RESTART重启。
		
		设置为SA_NODEFER，表示在执行捕捉函数期间，不希望自动阻塞该信号（发多次信号，会多次执行捕捉函数），除非sa_mask中包含该信号。

**fflush(stdout)函数;刷新缓存**

#### 示例：sigaction函数的使用

```C
/*
 * 当执行SIGINT信号处理函数期间
 * 多次收到SIGQUIT信号都将被屏蔽(阻塞)
 * SIGINT信号处理函数处理完，立刻解除对
 * SIGQUIT信号的屏蔽，由于没有捕捉该信号，
 * 将立刻执行该信号的默认动作，程序退出
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*自定义的信号捕捉函数*/
void sig_int(int signo)
{
	printf("catch signal SIGINT\n");	//单次打印，在10s内只处理一次
	sleep(10);	//模拟信号处理函数执行很长时间
	printf("----slept 10 s\n");
}

int main(void)
{
	struct sigaction act,old;		

	act.sa_handler = sig_int;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);		//不屏蔽任何信号
	sigaddset(&act.sa_mask, SIGQUIT);	//将SIGQUIT加入信号屏蔽集,这就导致,在调用信号处理函数期间不仅不响应SIGINT信号本身,还不响应SIGQUIT

	sigaction(SIGINT, &act, &old);
	sleep(10);
	printf("------------main slept 10\n");
  
	sigaction(SIGINT, &old, NULL);	//注册信号处理函数

	while(1);//该循环只是为了保证有足够的时间来测试函数特性

	return 0;
}

```

### 3.信号捕捉特性：

![信号捕捉特性](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E6%8D%95%E6%8D%89%E7%89%B9%E6%80%A7.png)

### 4.内核实现信号捕捉过程：

![内核实现信号捕捉过程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E6%A0%B8%E5%AE%9E%E7%8E%B0%E4%BF%A1%E5%8F%B7%E6%8D%95%E6%8D%89%E8%BF%87%E7%A8%8B.png)

### 5.SIGCHLD信号

	SIGCHLD的产生条件：
		
		子进程终止时
		
		子进程接收到SIGSTOP信号停止时
		
		子进程处在停止态，接受到SIGCONT后唤醒时

#### 示例：借助信号完成子进程回收。


```C
子进程结束运行，其父进程会收到SIGCHLD信号。该信号的默认处理动作是忽略。可以捕捉该信号，在捕捉函数中完成子进程状态的回收

//sigaction_child.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <pthread.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void catch_child(int signo)
{
    pid_t wpid;
    int status;

    //while((wpid = wait(NULL)) != -1) {
    while((wpid = waitpid(-1, &status, 0)) != -1) {         // 循环回收,防止僵尸进程出现.
        if (WIFEXITED(status))
            printf("---------------catch child id %d, ret=%d\n", wpid, WEXITSTATUS(status));
    }

    return ;
}

int main(int argc, char *argv[])
{
    pid_t pid;
//阻塞
    int i; 
    for (i = 0; i < 15; i++)
        if ((pid = fork()) == 0)                // 创建多个子进程
            break;

    if (15 == i) {
        struct sigaction act;

        act.sa_handler = catch_child;           // 设置回调函数
        sigemptyset(&act.sa_mask);              // 设置捕捉函数执行期间屏蔽字
        act.sa_flags = 0;                       // 设置默认属性, 本信号自动屏蔽

        sigaction(SIGCHLD, &act, NULL);         // 注册信号捕捉函数
//解除阻塞

        printf("I'm parent, pid = %d\n", getpid());

        while (1);

    } else {
        printf("I'm child pid = %d\n", getpid());
        return i;
    }

    return 0;
}

```

### 6.中断系统调用（了解）

![中断系统调用](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%B8%AD%E6%96%AD%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8.png)

	




























