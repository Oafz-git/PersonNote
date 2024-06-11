
# 网络基础

## 一、协议：
一组规则。
	
![网络协议](https://img-blog.csdnimg.cn/img_convert/10ffbc032d68c0f078d976752c8dbac6.png)
	
## 二、分层模型结构：

	OSI七层模型：  物、数、网、传、会、表、应

	TCP/IP 4层模型：网（链路层/网络接口层）、网、传、应

		应用层：http、ftp、nfs、ssh、telnet。。。

		传输层：TCP、UDP

		网络层：IP、ICMP、IGMP

		链路层：以太网帧协议、ARP
		
![OSI模型和TCP/IP模型](https://img-blog.csdnimg.cn/img_convert/60ae0f1ffa8685e64b67e178e783eb86.png)
![OSI模型说明](https://img-blog.csdnimg.cn/img_convert/e476950927031934b06cb8f651cee1d8.png)
**c/s模型：**

	client-server

**b/s模型：**

	browser-server

			C/S					B/S

	优点：	缓存大量数据、协议选择灵活			安全性、跨平台、开发工作量较小

		速度快

	缺点：	安全性、跨平台、开发工作量较大		不能缓存大量数据、严格遵守 http



## 三、网络传输流程（封装）：

	数据没有封装之前，是不能在网络中传递。

	数据-》应用层-》传输层-》网络层-》链路层  --- 网络环境
	
![TCP/IP通信过程](https://img-blog.csdnimg.cn/img_convert/d2449e72bd02b86fe61ac2aa1cb50832.png)

	数据包在不同协议层的称谓
	
		数据层：段
		
		网络层：数据报
		
		链路层：帧
		
![TCP/IP数据包过程](https://img-blog.csdnimg.cn/img_convert/f3dfef78042393dd39a2a09f8a0068d2.png)
	
## 四、以太网帧协议（广播）：

![ARP数据报格式](https://img-blog.csdnimg.cn/img_convert/876b9451ac5d8854d06b4880b19c0641.png)

### 1.ARP协议：根据 Ip 地址获取 mac 地址（硬件地址）

![ARP协议](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ARP%E5%8D%8F%E8%AE%AE.png)

### 2.以太网帧协议：根据mac地址，重新封装以太网帧，完成数据包传输

![以太网帧格式](https://img-blog.csdnimg.cn/img_convert/374ce50e4f42fe67990f6293c450d1f3.png)

## 五、IP协议：

![IP数据报格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/IP%E6%95%B0%E6%8D%AE%E6%8A%A5%E6%A0%BC%E5%BC%8F.png)

	版本： IPv4、IPv6  -- 4位

	TTL： time to live 。 设置数据包在路由节点中的跳转上限。每经过一个路由节点，该值-1， 减为0的路由，有义务将该数据包丢弃

	源IP： 32位。--- 4字节		192.168.1.108 --- 点分十进制 IP地址（string）  --->  二进制 

	目的IP：32位。--- 4字节

---

	IP地址：可以在网络环境中，唯一标识一台主机。

	端口号：可以网络的一台主机上，唯一标识一个进程。

	ip地址+端口号：可以在网络环境中，唯一标识一个进程。


## 六、UDP协议：
	
	16位：源端口号。	2^16 = 65536 --- 可以描述的最大端口号是65535

	16位：目的端口号。
	
![UDP数据段格式](https://img-blog.csdnimg.cn/img_convert/18d490ce0759b3196a7dd1f19bfa9990.png)

## 七、TCP协议：

	16位：源端口号。	2^16 = 65536 --- 可以描述的最大端口号是65535

	16位：目的端口号。

	32序号;	（滑动窗口）

	32确认序号。（滑动窗口）

	6个标志位。

	16位窗口大小。	2^16 = 65536 
	

![TCP数据段格式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E6%95%B0%E6%8D%AE%E6%AE%B5%E6%A0%BC%E5%BC%8F.png)

### 1. TCP通信时序（三次握手和四次挥手）

![TCP通信时序](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E9%80%9A%E4%BF%A1%E6%97%B6%E5%BA%8F.png)

	SYN, 1000(0), <mss 1460>：建立连接通信的标志位（标志位占一个字节）,包号（所携带的数据的大小），<传递数据的上限>
	
	mss（Maximum Segment Size）： 最大报文长度
	
	ACK 1001：应答（确认）的标志位，1001--表示1001以前的数据都收到了
	
	FIN：完成的标志位
	
**三次握手：**

	客户端：主动发起连接请求端，发送 SYN 标志位，请求建立连接。 携带序号、数据字节数(0)、滑动窗口大小。

	服务端：被动接受连接请求端，发送 ACK 标志位，同时服务端发起连接请求，携带 SYN 请求标志位。携带序号、确认序号、数据字节数(0)、滑动窗口大小。

	客户端：主动发起连接请求端，发送 ACK 标志位，应答服务器连接请求。携带确认序号。
	
**四次挥手：**

	客户端：主动关闭连接请求端， 发送 FIN 标志位。 

	服务端：被动关闭连接请求端， 应答 ACK 标志位。 		 ----- 半关闭完成。


	服务端：被动关闭连接请求端， 发送 FIN 标志位。

	客户端：主动关闭连接请求端， 应答 ACK 标志位。		 ----- 连接全部关闭

#### 示例：socket连接画图

![socket连接画图](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/socket%E8%BF%9E%E6%8E%A5%E7%94%BB%E5%9B%BE.png)

### 2.滑动窗口（TCP流量控制、批量回执）

	指定缓冲区大小
	
	发送给连接对端，本端的缓冲区大小（实时），保证数据不会丢失
	
	win：滑动窗口大小
	
	目的：防止数据丢失

![滑动窗口](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3.png)

### 3. TCP协议时序分析与代码的对应关系

![TCP通信时序与代码的对应关系](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E5%8D%8F%E8%AE%AE%E9%80%9A%E8%AE%AF%E6%B5%81%E7%A8%8B.png)

### 4. TCP状态转换

![TCP状态转换](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81%E8%BD%AC%E6%8D%A2.png)

	1. 主动发起连接请求端：	CLOSE -- 发送SYN -- SEND_SYN -- 接收 ACK、SYN -- SEND_SYN -- 发送 ACK -- ESTABLISHED（数据通信态）

	2. 主动关闭连接请求端： ESTABLISHED（数据通信态） -- 发送 FIN -- FIN_WAIT_1 -- 接收ACK -- FIN_WAIT_2（半关闭）

				-- 接收对端发送 FIN -- FIN_WAIT_2（半关闭）-- 回发ACK -- TIME_WAIT（只有主动关闭连接方，会经历该状态）

				-- 等 2MSL时长 -- CLOSE 

	3. 被动接收连接请求端： CLOSE -- LISTEN -- 接收 SYN -- LISTEN -- 发送 ACK、SYN -- SYN_RCVD -- 接收ACK -- ESTABLISHED（数据通信态）

	4. 被动关闭连接请求端： ESTABLISHED（数据通信态） -- 接收 FIN -- ESTABLISHED（数据通信态） -- 发送ACK 

				-- CLOSE_WAIT (说明对端【主动关闭连接端】处于半关闭状态) -- 发送FIN -- LAST_ACK -- 接收ACK -- CLOSE

	重点记忆： ESTABLISHED、FIN_WAIT_2 <--> CLOSE_WAIT、TIME_WAIT（2MSL）

`netstat -apn | grep  端口号`：查看通信状态

![TCP状态](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81.png)

![TCP状态-1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81-1.png)

![TCP状态-2](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/TCP%E7%8A%B6%E6%80%81-2.png)

### 5、 2MSL时长

	一定出现在【主动关闭连接请求端】。 --- 对应 TIME_WAIT 状态。

	保证：最后一个 ACK 能成功被对端接收。（等待期间，对端没收到我发的ACK，对端会再次发送FIN请求。）

![2MSL](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/2MSL.png)

### 6、 端口复用

![端口复用](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AB%AF%E5%8F%A3%E5%A4%8D%E7%94%A8.png)

	int opt = 1;		// 设置端口复用。

	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

### 7、半关闭

![半关闭状态](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%8D%8A%E5%85%B3%E9%97%AD%E7%8A%B6%E6%80%81.png)



