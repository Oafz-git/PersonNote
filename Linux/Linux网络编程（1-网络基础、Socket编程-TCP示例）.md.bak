
# 网络基础

## 一、协议：
一组规则。
	
![网络协议](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%85%B8%E5%9E%8B%E5%8D%8F%E8%AE%AE.png)
	
## 二、分层模型结构：

	OSI七层模型：  物、数、网、传、会、表、应

	TCP/IP 4层模型：网（链路层/网络接口层）、网、传、应

		应用层：http、ftp、nfs、ssh、telnet。。。

		传输层：TCP、UDP

		网络层：IP、ICMP、IGMP

		链路层：以太网帧协议、ARP
		
![OSI模型和TCP/IP模型](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/OSI%E6%A8%A1%E5%9E%8B%E5%92%8CTCP_IP%E6%A8%A1%E5%9E%8B.png)
![OSI模型说明](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/OSI%E6%A8%A1%E5%9E%8B%E8%AF%B4%E6%98%8E.png)
**c/s模型：**

	client-server

**b/s模型：**

	browser-server

			C/S					B/S

	优点：	缓存大量数据、协议选择灵活			安全性、跨平台、开发工作量较小

		速度快

	缺点：	安全性、跨平台、开发工作量较大			不能缓存大量数据、严格遵守 http



## 三、网络传输流程（封装）：

	数据没有封装之前，是不能在网络中传递。

	数据-》应用层-》传输层-》网络层-》链路层  --- 网络环境
	
![TCP/IP通信过程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP_IP%E9%80%9A%E4%BF%A1%E8%BF%87%E7%A8%8B.png)

	数据包在不同协议层的称谓
	
		数据层：段
		
		网络层：数据报
		
		链路层：帧
		
![TCP/IP数据包过程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP_IP%E5%B0%81%E8%A3%85%E8%BF%87%E7%A8%8B.png)
	
## 四、以太网帧协议（广播）：

![以太网帧格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BB%A5%E5%A4%AA%E7%BD%91%E5%B8%A7%E6%A0%BC%E5%BC%8F.png)

	ARP协议：根据 Ip 地址获取 mac 地址（硬件地址）。
	
	以太网帧协议：根据mac地址，完成数据包传输。
	
![ARP数据报格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ARP%E6%95%B0%E6%8D%AE%E6%8A%A5%E6%A0%BC%E5%BC%8F.png)

## 五、IP协议：

![IP数据报格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/IP%E6%95%B0%E6%8D%AE%E5%8C%85%E6%A0%BC%E5%BC%8F.png)
	
	版本： IPv4、IPv6  -- 4位

	TTL： time to live 。 设置数据包在路由节点中的跳转上限。每经过一个路由节点，该值-1， 减为0的路由，有义务将该数据包丢弃

	源IP： 32位。--- 4字节		192.168.1.108 --- 点分十进制 IP地址（string）  --->  二进制 

	目的IP：32位。--- 4字节

	========

	IP地址：可以在网络环境中，唯一标识一台主机。

	端口号：可以网络的一台主机上，唯一标识一个进程。

	ip地址+端口号：可以在网络环境中，唯一标识一个进程。


## 六、UDP：
	
	16位：源端口号。	2^16 = 65536  

	16位：目的端口号。
	
![UDP数据段格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/UDP%E6%95%B0%E6%8D%AE%E6%AE%B5%E6%A0%BC%E5%BC%8F.png)

## 七、TCP协议：

	16位：源端口号。	2^16 = 65536  

	16位：目的端口号。

	32序号/32位确认序号：标志位后的编号

	6个标志位。

	16位窗口大小。	2^16 = 65536 
	
![TCP数据段格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E6%95%B0%E6%8D%AE%E6%AE%B5%E6%A0%BC%E5%BC%8F.png)


# Socket编程

## 一、网络套接字：  socket

	一个文件描述符指向一个套接字（该套接字内部由内核借助两个缓冲区实现。）

	在通信过程中， 套接字一定是成对出现的。

