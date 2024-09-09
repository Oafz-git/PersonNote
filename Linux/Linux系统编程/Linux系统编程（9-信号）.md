# �ź�

## һ���źŵĸ���

### 1.�źŹ��ԣ�

	�򵥡�����Я��������Ϣ�����������ŷ��͡�

### 2.�źŵ����ʣ�

	�ź�����������ϵġ��жϡ���һ���źŲ��������۳���ִ�е�ʲôλ�ã���������ֹͣ���У������źţ�����������ټ���ִ�к���ָ�

**��ע�������źŵĲ���������ȫ�������ɡ��ںˡ���ɵġ�**

### 3.�ź���صĸ��

* **�����źţ�**

	1. ����������`Ctrl+c`��`Ctrl+z`��`Ctrl+\`
	
	2. ϵͳ���ò�����`kill`��`raise`��`abort`
	
	3. �������������**��ʱ��alarm**
	
	4. Ӳ���쳣������**�Ƿ������ڴ棨�δ���**��**��0�����������⣩**��**�ڴ����������ߴ���**
	
	5. ���������`kill`

* **δ����** ������ݴ�֮��״̬����Ҫ�������������Σ����¸�״̬

* **�ݴ** ���������ʹﵽ���̡�ֱ�ӱ��ں˴������

* **�źŴ���ʽ��**
 
	*	ִ��Ĭ�ϴ�����
	* ����
	* ��׽���Զ��壩
	
* **�����źż����ź������֣���**  ���ʣ�λͼ��������¼�źŵ�����״̬��һ�������ε��źţ��ڽ������ǰ��һֱ����δ��̬��
	
*	**δ���źż���** ���ʣ�λͼ��
	
	* ������¼�źŵĴ���״̬��	
	* ���źż��е��źţ���ʾ���Ѿ�����������δ�������״̬��
		
![�ź������ֺ�δ���źż�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E5%B1%8F%E8%94%BD%E5%AD%97%E5%92%8C%E6%9C%AA%E5%86%B3%E4%BF%A1%E5%8F%B7%E9%9B%86.png)

### 4.�ź���Ҫ�أ���ȷ��4Ҫ�أ��������ź�һ����

**��Ҫ�أ�** ��š����ơ���Ӧ�¼���Ĭ�ϴ�������

![�ź�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7.png)

**�����ź�һ����**

`man 7 signal`�鿴�����ĵ���Ҳ�ɲ鿴`/usr/src/linux-headers-3.16.0.30/arch/s390/include/uapi/asm/signal.h`

![�ź�һ����-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-1.png)
![�ź�һ����-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-2.png)
![�ź�һ����-3](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-3.png)

**�ܽ᣺**

![�ź��ܽ�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E6%80%BB%E7%BB%93.png)

## �����źŵĲ���

### 1.kill�����kill()�����������źţ���

	int kill��pid_t pid, int signum��

	������
		pid: 	> 0:�����źŸ�ָ������

			= 0�������źŸ�������kill�������Ǹ����̴���ͬһ������Ľ��̡�

			< -1: ȡ����ֵ�������źŸ��þ���ֵ����Ӧ�Ľ������������Ա��

			= -1�������źŸ�����Ȩ�޷��͵����н��̡�

		signum�������͵��źţ�ʹ�ú�

	����ֵ��
		�ɹ��� 0

		ʧ�ܣ� -1 errno

**��killȨ�ޡ�**

* **������** ÿ�����̶�����һ�������飬��������һ���������̼��ϣ������໥��������ͬ���һ��ʵ������ÿ�������鶼��һ�������鳤��Ĭ�Ͻ�����ID������鳤ID��ͬ

* **Ȩ�ޱ���** root�û����Է����źŸ������û�����ͨ�û��ǲ�����ϵͳ�û������źŵģ�

	* `kill -9 (root�û���pid)`�ǲ����Եģ�
	
	* ͬ������ͨ�û�Ҳ������������ͨ�û������źţ���ֹ����̡�ֻ�����Լ������Ľ��̷����źţ�
	
	* **��ͨ�û��Ļ������򣺷�����ʵ�ʻ���Ч�û�ID == ������ʵ�ʻ���Ч�û�ID**

#### ʾ����ѭ������5���ӽ��̣���������kill������ֹ����һ�ӽ���

```C++
int main(void)
{
	int i;				//Ĭ�ϴ���5���ӽ���

	for(i = 0; i < N; i++)	//����1,������ר�ó���
		if(fork() == 0)
			break;			//����2,�ӽ��̳���,i������

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

### 2.������������źţ�alarm��setitimer��

	unsigned int alarm(unsigned int seconds);
	
		������
			seconds����ʱ����

		����ֵ���ϴζ�ʱʣ��ʱ�䡣

			�޴�������
		
		ע�⣺
	
			�����״̬�޹أ�ʹ����Ȼ��ʱ����
	
			ÿ�����̶�����ֻ��Ψһһ����ʱ����

			��ʱ����SIGALRM��14������ǰ���̣�Ĭ�϶�������ֹ���̡�
			
			alarm��0���� ȡ�����ӣ����ؾ�������������

**time����Ż�IO����**  �鿴����ִ��ʱ�䡣  ʵ��ʱ�� = �û�ʱ�� + �ں�ʱ�� + �ȴ�ʱ��(��ȡ�豸)  --�� �Ż�ƿ�� IO

![time����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/time%E5%91%BD%E4%BB%A4.png)

#### ʾ����ʹ��alarm���������1s�������ٸ������������ļ���

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

	setitimer������

		int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);

		���ö�ʱ�����ɴ���alarm����������΢��us������ʵ�����ڶ�ʱ

		������
			which��	ITIMER_REAL�� ������Ȼ��ʱ��---> SIGALRM

				ITIMER_VIRTUAL: �����û��ռ��ʱ  ---> SIGVTALRM

				ITIMER_PROF: �����ں�+�û��ռ��ʱ ---> SIGPROF
		
			new_value����ʱ����

		           	���ͣ�struct itimerval {

               					struct timeval {
               						time_t      tv_sec;         /* seconds */
               						suseconds_t tv_usec;        /* microseconds */

           					}it_interval;---> ���ڶ�ʱ����

               				 	struct timeval {
               						time_t      tv_sec;         
               						suseconds_t tv_usec;        

           					}it_value;  ---> ��һ�ζ�ʱ����  
           			 	};

			old_value�������������ϴζ�ʱʣ��ʱ�䡣
			
		����ֵ��
			�ɹ��� 0

			ʧ�ܣ� -1 errno
	
		e.g.
			struct itimerval new_t;	
			struct itimerval old_t;	

			new_t.it_interval.tv_sec = 0;
			new_t.it_interval.tv_usec = 0;
			new_t.it_value.tv_sec = 1;
			new_t.it_value.tv_usec = 0;

			int ret = setitimer(&new_t, &old_t);  ��ʱ1��

