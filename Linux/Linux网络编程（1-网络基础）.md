
# �������

## һ��Э�飺
һ�����
	
![����Э��](https://img-blog.csdnimg.cn/img_convert/10ffbc032d68c0f078d976752c8dbac6.png)
	
## �����ֲ�ģ�ͽṹ��

	OSI�߲�ģ�ͣ�  ��������������ᡢ��Ӧ

	TCP/IP 4��ģ�ͣ�������·��/����ӿڲ㣩����������Ӧ

		Ӧ�ò㣺http��ftp��nfs��ssh��telnet������

		����㣺TCP��UDP

		����㣺IP��ICMP��IGMP

		��·�㣺��̫��֡Э�顢ARP
		
![OSIģ�ͺ�TCP/IPģ��](https://img-blog.csdnimg.cn/img_convert/60ae0f1ffa8685e64b67e178e783eb86.png)
![OSIģ��˵��](https://img-blog.csdnimg.cn/img_convert/e476950927031934b06cb8f651cee1d8.png)
**c/sģ�ͣ�**

	client-server

**b/sģ�ͣ�**

	browser-server

			C/S					B/S

	�ŵ㣺	����������ݡ�Э��ѡ�����			��ȫ�ԡ���ƽ̨��������������С

		�ٶȿ�

	ȱ�㣺	��ȫ�ԡ���ƽ̨�������������ϴ�		���ܻ���������ݡ��ϸ����� http



## �������紫�����̣���װ����

	����û�з�װ֮ǰ���ǲ����������д��ݡ�

	����-��Ӧ�ò�-�������-�������-����·��  --- ���绷��
	
![TCP/IPͨ�Ź���](https://img-blog.csdnimg.cn/img_convert/d2449e72bd02b86fe61ac2aa1cb50832.png)

	���ݰ��ڲ�ͬЭ���ĳ�ν
	
		���ݲ㣺��
		
		����㣺���ݱ�
		
		��·�㣺֡
		
![TCP/IP���ݰ�����](https://img-blog.csdnimg.cn/img_convert/f3dfef78042393dd39a2a09f8a0068d2.png)
	
## �ġ���̫��֡Э�飨�㲥����

![ARP���ݱ���ʽ](https://img-blog.csdnimg.cn/img_convert/876b9451ac5d8854d06b4880b19c0641.png)

### 1.ARPЭ�飺���� Ip ��ַ��ȡ mac ��ַ��Ӳ����ַ��

![ARPЭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ARP%E5%8D%8F%E8%AE%AE.png)

### 2.��̫��֡Э�飺����mac��ַ�����·�װ��̫��֡��������ݰ�����

![��̫��֡��ʽ](https://img-blog.csdnimg.cn/img_convert/374ce50e4f42fe67990f6293c450d1f3.png)

## �塢IPЭ�飺

![IP���ݱ���ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/IP%E6%95%B0%E6%8D%AE%E6%8A%A5%E6%A0%BC%E5%BC%8F.png)

	�汾�� IPv4��IPv6  -- 4λ

	TTL�� time to live �� �������ݰ���·�ɽڵ��е���ת���ޡ�ÿ����һ��·�ɽڵ㣬��ֵ-1�� ��Ϊ0��·�ɣ������񽫸����ݰ�����

	ԴIP�� 32λ��--- 4�ֽ�		192.168.1.108 --- ���ʮ���� IP��ַ��string��  --->  ������ 

	Ŀ��IP��32λ��--- 4�ֽ�

---

	IP��ַ�����������绷���У�Ψһ��ʶһ̨������

	�˿ںţ����������һ̨�����ϣ�Ψһ��ʶһ�����̡�

	ip��ַ+�˿ںţ����������绷���У�Ψһ��ʶһ�����̡�


## ����UDPЭ�飺
	
	16λ��Դ�˿ںš�	2^16 = 65536 --- �������������˿ں���65535

	16λ��Ŀ�Ķ˿ںš�
	
![UDP���ݶθ�ʽ](https://img-blog.csdnimg.cn/img_convert/18d490ce0759b3196a7dd1f19bfa9990.png)

## �ߡ�TCPЭ�飺

	16λ��Դ�˿ںš�	2^16 = 65536 --- �������������˿ں���65535

	16λ��Ŀ�Ķ˿ںš�

	32���;	���������ڣ�

	32ȷ����š����������ڣ�

	6����־λ��

	16λ���ڴ�С��	2^16 = 65536 
	

![TCP���ݶθ�ʽ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E6%95%B0%E6%8D%AE%E6%AE%B5%E6%A0%BC%E5%BC%8F.png)

### 1. TCPͨ��ʱ���������ֺ��Ĵλ��֣�

![TCPͨ��ʱ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E9%80%9A%E4%BF%A1%E6%97%B6%E5%BA%8F.png)

	SYN, 1000(0), <mss 1460>����������ͨ�ŵı�־λ����־λռһ���ֽڣ�,���ţ���Я�������ݵĴ�С����<�������ݵ�����>
	
	mss��Maximum Segment Size���� ����ĳ���
	
	ACK 1001��Ӧ��ȷ�ϣ��ı�־λ��1001--��ʾ1001��ǰ�����ݶ��յ���
	
	FIN����ɵı�־λ
	
**�������֣�**

	�ͻ��ˣ�����������������ˣ����� SYN ��־λ�����������ӡ� Я����š������ֽ���(0)���������ڴ�С��

	����ˣ�����������������ˣ����� ACK ��־λ��ͬʱ����˷�����������Я�� SYN �����־λ��Я����š�ȷ����š������ֽ���(0)���������ڴ�С��

	�ͻ��ˣ�����������������ˣ����� ACK ��־λ��Ӧ���������������Я��ȷ����š�
	
**�Ĵλ��֣�**

	�ͻ��ˣ������ر���������ˣ� ���� FIN ��־λ�� 

	����ˣ������ر���������ˣ� Ӧ�� ACK ��־λ�� 		 ----- ��ر���ɡ�


	����ˣ������ر���������ˣ� ���� FIN ��־λ��

	�ͻ��ˣ������ر���������ˣ� Ӧ�� ACK ��־λ��		 ----- ����ȫ���ر�

#### ʾ����socket���ӻ�ͼ

![socket���ӻ�ͼ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/socket%E8%BF%9E%E6%8E%A5%E7%94%BB%E5%9B%BE.png)

### 2.�������ڣ�TCP�������ơ�������ִ��

	ָ����������С
	
	���͸����ӶԶˣ����˵Ļ�������С��ʵʱ������֤���ݲ��ᶪʧ
	
	win���������ڴ�С
	
	Ŀ�ģ���ֹ���ݶ�ʧ

![��������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3.png)

### 3. TCPЭ��ʱ����������Ķ�Ӧ��ϵ

![TCPͨ��ʱ�������Ķ�Ӧ��ϵ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E5%8D%8F%E8%AE%AE%E9%80%9A%E8%AE%AF%E6%B5%81%E7%A8%8B.png)

### 4. TCP״̬ת��

![TCP״̬ת��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81%E8%BD%AC%E6%8D%A2.png)

	1. ����������������ˣ�	CLOSE -- ����SYN -- SEND_SYN -- ���� ACK��SYN -- SEND_SYN -- ���� ACK -- ESTABLISHED������ͨ��̬��

	2. �����ر���������ˣ� ESTABLISHED������ͨ��̬�� -- ���� FIN -- FIN_WAIT_1 -- ����ACK -- FIN_WAIT_2����رգ�

				-- ���նԶ˷��� FIN -- FIN_WAIT_2����رգ�-- �ط�ACK -- TIME_WAIT��ֻ�������ر����ӷ����ᾭ����״̬��

				-- �� 2MSLʱ�� -- CLOSE 

	3. ����������������ˣ� CLOSE -- LISTEN -- ���� SYN -- LISTEN -- ���� ACK��SYN -- SYN_RCVD -- ����ACK -- ESTABLISHED������ͨ��̬��

	4. �����ر���������ˣ� ESTABLISHED������ͨ��̬�� -- ���� FIN -- ESTABLISHED������ͨ��̬�� -- ����ACK 

				-- CLOSE_WAIT (˵���Զˡ������ر����Ӷˡ����ڰ�ر�״̬) -- ����FIN -- LAST_ACK -- ����ACK -- CLOSE

	�ص���䣺 ESTABLISHED��FIN_WAIT_2 <--> CLOSE_WAIT��TIME_WAIT��2MSL��

`netstat -apn | grep  �˿ں�`���鿴ͨ��״̬

![TCP״̬](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81.png)

![TCP״̬-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81-1.png)

![TCP״̬-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81-2.png)

### 5�� 2MSLʱ��

	һ�������ڡ������ر���������ˡ��� --- ��Ӧ TIME_WAIT ״̬��

	��֤�����һ�� ACK �ܳɹ����Զ˽��ա����ȴ��ڼ䣬�Զ�û�յ��ҷ���ACK���Զ˻��ٴη���FIN���󡣣�

![2MSL](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/2MSL.png)

### 6�� �˿ڸ���

![�˿ڸ���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AB%AF%E5%8F%A3%E5%A4%8D%E7%94%A8.png)

	int opt = 1;		// ���ö˿ڸ��á�

	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

### 7����ر�

![��ر�״̬](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%8D%8A%E5%85%B3%E9%97%AD%E7%8A%B6%E6%80%81.png)



