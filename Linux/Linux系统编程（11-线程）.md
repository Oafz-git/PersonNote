# 线程

## 一、线程概念：

![线程概念](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E6%A6%82%E5%BF%B5.png)

* `ps -Lf` 查看线程号（cpu 执行的最小单位）

![ps_Lf](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ps_Lf.png)

![最小执行单元](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%9C%80%E5%B0%8F%E6%89%A7%E8%A1%8C%E5%8D%95%E5%85%83.png)

## 二、Linux内核线程实现原理

![线程实现原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86.png)

## 三、三级映射（三级页表）

	进程PCB-->页目录（可看成数组，首地址位于PCB中）--》页表--》页目录（物理页表）--》内存单元
	
	参考：《Linux内核源代码情景分析》 ---毛德操
	
![三级映射](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%B8%89%E7%BA%A7%E6%98%A0%E5%B0%84.png)

![线程实现原理-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%AE%9E%E7%8E%B0%E5%8E%9F%E7%90%86-2.png)

## 四、线程共享资源

![线程共享资源](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%85%B1%E4%BA%AB%E8%B5%84%E6%BA%90.png)

## 五、线程非共享资源

![线程非共享资源](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E9%9D%9E%E5%85%B1%E4%BA%AB%E8%B5%84%E6%BA%90.png)

## 六、线程优缺点

![线程优缺点](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E4%BC%98%E7%BC%BA%E7%82%B9.png)

# 线程控制原语

## 一、pthread_self函数

**线程ID：用来表示线程身份的id号**

**线程号（LWP）：内核用来将线程作为进程看待**

	pthread_t pthread_self(void);	
		
		获取线程id。 线程id是在进程地址空间内部，用来标识线程身份的id号。

		返回值：本线程id（unsigned long类型）



## 二、pthread_create函数

	int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void *(*start_rountn)(void *), void *arg); //创建子线程。

		参1：传出参数，表新创建的子线程 id

		参2：线程属性。传NULL表使用默认属性。（线程状态：大小、优先级等）

		参3：子线程回调函数。创建成功，ptherad_create函数返回时，该函数会被自动调用。
		
		参4：参3的参数。没有的话，传NULL

		返回值：成功：0

			失败：返回errno
			

### 示例1：循环创建N个子线程：

		for （i = 0； i < 5; i++）

			pthread_create(&tid, NULL, tfn, (void *)i);   // 将 int 类型 i， 强转成 void *， 传参采用值传递

![循环创建子线程-错误分析](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%BE%AA%E7%8E%AF%E5%88%9B%E5%BB%BA%E5%AD%90%E7%BA%BF%E7%A8%8B-%E9%94%99%E8%AF%AF%E5%88%86%E6%9E%90.png)

### 示例2：线程共享全局变量

**线程默认共享数据段、代码段等地址空间，常用的是全局变量。**

**进程不共享全局变量，只能借助mmap**


## 三、pthread_exit函数

	void pthread_exit(void *retval);  退出当前线程。

		retval：退出值：返回线程，通常传NULL。
		
	三种退出的区别：

		exit();	退出当前进程。//exit(0)表示正常退出

		return: 返回到函数调用者那里去。

		pthread_exit(): 退出当前线程。
	
	注意：
		
		（1）多线程环境中，应尽量不使用exit函数，应该使用pthread_exit函数。
		
		（2）其它线程未结束，主线程不能return或exit。
		
		（3）在子线程中使用pthread_exit或return返回的指针所指向的内存单元必须是全局的或者malloc分配的，不能在线程函数的栈上分配，因为当其它线程得到这个返回指针时，线程函数已经退出了。

### 示例：exit、return、pthread_exit的区别

## 四、pthread_join函数

	int pthread_join(pthread_t thread, void **retval); //阻塞等待并回收线程，获取线程退出状态。

		thread: 待回收的线程id

		retval：传出参数。 回收的那个线程的退出值。

			线程异常借助，值为 -1。

		返回值：成功：0

			失败：errno
			
