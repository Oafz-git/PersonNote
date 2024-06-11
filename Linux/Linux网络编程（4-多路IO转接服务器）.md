# ��·IOת�ӷ�����

��·IOת�ӷ�����Ҳ����������IO�����������������ʵ�ֵ���ּ˼���ǣ�������Ӧ�ó����Լ����ӿͻ������ӣ��������ں���Ӧ�ó�������ļ���

![��·IOת�ӷ�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%A4%9A%E8%B7%AFIO%E8%BD%AC%E6%8E%A5%E6%9C%8D%E5%8A%A1%E5%99%A8%E8%AE%BE%E8%AE%A1%E6%80%9D%E8%B7%AF.png)

## һ��select

	ԭ��  �����ںˣ� select �������� �ͻ������ӡ�����ͨ���¼���

	void FD_ZERO(fd_set *set);	--- ���һ���ļ����������ϡ�

		fd_set rset;

		FD_ZERO(&rset);

	void FD_SET(int fd, fd_set *set);	--- �����������ļ�����������ӵ�����������

		FD_SET(3, &rset);	FD_SET(5, &rset);	FD_SET(6, &rset);


	void FD_CLR(int fd, fd_set *set);	--- ��һ���ļ��������Ӽ��������� �Ƴ���

		FD_CLR��4�� &rset��;

	int  FD_ISSET(int fd, fd_set *set);	--- �ж�һ���ļ��������Ƿ��ڼ��������С�

		����ֵ�� �ڣ�1�����ڣ�0��

		FD_ISSET��4�� &rset��;
		
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

