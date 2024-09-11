# �߳�

## һ���̸߳�����̺��̵߳�����

![�̸߳���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E6%A6%82%E5%BF%B5.png)

* `ps -eLf` �鿴�̺߳ţ�cpu ִ�е���С��λ��

![ps_Lf](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ps_Lf.png)

![��Сִ�е�Ԫ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%9C%80%E5%B0%8F%E6%89%A7%E8%A1%8C%E5%8D%95%E5%85%83.png)

## ����Linux�ں��߳�ʵ��ԭ��

![�߳�ʵ��ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.png)

## ��������ӳ�䣨����ҳ��

	����PCB-->ҳ�棨�ɿ������飬�׵�ַλ��PCB�У�--��ҳ��--��ҳĿ¼������ҳ��--���ڴ浥Ԫ
	
	�ο�����Linux�ں�Դ�����龰������ ---ë�²�
	
![����ӳ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%B8%89%E7%BA%A7%E6%98%A0%E5%B0%84.png)

![�߳�ʵ��ԭ��-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86-2.png)

## �ġ��̹߳�����Դ

![�̹߳�����Դ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%85%B1%E4%BA%AB%E8%B5%84%E6%BA%90.png)

## �塢�̷߳ǹ�����Դ

![�̷߳ǹ�����Դ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E9%9D%9E%E5%85%B1%E4%BA%AB%E8%B5%84%E6%BA%90.png)

## �����߳���ȱ��

![�߳���ȱ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E4%BC%98%E7%BC%BA%E7%82%B9.png)

# �߳̿���ԭ��

## һ��pthread_self����

**�߳�ID��������ʾ�߳���ݵ�id��**

**�̺߳ţ�LWP�����ں��������߳���Ϊ���̿���**

	pthread_t pthread_self(void);	
		
		��ȡ�߳�id�� �߳�id���ڽ��̵�ַ�ռ��ڲ���������ʶ�߳���ݵ�id�š�

		����ֵ�����߳�id��unsigned long���ͣ�



## ����pthread_create����

	int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*start_rountn)(void *), void *arg); //�������̡߳�

		��1�����������������´��������߳� id

		��2���߳����ԡ���NULL��ʹ��Ĭ�����ԡ����߳�״̬����С�����ȼ��ȣ�

		��3�����̻߳ص������������ɹ���ptherad_create��������ʱ���ú����ᱻ�Զ����á�
		
		��4���������������3�Ĳ�����û�еĻ�����NULL

		����ֵ���ɹ���0

			ʧ�ܣ�����errno
		
		����ʱ��Ҫ���붯̬�� -lpthread
			

### ʾ��1��ѭ������N�����̣߳�

```C			
void *tfn(void* arg)
{
        int i = (int)arg;
        sleep(i);
        if(i == 2)
         pthread_exit(NULL);//�˳���ǰ�߳�
        printf("--%dth pthread,pid=%d,tid=%lu\n", i+1,getpid(),pthread_self());
        return NULL;
}
int main(int argc, char* argv[])
{
        int i;
        int ret;
        pthread_t tid;
        for(i=0; i<5; i++)
        {
                ret = pthread_create(&tid,NULL,tfn,(void *)i);// ջ�ǲ�����ģ��� int ���� i�� ǿת�� void *�� ���β���ֵ����
                if(ret != 0)
                {
                        perror("pthread_create error");
                        exit(1);
                }
        }
        sleep(i);
        printf("main,pid=%d,tid=%lu\n", getpid(),pthread_self());
        return 0;
}
```	
			
![ѭ���������߳�-�������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%BE%AA%E7%8E%AF%E5%88%9B%E5%BB%BA%E5%AD%90%E7%BA%BF%E7%A8%8B-%E9%94%99%E8%AF%AF%E5%88%86%E6%9E%90.png)

### ʾ��2���̹߳���ȫ�ֱ���

**�߳�**Ĭ�Ϲ���**���ݶ�**��**�����**�ȵ�ַ�ռ䣬���õ���**ȫ�ֱ���**��

���̲�����ȫ�ֱ�����ֻ�ܽ���mmap