### 示例1：pthread_join函数的使用及注意事项

### 示例2：使用pthread_join函数将循环创建的多个子线程回收（使用数组）

## 五、pthread_detach函数

	int pthread_detach(pthread_t thread);		设置线程分离

		thread: 待分离的线程id

		返回值：成功：0

			失败：errno	

	（1）线程分离状态：指定该状态，线程主动与主线程断开关系。线程结束后，其退出状态不由其它线程获取，而直接自己自动释放。网络、多线程服务器常用。

	（2）进程若有该机制，将不会产生僵尸进程。僵尸进程的产生主要由于进程死后，大部分资源被释放，一点残留资源仍存于系统重，导致内核认为该进程仍存在。

	（3）也可使用`pthread_create`函数的参2（线程属性）来设置线程分离。

	（4）不能对一个已经处于detach状态的线程调用`pthread_join`，这样的调用将返回`EINVAL`无效错误。
	
	（5）使用pthread_join回收失败，说明分离成功

## 六、pthread_cancel函数

	int pthread_cancel(pthread_t thread);//杀死一个线程。

		thread: 待杀死的线程id
		
		返回值：成功：0，成功被 pthread_cancel()杀死的线程，返回 #define PTHREAD_CANDELED ((void *)-1)（表示非正常死亡）。使用pthead_join 回收

			失败：errno
			
	注意：
	
		（1）线程的取消并不是实时的，而有一定的延时。需要等待线程到达某个取消点（检查点）。如果，子线程没有到达取消点， 那么 pthread_cancel 无效。
	
		（2）可粗略认为一个系统调用（进入内核）即为一个取消点。
	
		（3）我们可以在程序中，手动添加一个取消点。使用 pthread_testcancel();
		
### 示例：线程的三种退出对比

## 七、检查错误返回
		
	检查出错返回：  线程中，只能使用strerror函数

	fprintf(stderr, "xxx error: %s\n", strerror(ret));

## 八、进程和线程控制原语对比

| 线程控制原语 | 进程控制原语 |
|--|--|
| pthread_create()|fork();|
|pthread_self()|getpid();|
|pthread_exit()|exit();    /return| 
|pthread_join()|wait()/waitpid()|
|pthread_cancel()|kill()|
|pthread_detach()|
	

## 九、设置线程属性（通过函数设置属性）

![线程属性](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E5%B1%9E%E6%80%A7.png)


	设置分离属性。

	pthread_attr_t attr  	创建一个线程属性结构体变量

	pthread_attr_init(pthread_attr_t *attr);	初始化线程属性
	
	pthread_attr_getdetachstate(pthread_attr_t *attr, int detachstate);//获取线程属性

	pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);//设置线程属性
	
	detachstate:
		
		PTHREAD_CREATE_DETACHED--分离线程
		
		PTHREAD_CREATE_JOINABLE--非分离线程（默认）
	
	pthread_create(&tid, &attr, tfn, NULL); 借助修改后的 设置线程属性 创建为分离态的新线程

	pthread_attr_destroy(pthread_attr_t *attr);	销毁线程属性


**线程同步问题：** 如果设置一个线程为**分离线程**，而这个线程运行又非常快，它可能在pthread_create函数返回之前就终止了；它终止之后可能将线程号和系统资源移交给其他的线程使用，这样调用pthread_create的线程就得到了错误的线程号。要避免这种情况可以采取一定的同步措施，最简单的方法之一是可以在被创建的线程里调用`pthread_cond_timewait`函数，设置一段等待时间，是在多线程编程里常用的方法。但注意不要使用诸如wait()之类的函数，它们是使整个进程睡眠，并不能解决线程同步的问题。

## 十、线程使用注意事项

![线程使用注意事项](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%BF%E7%A8%8B%E4%BD%BF%E7%94%A8%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9.png)


	