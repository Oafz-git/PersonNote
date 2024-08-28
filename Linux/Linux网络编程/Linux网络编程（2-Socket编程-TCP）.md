# Socket编程

## 一、网络套接字概念：socket

	一个文件描述符指向一个套接字（该套接字内部由内核借助两个缓冲区实现。）

	在通信过程中， 套接字一定是成对出现的。
	
![套接字通讯原理](https://img-blog.csdnimg.cn/img_convert/d0d34336162cb07337637e88271a287a.png)

## 二、网络字节序和主机字节序的转换函数（ip和端口）

	小端法：（pc本地存储、Intel架构）	高位存高地址。地位存低地址。	int a = 0x12345678

	大端法：（网络存储、IDM公司）	高位存低地址。地位存高地址。

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

![sockaddr数据结构](https://img-blog.csdnimg.cn/img_convert/a05070bf90ff67125ae18c5939af7547.png)

**man 7 ip命令**

![man_7_ip](https://img-blog.csdnimg.cn/img_convert/4c0b2e03b8b1ba7beacb1ec483c999f0.png)

	//定义
	struct sockaddr_in addr;      // #include<arpa/inet.h>
	
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

![socketApi](https://img-blog.csdnimg.cn/img_convert/0f6c2f8a364a2ab1160d78eac4460d7a.png)

![socket连续](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/socket%E8%BF%9E%E6%8E%A5.png)

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
		
		3. 从终端读取数据

		4. write()	写数据到 socket

		5. read()	读转换后的数据。

		6. 显示读取结果

		7. close()
		
### 示例：TCP通信完成客户端和服务端

```C
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


```C
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

## 七、错误处理函数： 

	封装目的： 

		在 server.c 编程过程中突出逻辑，将出错处理与逻辑分开，可以直接跳转man手册。


	【wrap.c】								【wrap.h】


	存放网络通信相关常用 自定义函数						存放 网络通信相关常用 自定义函数原型(声明)。

	命名方式：系统调用函数首字符大写, 方便查看man手册
		
		  如：Listen()、Accept();

	函数功能：调用系统调用函数，处理出错场景。

	在 server.c 和 client.c 中调用 自定义函数

	联合编译 server.c 和 wrap.c 生成 server
 
		 client.c 和 wrap.c 生成 client

---

	readn：
		读 N 个字节
		
	readline：
		读一行

	read 函数的返回值：

		1. > 0 实际读到的字节数

		2. = 0 已经读到结尾（对端已经关闭）【 ！重 ！点 ！】

		3. -1 应进一步判断errno的值：

			errno = EAGAIN or EWOULDBLOCK: 设置了非阻塞方式 读。 没有数据到达。 

			errno = EINTR 慢速系统调用被 中断。

			errno = “其他情况” 异常。



















