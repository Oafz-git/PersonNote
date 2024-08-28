# Socket编程-UDP

## 一、TCP通信和UDP通信各自的优缺点：


	TCP：	面向连接的，可靠数据包传输。对于不稳定的网络层，采取完全弥补的通信方式。 丢包重传。

		优点：
			稳定。		
				数据流量稳定、速度稳定、顺序
		缺点：
			传输速度慢。相率低。开销大。

		使用场景：数据的完整型要求较高，不追求效率。

			  大数据传输、文件传输。


	UDP：	无连接的，不可靠的数据报传递。对于不稳定的网络层，采取完全不弥补的通信方式。 默认还原网络状况

		优点：

			传输速度块。相率高。开销小。

		缺点：
			不稳定。
				数据流量。速度。顺序。


		使用场景：对时效性要求较高场合。稳定性其次。

			  游戏、视频会议、视频电话。		腾讯、华为、阿里  ---  应用层数据校验协议，弥补udp的不足。


## 二、UDP实现的 C/S 模型：

### 1.server

	lfd = socket(AF_INET, STREAM, 0);	SOCK_DGRAM --- 报式协议。

	bind();

	listen();  --- 可有可无

	while（1）{

		read(cfd, buf, sizeof) --- 被替换 --- recvfrom（） --- 涵盖accept传出地址结构。

		小-- 大
			
		write();--- 被替换 --- sendto（）---- connect

		}

	close();
		
### 2.client
	
	connfd = socket(AF_INET, SOCK_DGRAM, 0);

	sendto（‘服务器的地址结构’， 地址结构大小）

	recvfrom（）

	写到屏幕

	close();
		
* recv()/send() 只能用于 TCP 通信。 替代 read、write

* accpet(); ---- Connect(); ---被舍弃

### 3.recvfrom函数
	
	ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);

		参数：
	
			sockfd： 套接字

			buf：缓冲区地址

			len：缓冲区大小

			flags： 0

			src_addr：（struct sockaddr *）&addr 传出。 对端地址结构

			addrlen：传入传出。

		返回值： 
		
			成功：接收数据字节数。 
			
			失败：-1 errn。 
			
			0： 对端关闭。

### 4.sendto函数
		
	ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
	
		参数：
		
			sockfd： 套接字

			buf：存储数据的缓冲区

			len：数据长度

			flags： 0

			src_addr：（struct sockaddr *）&addr 传入。 目标地址结构

			addrlen：地址结构长度。

		返回值：
			
			成功：写出数据字节数。 
			
			失败：-1， errno		

### 5.示例：UDP实现并发服务器和客户端

```C

```

## 三、本地套接字：

* IPC： pipe、fifo、mmap、信号、本地套（domain）--- CS模型

### 1.对比网络编程 TCP C/S模型， 注意以下几点：

	1. int socket(int domain, int type, int protocol); 参数 domain：AF_INET --> AF_UNIX/AF_LOCAL 
	
							     type: SOCK_STREAM/SOCK_DGRAM  都可以。	
	2. 地址结构：  sockaddr_in --> sockaddr_un

		struct sockaddr_in srv_addr; --> struct sockaddr_un srv_adrr;

		srv_addr.sin_family = AF_INET;  --> srv_addr.sun_family = AF_UNIX;

		srv_addr.sin_port = htons(8888);    strcpy(srv_addr.sun_path, "srv.socket")

		srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);			len = offsetof(struct sockaddr_un, sun_path) + strlen("srv.socket");
	
		bind(fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));  --> 	bind(fd, (struct sockaddr *)&srv_addr, len); 


	3. bind()函数调用成功，会创建一个 socket。因此为保证bind成功，通常我们在 bind之前， 可以使用 unlink("srv.socket");


	4. 客户端不能依赖 “隐式绑定”。并且应该在通信建立过程中，创建且初始化2个地址结构：

		1） client_addr --> bind()

		2)  server_addr --> connect();


### 2.对比本地套接字 和 网络套接字。
					
					网络套接字						本地套接字

	server：	lfd = socket(AF_INET, SOCK_STREAM, 0);				lfd = socket(AF_UNIX, SOCK_STREAM, 0);
		
			bzero() ---- struct sockaddr_in serv_addr;		bzero() ---- struct sockaddr_un serv_addr, clie_addr;

			serv_addr.sin_family = AF_INET;				serv_addr.sun_family = AF_UNIX;	
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			serv_addr.sin_port = htons(8888);			strcpy（serv_addr.sun_path, "套接字文件名"）
										len = offsetof(sockaddr_un, sun_path) + strlen();

										
			bind(lfd, (struct sockaddr *)&serv_addr, sizeof());	unlink("套接字文件名");
										bind(lfd, (struct sockaddr *)&serv_addr, len);  创建新文件

			Listen(lfd, 128);					Listen(lfd, 128);

			cfd = Accept(lfd, ()&clie_addr, &len);			cfd = Accept(lfd, ()&clie_addr, &len);  


	client：		
			lfd = socket(AF_INET, SOCK_STREAM, 0);			lfd = socket(AF_UNIX, SOCK_STREAM, 0);

			" 隐式绑定 IP+port"					bzero() ---- struct sockaddr_un clie_addr;
										clie_addr.sun_family = AF_UNIX;
										strcpy（clie_addr.sun_path, "client套接字文件名"）
										len = offsetof(sockaddr_un, sun_path) + strlen();
										unlink( "client套接字文件名");
										bind(lfd, (struct sockaddr *)&clie_addr, len);

			bzero() ---- struct sockaddr_in serv_addr;		bzero() ---- struct sockaddr_un serv_addr;

			serv_addr.sin_family = AF_INET;				serv_addr.sun_family = AF_UNIX;
																	
			inet_pton(AF_INT, "服务器IP", &sin_addr.s_addr)							
										strcpy（serv_addr.sun_path, "server套接字文件名"）
			serv_addr.sin_port = htons("服务器端口");		
										
										len = offsetof(sockaddr_un, sun_path) + strlen();

			connect(lfd, &serv_addr, sizeof());			connect(lfd, &serv_addr, len);

### 3.示例：实现本地套接字