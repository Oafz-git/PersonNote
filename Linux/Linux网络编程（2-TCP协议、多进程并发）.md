# TCPЭ��

## һ��TCPͨ��ʱ���������ֺ��Ĵλ��֣�

	SYN,1000(0),<mss 1460>����������ͨ�ŵı�־λ,���ţ���Я�������ݵĴ�С����<�������ݵ�����>
	
	mss��Maximum Segment Size���� ����ĳ���
	
	ACK 1001��Ӧ��ı�־λ��1001--��ʾ1001��ǰ�����ݶ��յ���
	
	FIN����ɵı�־λ
	
**�������֣�**

	����������������ˣ����� SYN ��־λ�����������ӡ� Я����źš������ֽ���(0)���������ڴ�С��

	����������������ˣ����� ACK ��־λ��ͬʱЯ�� SYN �����־λ��Я����š�ȷ����š������ֽ���(0)���������ڴ�С��

	����������������ˣ����� ACK ��־λ��Ӧ���������������Я��ȷ����š�
	
**�Ĵλ��֣�**

	�����ر���������ˣ� ���� FIN ��־λ�� 

	�����ر���������ˣ� Ӧ�� ACK ��־λ�� 		 ----- ��ر���ɡ�


	�����ر���������ˣ� ���� FIN ��־λ��

	�����ر���������ˣ� Ӧ�� ACK ��־λ��		 ----- ����ȫ���ر�
	
![TCPͨ��ʱ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E9%80%9A%E4%BF%A1%E6%97%B6%E5%BA%8F.png)

## �����������ڣ�TCP�������ƣ�

	���͸����ӶԶˣ����˵Ļ�������С��ʵʱ������֤���ݲ��ᶪʧ
	
	win����������

![��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3.png)

## ����TCPЭ��ʱ�����

![TCPЭ��ͨѶ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E5%8D%8F%E8%AE%AE%E9%80%9A%E8%AE%AF%E6%B5%81%E7%A8%8B.png)

# ���������� 

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

# ����������

## һ������̲�����������server.c

	1. Socket();		���� �����׽��� lfd
	2. Bind()	�󶨵�ַ�ṹ Strcut scokaddr_in addr;
	3. Listen();	
	4. while (1) {

		cfd = Accpet();			���տͻ�����������
		pid = fork();
		if (pid == 0){			�ӽ��� read(cfd) --- С-���� --- write(cfd)

			close(lfd)		�ر����ڽ������ӵ��׽��� lfd

			read()
			С--��
			write()

		} else if ��pid > 0�� {	

			close(cfd);		�ر�������ͻ���ͨ�ŵ��׽��� cfd	
			contiue;
		}
	  }

	5. �ӽ��̣�

		close(lfd)

		read()

		С--��

		write()	

	   �����̣�

		close(cfd);

		ע���źŲ�׽������	SIGCHLD

		�ڻص������У� ����ӽ��̻���

			while ��waitpid()��;


## �������̲߳����������� server.c 

	1. Socket();		���� �����׽��� lfd

	2. Bind()		�󶨵�ַ�ṹ Strcut scokaddr_in addr;

	3. Listen();		

	4. while (1) {		

		cfd = Accept(lfd, );

		pthread_create(&tid, NULL, tfn, (void *)cfd);

		pthread_detach(tid);  				// pthead_join(tid, void **);  ���߳�---ר���ڻ������̡߳�
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





















