# ��·IOת�ӷ�������epoll��

�����������ԣ�https://blog.csdn.net/zero__007/article/details/121853458

## 1.epoll

![epoll](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/epoll.png)


## 2.epoll�������

	int epoll_create(int size);						����һ�ü��������

		size�������ĺ�����ļ����ڵ��������������ں˲ο�����

		����ֵ��ָ���´����ĺ�����ĸ��ڵ�� fd�� 

			ʧ�ܣ� -1 errno

---

	int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);	�������������

		epfd��epoll_create �����ķ���ֵ�� epfd

		op���Ըü�������������Ĳ�����

			EPOLL_CTL_ADD ���fd�� ���������

			EPOLL_CTL_MOD �޸�fd�� ����������ϵļ����¼���

			EPOLL_CTL_DEL ��һ��fd �Ӽ����������ժ�£�ȡ��������

		fd��
			��������fd

		event��	���� struct epoll_event ���ṹ�塿 ��ַ

				��Ա events��
		
					EPOLLIN / EPOLLOUT / EPOLLERR

				��Ա data�� �����壨�����壩��

					int fd;	  ��Ӧ�����¼��� fd

					void *ptr�� ����ָ�룺�ص�����ʱʹ��

					uint32_t u32;����ʹ�ã�

					uint64_t u64;����ʹ�ã�

		����ֵ���ɹ� 0�� ʧ�ܣ� -1 errno

---

	int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); 	 ����������

		epfd��epoll_create �����ķ���ֵ�� epfd

		events��������������-s ���顿�� ������������� ��Щ fd �ṹ�塣

		maxevents�����顾Ԫ�ص��ܸ�����- 1024
				
			struct epoll_event evnets[1024]
		timeout��

			-1: ����

			0�� ������

			>0: ��ʱʱ�� �����룩

		����ֵ��

			> 0: �����㡿�������ܸ����� ��������ѭ�����ޡ�

			0�� û��fd��������¼�

			-1��ʧ�ܡ� errno