![socketApi](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/socketApi.png)
![套接字通讯原理](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A5%97%E6%8E%A5%E5%AD%97%E9%80%9A%E8%AE%AF%E5%8E%9F%E7%90%86.png)

## 二、网络字节序和主机字节序的转换函数（ip和端口）
	小端法：（pc本地存储）	高位存高地址。地位存低地址。	int a = 0x12345678

	大端法：（网络存储）	高位存低地址。地位存高地址。

	#include <arpa/inet.h>
	
		htonl --> 本地(host)--》网络(net) （IP）			192.168.1.11 --> string --> atoi --> int --> htonl --> 网络字节序

		htons --> 本地--》网络 (port)

		ntohl --> 网络--》 本地（IP）

		ntohs --> 网络--》 本地（Port）
		
		h-->host;n-->network;l-->32位长整数; s-->16位短整数

## 三、IP地址转换函数（inet_pton）：

	int inet_pton(int af, const char *src, void *dst);		本地字节序（string IP） ---> 网络字节序

		af：AF_INET、AF_INET6

		src：传入，IP地址（点分十进制）

		dst：传出，转换后的 网络字节序的 IP地址。 

		返回值：

			成功： 1

			异常： 0， 说明src指向的不是一个有效的ip地址。

			失败：-1
	
	const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);	网络字节序（二进制） ---> 本地字节序（string IP）

		af：AF_INET、AF_INET6

		src: 网络字节序IP地址

		dst：本地字节序（string IP）--缓冲区

		size： dst 的大小。缓冲区大小

		返回值： 成功：dst。 	

			失败：NULL


## 四、sockaddr地址结构：	IP + port	--> 在网络环境中唯一标识一个进程。

![sockaddr数据结构](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/sockaddr%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84.png)

**man 7 ip**

![man_7_ip](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/man_7_ip.png)

	//定义
	struct sockaddr_in addr;
	
	//初始化
	addr.sin_family = AF_INET/AF_INET6				
	addr.sin_port = htons(9527);
		int dst;
		inet_pton(AF_INET, "192.157.22.45", (void *)&dst);//点分十进制（字符串类型）转为网络字节序
	addr.sin_addr.s_addr = dst;
	【*】addr.sin_addr.s_addr = htonl(INADDR_ANY);		INADDR_ANY取出本系统中有效的任意IP地址，二进制类型。转为网络字节序
	
	//使用
	bind(fd, (struct sockaddr *)&addr, size);


## 五、socket函数：

![socket连接](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/socket%E8%BF%9E%E6%8E%A5.png)

	#include <sys/socket.h>

	int socket(int domain, int type, int protocol);		创建一个 套接字

		domain：AF_INET、AF_INET6、AF_UNIX

		type：SOCK_STREAM（TCP）、SOCK_DGRAM（UDP）

		protocol: 0 

		返回值：
	
			成功： 新套接字所对应文件描述符

			失败: -1 errno 可使用perror();

---

	 #include <arpa/inet.h>

	 int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);		给socket绑定一个 地址结构 (IP+port)

		sockfd: socket 函数返回值

			struct sockaddr_in addr;

			addr.sin_family = AF_INET;

			addr.sin_port = htons(8888);

			addr.sin_addr.s_addr = htonl(INADDR_ANY);

		addr: 传入参数(struct sockaddr *)&addr

		addrlen: sizeof(addr) 地址结构的大小。

		返回值：

			成功：0

			失败：-1 errno

---

	int listen(int sockfd, int backlog);		设置同时与服务器建立连接的上限数。（同时进行3次握手的客户端数量）

		sockfd: socket 函数返回值

		backlog：上限数值。最大值 128.


		返回值：

			成功：0

			失败：-1 errno	

