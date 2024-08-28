# ��·IOת�ӷ�������select��poll��

��·IOת�ӷ�����Ҳ����������IO�����������������ʵ�ֵ���ּ˼���ǣ�������Ӧ�ó����Լ����ӿͻ������ӣ��������ں���Ӧ�ó�������ļ���

## һ��select

![select˼·](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/select%E6%80%9D%E8%B7%AF.png)

###	1��select�������

	ԭ��  �����ںˣ� select ֻ�������ںˣ����������������пͻ������ӣ� �ͻ������ӡ�����ͨ���¼���

	int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);

		nfds�������������ļ��������У�����ļ�������+1

		readfds�� �� �ļ��������������ϡ�	���롢��������

		writefds��д �ļ��������������ϡ�	���롢��������		NULL

		exceptfds���쳣 �ļ���������������	���롢��������		NULL

		timeout�� 	> 0: 	���ü�����ʱʱ����

				NULL:	��������

				0��	��������������ѯ
		����ֵ��

			> 0:	���м������ϣ�3�����У� �����Ӧ�¼���������

			0��	û����������������ļ�������

			-1�� 	errno

---

	void FD_ZERO(fd_set *set);	--- ���һ���ļ����������ϡ�

	void FD_SET(int fd, fd_set *set);	--- �����������ļ�����������ӵ�����������

	void FD_CLR(int fd, fd_set *set);	--- ��ĳһ���ļ��������Ӽ��������� �Ƴ���

	int  FD_ISSET(int fd, fd_set *set);	--- �ж�һ���ļ��������Ƿ��ڼ��������С�

		����ֵ�� �ڣ�1�����ڣ�0��

### 2��ʾ����select����ʵ�ֶ�·IOת�ӷ�����

**˼·������**

	int maxfd = 0��

	lfd = socket() ;			�����׽���

	maxfd = lfd��

	bind();					�󶨵�ַ�ṹ

	listen();				���ü�������

	fd_set rset�� allset;			����r��������

	FD_ZERO(&allset);			��r�����������

	FD_SET(lfd, &allset);			�� lfd ������������С�

	while��1�� {

		rset = allset��			�����������
	
		ret  = select(lfd+1�� &rset�� NULL�� NULL�� NULL);		�����ļ����������϶�Ӧ�¼��������rset�Ǵ����

		if��ret > 0�� {							�м����������������Ӧ�¼�
		
			if (FD_ISSET(lfd, &rset)) {				// 1 �ڡ� 0���ڡ�	 �����rset�Ǵ����ģ�

				cfd = accept������				�������ӣ���������ͨ�ŵ��ļ�������

				maxfd = cfd��

				FD_SET(cfd, &allset);				��ӵ�����ͨ�������������С�
			}

			for ��i = lfd+1�� i <= ����ļ�������; i++��{

				FD_ISSET(i, &rset)				��read��write�¼�

				read����

				С -- ��

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

    int nready, client[FD_SETSIZE];                 /* �Զ�������client, ��ֹ����1024���ļ�������  FD_SETSIZEĬ��Ϊ1024 */
    int maxfd, listenfd, connfd, sockfd;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];         /* #define INET_ADDRSTRLEN 16 */

    struct sockaddr_in clie_addr, serv_addr;
    socklen_t clie_addr_len;
    fd_set rset, allset;                            /* rset ���¼��ļ����������� allset�����ݴ� */

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&serv_addr, sizeof(serv_addr));				//��ַ���
    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port= htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    Listen(listenfd, 128);

    maxfd = listenfd;                                           /* ��� listenfd ��Ϊ����ļ������� */

    maxi = -1;                                                  /* ��������client[]���±�, ��ʼֵָ��0��Ԫ��֮ǰ�±�λ�� */
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;                                         /* ��-1��ʼ��client[] */

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);                                  /* ����select����ļ��������� */

    while (1) {   
        rset = allset;                                          /* ÿ��ѭ��ʱ����������select����źż� */

        nready = select(maxfd+1, &rset, NULL, NULL, NULL);  //2  1--lfd  1--connfd
        if (nready < 0)
            perr_exit("select error");

        if (FD_ISSET(listenfd, &rset)) {                        /* ˵�����µĿͻ����������� */

            clie_addr_len = sizeof(clie_addr);
            connfd = Accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);       /* Accept �������� */
            printf("received from %s at PORT %d\n",
                    inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                    ntohs(clie_addr.sin_port));

            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0) {                            /* ��client[]��û��ʹ�õ�λ�� */
                    client[i] = connfd;                         /* ����accept���ص��ļ���������client[]�� */
                    break;
                }

            if (i == FD_SETSIZE) {                              /* �ﵽselect�ܼ�ص��ļ��������� 1024 */
                fputs("too many clients\n", stderr);
                exit(1);
            }

            FD_SET(connfd, &allset);                            /* �����ļ�����������allset����µ��ļ�������connfd */

            if (connfd > maxfd)
                maxfd = connfd;                                 /* select��һ��������Ҫ */

            if (i > maxi)
                maxi = i;                                       /* ��֤maxi�������client[]���һ��Ԫ���±� */

            if (--nready == 0)
                continue;
        } 

        for (i = 0; i <= maxi; i++) {                               /* ����ĸ�clients �����ݾ��� */

            if ((sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {

                if ((n = Read(sockfd, buf, sizeof(buf))) == 0) {    /* ��client�ر�����ʱ,��������Ҳ�رն�Ӧ���� */
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);                        /* ���select�Դ��ļ��������ļ�� */
                    client[i] = -1;
                } else if (n > 0) {
                    for (j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(sockfd, buf, n);
                    Write(STDOUT_FILENO, buf, n);
                }
                if (--nready == 0)
                    break;                                          /* ����for, ������while�� */
            }
        }
    }
    Close(listenfd);
    return 0;
}