```C
int var = 100;
void* ftn(void* arg)
{
        printf("child,pid=%d, tid=%lu, var=%d\n", getpid(),pthread_self(),var);
        var = 200;
        pthread_exit(NULL);
}
int main(int argc, char* argv[])
{
        pthread_t tid;
        int ret;

        ret = pthread_create(&tid,NULL,ftn,NULL);
        if(ret!=0)
        {
                perror("pthread_create error");
                exit(1);
        }
        sleep(1);
        printf("main,var = %d\n",var);//ȫ�ֱ�������
        return 0;
}

```

## ����pthread_exit����

	void pthread_exit(void *retval);  �˳���ǰ�̡߳�

		retval���������������˳�ֵ�������̣߳�ͨ����NULL��
		
	�����˳�������

		exit();	�˳���ǰ���̡�//exit(0)��ʾ�����˳�

		return: ���ص���������������ȥ��

		pthread_exit(): �˳���ǰ�̡߳�
	
��ע�⡿
		
1. ���̻߳����У�Ӧ**������ʹ��**exit������Ӧ��ʹ��pthread_exit������
		
2. �����߳�δ���������߳�**����return��exit**��
		
**���ر�ע�⡿** �����߳���ʹ��pthread_exit��return���ص�ָ����ָ���**�ڴ浥Ԫ**������ȫ�ֵĻ���malloc����ģ��������̺߳�����ջ�Ϸ��䣬��Ϊ�������̵߳õ��������ָ��ʱ���̺߳����Ѿ��˳��ˡ�


## �ġ�pthread_join����

	int pthread_join(pthread_t thread, void **retval); //�����ȴ��������̣߳���ȡ�߳��˳�״̬��

		thread: �����������������յ��߳�id

		retval�������������� ���յ����̵߳�return�˳�ֵ��

			�߳��쳣������ֵΪ -1��

		����ֵ���ɹ���0

			ʧ�ܣ�errno
			
### ʾ��1��pthread_join������ʹ�ü�ע������

```C
//pthread_join.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

struct thrd {
    int var;
    char str[256];
};

void sys_err(const char *str)
{
	perror(str);
	exit(1);
}
/*
void *tfn(void *arg)
{
    struct thrd *tval;

    tval = malloc(sizeof(tval));//1���ڶ�����������
    tval->var = 100;
    strcpy(tval->str, "hello thread");

    return (void *)tval;
}
*/
/*
void *tfn(void *arg)
{
     struct thrd tval;              //2���ֲ�������ַ,����������ֵ

    tval.var = 100;
    strcpy(tval.str, "hello thread");

    return (void *)&tval;
}
*/ 
void *tfn(void *arg)
{
    struct thrd *tval = (struct thrd *)arg;

    tval->var = 100;
    strcpy(tval->str, "hello thread");

    return (void *)tval;
}

int main(int argc, char *argv[])
{
    pthread_t tid;

    struct thrd arg;//3��������main������������
    struct thrd *retval;

    int ret = pthread_create(&tid, NULL, tfn, (void *)&arg);
    if (ret != 0)
        sys_err("pthread_create error");

    //int pthread_join(pthread_t thread, void **retval);
    ret = pthread_join(tid, (void **)&retval);
    if (ret != 0)
        sys_err("pthread_join error");

    printf("child thread exit with var= %d, str= %s\n", retval->var, retval->str);
    
    pthread_exit(NULL);

}
```
### ʾ��2��ʹ��pthread_join������ѭ�������Ķ�����̻߳��գ�ʹ�����飩

