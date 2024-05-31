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
	
#### ʾ�������ʹ������ݣ�stdout��

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
	
### ʾ������д����ʹ��

## ��������������

**����������  ����ͨ���������ʹ�á� mutex**

![����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pthread_cond_wait%E5%87%BD%E6%95%B0.png)

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


## ʾ����ʹ���ź���ʵ�������ߡ�������ģ��

![�ź���-������������ģ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%87%8F-%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E6%A8%A1%E5%9E%8B.png)



































	

		



























