
# �������

## һ��Э�飺
һ�����
	
![����Э��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%85%B8%E5%9E%8B%E5%8D%8F%E8%AE%AE.png)
	
## �����ֲ�ģ�ͽṹ��

	OSI�߲�ģ�ͣ�  ��������������ᡢ��Ӧ

	TCP/IP 4��ģ�ͣ�������·��/����ӿڲ㣩����������Ӧ

		Ӧ�ò㣺http��ftp��nfs��ssh��telnet������

		����㣺TCP��UDP

		����㣺IP��ICMP��IGMP

		��·�㣺��̫��֡Э�顢ARP
		
![OSIģ�ͺ�TCP/IPģ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/OSI%E6%A8%A1%E5%9E%8B%E5%92%8CTCP_IP%E6%A8%A1%E5%9E%8B.png)
![OSIģ��˵��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/OSI%E6%A8%A1%E5%9E%8B%E8%AF%B4%E6%98%8E.png)
**c/sģ�ͣ�**

	client-server

**b/sģ�ͣ�**

	browser-server

			C/S					B/S

	�ŵ㣺	����������ݡ�Э��ѡ�����			��ȫ�ԡ���ƽ̨��������������С

		�ٶȿ�

	ȱ�㣺	��ȫ�ԡ���ƽ̨�������������ϴ�			���ܻ���������ݡ��ϸ����� http



## �������紫�����̣���װ����

	����û�з�װ֮ǰ���ǲ����������д��ݡ�

	����-��Ӧ�ò�-�������-�������-����·��  --- ���绷��
	
![TCP/IPͨ�Ź���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP_IP%E9%80%9A%E4%BF%A1%E8%BF%87%E7%A8%8B.png)

	���ݰ��ڲ�ͬЭ���ĳ�ν
	
		���ݲ㣺��
		
		����㣺���ݱ�
		
		��·�㣺֡
		
![TCP/IP���ݰ�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP_IP%E5%B0%81%E8%A3%85%E8%BF%87%E7%A8%8B.png)
	
## �ġ���̫��֡Э�飨�㲥����

![��̫��֡��ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BB%A5%E5%A4%AA%E7%BD%91%E5%B8%A7%E6%A0%BC%E5%BC%8F.png)

	ARPЭ�飺���� Ip ��ַ��ȡ mac ��ַ��Ӳ����ַ����
	
	��̫��֡Э�飺����mac��ַ��������ݰ����䡣
	
![ARP���ݱ���ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ARP%E6%95%B0%E6%8D%AE%E6%8A%A5%E6%A0%BC%E5%BC%8F.png)

## �塢IPЭ�飺

![IP���ݱ���ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/IP%E6%95%B0%E6%8D%AE%E5%8C%85%E6%A0%BC%E5%BC%8F.png)
	
	�汾�� IPv4��IPv6  -- 4λ

	TTL�� time to live �� �������ݰ���·�ɽڵ��е���ת���ޡ�ÿ����һ��·�ɽڵ㣬��ֵ-1�� ��Ϊ0��·�ɣ������񽫸����ݰ�����

	ԴIP�� 32λ��--- 4�ֽ�		192.168.1.108 --- ���ʮ���� IP��ַ��string��  --->  ������ 

	Ŀ��IP��32λ��--- 4�ֽ�

	========

	IP��ַ�����������绷���У�Ψһ��ʶһ̨������

	�˿ںţ����������һ̨�����ϣ�Ψһ��ʶһ�����̡�

	ip��ַ+�˿ںţ����������绷���У�Ψһ��ʶһ�����̡�


## ����UDP��
	
	16λ��Դ�˿ںš�	2^16 = 65536  

	16λ��Ŀ�Ķ˿ںš�
	
![UDP���ݶθ�ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/UDP%E6%95%B0%E6%8D%AE%E6%AE%B5%E6%A0%BC%E5%BC%8F.png)

## �ߡ�TCPЭ�飺

	16λ��Դ�˿ںš�	2^16 = 65536  

	16λ��Ŀ�Ķ˿ںš�

	32���;

	32ȷ����š�	

	6����־λ��

	16λ���ڴ�С��	2^16 = 65536 
	