```C
//pthrd_loop_join.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int var = 100;

void *tfn(void *arg)
{
    int i;
    i = (int)arg;
    
    sleep(i);
    if (i == 1) {
        var = 333;
        printf("var = %d\n", var);
        return (void *)var;

    } else  if (i == 3) {
        var = 777;
        printf("I'm %dth pthread, pthread_id = %lu\n var = %d\n", i+1, pthread_self(), var);
        pthread_exit((void *)var);

    } else  {
        printf("I'm %dth pthread, pthread_id = %lu\n var = %d\n", i+1, pthread_self(), var);
        pthread_exit((void *)var);
    }

    return NULL;
}

int main(void)
{
    pthread_t tid[5];
    int i;
    int *ret[5];  

    for (i = 0; i < 5; i++)
        pthread_create(&tid[i], NULL, tfn, (void *)i);

    for (i = 0; i < 5; i++) {
        pthread_join(tid[i], (void **)&ret[i]);
        printf("-------%d 's ret = %d\n", i, (int)ret[i]);
    }
        
    printf("I'm main pthread tid = %lu\t var = %d\n", pthread_self(), var);

    sleep(i);
    return 0;
}
```


## �塢pthread_detach����

	int pthread_detach(pthread_t thread);		�����̷߳���

		thread: ��������߳�id

		����ֵ���ɹ���0

			ʧ�ܣ�errno	--- �̱߳���ֱ�ӷ��ش���ţ�����ʹ��perror����ʹ��strerror������

	��1���̷߳���״̬��ָ����״̬���߳����������̶߳Ͽ���ϵ���߳̽��������˳�״̬���������̻߳�ȡ����ֱ���Լ��Զ��ͷš����硢���̷߳��������á�

	��2���������иû��ƣ������������ʬ���̡���ʬ���̵Ĳ�����Ҫ���ڽ������󣬴󲿷���Դ���ͷţ�һ�������Դ�Դ���ϵͳ�أ������ں���Ϊ�ý����Դ��ڡ�

	��3��Ҳ��ʹ��`pthread_create`�����Ĳ�2���߳����ԣ��������̷߳��롣

	��4�����ܶ�һ���Ѿ�����detach״̬���̵߳���`pthread_join`�������ĵ��ý�����`EINVAL`��Ч����
	
	��5��ʹ��pthread_join����ʧ�ܣ�˵������ɹ�
	
### ʾ����pthread_detach��ʹ��

```C
//pthread_detach.c
void *tfn(void *arg)
{
    printf("thread: pid = %d, tid = %lu\n", getpid(), pthread_self());

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid;

    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_detach(tid);              // �����̷߳���` �߳���ֹ,���Զ�����pcb,�������
    if (ret != 0) {
        fprintf(stderr, "pthread_detach error: %s\n", strerror(ret));
        exit(1);
    }

    sleep(1);

    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(1);
    }

    printf("main: pid = %d, tid = %lu\n", getpid(), pthread_self());

    pthread_exit((void *)0);
}
```

## ����pthread_cancel����

	int pthread_cancel(pthread_t thread);//ɱ��һ���̡߳�

		thread: ��ɱ�����߳�id
		
		����ֵ���ɹ���0���ɹ��� pthread_cancel()ɱ�����̣߳��޷�ʹ��pthread_join���գ����� #define PTHREAD_CANDELED ((void *)-1)����ʾ��������������ʹ��pthead_join ����

			ʧ�ܣ�errno
			
	ע�⣺
	
		��1���̵߳�ȡ��������ʵʱ�ģ�����һ������ʱ����Ҫ�ȴ��̵߳���ĳ��ȡ���㣨���㣩����������߳�û�е���ȡ���㣬 ��ô pthread_cancel ��Ч��
	
		��2��** �ɴ�����Ϊһ��ϵͳ���ã������ںˣ���Ϊһ��ȡ���㡣
	
		��3�����ǿ����ڳ����У��ֶ����һ��ȡ���㡣ʹ�� pthread_testcancel();

### ʾ����pthread_cancel��ʹ��

```C
//pthread_cancel.c
void* ftn(void* arg)
{
        while(1)
        {
                printf("child,tid=%lu\n", pthread_self());
                sleep(1);
                pthread_testcancel();//����ʹ������������в��ԣ����ں�
        }
}

