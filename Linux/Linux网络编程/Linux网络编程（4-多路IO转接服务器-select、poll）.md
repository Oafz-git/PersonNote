# 多路IO转接服务器（select、poll）

多路IO转接服务器也叫做多任务IO服务器。该类服务器实现的主旨思想是：不再由应用程序自己监视客户端连接，而是由内核替应用程序监视文件。

## 一、select

![select思路](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/select%E6%80%9D%E8%B7%AF.png)

###	1、select函数简介

	原理：  借助内核， select 只用来（内核）非阻塞监听不进行客户端连接， 客户端连接、数据通信事件。

	int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);

		nfds：监听的所有文件描述符中，最大文件描述符+1

		readfds： 读 文件描述符监听集合。	传入、传出参数

		writefds：写 文件描述符监听集合。	传入、传出参数		NULL

		exceptfds：异常 文件描述符监听集合	传入、传出参数		NULL

		timeout： 	> 0: 	设置监听超时时长。

				NULL:	阻塞监听

				0：	非阻塞监听，轮询
		返回值：

			> 0:	所有监听集合（3个）中， 满足对应事件的总数。

			0：	没有满足监听条件的文件描述符

			-1： 	errno

---

	void FD_ZERO(fd_set *set);	--- 清空一个文件描述符集合。

	void FD_SET(int fd, fd_set *set);	--- 将待监听的文件描述符，添加到监听集合中

	void FD_CLR(int fd, fd_set *set);	--- 将某一个文件描述符从监听集合中 移除。

	int  FD_ISSET(int fd, fd_set *set);	--- 判断一个文件描述符是否在监听集合中。

		返回值： 在：1；不在：0；

### 2、示例：select函数实现多路IO转接服务器

**思路分析：**

	int maxfd = 0；

	lfd = socket() ;			创建套接字

	maxfd = lfd；

	bind();					绑定地址结构

	listen();				设置监听上限

	fd_set rset， allset;			创建r监听集合

	FD_ZERO(&allset);			将r监听集合清空

	FD_SET(lfd, &allset);			将 lfd 添加至读集合中。

	while（1） {

		rset = allset；			保存监听集合
	
		ret  = select(lfd+1， &rset， NULL， NULL， NULL);		监听文件描述符集合对应事件；这里的rset是传入的

		if（ret > 0） {							有监听的描述符满足对应事件
		
			if (FD_ISSET(lfd, &rset)) {				// 1 在。 0不在。	 这里的rset是传出的；

				cfd = accept（）；				建立连接，返回用于通信的文件描述符

				maxfd = cfd；

				FD_SET(cfd, &allset);				添加到监听通信描述符集合中。
			}

			for （i = lfd+1； i <= 最大文件描述符; i++）{

				FD_ISSET(i, &rset)				有read、write事件

				read（）

				小 -- 大

				write();
			}	
		}
	}
	
```C
//select_server.c

#include "wrap.h"

#define SERV_PORT 6666

int main(int argc, char *argv[])
{
    int i, j, n, maxi;

    int nready, client[FD_SETSIZE];                 /* 自定义数组client, 防止遍历1024个文件描述符  FD_SETSIZE默认为1024 */
    int maxfd, listenfd, connfd, sockfd;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];         /* #define INET_ADDRSTRLEN 16 */

    struct sockaddr_in clie_addr, serv_addr;
    socklen_t clie_addr_len;
    fd_set rset, allset;                            /* rset 读事件文件描述符集合 allset用来暂存 */

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&serv_addr, sizeof(serv_addr));				//地址清空
    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port= htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    Listen(listenfd, 128);

    maxfd = listenfd;                                           /* 起初 listenfd 即为最大文件描述符 */

    maxi = -1;                                                  /* 将来用作client[]的下标, 初始值指向0个元素之前下标位置 */
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;                                         /* 用-1初始化client[] */

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);                                  /* 构造select监控文件描述符集 */

    while (1) {   
        rset = allset;                                          /* 每次循环时都从新设置select监控信号集 */

        nready = select(maxfd+1, &rset, NULL, NULL, NULL);  //2  1--lfd  1--connfd
        if (nready < 0)
            perr_exit("select error");

        if (FD_ISSET(listenfd, &rset)) {                        /* 说明有新的客户端链接请求 */

            clie_addr_len = sizeof(clie_addr);
            connfd = Accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);       /* Accept 不会阻塞 */
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                    ntohs(clie_addr.sin_port));

            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0) {                            /* 找client[]中没有使用的位置 */
                    client[i] = connfd;                         /* 保存accept返回的文件描述符到client[]里 */
                    break;
                }

            if (i == FD_SETSIZE) {                              /* 达到select能监控的文件个数上限 1024 */
                fputs("too many clients\n", stderr);
                exit(1);
            }

            FD_SET(connfd, &allset);                            /* 向监控文件描述符集合allset添加新的文件描述符connfd */

            if (connfd > maxfd)
                maxfd = connfd;                                 /* select第一个参数需要 */

            if (i > maxi)
                maxi = i;                                       /* 保证maxi存的总是client[]最后一个元素下标 */

            if (--nready == 0)
                continue;
        } 

        for (i = 0; i <= maxi; i++) {                               /* 检测哪个clients 有数据就绪 */

            if ((sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {

                if ((n = Read(sockfd, buf, sizeof(buf))) == 0) {    /* 当client关闭链接时,服务器端也关闭对应链接 */
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);                        /* 解除select对此文件描述符的监控 */
                    client[i] = -1;
                } else if (n > 0) {
                    for (j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(sockfd, buf, n);
                    Write(STDOUT_FILENO, buf, n);
                }
                if (--nready == 0)
                    break;                                          /* 跳出for, 但还在while中 */
            }
        }
    }
    Close(listenfd);
    return 0;
}


```
### 3、select优缺点：

	缺点：	监听上限受文件描述符限制。 最大 1024.

		检测满足条件的fd， 自己添加业务逻辑提高效率， 提高了编码难度。

	优点：	跨平台。win、linux、macOS、Unix、类Unix、mips

	

