# 线程同步：

	协同步调，对公共区域数据按序访问。防止数据混乱，产生与时间有关的错误。

**数据混乱的原因**

![数据混乱的原因](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%95%B0%E6%8D%AE%E6%B7%B7%E4%B9%B1%E5%8E%9F%E5%9B%A0.png)

## 一、互斥锁/互斥量mutex

![线程同步和锁](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%90%8C%E6%AD%A5%E5%92%8C%E9%94%81.png)

### 1. 建议锁（协同锁）：

	公共数据进行保护。所有线程【应该】在访问公共数据前先拿锁再访问。但，锁本身不具备强制性。

![建议锁](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%BB%BA%E8%AE%AE%E9%94%81.png)


### 2. 互斥锁的使用步骤：

![互斥锁的使用步骤](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BA%92%E6%96%A5%E9%94%81%E7%9A%84%E4%BD%BF%E7%94%A8.png)

	初始化互斥量：

		pthread_mutex_t mutex;

		1. pthread_mutex_init(&mutex, NULL);   			动态初始化。

		2. pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	静态初始化。

**restrict关键字：**

	用来限定指针变量。被该关键字限定的指针变量所指向的内存操作，只能由本指针完成。
	
#### 示例：访问共享数据（stdout）

### 3. 使用锁的注意事项：

	尽量保证锁的粒度， 越小越好。（访问共享数据前，加锁。访问结束【立即】解锁。）

	互斥锁，本质是结构体。 可以看成整数。 初始化时值为 1。（pthread_mutex_init() 函数调用成功。）

		lock加锁： --操作， 阻塞线程。

		unlock解锁： ++操作， 换醒阻塞在锁上的线程。

		try锁：尝试加锁，成功--。失败直接返回，同时设置错误号 EBUSY，不阻塞。

### 4. 死锁：

	是使用锁不恰当导致的现象：

		1. 线程视图对同一个互斥量A加锁两次。

		2. 线程1拥有A锁，请求获得B锁；线程2拥有B锁，请求获得A锁。

![死锁](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%AD%BB%E9%94%81.png)

## 二、读写锁：

* 锁只有一把。以读方式给数据加锁——读锁。以写方式给数据加锁——写锁。

* 读共享，写独占。

* 写锁优先级高。

* 相较于互斥量而言，当读线程多的时候，提高访问效率

![读写锁原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%AF%BB%E5%86%99%E9%94%81%E5%8E%9F%E7%90%86.png)

![读写锁特性](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%AF%BB%E5%86%99%E9%94%81%E7%89%B9%E6%80%A7.png)

	pthread_rwlock_t  rwlock;类型

	pthread_rwlock_init(&rwlock, NULL);

	pthread_rwlock_rdlock(&rwlock);		

	pthread_rwlock_wrlock(&rwlock);		
	
	pthread_rwlock_tryrdlock(&rwlock);		

	pthread_rwlock_trywrlock(&rwlock);		

	pthread_rwlock_unlock(&rwlock);

	pthread_rwlock_destroy(&rwlock);
	
### 示例：读写锁的使用

## 三、条件变量：

**本身不是锁！  但是通常结合锁来使用。 mutex**

![函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pthread_cond_wait%E5%87%BD%E6%95%B0.png)

	pthread_cond_t cond;//类型

	初始化条件变量：

		1. pthread_cond_init(&cond, NULL);   			动态初始化。

		2. pthread_cond_t cond = PTHREAD_COND_INITIALIZER;	静态初始化。

	阻塞等待条件：

		3. pthread_cond_wait(&cond, &mutex);

		作用：	1） 阻塞等待条件变量满足

			2） 解锁已经加锁成功的信号量 （相当于 pthread_mutex_unlock(&mutex)）
			
		注：1和2两步为一个原子操作

			3)  当条件满足，函数返回时，重新加锁信号量 （相当于， pthread_mutex_lock(&mutex);）

		4. pthread_cond_timedwait()：可设置超时

	5. pthread_cond_signal(): 唤醒阻塞在条件变量上的 (至少)一个线程。

	6. pthread_cond_broadcast()： 唤醒阻塞在条件变量上的 所有线程。
	
	7. pthread_cond_destroy(&cond)：销毁条件变量
 
### 示例：使用条件变量完成生产者、多个消费者模型

![条件变量-生产者/消费者模型](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%9D%A1%E4%BB%B6%E5%8F%98%E9%87%8F-%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E6%A8%A1%E5%9E%8B.png)

## 四、信号量： 

* 应用于线程、进程间同步（既能保证同步，数据不混乱，又能提高线程并发）。

* 相当于 初始化值为 N 的互斥量。  N值，表示可以同时访问共享数据区的线程数。

![信号量函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%87%8F-%E5%87%BD%E6%95%B0.png)
	
	sem_t sem;	定义类型。

	int sem_init(sem_t *sem, int pshared, unsigned int value);

	参数：
		sem： 信号量 

		pshared：	0： 用于线程间同步
				
				1： 用于进程间同步

		value：N值。（指定同时访问的线程数）

	sem_destroy();

	sem_wait();		一次调用，做一次-- 操作， 当信号量的值为 0 时，再次 -- 就会阻塞。 （对比 pthread_mutex_lock）

	sem_post();		一次调用，做一次++ 操作. 当信号量的值为 N 时, 再次 ++ 就会阻塞。（对比 pthread_mutex_unlock）


## 示例：使用信号量实现生产者、消费者模型

![信号量-生产者消费者模型](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BF%A1%E5%8F%B7%E9%87%8F-%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E6%A8%A1%E5%9E%8B.png)



































	

		



