int main(int argc, char* argv[])
{
        pthread_t tid;
        int ret;
        ret = pthread_create(&tid,NULL,ftn,NULL);
        if(ret != 0)
        {
                fprintf(stderr,"pthread_create err:%s",strerror(ret));
        }
        sleep(5);
        ret = pthread_cancel(tid);//��Ҫ����һ��ȡ�������ɱ���߳�,���ں�
        if(ret != 0)
        {
                fprintf(stderr, "pthread_cancel err:%s", strerror(ret));
        }
         pthread_join(tid,&tret);
         printf("pthread_join,tret=%d\n",(int)tret);//cancel���޷�ʹ��join���գ�����-1

        return 0;
}
```

## �ߡ������󷵻�
		
	�������أ��߳��У�ֻ��ʹ��strerror��������Ϊ�̺߳����Ƿ���errno������������errno��

	fprintf(stderr, "xxx error: %s\n", strerror(ret));

## �ˡ����̺��߳̿���ԭ��Ա�

| �߳̿���ԭ�� | ���̿���ԭ�� | ��; |
|--|--|--|
| pthread_create()|fork();|����|
|pthread_self()|getpid();|��ȡ|
|pthread_exit()|exit()/return|�˳�|
|pthread_join()|wait()/waitpid()|����|
|pthread_cancel()|kill()|ɱ��|
|pthread_detach()| |����|
	

## �š������߳����ԣ�ͨ�������������ԣ�

![�߳�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%B1%9E%E6%80%A7.png)

	pthread_attr_t attr  	����һ���߳����Խṹ�����

	pthread_attr_init(pthread_attr_t *attr);	��ʼ���߳�����
	
	pthread_attr_getdetachstate(pthread_attr_t *attr, int detachstate);//��ȡ�߳�����

	pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);//�����߳�����
	
	detachstate:
		
		PTHREAD_CREATE_DETACHED--�����߳�
		
		PTHREAD_CREATE_JOINABLE--�Ƿ����̣߳�Ĭ�ϣ�
	
	pthread_create(&tid, &attr, tfn, NULL); �����޸ĺ�� �����߳����� ����Ϊ����̬�����߳�

	pthread_attr_destroy(pthread_attr_t *attr);	�����߳�����

### ʾ����pthread_create�з������Ե�ʹ��

```C
//pthrd_attr_detach.c
void *tfn(void *arg)
{
    printf("thread: pid = %d, tid = %lu\n", getpid(), pthread_self());

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid;

    pthread_attr_t attr;

    int ret = pthread_attr_init(&attr);
    if (ret != 0) {
        fprintf(stderr, "attr_init error:%s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);      // �����߳�����Ϊ ��������
    if (ret != 0) {
        fprintf(stderr, "attr_setdetachstate error:%s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid, &attr, tfn, NULL);
    if (ret != 0) {
        perror("pthread_create error");
    }

    ret = pthread_attr_destroy(&attr);
    if (ret != 0) {
        fprintf(stderr, "attr_destroy error:%s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_join error:%s\n", strerror(ret));
        exit(1);
    }

    printf("main: pid = %d, tid = %lu\n", getpid(), pthread_self());

    pthread_exit((void *)0);
}

```

**�߳�ͬ�����⣺** �������һ���߳�Ϊ**�����߳�**��������߳������ַǳ��죬��������pthread_create��������֮ǰ����ֹ�ˣ�����ֹ֮����ܽ��̺߳ź�ϵͳ��Դ�ƽ����������߳�ʹ�ã���������pthread_create���߳̾͵õ��˴�����̺߳š�Ҫ��������������Բ�ȡһ����ͬ����ʩ����򵥵ķ���֮һ�ǿ����ڱ��������߳������`pthread_cond_timedwait`����������һ�εȴ�ʱ�䣬���ڶ��̱߳���ﳣ�õķ�������ע�ⲻҪʹ������wait()֮��ĺ�����������ʹ��������˯�ߣ������ܽ���߳�ͬ�������⡣

## ʮ���߳�ʹ��ע������

![�߳�ʹ��ע������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E4%BD%BF%E7%94%A8%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9.png)
![���߳�fork����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%9A%E7%BA%BF%E7%A8%8B%E4%BD%BF%E7%94%A8fork%E5%88%9B%E5%BB%BA%E8%BF%9B%E7%A8%8B.png)

	