---
	
	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);	阻塞等待客户端建立连接，成功的话，返回一个与客户端成功连接的socket文件描述符。
	第2卷---系统函数
		sockfd: socket 函数返回值

		addr：传出参数。成功与服务器建立连接的那个客户端的地址结构（IP+port）

			socklen_t clit_addr_len = sizeof(addr);

		addrlen：传入传出。 &clit_addr_len

			 入：addr的大小。 出：客户端addr实际大小。

		返回值：

			成功：能与客户端进行数据通信的 socket 对应的文件描述。

			失败： -1 ， errno

---

	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);	  使用现有的 socket 与服务器建立连接

		sockfd： socket 函数返回值

			struct sockaddr_in srv_addr;		// 服务器地址结构

			srv_addr.sin_family = AF_INET;

			srv_addr.sin_port = 9527 	跟服务器bind时设定的 port 完全一致。

			inet_pton(AF_INET, "服务器的IP地址"，&srv_adrr.sin_addr.s_addr);

		addr：传入参数。服务器的地址结构

		addrlen：服务器的地址结构的大小

		返回值：

			成功：0

			失败：-1 errno

		如果不使用bind绑定客户端地址结构, 采用"隐式绑定".


## 六、TCP通信流程分析:

	server:
		1. socket()	创建socket

		2. bind()	绑定服务器地址结构

		3. listen()	设置监听上限

		4. accept()	阻塞监听客户端连接

		5. read(fd)	读socket获取客户端数据

		6. 小--大写	toupper()

		7. write(fd)

		8. close();

	client:

		1. socket()	创建socket

		2. connect();	与服务器建立连接

		3. write()	写数据到 socket

		4. read()	读转换后的数据。

		5. 显示读取结果

		6. close()
		
		
# 示例

```
//server.c

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define SERV_PORT 54321

void sys_error(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int ret = 0;
	int lfd = 0, cfd = 0;
	char buf[BUFSIZ], clit_ip[BUFSIZ];//BUFSIZ 表示4096

	struct sockaddr_in serv_addr,clit_addr;
	socklen_t clit_addr_len;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	lfd = socket(AF_INET,SOCK_STREAM,0);	//创建套接字
	if(lfd == -1)
	{
		sys_error("socket error");	
	}	

	ret = bind(lfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));//绑定本地ip和端口
	if(ret == -1)
	{
		sys_error("bind error");
	}

	ret = listen(lfd,30);//设置套接字的最大连接数
	if(ret == -1)
	{
		sys_error("listen error");
	}	

	clit_addr_len = sizeof(clit_addr);
	cfd = accept(lfd,(struct sockaddr *)&clit_addr, &clit_addr_len);//设置阻塞监听,返回连接socket描述符
	if(cfd == -1)
	{
		sys_error("accept error");
	}
	printf("client ip:%s,port:%d\n",//打印客户端ip和port
		inet_ntop(AF_INET,&clit_addr.sin_addr.s_addr,clit_ip,sizeof(clit_ip)),
		ntohs(clit_addr.sin_port)
		);
	

	while(1)
	{
		ret = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, ret);
		if(ret == -1)
		{
			sys_error("read error");
		}
		for(int i=0; i<ret; i++)
			buf[i] = toupper(buf[i]);
		write(cfd, buf, ret);
	}

	close(lfd);
	close(cfd);

	return 0;
}
```

```
///client.c
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 54321

void sys_err(const char* str)
{
	perror(str);
	exit(1);
}

int main(int argc, char* argv[])
{
	int cfd = 0, ret = 0;
	char buf[BUFSIZ];
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);


	cfd = socket(AF_INET, SOCK_STREAM, 0);	
	if(cfd == -1)
	{
		sys_err("socket error");
	}

	//连接
	ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));	
	if(ret == -1)
	{
		sys_err("connect error");
	}
	while(1)	
	{
		ret = read(STDIN_FILENO, buf, sizeof(buf));
		//写
		ret = write(cfd,buf,ret);	
		if(ret == -1)
		{
			sys_err("wirte error");
		}
		ret = read(cfd, buf, sizeof(buf));
		write(STDOUT_FILENO, buf, ret);	
	}
	close(cfd);
	return 0;
}
```	