### 2.ʾ����epollʵ�ֶ�·IOת��˼·��

	lfd = socket����;			���������¼�lfd
	bind();
	listen();

	int epfd = epoll_create(1024);				epfd, �����������������

	struct epoll_event tep, ep[1024];			tep, �������õ���fd���ԣ� ep �� epoll_wait() ��������������¼������顣

	tep.events = EPOLLIN;					��ʼ��  lfd�ļ������ԡ�
	tep.data.fd = lfd

	epoll_ctl(epfd�� EPOLL_CTL_ADD, lfd, &tep);		�� lfd ��ӵ�����������ϡ�

	while (1) {

		ret = epoll_wait(epfd�� ep��1024�� -1);			ʵʩ����

		for (i = 0; i < ret; i++) {
			
			if (ep[i].data.fd == lfd) {				// lfd ������¼������µĿͻ��˷�����������

				cfd = Accept();

				tep.events = EPOLLIN;				��ʼ��  cfd�ļ������ԡ�
				tep.data.fd = cfd;

				epoll_ctl(epfd�� EPOLL_CTL_ADD, cfd, &tep);

			} else {						cfd �� ������¼��� �пͻ���д��������

				n = read(ep[i].data.fd, buf, sizeof(buf));

				if ( n == 0) {

					close(ep[i].data.fd);

					epoll_ctl(epfd�� EPOLL_CTL_DEL, ep[i].data.fd , NULL);	// ���رյ�cfd���Ӽ�������ժ�¡�

				} else if ��n > 0�� {

					С--��
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
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));      //�˿ڸ���
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    Listen(listenfd, 20);

    efd = epoll_create(OPEN_MAX);               //����epollģ��, efdָ���������ڵ�
    if (efd == -1)
        perr_exit("epoll_create error");

    struct epoll_event tep, ep[OPEN_MAX];       //tep: epoll_ctl����  ep[] : epoll_wait����

    tep.events = EPOLLIN; 
    tep.data.fd = listenfd;           //ָ��lfd�ļ���ʱ��Ϊ"��"

    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);    //��lfd����Ӧ�Ľṹ�����õ�����,efd���ҵ�����
    if (res == -1)
        perr_exit("epoll_ctl error");

    for ( ; ; ) {
        /*epollΪserver���������¼�, epΪstruct epoll_event��������, OPEN_MAXΪ��������, -1����������*/
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); 
        if (nready == -1)
            perr_exit("epoll_wait error");

        for (i = 0; i < nready; i++) {
            if (!(ep[i].events & EPOLLIN))      //�������"��"�¼�, ����ѭ��
                continue;

            if (ep[i].data.fd == listenfd) {    //�ж������¼���fd�ǲ���lfd            
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);    //��������

                printf("received from %s at PORT %d\n", 
                        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), 
                        ntohs(cliaddr.sin_port));
                printf("cfd %d---client %d\n", connfd, ++num);

                tep.events = EPOLLIN; tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);      //��������
                if (res == -1)
                    perr_exit("epoll_ctl error");

            } else {                                                    //����lfd, 
                sockfd = ep[i].data.fd;
                n = Read(sockfd, buf, MAXLINE);

                if (n == 0) {                                           //����0,˵���ͻ��˹ر�����
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //�����ļ��������Ӻ����ժ��
                    if (res == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);                                      //�ر���ÿͻ��˵�����
                    printf("client[%d] closed connection\n", sockfd);

                } else if (n < 0) {                                     //����
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);  //ժ���ڵ�
                    Close(sockfd);

                } else {                                                //ʵ�ʶ������ֽ���
                    for (i = 0; i < n; i++)
                        buf[i] = toupper(buf[i]);                       //ת��д,д�ظ��ͻ���

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


### 3.epoll �¼�ģ�ͣ�

![ET_LTģ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ET_LT%E6%A8%A1%E5%9E%8B.png)

	ETģʽ��

		���ش�������Чģʽ������ֻ֧�� ������ģʽ�� --- æ��ѯ��

			������ʣ��δ���������ݲ��ᵼ�� epoll_wait ���ء� �µ��¼����㣬�Żᴥ����

			struct epoll_event event;

			event.events = EPOLLIN | EPOLLET;
	LTģʽ��

		ˮƽ������Ĭ�ϲ���ģʽ��

			������ʣ��δ���������ݻᵼ�� epoll_wait ���ء�
			
* ���� LT ģʽ�������ļ����������� epoll_wait ��⵽�������¼������������¼�֪ͨӦ�ó����Ӧ�ó�����Բ�����������¼�����������Ӧ�ó�����һ�ε��� epoll_wait ʱ�������ٴ���Ӧ�ó���ͨ����¼���ֱ�����¼�������

* ���� ET ģʽ�������ļ����������� epoll_wait ��⵽�������¼������������¼�֪ͨӦ�ó����Ӧ�ó����������������¼�����Ϊ������ epoll_wait ���ý�������Ӧ�ó���֪ͨ��һ�¼�������**ETģʽ�ںܴ�̶��Ͻ�����ͬһ�� epoll �¼����ظ������Ĵ��������Ч�ʱ� LT ģʽ�ߡ�**

### 4.epoll��ETģʽ��ʹ��

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

    event.events = EPOLLIN | EPOLLET;     /* ET ���ش�����Ĭ����ˮƽ���� */

    //event.events = EPOLLIN;
    printf("Accepting connections ...\n");
    cliaddr_len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    printf("received from %s at PORT %d\n",
            inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
            ntohs(cliaddr.sin_port));

    flag = fcntl(connfd, F_GETFL);          /* �޸�connfdΪ�������� */
    flag |= O_NONBLOCK;
    fcntl(connfd, F_SETFL, flag);

    event.data.fd = connfd;
    epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event);      //��connfd������������
    while (1) {
        printf("epoll_wait begin\n");
        res = epoll_wait(efd, res_event, 10, -1);        //���10��, ��������
        printf("epoll_wait end res %d\n", res);

        if (res_event[0].data.fd == connfd) {
            while ((len = read(connfd, buf, MAXLINE/2)) >0 )    //��������, ��ѯ
                write(STDOUT_FILENO, buf, len);
        }
    }

    return 0;
}
```

### 4.epoll����ȱ��

	�ŵ㣺
		��Ч��ͻ��1024�ļ���������

	ȱ�㣺
		���ܿ�ƽ̨�� Linux��

### 5.epoll ��Ӧ��ģ�ͣ��ܿ���ģ�ʹ��룩

	epoll ETģʽ + ����������ѯ + void *ptr��

	ԭ����	socket��bind��listen -- epoll_create �������� ����� --  ���� epfd -- epoll_ctl() ���������һ������fd -- while��1��--

		-- epoll_wait ���� -- ��Ӧ����fd���¼����� -- ���� �����������顣 -- �жϷ�������Ԫ�� -- lfd���� -- Accept -- cfd ���� 

		-- read() --- С->�� -- write��ȥ��

	��Ӧ�ѣ�����Ҫ���� cfd �Ķ��¼�����Ҫ����cfd��д�¼���

		socket��bind��listen -- epoll_create �������� ����� --  ���� epfd -- epoll_ctl() ���������һ������fd -- while��1��--

		-- epoll_wait ���� -- ��Ӧ����fd���¼����� -- ���� �����������顣 -- �жϷ�������Ԫ�� -- lfd���� -- Accept -- cfd ���� 

		-- read() --- С->�� ��-- cfd�Ӽ����������ժ�� -- EPOLLOUT���ж��Ƿ��д���������д�¼���ԭ������ʵ�ʻ����У����ܳ��ְ�ر�״̬�򻬶���������������޷�д����ȥ��
		
		-- �ص����� -- epoll_ctl() -- EPOLL_CTL_ADD ���·ŵ�����ϼ���д�¼�-- �ȴ� epoll_wait ���� -- ˵�� cfd ��д -- write��ȥ 
		
		-- cfd�Ӽ����������ժ�� -- EPOLLIN -- epoll_ctl() -- EPOLL_CTL_ADD ���·ŵ�����ϼ������¼� -- epoll_wait ������


	



























		
				
