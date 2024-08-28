# Linux网络配置
	
	# 默认配置
	TYPE="Ethernet" 		# 类型:以太网，我们现在用的网络都是以太网，数据链路基层都是以太网协议，没有别的协议。1982年以太网统一了链路层的协议。
	PROXY_METHOD="none"		# 代理方法，目前无用，删除
	BRONSER_ONLY="no"		# 只允许浏览器使用，没用，删除
	B0OTPROTO="dhcp" 		# 获取ip地址的方法，目前是dhcp；改为static，静态指定ip地址。
	DEFROUTE="yes"			#默认路由，没用，删除
	IPV4_FAILURE_FATAL="no"		# 从这一行开始开始，往下数6行，都删掉
	IPVSINIT="yes"
	IPV6_AUTOCONF="yes"
	IPV6 DEFROUTE="yes"
	IPVS FAILURE FATAL="no"
	IPV6 ADDR GEN MoDE="stable-privacy"
	NAME="ens33” 			#名字改为ens36
	UUID="15723721-cab7-40f6-bcee-4789906f8661"	#这是唯一标识符，这个没用，删掉
	DEVICE="ens33"
	ONBOOT="yes"
	
	#修改后的配置
	TYPE="Ethernet"				#以太网类型
	BOOTPROTo="static"			#dhcp自动获取 none.static手动配置
	NAME="ens33"				#网络的名字	
	DEVICE="ens33"				#网卡的名字
	ONBOOT="'yes"				#开机自启
	IPADDR=192.168.61.100			#ip地址
	NETMASK=255.255.255.0			#子网掩码
	
	
	#其实下面网卡和dns都可以不用配置，因为我有两块网卡，只要有一块网卡有了下面网卡等的配置即可
	GATEWAY=192.168.61.2	#网关
	DNS1=223.5.5.5		#dns1
	DNS2=180.76.76.76	#dns2
	
# 重启网络`service network start`