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

# ���̿���

## һ��fork�����������ӽ��̣�/getpid������getppid��������ȡ����ID��

	pid_t fork(void)
	
	fork֮�󸸽�����ִ�л����ӽ�����ִ�в�ȷ����ȡ�����ں���ʹ�õĵ����㷨��

	����ֵ�������ӽ��̡����ӽ��̸��Է��ء������̷����ӽ���pid�� �ӽ��̷��� 0.
	
	getpid();getppid();����ȡ����ID��

![fork����ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/fork%E5%87%BD%E6%95%B0%E5%8E%9F%E7%90%86.png)
	
### ʾ����ѭ������n���ӽ���

```C
//loop_fork.c
int main(int argc, char* argv[])
{
        int i;
        pid_t pid;
        for(i=0; i<5; i++)	//ѭ���ڼ䣬�ӽ��̲�fork
        {
                if(fork() == 0) break;
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

## �������̹������ӽ��̲��죩

![���̹���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E5%85%B1%E4%BA%AB.png)

## �������ӽ���gdb����

ʹ��gdb���Ե�ʱ��gdbֻ�ܸ���һ�����̡�������fork��������֮ǰ��ͨ��ָ������gdb���Թ��߸��ٸ����̻�����ӽ��̡�Ĭ�ϸ��ٸ����̡�

`set follow-fork-mode child`��������gdb��fork֮������ӽ��̡�

`set follow-fork-mode parent`���ø��ٸ�����

ע��һ��Ҫ��fork��������֮ǰ���ò���Ч��

## �ġ�exec�����壺

![exec������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F.png)

![exec������ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E5%8E%9F%E7%90%86.png)

### ʾ��1

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

### ����

![exec��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E7%89%B9%E6%80%A7%EF%BC%881%EF%BC%89.png)
![exec��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/exec%E5%87%BD%E6%95%B0%E6%97%8F%E7%89%B9%E6%80%A7%EF%BC%882%EF%BC%89.png)

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

## �塢�����ӽ���

`ps ajx`�鿴���ӽ���

### 1.�¶����̣�

	�����������ӽ���ֹ���ӽ�����Ϊ���¶����̡����ᱻ init ����������

### 2.��ʬ���̣�

	�ӽ�����ֹ����������δ���ӽ��̽��л��գ��ڴ��ڼ䣬�ӽ��̲�����Դ��PCB��������ں��У���Ϊ����ʬ���̡���  kill ������Ч��


### 3.wait������

	pid_t wait(int *status)

	�������������� ���ս��̵�״̬��

	����ֵ���ɹ��� ���ս��̵�pid

		ʧ�ܣ� -1�� errno
		
	�����̵���wait�������Ի����ӽ����˳���Դ�� ������������һ����

		��������1��	�����ȴ��ӽ����˳�

		��������2��	�����ӽ��̲������ں˵� pcb ��Դ

		��������3��	ͨ�������������õ��ӽ��̽���״̬

	��ȡ�ӽ���������ֵֹ��

		WIFEXITED(status) --�� Ϊ�棬˵��������ֹ --������ WEXITSTATUS(status) --�� �õ� �ӽ��� �˳�ֵ��

	��ȡ�����ӽ����쳣��ֹ�źţ�

		WIFSIGNALED(status) --�� Ϊ�棬˵���쳣��ֹ --������ WTERMSIG(status) --�� �õ� �����ӽ����쳣��ֹ���źű�š�

#### ʾ����ʹ��wait�����ӽ���

### 4.waitpid������	ָ��ĳһ�����̽��л��ա��������÷�������			waitpid(-1, &status, 0) == wait(&status);

	pid_t waitpid(pid_t pid, int *status, int options)

	������
		pid��ָ������ĳһ���ӽ���pid

			> 0: ����ָ��pid���ӽ���

			-1�����������ӽ��̣��൱��wait��

			0�����պ͵�ǰ����waitpidһ����������ӽ���
			
			<-1(�������ȡ��-1003)������ָ���������ڵ������ӽ���

		status���������� ���ս��̵�״̬��

		options��WNOHANG ָ�����շ�ʽΪ������Ϊ������״̬��

	����ֵ��

		> 0 : ��ɹ����յ��ӽ��� pid

		0 : ��������ʱ�� ��3 ָ����WNOHANG�� ���ң�û���ӽ��̽�����

		-1: ʧ�ܡ�errno

	�ܽ᣺

		wait��waitpid	һ�ε��ã�����һ���ӽ��̡�

		����ն����while 

#### ʾ����ʹ��waitpid���ն���ӽ���

#### ��ҵ��������fork3���ӽ��̣������ӽ���һ������ps���һ�������Զ������1����������һ�������Զ������2���δ��󣩡�������ʹ��waitpid�����ӽ��̽��л��ա�
