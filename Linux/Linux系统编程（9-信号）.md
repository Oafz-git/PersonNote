# �ź�

## һ���źŵĸ���

### 1.�źŹ��ԣ�

	�򵥡�����Я��������Ϣ�����������ŷ��͡�

### 2.�źŵ����ʣ�

	�ź�����������ϵġ��жϡ���һ���źŲ��������۳���ִ�е�ʲôλ�ã���������ֹͣ���У������źţ�����������ټ���ִ�к���ָ�

**�����źŵĲ���������ȫ�������ɡ��ںˡ���ɵġ�**

### 3.�ź���صĸ��

* **�����źţ�**

![�����ź�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BA%A7%E7%94%9F%E4%BF%A1%E5%8F%B7.png)

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

![�ź�һ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-1.png)
![�ź�һ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-2.png)
![�ź�һ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E4%B8%80%E8%A7%88%E8%A1%A8-3.png)

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

![killȨ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/kill%E6%9D%83%E9%99%90.png)

#### ʾ����ѭ������5���ӽ��̣���������kill������ֹ����һ�ӽ���

```C++

```

### 2.������������ź�

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

#### ʾ����ʹ��alarm���������1s�������ٸ���

```C

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

####ʾ����ʹ��setitimer����ʵ��alarm�������ظ������1����������

```C
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

```

## �ġ��źŲ�׽

### 1.signal()����
	
**ע��**һ���źŲ�׽�������ú�����ANSI���壬������ʷԭ���ڲ�ͬ�汾��UNIX�Ͳ�ͬ�汾��LINUX�п����в�ͬ����Ϊ��Ӧ��������ʹ������

![signal����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/signal%E5%87%BD%E6%95%B0.png)	

#### ʾ����signal������ʹ��

```C

```

### 2.sigaction()���� �ص㣡����

![sigaction����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/sigaction%E5%87%BD%E6%95%B0.png)

	������
		act������������µĴ���ʽ
		
		oldact�������������ɵĴ���ʽ

![struct_sigaction](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_sigaction.png)

	sa_handler��ָ���źŲ�׽��Ĵ�����������ע�ắ������Ҳ�ɸ�ֵΪSIG_IGN������ԣ���SIG_DFL����ִ��Ĭ�϶�����
	
	sa_mask�������źŴ�����ʱ����Ҫ���ε��źż��ϣ��ź������֣���ע�⣺���ڴ������������ڼ�������Ч������ʱ�����á�
	
	sa_flags��
		
		ͨ������Ϊ0����ʹ��Ĭ�����ԡ�
		
		���ñ��ź��жϺ�ϵͳ�����Ƿ�������SA_INTERRURT��������SA_RESTART������
		
		����ΪSA_NODEFER����ʾ��ִ�в�׽�����ڼ䣬��ϣ���Զ��������źţ�����sa_mask�а������źš�

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

	�ӽ��̽������У��丸���̻��յ�SIGCHLD�źš����źŵ�Ĭ�ϴ������Ǻ��ԡ����Բ�׽���źţ��ڲ�׽����������ӽ���״̬�Ļ���

```C

```

### 6.�ж�ϵͳ���ã��˽⣩

![�ж�ϵͳ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%B8%AD%E6%96%AD%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8.png)

	




























