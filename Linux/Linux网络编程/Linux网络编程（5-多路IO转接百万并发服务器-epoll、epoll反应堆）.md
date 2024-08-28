# 多路IO转接服务器（epoll）

部分内容来自：https://blog.csdn.net/zero__007/article/details/121853458

## 1.epoll

![epoll](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/epoll.png)


## 2.epoll函数简介

	int epoll_create(int size);						创建一棵监听红黑树

		size：创建的红黑树的监听节点数量。（仅供内核参考。）

		返回值：指向新创建的红黑树的根节点的 fd。 

			失败： -1 errno

---

	int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);	操作监听红黑树

		epfd：epoll_create 函数的返回值。 epfd

		op：对该监听红黑数所做的操作。

			EPOLL_CTL_ADD 添加fd到 监听红黑树

			EPOLL_CTL_MOD 修改fd在 监听红黑树上的监听事件。

			EPOLL_CTL_DEL 将一个fd 从监听红黑树上摘下（取消监听）

		fd：
			待监听的fd

		event：	本质 struct epoll_event 【结构体】 地址

				成员 events：
		
					EPOLLIN / EPOLLOUT / EPOLLERR

				成员 data： 联合体（共用体）：

					int fd;	  对应监听事件的 fd

					void *ptr； 泛型指针：回调函数时使用

					uint32_t u32;（不使用）

					uint64_t u64;（不使用）

		返回值：成功 0； 失败： -1 errno

---

	int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); 	 阻塞监听。

		epfd：epoll_create 函数的返回值。 epfd

		events：传出参数，【-s 数组】， 满足监听条件的 哪些 fd 结构体。

		maxevents：数组【元素的总个数】- 1024
				
			struct epoll_event evnets[1024]
		timeout：

			-1: 阻塞

			0： 不阻塞

			>0: 超时时间 （毫秒）

		返回值：

			> 0: 【满足】监听的总个数。 可以用作循环上限。

			0： 没有fd满足监听事件

			-1：失败。 errno


### 2.示例：epoll实现多路IO转接思路：

	lfd = socket（）;			监听连接事件lfd
	bind();
	listen();

	int epfd = epoll_create(1024);				epfd, 监听红黑树的树根。

	struct epoll_event tep, ep[1024];			tep, 用来设置单个fd属性， ep 是 epoll_wait() 传出的满足监听事件的数组。

	tep.events = EPOLLIN;					初始化  lfd的监听属性。
	tep.data.fd = lfd

	epoll_ctl(epfd， EPOLL_CTL_ADD, lfd, &tep);		将 lfd 添加到监听红黑树上。

	while (1) {

		ret = epoll_wait(epfd， ep，1024， -1);			实施监听

		for (i = 0; i < ret; i++) {
			
			if (ep[i].data.fd == lfd) {				// lfd 满足读事件，有新的客户端发起连接请求

				cfd = Accept();

				tep.events = EPOLLIN;				初始化  cfd的监听属性。
				tep.data.fd = cfd;

				epoll_ctl(epfd， EPOLL_CTL_ADD, cfd, &tep);

			} else {						cfd 们 满足读事件， 有客户端写数据来。

				n = read(ep[i].data.fd, buf, sizeof(buf));

				if ( n == 0) {

					close(ep[i].data.fd);

					epoll_ctl(epfd， EPOLL_CTL_DEL, ep[i].data.fd , NULL);	// 将关闭的cfd，从监听树上摘下。

				} else if （n > 0） {

					小--大
					write(ep[i].data.fd, buf, n);
				}
			}
		}
	}

```C
//epoll_server.c

#include "wrap.h"

#define MAXLINE 8192
#define SERV_PORT 8000

#define OPEN_MAX 5000

int main(int argc, char *argv[])
{
    int i, listenfd, connfd, sockfd;
    int  n, num = 0;
    ssize_t nready, efd, res;
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;

    struct sockaddr_in cliaddr, servaddr;


    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));      //端口复用
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    Listen(listenfd, 20);

    efd = epoll_create(OPEN_MAX);               //创建epoll模型, efd指向红黑树根节点
    if (efd == -1)
        perr_exit("epoll_create error");

    struct epoll_event tep, ep[OPEN_MAX];       //tep: epoll_ctl参数  ep[] : epoll_wait参数

    tep.events = EPOLLIN; 
    tep.data.fd = listenfd;           //指定lfd的监听时间为"读"

    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);    //将lfd及对应的结构体设置到树上,efd可找到该树
    if (res == -1)
        perr_exit("epoll_ctl error");

    for ( ; ; ) {
        /*epoll为server阻塞监听事件, ep为struct epoll_event类型数组, OPEN_MAX为数组容量, -1表永久阻塞*/
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); 
        if (nready == -1)
            perr_exit("epoll_wait error");

        for (i = 0; i < nready; i++) {
            if (!(ep[i].events & EPOLLIN))      //如果不是"读"事件, 继续循环
                continue;

            if (ep[i].data.fd == listenfd) {    //判断满足事件的fd是不是lfd            
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);    //接受链接

                printf("received from %s at PORT %d\n", 
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
                        ntohs(cliaddr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                tep.events = EPOLLIN; tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);      //加入红黑树
                if (res == -1)
                    perr_exit("epoll_ctl error");

            } else {                                                    //不是lfd, 
                sockfd = ep[i].data.fd;
                n = Read(sockfd, buf, MAXLINE);

                if (n == 0) {                                           //读到0,说明客户端关闭链接
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //将该文件描述符从红黑树摘除
                    if (res == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);                                      //关闭与该客户端的链接
                    printf("client[%d] closed connection\n", sockfd);

                } else if (n < 0) {                                     //出错
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //摘除节点
                    Close(sockfd);

                } else {                                                //实际读到了字节数
                    for (i = 0; i < n; i++)
                        buf[i] = toupper(buf[i]);                       //转大写,写回给客户端

                    Write(STDOUT_FILENO, buf, n);
                    Writen(sockfd, buf, n);
                }
            }
        }
    }
    Close(listenfd);
    Close(efd);

    return 0;
}
```


