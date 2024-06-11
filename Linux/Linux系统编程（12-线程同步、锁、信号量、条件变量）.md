# �߳�ͬ����

	Эͬ�������Թ����������ݰ�����ʡ���ֹ���ݻ��ң�������ʱ���йصĴ���

**���ݻ��ҵ�ԭ��**

![���ݻ��ҵ�ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%95%B0%E6%8D%AE%E6%B7%B7%E4%B9%B1%E5%8E%9F%E5%9B%A0.png)

## һ��������/������mutex

![�߳�ͬ������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%90%8C%E6%AD%A5%E5%92%8C%E9%94%81.png)

### 1. ��������Эͬ������

	�������ݽ��б����������̡߳�Ӧ�á��ڷ��ʹ�������ǰ�������ٷ��ʡ������������߱�ǿ���ԡ�

![������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%BB%BA%E8%AE%AE%E9%94%81.png)


### 2. ��������ʹ�ò��裺

![��������ʹ�ò���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BA%92%E6%96%A5%E9%94%81%E7%9A%84%E4%BD%BF%E7%94%A8.png)

	��ʼ����������

		pthread_mutex_t mutex;

		1. pthread_mutex_init(&mutex, NULL);   			��̬��ʼ����

		2. pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	��̬��ʼ����

**restrict�ؼ��֣�**

	�����޶�ָ����������ùؼ����޶���ָ�������ָ����ڴ������ֻ���ɱ�ָ����ɡ�

### 3. ʹ������ע�����

	������֤�������ȣ� ԽСԽ�á������ʹ�������ǰ�����������ʽ�������������������

	�������������ǽṹ�塣 ���Կ��������� ��ʼ��ʱֵΪ 1����pthread_mutex_init() �������óɹ�����

		lock������ --������ �����̡߳�

		unlock������ ++������ �������������ϵ��̡߳�

		try�������Լ������ɹ�--��ʧ��ֱ�ӷ��أ�ͬʱ���ô���� EBUSY����������

### 4. ������

	��ʹ������ǡ�����µ�����

		1. �߳���ͼ��ͬһ��������A�������Ρ�

		2. �߳�1ӵ��A����������B�����߳�2ӵ��B����������A����

![����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%AD%BB%E9%94%81.png)

#### ʾ�������ʹ������ݣ�stdout��

```C
//pthrd_shared.c
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *tfn(void *arg)
{
    srand(time(NULL));

    while (1) {
        pthread_mutex_lock(&mutex);
        printf("hello ");
        sleep(rand() % 3);	/*ģ�ⳤʱ�����������Դ������cpu������������ʱ���йصĴ���*/
        printf("world\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);//��֤��������ԽСԽ�ã������ʽ�������������
    }

    return NULL;
}

int main(void)
{
    pthread_t tid;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid, NULL, tfn, NULL);
    while (1) {

        pthread_mutex_lock(&mutex);
        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);

    }
    pthread_join(tid, NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}
```

## ������д����

* ��ֻ��һ�ѡ��Զ���ʽ�����ݼ���������������д��ʽ�����ݼ�������д����

* ������д��ռ��

* д�����ȼ��ߡ�

* ����ڻ��������ԣ������̶߳��ʱ����߷���Ч��

![��д��ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%AF%BB%E5%86%99%E9%94%81%E5%8E%9F%E7%90%86.png)

![��д������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%AF%BB%E5%86%99%E9%94%81%E7%89%B9%E6%80%A7.png)

	pthread_rwlock_t  rwlock;����

	pthread_rwlock_init(&rwlock, NULL);

	pthread_rwlock_rdlock(&rwlock);		

	pthread_rwlock_wrlock(&rwlock);		
	
	pthread_rwlock_tryrdlock(&rwlock);		

	pthread_rwlock_trywrlock(&rwlock);		

	pthread_rwlock_unlock(&rwlock);

	pthread_rwlock_destroy(&rwlock);
	
### ʾ����3���̲߳���ʱ "д" ȫ����Դ��5���̲߳���ʱ "��" ͬһȫ����Դ

