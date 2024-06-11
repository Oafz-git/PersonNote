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

## 三、服务器程序上传至外网服务器，并访问

```sheel
scp -r ./test/ oafz@192.168.252.128:/home/oafz/code 
```