```
### 3��select��ȱ�㣺

	ȱ�㣺	�����������ļ����������ơ� ��� 1024.

		�������������fd�� �Լ����ҵ���߼����Ч�ʣ� ����˱����Ѷȡ�

	�ŵ㣺	��ƽ̨��win��linux��macOS��Unix����Unix��mips

	

## ����poll��

### 1��poll�������

	int poll(struct pollfd *fds, nfds_t nfds, int timeout);

		fds���������ļ������������顿

			struct pollfd {
				
				int fd��	���������ļ�������
				
				short events��	���������ļ���������Ӧ�ļ����¼�

						ȡֵ��POLLIN��POLLOUT��POLLERR

				short revnets��	����ʱ�� ��0����������Ӧ�¼��Ļ��� ���� ��0 --> POLLIN��POLLOUT��POLLERR
			}

		nfds: ��������ģ���ʵ�ʡ���Ч����������

		timeout:  > 0:  ��ʱʱ������λ�����롣

			  -1:	�����ȴ�

			  0��  ������

		����ֵ�����������Ӧ�����¼����ļ������� �ܸ�����

### 2��poll������ȱ��

	�ŵ㣺
		�Դ�����ṹ�� ���Խ� �����¼����� �� �����¼����� ���롣

		��չ �������ޡ� ���� 1024���ơ�

	ȱ�㣺
		���ܿ�ƽ̨�� Linux

		�޷�ֱ�Ӷ�λ��������¼����ļ��������� �����ѶȽϴ� 
		
### 3��ʾ����ʹ��poll����ʵ�ֶ�·IOת�ӷ�����

![poll����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/poll%E5%87%BD%E6%95%B0.png)

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
		//����fld,����cfd
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
				maxi = i; //�������ʹ�õ��±�
			printf("maxi:%d\n",maxi);
			printf("nread:%d\n", nready);
			if(--nready <= 0)
				continue;
		}
		//����cfd
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
					{//�յ�RST��־
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


## ����ͻ�� 1024 �ļ����������ƣ���ϵͳ�����йأ�

	cat /proc/sys/fs/file-max  --> ��ǰ��������ܴ򿪵�����ļ������� ��Ӳ��Ӱ�졣

	ulimit -a 	����> ��ǰ�û��µĽ��̣�Ĭ�ϴ��ļ�������������  ȱʡΪ 1024

	�޸ģ�
		�� sudo vi /etc/security/limits.conf�� д�룺

		* soft nofile 65536			--> ����Ĭ��ֵ�� ����ֱ�ӽ��������޸ġ� ��ע���û���ʹ����Ч��

		* hard nofile 100000			--> �����޸����ޡ�
	