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

## ���������������ϴ���������������������

```sheel
scp -r ./test/ oafz@192.168.252.128:/home/oafz/code 
```
