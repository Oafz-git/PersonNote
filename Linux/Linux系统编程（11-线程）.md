# �߳�

## һ���̸߳��

![�̸߳���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E6%A6%82%E5%BF%B5.png)

* `ps -Lf` �鿴�̺߳ţ�cpu ִ�е���С��λ��

![ps_Lf](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ps_Lf.png)

![��Сִ�е�Ԫ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%9C%80%E5%B0%8F%E6%89%A7%E8%A1%8C%E5%8D%95%E5%85%83.png)

## ����Linux�ں��߳�ʵ��ԭ��

![�߳�ʵ��ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.png)

## ��������ӳ�䣨����ҳ��

	����PCB-->ҳĿ¼���ɿ������飬�׵�ַλ��PCB�У�--��ҳ��--��ҳĿ¼������ҳ��--���ڴ浥Ԫ
	
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

		��1���������������´��������߳� id

		��2���߳����ԡ���NULL��ʹ��Ĭ�����ԡ����߳�״̬����С�����ȼ��ȣ�

		��3�����̻߳ص������������ɹ���ptherad_create��������ʱ���ú����ᱻ�Զ����á�
		
		��4����3�Ĳ�����û�еĻ�����NULL

		����ֵ���ɹ���0

			ʧ�ܣ�����errno
			

### ʾ��1��ѭ������N�����̣߳�

		for ��i = 0�� i < 5; i++��

			pthread_create(&tid, NULL, tfn, (void *)i);   // �� int ���� i�� ǿת�� void *�� ���β���ֵ����

![ѭ���������߳�-�������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%BE%AA%E7%8E%AF%E5%88%9B%E5%BB%BA%E5%AD%90%E7%BA%BF%E7%A8%8B-%E9%94%99%E8%AF%AF%E5%88%86%E6%9E%90.png)

### ʾ��2���̹߳���ȫ�ֱ���

**�߳�Ĭ�Ϲ������ݶΡ�����εȵ�ַ�ռ䣬���õ���ȫ�ֱ�����**

**���̲�����ȫ�ֱ�����ֻ�ܽ���mmap**


## ����pthread_exit����

	void pthread_exit(void *retval);  �˳���ǰ�̡߳�

		retval���˳�ֵ�������̣߳�ͨ����NULL��
		
	�����˳�������

		exit();	�˳���ǰ���̡�//exit(0)��ʾ�����˳�

		return: ���ص���������������ȥ��

		pthread_exit(): �˳���ǰ�̡߳�
	
	ע�⣺
		
		��1�����̻߳����У�Ӧ������ʹ��exit������Ӧ��ʹ��pthread_exit������
		
		��2�������߳�δ���������̲߳���return��exit��
		
		��3�������߳���ʹ��pthread_exit��return���ص�ָ����ָ����ڴ浥Ԫ������ȫ�ֵĻ���malloc����ģ��������̺߳�����ջ�Ϸ��䣬��Ϊ�������̵߳õ��������ָ��ʱ���̺߳����Ѿ��˳��ˡ�

### ʾ����exit��return��pthread_exit������

## �ġ�pthread_join����

	int pthread_join(pthread_t thread, void **retval); //�����ȴ��������̣߳���ȡ�߳��˳�״̬��

		thread: �����յ��߳�id

		retval������������ ���յ��Ǹ��̵߳��˳�ֵ��

			�߳��쳣������ֵΪ -1��

		����ֵ���ɹ���0

			ʧ�ܣ�errno
			
### ʾ��1��pthread_join������ʹ�ü�ע������

### ʾ��2��ʹ��pthread_join������ѭ�������Ķ�����̻߳��գ�ʹ�����飩

