# �̳߳�

## һ���̳߳�ģ��ԭ�����

![�̳߳�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E6%B1%A0.png)

## �����̳߳������ṹ��

	struct threadpool_t {

	    pthread_mutex_t lock;               /* ������ס���ṹ�� */    
	    pthread_mutex_t thread_counter;     /* ��¼æ״̬�̸߳���de�� -- busy_thr_num */

	    pthread_cond_t queue_not_full;      /* �����������ʱ�����������߳��������ȴ����������� */
	    pthread_cond_t queue_not_empty;     /* ��������ﲻΪ��ʱ��֪ͨ�ȴ�������߳� */

	    pthread_t *threads;                 /* ����̳߳���ÿ���̵߳�tid������ */
	    pthread_t adjust_tid;               /* ������߳�tid */
	    threadpool_task_t *task_queue;      /* �������(�����׵�ַ) */

	    int min_thr_num;                    /* �̳߳���С�߳��� */
	    int max_thr_num;                    /* �̳߳�����߳��� */
	    int live_thr_num;                   /* ��ǰ����̸߳��� */
	    int busy_thr_num;                   /* æ״̬�̸߳��� */
	    int wait_exit_thr_num;              /* Ҫ���ٵ��̸߳��� */

	    int queue_front;                    /* task_queue��ͷ�±� */
	    int queue_rear;                     /* task_queue��β�±� */
	    int queue_size;                     /* task_queue����ʵ�������� */
	    int queue_max_size;                 /* task_queue���п��������������� */

	    int shutdown;                       /* ��־λ���̳߳�ʹ��״̬��true��false */
	};


	typedef struct {

	    void *(*function)(void *);          /* ����ָ�룬�ص����� */
	    void *arg;                          /* ���溯���Ĳ��� */

	} threadpool_task_t;                    /* ��������߳�����ṹ�� */

	rear = 5 % 5

## �����̳߳�ģ�������

	1. main();		

		�����̳߳ء�

		���̳߳���������� �����ص���������

		�����̳߳ء�

	2. pthreadpool_create();

		�����̳߳ؽṹ�� ָ�롣

		��ʼ���̳߳ؽṹ�� {  N ����Ա���� }

		���� N �������̡߳�

		���� 1 ���������̡߳�

		ʧ��ʱ�����ٿ��ٵ����пռ䡣���ͷţ�

	3. threadpool_thread����

		�������̻߳ص�������

		���ղ��� void *arg  --�� pool �ṹ��

		���� --��lock --�� �����ṹ����

		�ж��������� --�� wait  -------------------170

	4. adjust_thread����

		ѭ�� 10 s ִ��һ�Ρ�

		����������̻߳ص�����

		���ղ��� void *arg  --�� pool �ṹ��

		���� --��lock --�� �����ṹ����

		��ȡ�����̳߳�Ҫ�õĵ� ������	task_num, live_num, busy_num

		���ݼȶ��㷨��ʹ������3�������ж��Ƿ�Ӧ�� �����������̳߳��� ָ���������̡߳�

	5. threadpool_add ()

		�ܹ��ܣ�

			ģ���������   num[20]

			���ûص������� ��������  sleep��1�� ��������ɡ�

		�ڲ�ʵ�֣�
	
			����

			��ʼ�� ������нṹ���Ա��   �ص����� function�� arg

			���û��ζ��л��ƣ�ʵ��������� ������βָ��Ų�� % ʵ�֡�

			���������� ���������ϵ��̡߳�
	
			����

	6.  �� 3. �е�wait֮�����ִ�У���������

		����
		
		��ȡ ������ص�������������

		���û��ζ��л��ƣ�ʵ�ִ������� ������ͷָ��Ų�� % ʵ�֡�

		���������� �������� �ϵ� server��

		����

		���� 

		��æ�߳���++

		����

		ִ�д���������߳�

		���� 

		��æ�߳�������

		����

	7. ���� �����߳�

		�������̸߳��� task_num, live_num, busy_num  

		���ݼȶ��㷨��ʹ������3�������ж��Ƿ�Ӧ�� �����������̳߳��� ָ���������̡߳�

		������� ��������

			pthread_create();   �ص� �����̺߳�����		live_num++

		������� ��������

			wait_exit_thr_num = 10;  

			signal �� ���������������ϵ��߳� ���� �����������ź�    

			��ת��  --170 wait�����̻߳ᱻ ���ź� ���ѡ��жϣ� wait_exit_thr_num  > 0 pthread_exit();          
	
## �ġ�ʾ�����̳߳ص�ʵ��
