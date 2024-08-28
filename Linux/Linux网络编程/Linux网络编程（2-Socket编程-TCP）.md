# Socket���

## һ�������׽��ָ��socket

	һ���ļ�������ָ��һ���׽��֣����׽����ڲ����ں˽�������������ʵ�֡���

	��ͨ�Ź����У� �׽���һ���ǳɶԳ��ֵġ�
	
![�׽���ͨѶԭ��](https://img-blog.csdnimg.cn/img_convert/d0d34336162cb07337637e88271a287a.png)

## ���������ֽ���������ֽ����ת��������ip�Ͷ˿ڣ�

	С�˷�����pc���ش洢��Intel�ܹ���	��λ��ߵ�ַ����λ��͵�ַ��	int a = 0x12345678

	��˷���������洢��IDM��˾��	��λ��͵�ַ����λ��ߵ�ַ��

	#include <arpa/inet.h>
	
		htonl --> ����(host)--������(net) ��IP��			192.168.1.11 --> string --> atoi --> int --> htonl --> �����ֽ���

		htons --> ����--������ (port)

		ntohl --> ����--�� ���أ�IP��

		ntohs --> ����--�� ���أ�Port��
		
		h-->host;n-->network;l-->32λ������; s-->16λ������

## ����IP��ַת��������inet_pton����

	int inet_pton(int af, const char *src, void *dst);		�����ֽ���string IP�� ---> �����ֽ���

		af��AF_INET��AF_INET6

		src�����룬IP��ַ�����ʮ���ƣ�

		dst��������ת����� �����ֽ���� IP��ַ�� 

		����ֵ��

			�ɹ��� 1

			�쳣�� 0�� ˵��srcָ��Ĳ���һ����Ч��ip��ַ��

			ʧ�ܣ�-1
	
	const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);	�����ֽ��򣨶����ƣ� ---> �����ֽ���string IP��

		af��AF_INET��AF_INET6

		src: �����ֽ���IP��ַ

		dst�������ֽ���string IP��--������

		size�� dst �Ĵ�С����������С

		����ֵ�� �ɹ���dst�� 	

			ʧ�ܣ�NULL


## �ġ�sockaddr��ַ�ṹ��	IP + port	--> �����绷����Ψһ��ʶһ�����̡�

![sockaddr���ݽṹ](https://img-blog.csdnimg.cn/img_convert/a05070bf90ff67125ae18c5939af7547.png)

**man 7 ip����**

![man_7_ip](https://img-blog.csdnimg.cn/img_convert/4c0b2e03b8b1ba7beacb1ec483c999f0.png)

	//����
	struct sockaddr_in addr;      // #include<arpa/inet.h>
	
	//��ʼ��
	addr.sin_family = AF_INET/AF_INET6				
	addr.sin_port = htons(9527);
		int dst;
		inet_pton(AF_INET, "192.157.22.45", (void *)&dst);//���ʮ���ƣ��ַ������ͣ�תΪ�����ֽ���
	addr.sin_addr.s_addr = dst;
	��*��addr.sin_addr.s_addr = htonl(INADDR_ANY);		INADDR_ANYȡ����ϵͳ����Ч������IP��ַ�����������͡�תΪ�����ֽ���
	
	//ʹ��
	bind(fd, (struct sockaddr *)&addr, size);


## �塢socket������

![socketApi](https://img-blog.csdnimg.cn/img_convert/0f6c2f8a364a2ab1160d78eac4460d7a.png)

![socket����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/socket%E8%BF%9E%E6%8E%A5.png)

	#include <sys/socket.h>

	int socket(int domain, int type, int protocol);		����һ�� �׽���

		domain��AF_INET��AF_INET6��AF_UNIX

		type��SOCK_STREAM��TCP����SOCK_DGRAM��UDP��

		protocol: 0 

		����ֵ��
	
			�ɹ��� ���׽�������Ӧ�ļ�������

			ʧ��: -1 errno ��ʹ��perror();

---

	 #include <arpa/inet.h>

	 int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);		��socket��һ�� ��ַ�ṹ (IP+port)

		sockfd: socket ��������ֵ

			struct sockaddr_in addr;

			addr.sin_family = AF_INET;

			addr.sin_port = htons(8888);

			addr.sin_addr.s_addr = htonl(INADDR_ANY);

		addr: �������(struct sockaddr *)&addr

		addrlen: sizeof(addr) ��ַ�ṹ�Ĵ�С��

		����ֵ��

			�ɹ���0

			ʧ�ܣ�-1 errno

---

	int listen(int sockfd, int backlog);		����ͬʱ��������������ӵ�����������ͬʱ����3�����ֵĿͻ���������

		sockfd: socket ��������ֵ

		backlog��������ֵ�����ֵ 128.


		����ֵ��

			�ɹ���0

			ʧ�ܣ�-1 errno	

---
	
	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);	�����ȴ��ͻ��˽������ӣ��ɹ��Ļ�������һ����ͻ��˳ɹ����ӵ�socket�ļ���������
	��2��---ϵͳ����
		sockfd: socket ��������ֵ

		addr�������������ɹ���������������ӵ��Ǹ��ͻ��˵ĵ�ַ�ṹ��IP+port��

			socklen_t clit_addr_len = sizeof(addr);

		addrlen�����봫���� &clit_addr_len

			 �룺addr�Ĵ�С�� �����ͻ���addrʵ�ʴ�С��

		����ֵ��

			�ɹ�������ͻ��˽�������ͨ�ŵ� socket ��Ӧ���ļ�������

			ʧ�ܣ� -1 �� errno

---

	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);	  ʹ�����е� socket ���������������

		sockfd�� socket ��������ֵ

			struct sockaddr_in srv_addr;		// ��������ַ�ṹ

			srv_addr.sin_family = AF_INET;

			srv_addr.sin_port = 9527 	��������bindʱ�趨�� port ��ȫһ�¡�

			inet_pton(AF_INET, "��������IP��ַ"��&srv_adrr.sin_addr.s_addr);

		addr������������������ĵ�ַ�ṹ

		addrlen���������ĵ�ַ�ṹ�Ĵ�С

		����ֵ��

			�ɹ���0

			ʧ�ܣ�-1 errno

		�����ʹ��bind�󶨿ͻ��˵�ַ�ṹ, ����"��ʽ��".