## �塢pthread_detach����

	int pthread_detach(pthread_t thread);		�����̷߳���

		thread: ��������߳�id

		����ֵ���ɹ���0

			ʧ�ܣ�errno	

	��1���̷߳���״̬��ָ����״̬���߳����������̶߳Ͽ���ϵ���߳̽��������˳�״̬���������̻߳�ȡ����ֱ���Լ��Զ��ͷš����硢���̷߳��������á�

	��2���������иû��ƣ������������ʬ���̡���ʬ���̵Ĳ�����Ҫ���ڽ������󣬴󲿷���Դ���ͷţ�һ�������Դ�Դ���ϵͳ�أ������ں���Ϊ�ý����Դ��ڡ�

	��3��Ҳ��ʹ��`pthread_create`�����Ĳ�2���߳����ԣ��������̷߳��롣

	��4�����ܶ�һ���Ѿ�����detach״̬���̵߳���`pthread_join`�������ĵ��ý�����`EINVAL`��Ч����
	
	��5��ʹ��pthread_join����ʧ�ܣ�˵������ɹ�

## ����pthread_cancel����

	int pthread_cancel(pthread_t thread);//ɱ��һ���̡߳�

		thread: ��ɱ�����߳�id
		
		����ֵ���ɹ���0���ɹ��� pthread_cancel()ɱ�����̣߳����� #define PTHREAD_CANDELED ((void *)-1)����ʾ��������������ʹ��pthead_join ����

			ʧ�ܣ�errno
			
	ע�⣺
	
		��1���̵߳�ȡ��������ʵʱ�ģ�����һ������ʱ����Ҫ�ȴ��̵߳���ĳ��ȡ���㣨���㣩����������߳�û�е���ȡ���㣬 ��ô pthread_cancel ��Ч��
	
		��2���ɴ�����Ϊһ��ϵͳ���ã������ںˣ���Ϊһ��ȡ���㡣
	
		��3�����ǿ����ڳ����У��ֶ����һ��ȡ���㡣ʹ�� pthread_testcancel();
		
### ʾ�����̵߳������˳��Ա�

## �ߡ������󷵻�
		
	�������أ�  �߳��У�ֻ��ʹ��strerror����

	fprintf(stderr, "xxx error: %s\n", strerror(ret));

## �ˡ����̺��߳̿���ԭ��Ա�

| �߳̿���ԭ�� | ���̿���ԭ�� |
|--|--|
| pthread_create()|fork();|
|pthread_self()|getpid();|
|pthread_exit()|exit();    /return| 
|pthread_join()|wait()/waitpid()|
|pthread_cancel()|kill()|
|pthread_detach()|
	

## �š������߳����ԣ�ͨ�������������ԣ�

![�߳�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%B1%9E%E6%80%A7.png)


	���÷������ԡ�

	pthread_attr_t attr  	����һ���߳����Խṹ�����

	pthread_attr_init(pthread_attr_t *attr);	��ʼ���߳�����
	
	pthread_attr_getdetachstate(pthread_attr_t *attr, int detachstate);//��ȡ�߳�����

	pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);//�����߳�����
	
	detachstate:
		
		PTHREAD_CREATE_DETACHED--�����߳�
		
		PTHREAD_CREATE_JOINABLE--�Ƿ����̣߳�Ĭ�ϣ�
	
	pthread_create(&tid, &attr, tfn, NULL); �����޸ĺ�� �����߳����� ����Ϊ����̬�����߳�

	pthread_attr_destroy(pthread_attr_t *attr);	�����߳�����


**�߳�ͬ�����⣺** �������һ���߳�Ϊ**�����߳�**��������߳������ַǳ��죬��������pthread_create��������֮ǰ����ֹ�ˣ�����ֹ֮����ܽ��̺߳ź�ϵͳ��Դ�ƽ����������߳�ʹ�ã���������pthread_create���߳̾͵õ��˴�����̺߳š�Ҫ��������������Բ�ȡһ����ͬ����ʩ����򵥵ķ���֮һ�ǿ����ڱ��������߳������`pthread_cond_timewait`����������һ�εȴ�ʱ�䣬���ڶ��̱߳���ﳣ�õķ�������ע�ⲻҪʹ������wait()֮��ĺ�����������ʹ��������˯�ߣ������ܽ���߳�ͬ�������⡣

## ʮ���߳�ʹ��ע������

![�߳�ʹ��ע������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E4%BD%BF%E7%94%A8%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9.png)


	