## 二、poll：

### 1、poll函数简介

	int poll(struct pollfd *fds, nfds_t nfds, int timeout);

		fds：监听的文件描述符【数组】

			struct pollfd {
				
				int fd：	待监听的文件描述符
				
				short events：	待监听的文件描述符对应的监听事件

						取值：POLLIN、POLLOUT、POLLERR

				short revnets：	传入时， 给0。如果满足对应事件的话， 返回 非0 --> POLLIN、POLLOUT、POLLERR
			}

		nfds: 监听数组的，【实际】有效监听个数。

		timeout:  > 0:  超时时长。单位：毫秒。

			  -1:	阻塞等待

			  0：  不阻塞

		返回值：返回满足对应监听事件的文件描述符 总个数。

### 2、poll函数优缺点

	优点：
		自带数组结构。 可以将 监听事件集合 和 返回事件集合 分离。

		拓展 监听上限。 超出 1024限制。

	缺点：
		不能跨平台。 Linux

		无法直接定位满足监听事件的文件描述符， 编码难度较大。 
		
### 3、示例：使用poll函数实现多路IO转接服务器

![poll函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/poll%E5%87%BD%E6%95%B0.png)

```C
//poll_server.c
#include "warp.h"
#include <string.h>

#define INPORT_ANY 54321
#define POLL_MAX 1024
int main(int argc, char* argv[])
{
	int lfd,cfd,n,i, j, ret, maxi, nready, sockfd;
	struct pollfd fds[POLL_MAX];
	struct sockaddr_in serv_addr, clit_addr;
	char buf[BUFSIZ];
	char str[128];

	socklen_t clit_addr_len = sizeof(clit_addr);
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(INPORT_ANY);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	lfd = Socket(AF_INET,SOCK_STREAM,0);
	int opt = 1;
	setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	Bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	Listen(lfd,128);
	//
	fds[0].fd = lfd;
	fds[0].events = POLLIN;
	fds[0].revents = 0;
	for(i=1;i<POLL_MAX;i++)
	{
		fds[i].fd = -1;
	}
	maxi = 0;
	while(1)
	{
		nready = Poll(fds,maxi+1,-1);
		//处理fld,生成cfd
		if(fds[0].revents & POLLIN)
		{
			cfd = Accept(lfd,(struct sockaddr*)&clit_addr,&clit_addr_len);
			printf("accept from %s at port %d\n", inet_ntop(AF_INET,&clit_addr.sin_addr, str,sizeof(str)),ntohs(clit_addr.sin_port));
			for(i=0;i<POLL_MAX;i++)
			{
				if(fds[i].fd == -1)
				{
					printf("i:%d\n",i);
					fds[i].fd = cfd;
					fds[i].events = POLLIN;
					fds[i].revents = 0;
					break;
				}
			}
			if(i == POLL_MAX)
				perror_exit("too many clients");
			if(i>maxi)
				maxi = i; //更新最大使用的下标
			printf("maxi:%d\n",maxi);
			printf("nread:%d\n", nready);
			if(--nready <= 0)
				continue;
		}
		//处理cfd
		for(i=1; i<=maxi;i++)
		{
			printf("maxi:%d\n",i);
			if((sockfd = fds[i].fd) < 0)
				continue;

			if(fds[i].revents & POLLIN)
			{
				n = read(sockfd,buf,sizeof(buf));
				if(n == -1)
				{
					if(errno == ECONNRESET)
					{//收到RST标志
						printf("client[%d] aborted connection\n", i);
						close(sockfd);
						sockfd= -1;

					}
					perror_exit("read error");
				}
				else if(n == 0)
				{
					printf("client[%d] close connection\n", i);
					close(sockfd);
					sockfd = -1;
				}
				else
				{
					write(STDOUT_FILENO,buf,n);
					for(j=0; j<n; j++)
					{
						buf[j] = toupper(buf[j]);
					}
					write(sockfd,buf,n);
				}
				if(--nready == 0)
					break;
			}
		}
	}
	return 0;
}
```


## 三、突破 1024 文件描述符限制（与系统配置有关）

	cat /proc/sys/fs/file-max  --> 当前计算机所能打开的最大文件个数。 受硬件影响。

	ulimit -a 	——> 当前用户下的进程，默认打开文件描述符个数。  缺省为 1024

	修改：
		打开 sudo vi /etc/security/limits.conf， 写入：

		* soft nofile 65536			--> 设置默认值， 可以直接借助命令修改。 【注销用户，使其生效】

		* hard nofile 100000			--> 命令修改上限。
	