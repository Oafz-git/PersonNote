# 应用层

* 域名系统DNS（Domain Name System）
* 动态主机配置协议DHCP
* 文件传送协议FTP（File Transfer Protocol）
* 远程终端协议TELNET
* 远程桌面协议RDP
* 万维网WWW（World Wide Web）
* 电子邮件协议（SMTP, POP3, IMAP） 

## 一、域名系统DNS（Domain Name System）

1. DNS服务作用：负责将域名解析为IP地址
	* ？QQ能登录但网页打不开（可能是域名服务器出现了问题）

	* 互联网上的域名必须全球唯一
	
2. 域名结构

	* 顶级域名（根）、二级域名、三级域名
	
	* 电信域名服务器：222.222.222.222
	
	* 谷歌域名服务器：8.8.8.8
	
```
nslookup //查看域名服务器是否正常

nslookup www.sohu.com

ping www.sohu.com
```

3. 域名注册

4. 域名解析的过程（分布式）

5. 如何安装自己的DNS服务器（Windows）

	1. 如何管理DNS服务器？
	
	2. 如何配置所负责的域名解析？（正向查找区域）
	
		* 新建主机
		* 新建区域
		* 新建根区域

	3. 为甚麽需要安装自己的DNS服务器呢？（3种场景）
	
		* 解析内网自己的域名
		* 节省解析DNS服务器的流量
		* 域环境


## 二、动态主机配置DHCP服务器

1. 作用：已知MAC地址【广播】找到IP地址（逆向ARP）

2. DHCP客户端请求IP地址的过程【DHCP池】

3. 如何安装DHCP服务（Windows）

（1）安装DHCP服务——（2）新建作用域向导【起始IP地址——结束IP地址（必须和DHCP服务器的网段一致）】——（3）添加排除向导——（4）租约期限——（5）配置其它选项【网关、DNS服务器等】

【注】DHCP服务器必须是静态IP地址

```
ipconfig /all	//查看DHCP服务分配的所有IP地址

ipconfig /release	//主动释放DHCP服务分配的IP地址

ipconfig /renew	//重新获取DHCP服务分配的IP地址
```

4. [【实验】DHCP跨网段分配IP地址](https://blog.csdn.net/qq_38151401/article/details/105144547)

	1. 为多网段分配IP地址
	
		* 其它网段【广播】->本网段【单播】
	
		* 单网段【广播】
	
	2. 需要在路由器接口上使用`IP helper-address （DHCP服务器IP）`命令配置

## 3. 文件传输协议FTP

1. 连接方式

	1. TCP控制连接（传送操作命令）
	
	2. TCP数据连接
	
		1. 【主动模式】（FTP客户端告诉FTP服务器在使用什么端口侦听，FTP服务器（源端口，默认20）主动向FTP客户端的这个端口（目标端口）建立连接；
		2. 【被动模式】FTP服务器高速FTP客户量打开了一个新端口，等待FTP客户端进行连接；

2. 安装和配置FTP服务器：（1）安装FTP服务——（2）Internet信息服务（IIS）管理器——（3）新建FTP站点
			
	1. 可以通过浏览器访问FTP服务器（只能下载）
	
	2. 通过Windows资源管理器访问FTP服务（能下载和上传）：同时传两个文件会建立两个会话
	
	3. 如何查看使用什么模式和修改模式
	
		* `netstat -n`：如果使用的是20端口，说明使用了主动模式，否则使用了被动模式
		
		* 修改模式：在Windows资源管理器（工具）——Internet选项——可修改为主动模式

## 4. TELNET协议

1. 远程调试服务器/路由器（默认端口23）：`telent IP地址`

2. 测试远程服务器端口是否打开：`telnet IP地址 端口`

```
net user administrator （密码）a1！	//Windows重设密码为a1！

net localgroup （用户组）administrator （用户名）han /add	//将han添加到administrator用户组

shutdown -r -t 0	//远程重启
```

## 5. 远程桌面协议RDP（Remote Desktop Protrol）

* `mstsc`：微软终端客户端

* 可将用户添加至远程桌面组（Remote Desktop Users组）

* Server多用户操作系统：启用远程桌面可多用户同时使用服务器

* XP和Windows7单用户操作系统：不支持多用户同时登陆
 
* 可以使用远程桌面将本地硬盘映到远程（配置本地资源）

## 6. 万维网（www）和超文本传输协议HTTP（Hyper TextTransfer Protocol）

1. Windows如何安装web服务，创建web站点？

	* 如何区分网站？（网站的标识：可使用端口、IP地址、或域名（主机头）区分）

2. web代理服务器

	1. 代理服务器的用途：
	
		1. 节省内网访问Internet的带宽（缓存网站到web代理服务器）
		
		2. 可以绕过防火墙（翻墙）
		
		3. 可以避免跟踪
		
	2. 使用代理软件`CCProxy 6.0`：
		
		1. 在服务器上安装代理软件`CCProxy 6.0`
		
		2. 在浏览器上指定代理服务器IP地址
		
## 7.电子邮件（发邮件：SMTP   收邮件：POP3、IMAP）-邮件服务器

1. Internet发送和接收电子邮件的过程

```
nslookup

set type-mx	//进行邮箱查找

set type-a	//进行域名解析
```

2. 【实验步骤】安装和配置邮件服务器

	1. 准备邮件服务器环境
	
	2. 安装POP3服务、SMTP服务和DNS服务
	
	3. 在DNS服务器上创建`91xueit.com`和`51cto.com`
		
		* 创建主机记录`mail 192.168.80.100`
		
		* 创建邮件交换记录-MX记录
		
	4. 在POP3服务上创建域名，创建邮箱
	
	5. 配置SMTP服务器：创建远程域名`*.com`，允许发送到远程
	
	6. 配置outlookExpress客户端：指明收件的服务器和发邮件服务器，使用POP3协议收邮件
	
3. 搭建能够在Internet上使用的邮件服务器
	
	* 在Internet上注册域名MX记录
	
	* 邮件服务器有公网IP地址，或端口映射到邮件服务器