### 3.epoll 事件模型：

![ET_LT模型](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ET_LT%E6%A8%A1%E5%9E%8B.png)

	ET模式：

		边沿触发：高效模式，但是只支持 非阻塞模式。 --- 忙轮询。

			缓冲区剩余未读尽的数据不会导致 epoll_wait 返回。 新的事件满足，才会触发。

			struct epoll_event event;

			event.events = EPOLLIN | EPOLLET;
	LT模式：

		水平触发（默认采用模式）

			缓冲区剩余未读尽的数据会导致 epoll_wait 返回。
			
* 对于 LT 模式操作的文件描述符，当 epoll_wait 检测到其上有事件发生并将此事件通知应用程序后，应用程序可以不立即处理该事件。这样，当应用程序下一次调用 epoll_wait 时，还会再次向应用程序通告此事件，直到该事件被处理。

* 对于 ET 模式操作的文件描述符，当 epoll_wait 检测到其上有事件发生并将此事件通知应用程序后，应用程序必须立即处理该事件，因为后续的 epoll_wait 调用将不再向应用程序通知这一事件。所以**ET模式在很大程度上降低了同一个 epoll 事件被重复触发的次数，因此效率比 LT 模式高。**

### 4.epoll的ET模式的使用

```C
//epoll_et_server.c
#include "warp.h"

#define MAXLINE 10
#define SERV_PORT 8000

int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int efd, flag;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 20);

    ///////////////////////////////////////////////////////////////////////
    struct epoll_event event;
    struct epoll_event res_event[10];
    int res, len;

    efd = epoll_create(10);

    event.events = EPOLLIN | EPOLLET;     /* ET 边沿触发，默认是水平触发 */

    //event.events = EPOLLIN;
    printf("Accepting connections ...\n");
    cliaddr_len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    printf("received from %s at PORT %d\n",
            inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
            ntohs(cliaddr.sin_port));

    flag = fcntl(connfd, F_GETFL);          /* 修改connfd为非阻塞读 */
    flag |= O_NONBLOCK;
    fcntl(connfd, F_SETFL, flag);

    event.data.fd = connfd;
    epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event);      //将connfd加入监听红黑树
    while (1) {
        printf("epoll_wait begin\n");
        res = epoll_wait(efd, res_event, 10, -1);        //最多10个, 阻塞监听
        printf("epoll_wait end res %d\n", res);

        if (res_event[0].data.fd == connfd) {
            while ((len = read(connfd, buf, MAXLINE/2)) >0 )    //非阻塞读, 轮询
                write(STDOUT_FILENO, buf, len);
        }
    }

    return 0;
}
```

### 4.epoll的优缺点

	优点：
		高效。突破1024文件描述符。

	缺点：
		不能跨平台。 Linux。

### 5.epoll 反应堆模型（能看懂模型代码）

	epoll ET模式 + 非阻塞、轮询 + void *ptr。

	原来：	socket、bind、listen -- epoll_create 创建监听 红黑树 --  返回 epfd -- epoll_ctl() 向树上添加一个监听fd -- while（1）--

		-- epoll_wait 监听 -- 对应监听fd有事件产生 -- 返回 监听满足数组。 -- 判断返回数组元素 -- lfd满足 -- Accept -- cfd 满足 

		-- read() --- 小->大 -- write回去。

	反应堆：不但要监听 cfd 的读事件、还要监听cfd的写事件。

		socket、bind、listen -- epoll_create 创建监听 红黑树 --  返回 epfd -- epoll_ctl() 向树上添加一个监听fd -- while（1）--

		-- epoll_wait 监听 -- 对应监听fd有事件产生 -- 返回 监听满足数组。 -- 判断返回数组元素 -- lfd满足 -- Accept -- cfd 满足 

		-- read() --- 小->大 【-- cfd从监听红黑树上摘下 -- EPOLLOUT（判断是否可写：这里监听写事件，原因是在实际环境中，可能出现半关闭状态或滑动窗口满的情况，无法写不进去）
		
		-- 回调函数 -- epoll_ctl() -- EPOLL_CTL_ADD 重新放到红黑上监听写事件-- 等待 epoll_wait 返回 -- 说明 cfd 可写 -- write回去 
		
		-- cfd从监听红黑树上摘下 -- EPOLLIN -- epoll_ctl() -- EPOLL_CTL_ADD 重新放到红黑上监听读事件 -- epoll_wait 监听】


	



























		
				
