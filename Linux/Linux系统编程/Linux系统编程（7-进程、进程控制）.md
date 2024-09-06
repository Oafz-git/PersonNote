# ������ظ���
	�������ġ�ֻռ�ô��̿ռ䡣		�����籾��

	���̣���ġ����������ĳ���ռ���ڴ桢cpu��ϵͳ��Դ��	����Ϸ��
	
### һ�������ڴ�ӳ��MMU�������ڴ�������ڴ�ӳ�䣩

![CPU��MMU](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/CPU%E5%92%8CMMU.png)
![MMU](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/MMU.png)

### ����PCB���̿��ƿ飺

��`/usr/src/linux-headers-3.16.0-30/include/linux/sched.h`�в鿴`struct task_struct`�ṹ�嶨�塣��Ҫ�������£�

* **����id**���鿴����id`ps aux`

* **�ļ���������**�������ܶ�ָ��file�ṹ���ָ��

* **����״̬**����ʼ̬������̬������̬������̬����ֹ̬��

* **��ǰ���̹���Ŀ¼λ��**

* **umask����** ������ǽ��̵ĸ��

* �ź������Ϣ��Դ��

* �û�id����id

* �Ự�ͽ�����

* ���̿���ʹ�õ���Դ����

* �����л�ʱ��Ҫ����ͻָ���һЩCPU�Ĵ���

* ���������ַ�ռ����Ϣ

* ���������ն˵���Ϣ

### ������������

* `LD_LIBRARY_PATH`������̬���ӿ�ʹ��
* `PATH`����¼��ִ���ļ�λ��
* `SHELL`���������ֵͨ����`/bin/bash`
* `TERM`����ǰ�ն�����
* `LANG`������
* `HOME`����Ŀ¼
* `env`���鿴���л�������

# ���̿���

## һ��fork�����������ӽ��̣�

	pid_t fork(void)
	
	fork֮�󸸽�����ִ�л����ӽ�����ִ�в�ȷ����ȡ�����ں���ʹ�õĵ����㷨��

	����ֵ��
	
		�����ӽ��̡����ӽ��̸��Է��ء������̷����ӽ���pid�� �ӽ��̷��� 0.
![fork����ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/fork%E5%87%BD%E6%95%B0%E5%8E%9F%E7%90%86.png)

### ʾ����ѭ������n���ӽ���

```C
//loop_fork.c
int main(int argc, char* argv[])
{
        int i;
        pid_t pid;
        for(i=0; i<5; i++)	//����1,������ר�ó��ڣ�ѭ���ڼ䣬�ӽ��̲�fork
        {
                if(fork() == 0) break;//����2,�ӽ��̳���,i������
        }
        if(5 == i)	//�����̣��ӱ��ʽ2����
        {
                sleep(5);
                printf("I'm parent\n");
        }else	//�ӽ��̣���break����
        {
                sleep(i);
                printf("I'm %dth child\n",i+1);
        }
        return 0;
}
```

## ������ȡ���������id����

1. getpid��������ȡ��ǰ����ID`pid_t getpid();`

2. getppid��������ȡ��ǰ���̵ĸ�����ID`pid_t getppid();`

3. getuid������

	* ��ȡ��ǰ����ʵ���û�ID`uid_t getuid();`
	
	* ��ȡ��ǰ������Ч�û�ID`uid_t geteuid();`

4. getgid������
	
	* ��ȡ��ǰ����ʹ���û���ID`gid_t getgid();`
	
	* ��ȡ��ǰ������Ч�û���ID`gid_t getegid();`

��ע������һ�������ǡ�ϵͳ���������ǡ��⺯������

*  �Ƿ�����ں����ݽṹ
	
* �Ƿ�����ⲿӲ����Դ 

## �������̹������ӽ��̲��죩

�ڸ�ʹ��`fork`�����ӽ���ʱ�����ӽ���֮������Щ��֮ͬ���أ�

|������ͬ��|���Ӳ�ͬ��|
|----|----|
|**ȫ�ֱ���**��.data��.text��ջ���ѡ������������û�ID������Ŀ¼�����̹���Ŀ¼���źŴ���ʽ|1.����ID��2.fork����ֵ��3.������ID��4.��������ʱ�䡢5.���ӣ���ʱ������6.δ���źż�|