#### ʾ��1��ʹ��setitimer����ʵ��alarm�������ظ������1����������

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

#### ʾ��2����׽setitimer�ź�
```C
int main(void)
{
	struct itimerval it, oldit;

	signal(SIGALRM, myfunc);   //ע��SIGALRM�źŵĲ�׽��������

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


### 3.�����������źź�����

	int raise(int sig);

	void abort(void);


## �����źż���������(�����źż�)

![�źż���������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%9B%86%E6%93%8D%E4%BD%9C%E5%87%BD%E6%95%B0.png)

### 1.�Զ���set

	sigset_t set;  �Զ����źż���

	sigemptyset(sigset_t *set);	����źż�

	sigfillset(sigset_t *set);	ȫ����1

	sigaddset(sigset_t *set, int signum);	��һ���ź���ӵ�������

	sigdelset(sigset_t *set, int signum);	��һ���źŴӼ������Ƴ�

	sigismember��const sigset_t *set��int signum); �ж�һ���ź��Ƿ��ڼ����С� ��--������1�� ����--������0

### 2.�����ź������ֺͽ�����Σ�

	int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);

		how:	SIG_BLOCK:	����������λ��

			SIG_UNBLOCK:	ȡ��������ȡ������λ�룩

			SIG_SETMASK:	���Զ���set�滻mask�������ǣ�

		set��	�Զ���set

		oldset�����е� mask��

### 3.�鿴δ���źż���

	int sigpending(sigset_t *set);
	
	������

		set�� ������ δ���źż���
		
`ctrl-d`���Ƿ����źţ���д��EOF

#### ʾ�����źż�����������ϰ

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
	sigaddset(&set, SIGKILL);	//����������
	sigaddset(&set, SIGSEGV);
	sigfillset(&set);
#endif
	sigprocmask(SIG_BLOCK, &set, &oldset);	

	while(1){
		sigpending(&ped);       //��ȡδ���źż�
		printset(&ped);
		sleep(1);
	}
```

## �ġ��źŲ�׽

### 1.signal()����
	
**ע��**һ���źŲ�׽�������ú�����ANSI���壬������ʷԭ���ڲ�ͬ�汾��UNIX�Ͳ�ͬ�汾��LINUX�п����в�ͬ����Ϊ��Ӧ��������ʹ������

![signal����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/signal%E5%87%BD%E6%95%B0.png)	

#### ʾ����signal������ʹ��

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

### 2.sigaction()���� ���ص㣡������

![sigaction����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/sigaction%E5%87%BD%E6%95%B0.png)

	������
		act������������µĴ���ʽ
		
		oldact�������������ɵĴ���ʽ��Ĭ�ϴ�NULL