![TCP���ݶθ�ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E6%95%B0%E6%8D%AE%E6%AE%B5%E6%A0%BC%E5%BC%8F.png)


# Socket���

## һ�������׽��֣�  socket

	һ���ļ�������ָ��һ���׽��֣����׽����ڲ����ں˽�������������ʵ�֡���

	��ͨ�Ź����У� �׽���һ���ǳɶԳ��ֵġ�

## ���������ֽ���

	С�˷�����pc���ش洢��	��λ��ߵ�ַ����λ��͵�ַ��	int a = 0x12345678

	��˷���������洢��	��λ��͵�ַ����λ��ߵ�ַ��

	htonl --> ����--������ ��IP��			192.168.1.11 --> string --> atoi --> int --> htonl --> �����ֽ���

	htons --> ����--������ (port)

	ntohl --> ����--�� ���أ�IP��

	ntohs --> ����--�� ���أ�Port��

IP��ַת��������

	int inet_pton(int af, const char *src, void *dst);		�����ֽ���string IP�� ---> �����ֽ���

		af��AF_INET��AF_INET6

		src�����룬IP��ַ�����ʮ���ƣ�

		dst��������ת����� �����ֽ���� IP��ַ�� 

		����ֵ��

			�ɹ��� 1

			�쳣�� 0�� ˵��srcָ��Ĳ���һ����Ч��ip��ַ��

			ʧ�ܣ�-1
	
       const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);	�����ֽ��� ---> �����ֽ���string IP��

		af��AF_INET��AF_INET6

		src: �����ֽ���IP��ַ

		dst�������ֽ���string IP��

		size�� dst �Ĵ�С��

		����ֵ�� �ɹ���dst�� 	

			ʧ�ܣ�NULL


sockaddr��ַ�ṹ��	IP + port	--> �����绷����Ψһ��ʶһ�����̡�

	struct sockaddr_in addr;

	addr.sin_family = AF_INET/AF_INET6				man 7 ip

	addr.sin_port = htons(9527);
			
		int dst;

		inet_pton(AF_INET, "192.157.22.45", (void *)&dst);

	addr.sin_addr.s_addr = dst;

	��*��addr.sin_addr.s_addr = htonl(INADDR_ANY);		ȡ��ϵͳ����Ч������IP��ַ�����������͡�

	bind(fd, (struct sockaddr *)&addr, size);


socket������

	#include <sys/socket.h>

	int socket(int domain, int type, int protocol);		����һ�� �׽���

		domain��AF_INET��AF_INET6��AF_UNIX

		type��SOCK_STREAM��SOCK_DGRAM

		protocol: 0 

		����ֵ��
	
			�ɹ��� ���׽�������Ӧ�ļ�������

			ʧ��: -1 errno

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

	int listen(int sockfd, int backlog);		����ͬʱ��������������ӵ�����������ͬʱ����3�����ֵĿͻ���������

		sockfd: socket ��������ֵ

		backlog��������ֵ�����ֵ 128.


		����ֵ��

			�ɹ���0

			ʧ�ܣ�-1 errno	

	int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);	�����ȴ��ͻ��˽������ӣ��ɹ��Ļ�������һ����ͻ��˳ɹ����ӵ�socket�ļ���������

		sockfd: socket ��������ֵ

		addr�������������ɹ���������������ӵ��Ǹ��ͻ��˵ĵ�ַ�ṹ��IP+port��

			socklen_t clit_addr_len = sizeof(addr);

		addrlen�����봫���� &clit_addr_len

			 �룺addr�Ĵ�С�� �����ͻ���addrʵ�ʴ�С��

		����ֵ��

			�ɹ�������ͻ��˽�������ͨ�ŵ� socket ��Ӧ���ļ�������

			ʧ�ܣ� -1 �� errno

	
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


TCPͨ�����̷���:

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

		3. write()	д���ݵ� socket

		4. read()	��ת��������ݡ�

		5. ��ʾ��ȡ���

		6. close()

		
 




























	