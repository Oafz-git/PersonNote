# Socket���-UDP

## һ��TCPͨ�ź�UDPͨ�Ÿ��Ե���ȱ�㣺


	TCP��	�������ӵģ��ɿ����ݰ����䡣���ڲ��ȶ�������㣬��ȡ��ȫ�ֲ���ͨ�ŷ�ʽ�� �����ش���

		�ŵ㣺
			�ȶ���		
				���������ȶ����ٶ��ȶ���˳��
		ȱ�㣺
			�����ٶ��������ʵ͡�������

		ʹ�ó��������ݵ�������Ҫ��ϸߣ���׷��Ч�ʡ�

			  �����ݴ��䡢�ļ����䡣


	UDP��	�����ӵģ����ɿ������ݱ����ݡ����ڲ��ȶ�������㣬��ȡ��ȫ���ֲ���ͨ�ŷ�ʽ�� Ĭ�ϻ�ԭ����״��

		�ŵ㣺

			�����ٶȿ顣���ʸߡ�����С��

		ȱ�㣺
			���ȶ���
				�����������ٶȡ�˳��


		ʹ�ó�������ʱЧ��Ҫ��ϸ߳��ϡ��ȶ�����Ρ�

			  ��Ϸ����Ƶ���顢��Ƶ�绰��		��Ѷ����Ϊ������  ---  Ӧ�ò�����У��Э�飬�ֲ�udp�Ĳ��㡣


## ����UDPʵ�ֵ� C/S ģ�ͣ�

### 1.server

	lfd = socket(AF_INET, STREAM, 0);	SOCK_DGRAM --- ��ʽЭ�顣

	bind();

	listen();  --- ���п���

	while��1��{

		read(cfd, buf, sizeof) --- ���滻 --- recvfrom���� --- ����accept������ַ�ṹ��

		С-- ��
			
		write();--- ���滻 --- sendto����---- connect

		}

	close();
		
### 2.client
	
	connfd = socket(AF_INET, SOCK_DGRAM, 0);

	sendto�����������ĵ�ַ�ṹ���� ��ַ�ṹ��С��

	recvfrom����

	д����Ļ

	close();
		
* recv()/send() ֻ������ TCP ͨ�š� ��� read��write

* accpet(); ---- Connect(); ---������

### 3.recvfrom����
	
	ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);

		������
	
			sockfd�� �׽���

			buf����������ַ

			len����������С

			flags�� 0

			src_addr����struct sockaddr *��&addr ������ �Զ˵�ַ�ṹ

			addrlen�����봫����

		����ֵ�� 
		
			�ɹ������������ֽ����� 
			
			ʧ�ܣ�-1 errn�� 
			
			0�� �Զ˹رա�

### 4.sendto����
		
	ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
	
		������
		
			sockfd�� �׽���

			buf���洢���ݵĻ�����

			len�����ݳ���

			flags�� 0

			src_addr����struct sockaddr *��&addr ���롣 Ŀ���ַ�ṹ

			addrlen����ַ�ṹ���ȡ�

		����ֵ��
			
			�ɹ���д�������ֽ����� 
			
			ʧ�ܣ�-1�� errno		

### 5.ʾ����UDPʵ�ֲ����������Ϳͻ���

```C

```

## ���������׽��֣�

* IPC�� pipe��fifo��mmap���źš������ף�domain��--- CSģ��

### 1.�Ա������� TCP C/Sģ�ͣ� ע�����¼��㣺

	1. int socket(int domain, int type, int protocol); ���� domain��AF_INET --> AF_UNIX/AF_LOCAL 
	
							     type: SOCK_STREAM/SOCK_DGRAM  �����ԡ�	
	2. ��ַ�ṹ��  sockaddr_in --> sockaddr_un

		struct sockaddr_in srv_addr; --> struct sockaddr_un srv_adrr;

		srv_addr.sin_family = AF_INET;  --> srv_addr.sun_family = AF_UNIX;

		srv_addr.sin_port = htons(8888);    strcpy(srv_addr.sun_path, "srv.socket")

		srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);			len = offsetof(struct sockaddr_un, sun_path) + strlen("srv.socket");
	
		bind(fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr));  --> 	bind(fd, (struct sockaddr *)&srv_addr, len); 


	3. bind()�������óɹ����ᴴ��һ�� socket�����Ϊ��֤bind�ɹ���ͨ�������� bind֮ǰ�� ����ʹ�� unlink("srv.socket");


	4. �ͻ��˲������� ����ʽ�󶨡�������Ӧ����ͨ�Ž��������У������ҳ�ʼ��2����ַ�ṹ��

		1�� client_addr --> bind()

		2)  server_addr --> connect();


### 2.�Աȱ����׽��� �� �����׽��֡�
					
					�����׽���						�����׽���

	server��	lfd = socket(AF_INET, SOCK_STREAM, 0);				lfd = socket(AF_UNIX, SOCK_STREAM, 0);
		
			bzero() ---- struct sockaddr_in serv_addr;		bzero() ---- struct sockaddr_un serv_addr, clie_addr;

			serv_addr.sin_family = AF_INET;				serv_addr.sun_family = AF_UNIX;	
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			serv_addr.sin_port = htons(8888);			strcpy��serv_addr.sun_path, "�׽����ļ���"��
										len = offsetof(sockaddr_un, sun_path) + strlen();

										
			bind(lfd, (struct sockaddr *)&serv_addr, sizeof());	unlink("�׽����ļ���");
										bind(lfd, (struct sockaddr *)&serv_addr, len);  �������ļ�

			Listen(lfd, 128);					Listen(lfd, 128);

			cfd = Accept(lfd, ()&clie_addr, &len);			cfd = Accept(lfd, ()&clie_addr, &len);  


	client��		
			lfd = socket(AF_INET, SOCK_STREAM, 0);			lfd = socket(AF_UNIX, SOCK_STREAM, 0);

			" ��ʽ�� IP+port"					bzero() ---- struct sockaddr_un clie_addr;
										clie_addr.sun_family = AF_UNIX;
										strcpy��clie_addr.sun_path, "client�׽����ļ���"��
										len = offsetof(sockaddr_un, sun_path) + strlen();
										unlink( "client�׽����ļ���");
										bind(lfd, (struct sockaddr *)&clie_addr, len);

			bzero() ---- struct sockaddr_in serv_addr;		bzero() ---- struct sockaddr_un serv_addr;

			serv_addr.sin_family = AF_INET;				serv_addr.sun_family = AF_UNIX;
																	
			inet_pton(AF_INT, "������IP", &sin_addr.s_addr)							
										strcpy��serv_addr.sun_path, "server�׽����ļ���"��
			serv_addr.sin_port = htons("�������˿�");		
										
										len = offsetof(sockaddr_un, sun_path) + strlen();

			connect(lfd, &serv_addr, sizeof());			connect(lfd, &serv_addr, len);

### 3.ʾ����ʵ�ֱ����׽���