```C
//rwlock.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int counter;                          //ȫ����Դ
pthread_rwlock_t rwlock;

void *th_write(void *arg)
{
    int t;
    int i = (int)arg;

    while (1) {
        t = counter;                    // ����д֮ǰ��ֵ
        usleep(1000);

        pthread_rwlock_wrlock(&rwlock);
        printf("=======write %d: %lu: counter=%d ++counter=%d\n", i, pthread_self(), t, ++counter);
        pthread_rwlock_unlock(&rwlock);

        usleep(9000);               // �� r ���ṩ����
    }
    return NULL;
}

void *th_read(void *arg)
{
    int i = (int)arg;

    while (1) {
        pthread_rwlock_rdlock(&rwlock);
        printf("----------------------------read %d: %lu: %d\n", i, pthread_self(), counter);
        pthread_rwlock_unlock(&rwlock);

        usleep(2000);                // ��д���ṩ����
    }
    return NULL;
}

int main(void)
{
    int i;
    pthread_t tid[8];

    pthread_rwlock_init(&rwlock, NULL);

    for (i = 0; i < 3; i++)
        pthread_create(&tid[i], NULL, th_write, (void *)i);

    for (i = 0; i < 5; i++)
        pthread_create(&tid[i+3], NULL, th_read, (void *)i);

    for (i = 0; i < 8; i++)
        pthread_join(tid[i], NULL);

    pthread_rwlock_destroy(&rwlock);            //�ͷŶ�д��

    return 0;
}
```

## ��������������

**����������  ����ͨ���������ʹ�á� mutex**

![pthread_cond_wait����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pthread_cond_wait%E5%87%BD%E6%95%B0.png)

	pthread_cond_t cond;//����

	��ʼ������������

		1. pthread_cond_init(&cond, NULL);   			��̬��ʼ����

		2. pthread_cond_t cond = PTHREAD_COND_INITIALIZER;	��̬��ʼ����

	�����ȴ�������

		3. pthread_cond_wait(&cond, &mutex);

		���ã�	1�� �����ȴ�������������

			2�� �����Ѿ������ɹ����ź��� ���൱�� pthread_mutex_unlock(&mutex)��
			
		ע��1��2����Ϊһ��ԭ�Ӳ���

			3)  ���������㣬��������ʱ�����¼����ź��� ���൱�ڣ� pthread_mutex_lock(&mutex);��

		4. pthread_cond_timedwait()�������ó�ʱ

	5. pthread_cond_signal(): �������������������ϵ� (����)һ���̡߳�

	6. pthread_cond_broadcast()�� �������������������ϵ� �����̡߳�
	
	7. pthread_cond_destroy(&cond)��������������
 
### ʾ����ʹ������������������ߡ����������ģ��

![��������-������/������ģ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%9D%A1%E4%BB%B6%E5%8F%98%E9%87%8F-%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E6%A8%A1%E5%9E%8B.png)

```C
//������������ģ�� ������-����������
//pthread_cond_produce_consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void err_thread(int ret, char *str)
{
    if (ret != 0) {
        fprintf(stderr, "%s:%s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

struct msg {
    int num;
    struct msg *next;
};

struct msg *head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      // ����/��ʼ��һ��������
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;      // ����/��ʼ��һ����������

void *produser(void *arg)
{
    while (1) {
        struct msg *mp = malloc(sizeof(struct msg));

        mp->num = rand() % 1000 + 1;                        // ģ������һ������`
        printf("--produce %d\n", mp->num);

        pthread_mutex_lock(&mutex);                         // ���� ������
        mp->next = head;                                    // д��������
        head = mp;
        pthread_mutex_unlock(&mutex);                       // ���� ������

        pthread_cond_signal(&has_data);                     // ������������������ has_data�ϵ��߳�.

        sleep(rand() % 3);
    }

    return NULL;
}

