
# libevent库

	开源。精简。跨平台（Windows、Linux、maxos、unix）。专注于网络通信。

## 1.源码包安装：  参考 README、readme

	./configure		检查安装环境 生成 makefile

	make			生成 .o 和 可执行文件

	sudo make install	将必要的资源cp置系统指定目录。

	进入 sample 目录，运行demo验证库安装使用情况。

	编译使用库的 .c 时，需要加 -levent 选项。

	库名 libevent.so --> /usr/local/lib   查看的到。

## 2.特性：

	基于“事件”异步通信模型。--- 回调。


## 3.libevent框架：

	1. 创建 event_base		(乐高底座)

		struct event_base *event_base_new(void);

		struct event_base *base = event_base_new();

	2. 创建 事件evnet	

		常规事件 event	--> event_new(); 

		bufferevent --> bufferevent_socket_new();

	3. 将事件 添加到 base上	

		int event_add(struct event *ev, const struct timeval *tv)

	4. 循环监听事件满足

		int event_base_dispatch(struct event_base *base);

			event_base_dispatch(base);

	5. 释放 event_base

		event_base_free(base);

## 4.常规事件event

### a.创建事件event：

		struct event *ev；

		struct event *event_new(struct event_base *base，evutil_socket_t fd，short what，event_callback_fn cb;  void *arg);

			base： event_base_new()返回值。

			 fd： 绑定到 event 上的 文件描述符

			what：对应的事件（r、w、e）

				EV_READ		一次 读事件

				EV_WRTIE	一次 写事件

				EV_PERSIST	持续触发。 结合 event_base_dispatch 函数使用，生效。

			cb：一旦事件满足监听条件，回调的函数。

			typedef void (*event_callback_fn)(evutil_socket_t fd,  short,  void *)	

			arg： 回调的函数的参数。

			返回值：成功创建的 event

### b.添加事件到 event_base

		int event_add(struct event *ev, const struct timeval *tv);

			ev: event_new() 的返回值。

			tv：NULL

### c.从event_base上摘下事件				【了解】

		int event_del(struct event *ev);

			ev: event_new() 的返回值。

### d.销毁事件

		int event_free(struct event *ev);

			ev: event_new() 的返回值。

### e.未决和非未决：

![libevent 未决和非未决](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/libevent%E6%9C%AA%E5%86%B3%E5%92%8C%E9%9D%9E%E6%9C%AA%E5%86%B3.png)

	非未决: 没有资格被处理

	未决： 有资格被处理，但尚未被处理

	event_new --> event ---> 非未决 --> event_add --> 未决 --> dispatch() && 监听事件被触发 --> 激活态 

	--> 执行回调函数 --> 处理态 --> 非未决 event_add && EV_PERSIST --> 未决 --> event_del --> 非未决
	

## 5.带缓冲区的事件 bufferevent

	#include <event2/bufferevent.h> 

	read/write 两个缓冲. 借助 队列.

### a.创建、销毁bufferevent：

	struct bufferevent *ev；

	struct bufferevent *bufferevent_socket_new(struct event_base *base, evutil_socket_t fd, enum bufferevent_options options);

		base： event_base

		fd:	封装到bufferevent内的 fd

		options：BEV_OPT_CLOSE_ON_FREE

	返回： 成功创建的 bufferevent事件对象。

	void  bufferevent_socket_free(struct bufferevent *ev);

### b.给bufferevent设置回调：
	
	对比event：	event_new( fd, callback );  					event_add() -- 挂到 event_base 上。

	
			bufferevent_socket_new（fd）  bufferevent_setcb（ callback ）

	void bufferevent_setcb(struct bufferevent * bufev,
				bufferevent_data_cb readcb,
				bufferevent_data_cb writecb,
				bufferevent_event_cb eventcb,
				void *cbarg );

	bufev： bufferevent_socket_new() 返回值

	readcb： 设置 bufferevent 读缓冲，对应回调  read_cb{  bufferevent_read() 读数据  }

	writecb： 设置 bufferevent 写缓冲，对应回调 write_cb {  } -- 给调用者，发送写成功通知。  可以 NULL

	eventcb： 设置 事件回调。   也可传NULL

		typedef void (*bufferevent_event_cb)(struct bufferevent *bev,  short events, void *ctx);

		void event_cb(struct bufferevent *bev,  short events, void *ctx)
		{

			。。。。。
		}

		events： BEV_EVENT_CONNECTED


	cbarg：	上述回调函数使用的 参数。

	read 回调函数类型：

		typedef void (*bufferevent_data_cb)(struct bufferevent *bev, void*ctx);

		void read_cb(struct bufferevent *bev, void *cbarg )
		{
			.....
			bufferevent_read();   --- read();
		}

	bufferevent_read()函数的原型：

		size_t bufferevent_read(struct bufferevent *bev, void *buf, size_t bufsize);

	
	write 回调函数类型：

		int bufferevent_write(struct bufferevent *bufev, const void *data,  size_t size); 


### c.启动、关闭 bufferevent的 缓冲区：

	void bufferevent_enable(struct bufferevent *bufev, short events);   启动	

		events： EV_READ、EV_WRITE、EV_READ|EV_WRITE

		默认、write 缓冲是 enable、read 缓冲是 disable

			bufferevent_enable(evev, EV_READ);		-- 开启读缓冲。


### d.连接客户端：

	socket();connect();

	int bufferevent_socket_connect(struct bufferevent *bev, struct sockaddr *address, int addrlen);

		bev: bufferevent 事件对象（封装了fd）

		address、len：等同于 connect() 参2/3


### e.创建监听服务器：

	------ socket();bind();listen();accept();

	struct evconnlistener * listner

	struct evconnlistener *evconnlistener_new_bind (	
		struct event_base *base,
		evconnlistener_cb cb, 
		void *ptr, 
		unsigned flags,
		int backlog,
		const struct sockaddr *sa,
		int socklen);

	base： event_base

	cb: 回调函数。 一旦被回调，说明在其内部应该与客户端完成， 数据读写操作，进行通信。

	ptr： 回调函数的参数

	flags： LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE

	backlog： listen() 2参。 -1 表最大值

	sa：服务器自己的地址结构体

	socklen：服务器自己的地址结构体大小。

	返回值：成功创建的监听器。

### f.释放监听服务器:

	void evconnlistener_free(struct evconnlistener *lev);


### 6.示例：服务器端 libevent 创建TCP连接：

	1. 创建event_base

	2. 创建bufferevent事件对象。bufferevent_socket_new();

	3. 使用bufferevent_setcb() 函数给 bufferevent的 read、write、event 设置回调函数。

	4. 当监听的 事件满足时，read_cb会被调用， 在其内部 bufferevent_read();读

	5. 使用 evconnlistener_new_bind 创建监听服务器， 设置其回调函数，当有客户端成功连接时，这个回调函数会被调用。

	6. 封装 listner_cb() 在函数内部。完成与客户端通信。

	7. 设置读缓冲、写缓冲的 使能状态 enable、disable

	7. 启动循环 event_base_dispath();

	8. 释放连接。

### 7.客户端端 libevent 创建TCP连接：















































































	

	