���ƺ����ӽ��̸����˸�����0-3G�û��ռ����ݣ��Լ������̵�PCB����pid��ͬ��

�����⡿���ÿforkһ���ӽ��̶�Ҫ�������̵�0-3G��ַ�ռ���ȫ����һ�ݣ�Ȼ����ӳ���������ڴ���

���𡿵�Ȼ���ǣ����ӽ��̼���ѭ**��ʱ����дʱ����**��ԭ����������ƣ������ӽ���ִ�и����̵��߼�����ִ���Լ����߼����ܽ�ʡ�ڴ濪����

���ص㡿���ӽ��̹���

1. **�ļ�������** 

2. **mmap������ӳ����**

#### ʾ��1����д������ԣ����ӽ����Ƿ���ȫ�ֱ��������ӽ��̲�����ȫ�ֱ�����

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

## �ġ����ӽ���gdb����

ʹ��gdb���Ե�ʱ��gdbֻ�ܸ���һ�����̡�������fork��������֮ǰ��ͨ��ָ������gdb���Թ��߸��ٸ����̻�����ӽ��̡�Ĭ�ϸ��ٸ����̡�

`set follow-fork-mode child`��������gdb��fork֮������ӽ��̡�

`set follow-fork-mode parent`���ø��ٸ�����

**ע��һ��Ҫ��fork��������֮ǰ���ò���Ч��**

## �塢exec������

* fork�����ӽ��̺�ִ�е��Ǻ͸�������ͬ�ĳ��򣨵�����ִ�в�ͬ�Ĵ����֧�����ӽ�������Ҫ����һ��exec������ִ����һ������

* ������һ��exec����ʱ���ý��̵�**�û��ռ����**��**����**��ȫ���³����滻�����³�����������̿�ʼִ�С�

* ����exec**���������½���**�����Ե���execǰ��ý��̵�id��δ�ı䡣

* ����ǰ���̵�`.text/.data`�滻Ϊ��Ҫ���صĳ����`.text/.data`��Ȼ���ý��̴��µ�.text��һ��ָ�ʼִ�У�������ID���䣬**���˲�����**

![exec������ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E5%8E%9F%E7%90%86.png)

* ����exec����

	   int execl(const char *path, const char *arg, ...);
	   int execlp(const char *file, const char *arg, ...);
	   int execle(const char *path, const char *arg,..., char * const envp[]);
	   int execv(const char *path, char *const argv[]);
	   int execvp(const char *file, char *const argv[]);
	   int execvpe(const char *file, char *const argv[],char *const envp[]);

* �����ԡ�exec����һ�����óɹ���ִ���µĳ���**������**��**ֻ����ʧ�ܲŻ᷵�أ�����ֵ-1**������ͨ������ֱ����exec�������ú�ֱ�ӵ���perror()��exit()������if�жϡ�

	* `l(list)`�������в����б�
	
	* `p(path)`������fileʱʹ��path����
	
	* `v(vector)`��ʹ�������в�������
	
	* `e(environment)`��ʹ�������в������飬��ʹ�ý���ԭ�еĻ��������������¼��س������еĻ�������
	
��ʵ�ϣ�ֻ��`execve`��������ϵͳ���ã���������������ն�����`execve`������`execve`��man�ֲ��2�ڣ�����������man������3�ڡ���Щ����֮��Ĺ�ϵ����

![exec��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E7%89%B9%E6%80%A7%EF%BC%882%EF%BC%89.png)

### ʾ��1:execlp/execl������ʹ��

```C
//fork_exec()
int main(int argc, char* argv[])
{
        pid_t pid = fork();             //�����ӽ���
        if(pid == -1)
        {
                perror("fork error");
        } else if(pid == 0) //�ӽ���
        {
                execlp("ls", "ls", "-l", "-d", NULL);//NULLΪ�ڱ�����ʾ��β
                //execl("./a.out","./a.out", NULL);
                //execl("/bin/ls", "ls", "-l", NULL);
                
              	//char *argv[] = {"ls", "-l", "-h", NULL};
              	//execvp("ls", argv);
                
                perror("execlp error");//ֻ��execlpִ�г���ʱ�Ż�ִ�У�����ִ��
                exit(1);
        } else if(pid > 0)//������
        {       
                printf("I'm parent: %d\n", getpid());
        }
        
        return 0;
}
```