## ����TCPͨ�����̷���:

	server:
		1. socket()	����socket

		2. bind()	�󶨷�������ַ�ṹ

		3. listen()	���ü�������

		4. accept()	���������ͻ�������

		5. read(fd)	��socket��ȡ�ͻ�������

		6. С--��д	toupper()

		7. write(fd)

		8. close();

	client:

		1. socket()	����socket

		2. connect();	���������������
		
		3. ���ն˶�ȡ����

		4. write()	д���ݵ� socket

		5. read()	��ת��������ݡ�

		6. ��ʾ��ȡ���

		7. close()
		
### ʾ����TCPͨ����ɿͻ��˺ͷ����

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
	char buf[BUFSIZ], clit_ip[BUFSIZ];//BUFSIZ ��ʾ4096

	struct sockaddr_in serv_addr,clit_addr;
	socklen_t clit_addr_len;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	lfd = socket(AF_INET,SOCK_STREAM,0);	//�����׽���
	if(lfd == -1)
	{
		sys_error("socket error");	
	}	

	ret = bind(lfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));//�󶨱���ip�Ͷ˿�
	if(ret == -1)
	{
		sys_error("bind error");
	}

	ret = listen(lfd,30);//�����׽��ֵ����������
	if(ret == -1)
	{
		sys_error("listen error");
	}	

	clit_addr_len = sizeof(clit_addr);
	cfd = accept(lfd,(struct sockaddr *)&clit_addr, &clit_addr_len);//������������,��������socket������
	if(cfd == -1)
	{
		sys_error("accept error");
	}
	printf("client ip:%s,port:%d\n",//��ӡ�ͻ���ip��port
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

	//����
	ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));	
	if(ret == -1)
	{
		sys_err("connect error");
	}
	while(1)	
	{
		ret = read(STDIN_FILENO, buf, sizeof(buf));
		//д
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

## �ߡ����������� 

	��װĿ�ģ� 

		�� server.c ��̹�����ͻ���߼��������������߼��ֿ�������ֱ����תman�ֲᡣ


	��wrap.c��								��wrap.h��


	�������ͨ����س��� �Զ��庯��						��� ����ͨ����س��� �Զ��庯��ԭ��(����)��

	������ʽ��ϵͳ���ú������ַ���д, ����鿴man�ֲ�
		
		  �磺Listen()��Accept();

	�������ܣ�����ϵͳ���ú����������������

	�� server.c �� client.c �е��� �Զ��庯��

	���ϱ��� server.c �� wrap.c ���� server
 
		 client.c �� wrap.c ���� client

---

	readn��
		�� N ���ֽ�
		
	readline��
		��һ��

	read �����ķ���ֵ��

		1. > 0 ʵ�ʶ������ֽ���

		2. = 0 �Ѿ�������β���Զ��Ѿ��رգ��� ���� ���� ����

		3. -1 Ӧ��һ���ж�errno��ֵ��

			errno = EAGAIN or EWOULDBLOCK: �����˷�������ʽ ���� û�����ݵ�� 

			errno = EINTR ����ϵͳ���ñ� �жϡ�

			errno = ����������� �쳣��



