void *consumer(void *arg)
{
    while (1) {
        struct msg *mp;

        pthread_mutex_lock(&mutex);                         // ���� ������
        while (head == NULL) {															// ע����������ߣ�������Ҫʹ��while������ʹ��if
            pthread_cond_wait(&has_data, &mutex);           // �����ȴ���������, ����
        }                                                   // pthread_cond_wait ����ʱ, ���¼��� mutex

        mp = head;																					//����������
        head = mp->next;

        pthread_mutex_unlock(&mutex);                       // ���� ������
        printf("---------consumer id: %lu :%d\n", pthread_self(), mp->num);

        free(mp);
        sleep(rand()%3);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t pid, cid;

    srand(time(NULL));

    ret = pthread_create(&pid, NULL, produser, NULL);           // ������
    if (ret != 0) 
        err_thread(ret, "pthread_create produser error");

    ret = pthread_create(&cid, NULL, consumer, NULL);           // ������
    if (ret != 0) 
        err_thread(ret, "pthread_create consuer error");
    ret = pthread_create(&cid, NULL, consumer, NULL);           // ������
    if (ret != 0) 
        err_thread(ret, "pthread_create consuer error");
    ret = pthread_create(&cid, NULL, consumer, NULL);           // ������
    if (ret != 0) 
        err_thread(ret, "pthread_create consuer error");

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}
```


## �ġ��ź����� 

* Ӧ�����̡߳����̼�ͬ�������ܱ�֤ͬ�������ݲ����ң���������̲߳�������

* �൱�� ��ʼ��ֵΪ N �Ļ�������  Nֵ����ʾ����ͬʱ���ʹ������������߳�����

![�ź�������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%87%8F-%E5%87%BD%E6%95%B0.png)
	
	sem_t sem;	�������͡�

	int sem_init(sem_t *sem, int pshared, unsigned int value);

	������
		sem�� �ź��� 

		pshared��	0�� �����̼߳�ͬ��
				
				1�� ���ڽ��̼�ͬ��

		value��Nֵ����ָ��ͬʱ���ʵ��߳�����

	sem_destroy();

	sem_wait();		һ�ε��ã���һ��-- ������ ���ź�����ֵΪ 0 ʱ���ٴ� -- �ͻ������� ���Ա� pthread_mutex_lock��

	sem_post();		һ�ε��ã���һ��++ ����. ���ź�����ֵΪ N ʱ, �ٴ� ++ �ͻ����������Ա� pthread_mutex_unlock��

	sem_timewait(sem_t *sem, const struct timespec* abs_timeout);
		
			//abs_timeout ���õ��Ǿ���ʱ�䡣
			
		��ʱ1�룺
		
			time_t cur = time(NULL);��ȡ��ǰʱ�䣨���ʱ�䣩

			struct timespec t;����timespec�ṹ�����t
			
			t.tv_sec = cur + 1;��ʱ1��
			
			t.tv_nsec = t.tv_sec+100;
		
			sem_timedwait(&sem, &t);����
			
## ʾ����ʹ���ź���ʵ�������ߡ�������ģ��

![�ź���-������������ģ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%87%8F-%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E6%A8%A1%E5%9E%8B.png)


```C
//sem_product_consumer.c
/*�ź���ʵ�� ������ ����������*/

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define NUM 5               

int queue[NUM];                                     //ȫ������ʵ�ֻ��ζ���
sem_t blank_number, product_number;                 //�ո����ź���, ��Ʒ�ź���

void *producer(void *arg)
{
    int i = 0;

    while (1) {
        sem_wait(&blank_number);                    //�����߽��ո�����--,Ϊ0�������ȴ�
        queue[i] = rand() % 1000 + 1;               //����һ����Ʒ
        printf("----Produce---%d\n", queue[i]);        
        sem_post(&product_number);                  //����Ʒ��++

        i = (i+1) % NUM;                            //�����±�ʵ�ֻ���
        sleep(rand()%1);
    }
}

void *consumer(void *arg)
{
    int i = 0;

    while (1) {
        sem_wait(&product_number);                  //�����߽���Ʒ��--,Ϊ0�������ȴ�
        printf("-Consume---%d\n", queue[i]);
        queue[i] = 0;                               //����һ����Ʒ 
        sem_post(&blank_number);                    //���ѵ��Ժ�,���ո�����++

        i = (i+1) % NUM;
        sleep(rand()%3);
    }
}

int main(int argc, char *argv[])
{
    pthread_t pid, cid;

    sem_init(&blank_number, 0, NUM);                //��ʼ���ո����ź���Ϊ5, �̼߳乲�� -- 0
    sem_init(&product_number, 0, 0);                //��Ʒ��Ϊ0

    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}

```

































	

		



