˼·������

	int maxfd = 0��

	lfd = socket() ;			�����׽���

	maxfd = lfd��

	bind();					�󶨵�ַ�ṹ

	listen();				���ü�������

	fd_set rset�� allset;			����r��������

	FD_ZERO(&allset);				��r�����������

	FD_SET(lfd, &allset);			�� lfd ������������С�

	while��1�� {

		rset = allset��			�����������
	
		ret  = select(lfd+1�� &rset�� NULL�� NULL�� NULL);		�����ļ����������϶�Ӧ�¼���

		if��ret > 0�� {							�м����������������Ӧ�¼�
		
			if (FD_ISSET(lfd, &rset)) {				// 1 �ڡ� 0���ڡ�

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

select��ȱ�㣺

	ȱ�㣺	�����������ļ����������ơ� ��� 1024.

		�������������fd�� �Լ����ҵ���߼����С�� ����˱����Ѷȡ�

	�ŵ㣺	��ƽ̨��win��linux��macOS��Unix����Unix��mips

	

## ����poll��
	int poll(struct pollfd *fds, nfds_t nfds, int timeout);

		fds���������ļ������������顿

			struct pollfd {
				
				int fd��	���������ļ�������
				
				short events��	���������ļ���������Ӧ�ļ����¼�

						ȡֵ��POLLIN��POLLOUT��POLLERR

				short revnets��	����ʱ�� ��0����������Ӧ�¼��Ļ��� ���� ��0 --> POLLIN��POLLOUT��POLLERR
			}

		nfds: ��������ģ�ʵ����Ч����������

		timeout:  > 0:  ��ʱʱ������λ�����롣

			  -1:	�����ȴ�

			  0��  ������

		����ֵ�����������Ӧ�����¼����ļ������� �ܸ�����

	�ŵ㣺
		�Դ�����ṹ�� ���Խ� �����¼����� �� �����¼����� ���롣

		��չ �������ޡ� ���� 1024���ơ�

	ȱ�㣺
		���ܿ�ƽ̨�� Linux

		�޷�ֱ�Ӷ�λ��������¼����ļ��������� �����ѶȽϴ�

read ��������ֵ��
		
	> 0: ʵ�ʶ������ֽ���

	=0�� socket�У���ʾ�Զ˹رա�close����

	-1��	��� errno == EINTR   ���쳣�նˡ� ��Ҫ������

		��� errno == EAGIN �� EWOULDBLOCK �Է�������ʽ�����ݣ�����û�����ݡ�  ��Ҫ���ٴζ���

		��� errno == ECONNRESET  ˵�����ӱ� ���á� ��Ҫ close�������Ƴ��������С�

		���� 

ͻ�� 1024 �ļ����������ƣ�

	cat /proc/sys/fs/file-max  --> ��ǰ��������ܴ򿪵�����ļ������� ��Ӳ��Ӱ�졣

	ulimit -a 	����> ��ǰ�û��µĽ��̣�Ĭ�ϴ��ļ�������������  ȱʡΪ 1024

	�޸ģ�
		�� sudo vi /etc/security/limits.conf�� д�룺

		* soft nofile 65536			--> ����Ĭ��ֵ�� ����ֱ�ӽ��������޸ġ� ��ע���û���ʹ����Ч��

		* hard nofile 100000			--> �����޸����ޡ�
	
## ����epoll��
	int epoll_create(int size);						����һ�ü��������

		size�������ĺ�����ļ����ڵ��������������ں˲ο�����

		����ֵ��ָ���´����ĺ�����ĸ��ڵ�� fd�� 

			ʧ�ܣ� -1 errno

	int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);	�������������

		epfd��epoll_create �����ķ���ֵ�� epfd

		op���Ըü�������������Ĳ�����

			EPOLL_CTL_ADD ���fd�� ���������

			EPOLL_CTL_MOD �޸�fd�� ����������ϵļ����¼���

			EPOLL_CTL_DEL ��һ��fd �Ӽ����������ժ�£�ȡ��������

		fd��
			��������fd

		event��	���� struct epoll_event �ṹ�� ��ַ

			��Ա events��
	
				EPOLLIN / EPOLLOUT / EPOLLERR

			��Ա data�� �����壨�����壩��

				int fd;	  ��Ӧ�����¼��� fd

				void *ptr�� 

				uint32_t u32;

				uint64_t u64;		

		����ֵ���ɹ� 0�� ʧ�ܣ� -1 errno


	int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout); 	 ����������

		epfd��epoll_create �����ķ���ֵ�� epfd

		events�����������������顿�� ������������� ��Щ fd �ṹ�塣

		maxevents������ Ԫ�ص��ܸ����� 1024
				
			struct epoll_event evnets[1024]
		timeout��

			-1: ����

			0�� ������

			>0: ��ʱʱ�� �����룩

		����ֵ��

			> 0: ��������� �ܸ����� ��������ѭ�����ޡ�

			0�� û��fd��������¼�

			-1��ʧ�ܡ� errno


epollʵ�ֶ�·IOת��˼·��

	
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

epoll �¼�ģ�ͣ�

	ETģʽ��

		���ش�����

			������ʣ��δ���������ݲ��ᵼ�� epoll_wait ���ء� �µ��¼����㣬�Żᴥ����

			struct epoll_event event;

			event.events = EPOLLIN | EPOLLET;
	LTģʽ��

		ˮƽ���� -- Ĭ�ϲ���ģʽ��

			������ʣ��δ���������ݻᵼ�� epoll_wait ���ء�

	
	���ۣ�
		epoll �� ETģʽ�� ��Чģʽ������ֻ֧�� ������ģʽ�� --- æ��ѯ��

		struct epoll_event event;

		event.events = EPOLLIN | EPOLLET;

		epoll_ctl(epfd, EPOLL_CTL_ADD, cfd�� &event);	

		int flg = fcntl(cfd, F_GETFL);	

		flg |= O_NONBLOCK;

		fcntl(cfd, F_SETFL, flg);

	�ŵ㣺

		��Ч��ͻ��1024�ļ���������

	ȱ�㣺
		���ܿ�ƽ̨�� Linux��


epoll ��Ӧ��ģ�ͣ�

	epoll ETģʽ + ����������ѯ + void *ptr��

	ԭ����	socket��bind��listen -- epoll_create �������� ����� --  ���� epfd -- epoll_ctl() ���������һ������fd -- while��1��--

		-- epoll_wait ���� -- ��Ӧ����fd���¼����� -- ���� �����������顣 -- �жϷ�������Ԫ�� -- lfd���� -- Accept -- cfd ���� 

		-- read() --- С->�� -- write��ȥ��

	��Ӧ�ѣ�����Ҫ���� cfd �Ķ��¼�����Ҫ����cfd��д�¼���

		socket��bind��listen -- epoll_create �������� ����� --  ���� epfd -- epoll_ctl() ���������һ������fd -- while��1��--

		-- epoll_wait ���� -- ��Ӧ����fd���¼����� -- ���� �����������顣 -- �жϷ�������Ԫ�� -- lfd���� -- Accept -- cfd ���� 

		-- read() --- С->�� -- cfd�Ӽ����������ժ�� -- EPOLLOUT -- �ص����� -- epoll_ctl() -- EPOLL_CTL_ADD ���·ŵ�����ϼ���д�¼�

		-- �ȴ� epoll_wait ���� -- ˵�� cfd ��д -- write��ȥ -- cfd�Ӽ����������ժ�� -- EPOLLIN 

		-- epoll_ctl() -- EPOLL_CTL_ADD ���·ŵ�����ϼ������¼� -- epoll_wait ����

	eventset������

		���ûص�������   lfd --�� acceptconn()

				cfd --> recvdata();

				cfd --> senddata();
	eventadd������

		��һ��fd�� ��ӵ� �����������  ���ü��� read�¼������Ǽ���д�¼���


	�������У�  	read --- recv()

			write --- send();
	



























		
				
