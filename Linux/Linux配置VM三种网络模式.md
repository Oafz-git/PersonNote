# Linux��������
	
	# Ĭ������
	TYPE="Ethernet" 		# ����:��̫�������������õ����綼����̫����������·���㶼����̫��Э�飬û�б��Э�顣1982����̫��ͳһ����·���Э�顣
	PROXY_METHOD="none"		# ��������Ŀǰ���ã�ɾ��
	BRONSER_ONLY="no"		# ֻ���������ʹ�ã�û�ã�ɾ��
	B0OTPROTO="dhcp" 		# ��ȡip��ַ�ķ�����Ŀǰ��dhcp����Ϊstatic����ָ̬��ip��ַ��
	DEFROUTE="yes"			#Ĭ��·�ɣ�û�ã�ɾ��
	IPV4_FAILURE_FATAL="no"		# ����һ�п�ʼ��ʼ��������6�У���ɾ��
	IPVSINIT="yes"
	IPV6_AUTOCONF="yes"
	IPV6 DEFROUTE="yes"
	IPVS FAILURE FATAL="no"
	IPV6 ADDR GEN MoDE="stable-privacy"
	NAME="ens33�� 			#���ָ�Ϊens36
	UUID="15723721-cab7-40f6-bcee-4789906f8661"	#����Ψһ��ʶ�������û�ã�ɾ��
	DEVICE="ens33"
	ONBOOT="yes"
	
	#�޸ĺ������
	TYPE="Ethernet"				#��̫������
	BOOTPROTo="static"			#dhcp�Զ���ȡ none.static�ֶ�����
	NAME="ens33"				#���������	
	DEVICE="ens33"				#����������
	ONBOOT="'yes"				#��������
	IPADDR=192.168.61.100			#ip��ַ
	NETMASK=255.255.255.0			#��������
	
	
	#��ʵ����������dns�����Բ������ã���Ϊ��������������ֻҪ��һ�������������������ȵ����ü���
	GATEWAY=192.168.61.2	#����
	DNS1=223.5.5.5		#dns1
	DNS2=180.76.76.76	#dns2
	
# ��������`service network start`