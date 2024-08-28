# ����������

## һ������̲�����������server.c

	1. Socket();		���� �����׽��� lfd
	2. Bind()	�󶨵�ַ�ṹ Strcut scokaddr_in addr;
	3. Listen();	
	4. while (1) {

		cfd = Accpet();			�������տͻ�����������
		
		pid = fork();			�����ӽ���
		
		if (pid == 0){			�ӽ��� read(cfd) --- С-���� --- write(cfd)

			close(lfd);	�ر����ڽ������ӵ��׽��� lfd

			read()
			
			С--����
			
			write()

		} else if ��pid > 0�� {	������

			close(cfd);	�ر�������ͻ���ͨ�ŵ��׽��� cfd	

			ע���źŲ�׽������SIGCHLD

			�ڻص������У� ����ӽ��̻��� while ��waitpid()��;
			
			contiue;
		}
	}
	
### ʾ��������̲�����������ʵ��

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
        struct sockaddr_in serv_addr, clit_addr;//��ַ�Ͷ˿ں�
        int clit_len;
        char buf[BUFSIZ];
        pid_t pid;

        bzero(&serv_addr, sizeof(serv_addr));//����ַ�ṹ�������

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(INPORT_ANY);
        lfd = Socket(AF_INET,SOCK_STREAM,0);//��������Socket
        Bind(lfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));//�󶨵�ַ
        Listen(lfd,20);//����Socket�����������
        clit_len = sizeof(clit_addr);
        while(1)
        {
                pid = fork();//���������ӽ���
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

## �������̲߳����������� server.c 

	1. Socket();		���� �����׽��� lfd

	2. Bind()		�󶨵�ַ�ṹ Strcut scokaddr_in addr;

	3. Listen();		

	4. while (1) {		

		cfd = Accept(lfd, );

		pthread_create(&tid, NULL, tfn, (void *)cfd);

		pthread_detach(tid);  	// pthead_join(tid, void **);  �ɵ�������һ�����߳�---ר���ڻ������̡߳�
	  }

	5. ���̣߳�

		void *tfn(void *arg) 
		{
			// close(lfd)			���ܹرա� ���߳�Ҫʹ��lfd

			read(cfd)

			С--��

			write(cfd)

			pthread_exit��(void *)10��;	
		}

* ����ַ�ṹ���㣺`memset(void* s, int c, size_t n)`��`bzero(void* s, size_t n)`

### ʾ�������̲߳�����������ʵ��

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

struct s_info {                     //����һ���ṹ��, ����ַ�ṹ��cfd����
    struct sockaddr_in cliaddr;
    int connfd;
};

void *do_work(void *arg)
{
    int n,i;
    struct s_info *ts = (struct s_info*)arg;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];      //#define INET_ADDRSTRLEN 16  ����"[+d"�鿴

    while (1) {
        n = Read(ts->connfd, buf, MAXLINE);                     //���ͻ���
        if (n == 0) {
            printf("the client %d closed...\n", ts->connfd);
            break;                                              //����ѭ��,�ر�cfd
        }
        printf("received from %s at PORT %d\n",
                inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
                ntohs((*ts).cliaddr.sin_port));                 //��ӡ�ͻ�����Ϣ(IP/PORT)

        for (i = 0; i < n; i++) 
            buf[i] = toupper(buf[i]);                           //Сд-->��д

        Write(STDOUT_FILENO, buf, n);                           //д������Ļ
        Write(ts->connfd, buf, n);                              //��д���ͻ���
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

    struct s_info ts[256];      //�����ṹ������.
    int i = 0;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);                     //����һ��socket, �õ�lfd

    bzero(&servaddr, sizeof(servaddr));                             //��ַ�ṹ����
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);                               //ָ����������IP
    servaddr.sin_port = htons(SERV_PORT);                                       //ָ���˿ں� 

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));             //��

    Listen(listenfd, 128);                                                      //����ͬһʱ�����ӷ�����������

    printf("Accepting client connect ...\n");

    while (1) {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);   //���������ͻ�����������
        ts[i].cliaddr = cliaddr;
        ts[i].connfd = connfd;

        pthread_create(&tid, NULL, do_work, (void*)&ts[i]);
        pthread_detach(tid);                                                    //���̷߳���,��ֹ���̲߳���.
        i++;
    }

    return 0;
}
```

## ���������������ϴ���������������������

```sheel
scp -r ./test/ oafz@192.168.252.128:/home/oafz/code 
```