![struct_sigaction](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_sigaction.png)

	sa_handler��
	
		ָ���źŲ�׽��Ĵ�����������ע�ắ������
	
		Ҳ�ɸ�ֵΪSIG_IGN������ԣ���SIG_DFL����ִ��Ĭ�϶�����
	
	sa_mask��
	
		* �����źŴ�����ʱ����Ҫ���ε��źż��ϣ��ź������֣���
		
		* ע�⣺���ڴ������������ڼ�������Ч������ʱ�����á�
	
	sa_flags��
		
		* ͨ������Ϊ0����Ĭ�����ԣ����ź�Ĭ�����Σ�
		
		���ñ��ź��жϺ�ϵͳ�����Ƿ�������SA_INTERRURT��������SA_RESTART������
		
		����ΪSA_NODEFER����ʾ��ִ�в�׽�����ڼ䣬��ϣ���Զ��������źţ�������źţ�����ִ�в�׽������������sa_mask�а������źš�

**fflush(stdout)����;ˢ�»���**

#### ʾ����sigaction������ʹ��

```C
/*
 * ��ִ��SIGINT�źŴ������ڼ�
 * ����յ�SIGQUIT�źŶ���������(����)
 * SIGINT�źŴ����������꣬���̽����
 * SIGQUIT�źŵ����Σ�����û�в�׽���źţ�
 * ������ִ�и��źŵ�Ĭ�϶����������˳�
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*�Զ�����źŲ�׽����*/
void sig_int(int signo)
{
	printf("catch signal SIGINT\n");	//���δ�ӡ����10s��ֻ����һ��
	sleep(10);	//ģ���źŴ�����ִ�кܳ�ʱ��
	printf("----slept 10 s\n");
}

int main(void)
{
	struct sigaction act,old;		

	act.sa_handler = sig_int;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);		//�������κ��ź�
	sigaddset(&act.sa_mask, SIGQUIT);	//��SIGQUIT�����ź����μ�,��͵���,�ڵ����źŴ������ڼ䲻������ӦSIGINT�źű���,������ӦSIGQUIT

	sigaction(SIGINT, &act, &old);
	sleep(10);
	printf("------------main slept 10\n");
  
	sigaction(SIGINT, &old, NULL);	//ע���źŴ�����

	while(1);//��ѭ��ֻ��Ϊ�˱�֤���㹻��ʱ�������Ժ�������

	return 0;
}

```

### 3.�źŲ�׽���ԣ�

![�źŲ�׽����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E6%8D%95%E6%8D%89%E7%89%B9%E6%80%A7.png)

### 4.�ں�ʵ���źŲ�׽���̣�

![�ں�ʵ���źŲ�׽����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%85%E6%A0%B8%E5%AE%9E%E7%8E%B0%E4%BF%A1%E5%8F%B7%E6%8D%95%E6%8D%89%E8%BF%87%E7%A8%8B.png)

### 5.SIGCHLD�ź�

	SIGCHLD�Ĳ���������
		
		�ӽ�����ֹʱ
		
		�ӽ��̽��յ�SIGSTOP�ź�ֹͣʱ
		
		�ӽ��̴���ֹ̬ͣ�����ܵ�SIGCONT����ʱ

#### ʾ���������ź�����ӽ��̻��ա�


```C
�ӽ��̽������У��丸���̻��յ�SIGCHLD�źš����źŵ�Ĭ�ϴ������Ǻ��ԡ����Բ�׽���źţ��ڲ�׽����������ӽ���״̬�Ļ���

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
    while((wpid = waitpid(-1, &status, 0)) != -1) {         // ѭ������,��ֹ��ʬ���̳���.
        if (WIFEXITED(status))
            printf("---------------catch child id %d, ret=%d\n", wpid, WEXITSTATUS(status));
    }

    return ;
}

int main(int argc, char *argv[])
{
    pid_t pid;
//����
    int i; 
    for (i = 0; i < 15; i++)
        if ((pid = fork()) == 0)                // ��������ӽ���
            break;

    if (15 == i) {
        struct sigaction act;

        act.sa_handler = catch_child;           // ���ûص�����
        sigemptyset(&act.sa_mask);              // ���ò�׽����ִ���ڼ�������
        act.sa_flags = 0;                       // ����Ĭ������, ���ź��Զ�����

        sigaction(SIGCHLD, &act, NULL);         // ע���źŲ�׽����
//�������

        printf("I'm parent, pid = %d\n", getpid());

        while (1);

    } else {
        printf("I'm child pid = %d\n", getpid());
        return i;
    }

    return 0;
}

```

### 6.�ж�ϵͳ���ã��˽⣩

![�ж�ϵͳ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%B8%AD%E6%96%AD%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8.png)

	




