### ʾ��2������ǰϵͳ�еĽ�����Ϣ����ӡ���ļ���

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

## ���������ӽ���

`ps ajx`�鿴���ӽ���

### 1.�¶����̣�

�����������ӽ���ֹ���ӽ�����Ϊ**�¶�����**���ᱻ**init����**������

### 2.��ʬ���̣�

�ӽ�����ֹ����������δ���ӽ��̽��л��գ��ڴ��ڼ䣬�ӽ��̲�����Դ��PCB��������ں��У���Ϊ**��ʬ����**��  kill ������Ч��

### 3.wait������

	pid_t wait(int *status)

	�������������� ���ս��̵�״̬��

	����ֵ���ɹ��� ���ս��̵�pid

		ʧ�ܣ� -1�� errno
		
	�����̵���wait�������Ի����ӽ����˳���Դ�� ������������һ����

		��������1��	�����ȴ��ӽ����˳�

		��������2��	�����ӽ��̲������ں˵� pcb ��Դ

		��������3��	ͨ�������������õ��ӽ��̽���״̬

	��ȡ�ӽ���������ֵֹ��״̬����

		WIFEXITED(status) --�� Ϊ�棬˵��������ֹ --������ WEXITSTATUS(status) --�� �õ� �ӽ��� �˳�ֵ��

	��ȡ�����ӽ����쳣��ֹ�źţ�״̬����

		WIFSIGNALED(status) --�� Ϊ�棬˵���쳣��ֹ --������ WTERMSIG(status) --�� �õ� �����ӽ����쳣��ֹ���źű�š�

#### ʾ����ʹ��wait�����ӽ���

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
		//wpid = wait(NULL);	//��������
		wpid = wait(&status);	//��������

		if(WIFEXITED(status)){	//�����˳�
			printf("I'm parent, The child process "
					"%d exit normally\n", wpid);
			printf("return value:%d\n", WEXITSTATUS(status));

		} else if (WIFSIGNALED(status)) {	//�쳣�˳�
			printf("The child process exit abnormally, "
					"killed by signal %d\n", WTERMSIG(status));
										//��ȡ�źű��
		} else {
			printf("other...\n");
		}
	}

	return 0;
}
```

### 4.waitpid������	ָ��ĳһ�����̽��л��ա��������÷�������			

	pid_t waitpid(pid_t pid, int *status, int options)
	
	waitpid(-1, &status, 0) == wait(&status);

	������
		pid��ָ������ĳһ���ӽ���pid

			> 0: ����ָ��pid���ӽ���

			-1�����������ӽ��̣��൱��wait��

			0�����պ͵�ǰ����waitpidһ����������ӽ���
			
			<-1(�������ȡ��-1003)������ָ���������ڵ������ӽ���

		status���������� ���ս��̵�״̬��

		options��WNOHANG ָ�����շ�ʽΪ������Ϊ������״̬������Ϊ0 Ĭ��Ϊ��������

	����ֵ��

		> 0 : ��ɹ����յ��ӽ��� pid

		0 : ��������ʱ�� �����3ָ����WNOHANG�� ���ң�û���ӽ��̽���ʱ������0��

		-1: ʧ�ܡ�errno

	�ܽ᣺

		wait��waitpid	һ�ε��ã�����һ���ӽ��̡�

		����ն����while 

#### ʾ��1������������

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
			wpid = waitpid(pid, NULL, WNOHANG);//����������
            		//wpid = wait(NULL);
			printf("---wpid = %d--------%d\n", wpid, flg++);
			if(wpid == 0){
				printf("NO child exited\n");
				sleep(1);		
			}
		} while (wpid == 0);		//�ӽ��̲��ɻ���

		if(wpid == pid){		//������ָ���ӽ���
			printf("I'm parent, I catched child process,"
					"pid = %d\n", wpid);
		} else {
			printf("other...\n");
		}
	}
	return 0;
}
```

#### ʾ��2��ʹ��waitpid���ն���ӽ���

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

#### ��ҵ��������fork3���ӽ��̣������ӽ���һ������ps���һ�������Զ������1����������һ�������Զ������2���δ��󣩡�������ʹ��waitpid�����ӽ��̽��л��ա�
