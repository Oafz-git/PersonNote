# 并发服务器

## 一、多进程并发服务器：server.c

	1. Socket();		创建 监听套接字 lfd
	2. Bind()	绑定地址结构 Strcut scokaddr_in addr;
	3. Listen();	
	4. while (1) {

		cfd = Accpet();			阻塞接收客户端连接请求。
		
		pid = fork();			创建子进程
		
		if (pid == 0){			子进程 read(cfd) --- 小-》大 --- write(cfd)

			close(lfd);	关闭用于建立连接的套接字 lfd

			read()
			
			小--》大
			
			write()

		} else if （pid > 0） {	父进程

			close(cfd);	关闭用于与客户端通信的套接字 cfd	

			注册信号捕捉函数：SIGCHLD

			在回调函数中， 完成子进程回收 while （waitpid()）;
			
			contiue;
		}
	}
	
### 示例：多进程并发服务器的实现

```C
//thread_server.c 

#include "warp.h"

#define INPORT_ANY 54321

void catch_child(int arg)
{
        pid_t wpid;
        while((waitpid(0,NULL,WNOHANG))>0);
        return;
}

int main(int argc, char* argv[])
{
        int lfd, cfd, n,ret,i;
        struct sockaddr_in serv_addr, clit_addr;//地址和端口号
        int clit_len;
        char buf[BUFSIZ];
        pid_t pid;

        bzero(&serv_addr, sizeof(serv_addr));//将地址结构清空置零

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(INPORT_ANY);
        lfd = Socket(AF_INET,SOCK_STREAM,0);//创建监听Socket
        Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));//绑定地址
        Listen(lfd,20);//设置Socket最多连接数量
        clit_len = sizeof(clit_addr);
        while(1)
        {
                pid = fork();//阻塞创建子进程
                if(pid == -1)
                {
                        perror("fork error");
                        exit(1);
                }
                else if(pid == 0)//child
                {
                        cfd = Accept(lfd, (struct sockaddr*)&clit_addr, &clit_len);
                        while(1)
                        {
                                n = read(cfd,buf,sizeof(buf));
                                write(STDOUT_FILENO,buf,n);
                                for(i=0;i<n;i++)
                                {
                                        buf[i] = toupper(buf[i]);
                                }
                                write(cfd,buf,n);
                        }
                        close(lfd);
                        break;
                }
                else if(pid > 0)//parent
                {
                        struct sigaction act;
                        act.sa_handler = catch_child;
                        act.sa_flags = 0;
                        sigemptyset(&act.sa_mask);
                        ret = sigaction(SIGCHLD,&act,NULL);
                        if(ret == -1)
                        {
                                perror("sigaction error");
                                exit(1);
                        }
                        close(cfd);
                        continue;
                }
        }
        return 0;
}
```

## 二、多线程并发服务器： server.c 

	1. Socket();		创建 监听套接字 lfd

	2. Bind()		绑定地址结构 Strcut scokaddr_in addr;

	3. Listen();		

	4. while (1) {		

		cfd = Accept(lfd, );

		pthread_create(&tid, NULL, tfn, (void *)cfd);

		pthread_detach(tid);  	// pthead_join(tid, void **);  可单独创建一个新线程---专用于回收子线程。
	  }

	5. 子线程：

		void *tfn(void *arg) 
		{
			// close(lfd)			不能关闭。 主线程要使用lfd

			read(cfd)

			小--大

			write(cfd)

			pthread_exit（(void *)10）;	
		}

* 将地址结构清零：`memset(void* s, int c, size_t n)`和`bzero(void* s, size_t n)`

### 示例：多线程并发服务器的实现

```C
//pthread_server.c

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#include "wrap.h"

#define MAXLINE 8192
#define SERV_PORT 8000

struct s_info {                     //定义一个结构体, 将地址结构跟cfd捆绑
    struct sockaddr_in cliaddr;
    int connfd;
};

void *do_work(void *arg)
{
    int n,i;
    struct s_info *ts = (struct s_info*)arg;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];      //#define INET_ADDRSTRLEN 16  可用"[+d"查看

    while (1) {
        n = Read(ts->connfd, buf, MAXLINE);                     //读客户端
        if (n == 0) {
            printf("the client %d closed...\n", ts->connfd);
            break;                                              //跳出循环,关闭cfd
        }
        printf("received from %s at PORT %d\n",
                inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
                ntohs((*ts).cliaddr.sin_port));                 //打印客户端信息(IP/PORT)

        for (i = 0; i < n; i++) 
            buf[i] = toupper(buf[i]);                           //小写-->大写

        Write(STDOUT_FILENO, buf, n);                           //写出至屏幕
        Write(ts->connfd, buf, n);                              //回写给客户端
    }
    Close(ts->connfd);

    return (void *)0;
}

int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    pthread_t tid;

    struct s_info ts[256];      //创建结构体数组.
    int i = 0;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);                     //创建一个socket, 得到lfd

    bzero(&servaddr, sizeof(servaddr));                             //地址结构清零
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);                               //指定本地任意IP
    servaddr.sin_port = htons(SERV_PORT);                                       //指定端口号 

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));             //绑定

    Listen(listenfd, 128);                                                      //设置同一时刻链接服务器上限数

    printf("Accepting client connect ...\n");

    while (1) {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);   //阻塞监听客户端链接请求
        ts[i].cliaddr = cliaddr;
        ts[i].connfd = connfd;

        pthread_create(&tid, NULL, do_work, (void*)&ts[i]);
        pthread_detach(tid);                                                    //子线程分离,防止僵线程产生.
        i++;
    }

    return 0;
}
```

## 三、服务器程序上传至外网服务器，并访问

```sheel
scp -r ./test/ oafz@192.168.252.128:/home/oafz/code 
```
