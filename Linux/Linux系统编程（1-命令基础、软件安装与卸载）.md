![Unix家谱](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Unix%E5%AE%B6%E8%B0%B1.jpg)
# 一、shell简介

shell：命令解释器，根据输入的命令执行相应命令。

![shell](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Unix%E7%B3%BB%E7%BB%9F%E4%BD%93%E7%B3%BB%E7%BB%93%E6%9E%84.png)

* 查看当前系统有哪些shell：

```shell
cat /etc/shells

	/bin/sh		已经被/bin/bash取代
	/bin/bash	Linux默认的shell
	/bin/ksh	Kornshell有AT&T Bell lab 发展出来的，兼容于bash
	/bin/tcsh	整合 C Shell，提供更多的功能
	/bin/csh	被/bin/tcsh所取代
	/bin/zsh	基于ksh发展出来的，功能更强大的shell
```

* 查看当前系统正在使用的shell

```shell
echo $SHELL 
	echo：回显，显示字符串；$：（取值）把命令解释器取出；SHELL：指命令解释器

env 	把当前系统所有的环境变量都显示出来

top 	文字版的任务管理器

kill 	杀死进程

ps	查看系统级下的进程状态

jobs	查看当前用户下的进程状态，

alias	给命令起别名

umask [-p] -S [mode] 
	umask指定用户创建文件时的掩码，其中的mode和chmod的命令中的格式一样。如果不用mode参数，则显示当前的umask设置。如果使用-S，则以符号形式显示设置。
```



* 主键盘快捷键

|   功能    |  快捷键   |       助记       |
| :-------: | :-------: | :--------------: |
|    上     |  Ctrl-p   |     previous     |
|    下     |  Ctrl-n   |       next       |
|    左     |  Ctrl-b   |     backward     |
|    右     |  Ctrl-f   |     forward      |
|    Del    |  Ctrl-d   | delete光标后面的 |
|   Home    |  Ctrl-a   | the first letter |
|    End    |  Ctrl-e   |       end        |
| Backspace | Backspace | delete光标前面的 |

热键呼出终端`Ctrl-p`

# 二、类Unix系统目录结构

## 1./ 根目录

	bin	系统可执行程序，如命令
	boot	内核和启动程序，所有和启动相关文件都存在这里
		grub	引导器相关文件
	dev	存放设备文件
	home	用户的主目录。下面是自己定义的用户名的文件夹
	etc	系统软件的启动和配置文件，系统在启动过程中需要读取的文件都在这个目录。如LIL0参数、用户账号和密码
	lib	系统程序库文件，这个目录里存放着系统最基本的动态链接共享库，类似于Windows下的system32目录，几乎所有的应用程序都需要用到这些共享库
	media	挂载媒体设备、如光驱、U盘等
	mnt	目录是让用户临时挂载别的文件系统，如挂载Windows下的某个分区，ubuntu默认还是挂载在/media目录
	opt	可选的应用软件包（很少使用）
	proc	这个目录是系统内存的映射，我们可以直接访问这个目录来获取系统信息。也就是说，这个目录的内容不在硬盘而是在内存里
	sbin	管理员系统程序
		selinux
		
	srv
	sys	udev用到的设备目录树，/sys反映你机器当前所接的设备
	tmp	临时文件夹
	root	管理员宿主目录（家目录）
	usr	用户资源管理目录
		bin	应用程序
		game	游戏程序
		include
		lib	应用程序的库文件
		lib64
		local	包含用户程序等
		sbin	管理员应用程序

## 2.Linux系统文件类型

	普通文件：-

	目录文件：d

	字符设备文件：c

	块设备文件：b

	软连接：l

	管道文件：p

	套接字：s

	未知文件：。

# 三、基础命令行

## a.目录、文件命令

### 1、ls

```shell
ls [参数] [目录]
	-a  #显示所有档案及目录（ls内定将档案名或目录名称为“.”的视为影藏，不会列出）；
	-A  #显示除影藏文件“.”和“…”以外的所有文件列表；
	-l  #与“-C”选项功能相反，所有输出信息用单列格式输出，不输出为多列；
	-h  #以人类的方式查看
	-F  #在每个输出项后追加文件的类型标识符，具体含义：“”表示具有可执行权限的普通文件，“/”表示目录，“@”表示符号链接，“|”表示命令管道FIFO，“=”表示sockets套接字。当文件为普通文件时，不输出任何标识符；类型标识符
	-b  #将文件中的不可输出的字符以反斜线“”加字符编码的方式输出；
	-c  #与“-lt”选项连用时，按照文件状态时间排序输出目录内容，排序的依据是文件的索引节点中的ctime字段。与“-l”选项连用时，则排序的一句是文件的状态改变时间；
	-d  #仅显示目录名，而不显示目录下的内容列表。显示符号链接文件本身，而不显示其所指向的目录列表；
	-f  #此参数的效果和同时指定“aU”参数相同，并关闭“lst”参数的效果；
	-i  #显示文件索引节点号（inode）。一个索引节点代表一个文件；
	–file-type  #与“-F”选项的功能相同，但是不显示“”；
	-k  #以KB（千字节）为单位显示文件大小；
	-l  #以长格式显示目录下的内容列表。输出的信息从左到右依次包括文件名，文件类型、权限模式、硬连接数、所有者、组、文件大小和文件的最后修改时间等；
	-m  #用“,”号区隔每个文件和目录的名称；
	-n  #以用户识别码和群组识别码替代其名称；
	-r  #以文件名反序排列并输出目录内容列表；
	-s  #显示文件和目录的大小，以区块为单位；
	-t  #用文件和目录的更改时间排序；
	-L  #如果遇到性质为符号链接的文件或目录，直接列出该链接所指向的原始文件或目录；
	-R  #递归处理，将指定目录下的所有文件及子目录一并处理；
	–full-time  #列出完整的日期与时间；
	–color[=WHEN]  #使用不同的颜色高亮显示不同类型的。
```

### 2、Which

```shell
which ls 查看制定命令所在路径
```

如何省略用户头：`vi .bashrc`，添加`PS1=$`

### 3、pwd

```shell
pwd 查看当前所在目录
```

### 4、mkdir

```shell
mkdir [OPTION] DIRECTORY
	创建目录DIRECTORY，可以一次创建多个。如果OPTION是-p，表示可以连同父目录一起创建。
```

### 5、rmdir

```shell
rmdir [OPTION] DIRECTORY
	删除空目录，可以一次删除多个。OPTION如果是-p，表示可以连同空的父目录一起删除。
	空目录：只包含.和..的目录为空目录。
```

### 6、touch

```shell
touch [OPTION] FILE
	将每个文件的访问及修改时间都更新为目前的时间
	如果文件不存在，则创建一个字节数为0的文件
```

### 7、rm

```shell
rm file 
	删除文件或目录
	-r 递归删除
	-f 强制删除
```

### 8、mv

```shell
mv file1 file2 
	文件重命名
	移动文件
```

### 9、cp

```shell
拷贝文件
	cp file1 file2
	cp file1 dir/
	cp file1 ../

拷贝目录
	cp dir1 dir2 #如果dir1不是空的，会显示“略过目录”

	cp -r dir1 dir2 
	cp -r dir1 ~/
	cp -a dir1 dir2 
	cp -a dir1 ~/
		-r #递归
		-a #all，全部
		-r和-a的区别：-a的拷贝过去的最后修改时间不会改变
```

## b.文件读取命令行

### 1.cat

```shell
cat file 
	查看文件内容，输出到终端；
	如果cat后没跟文件名，则读取终端的标准输入，遇到\n后，输出标准输出，终端下输入Ctrl-d表示结束

tac file 
	将文件内容倒序输出到终端
```

### 2、more、less

```shell
more [OPTION] FILE
less [OPTION] FILE
	查看文本文件内容，屏幕显示完一屏就等待用户按下任意键再滚动到下一屏，如果中途不想继续看下去，可以按Ctrl-c或Ctrl-q终止显示
```

### 3、head、tail

```shell
head [OPTION] FILE 
	显示指定文件的前几行。如果没有指定文件，将从标准输入（键盘）上读取；如果没有指定要显示的行数，则默认显示前10行，指定行数：head -5 file

tail [OPTION] FILE 
	显示指定文件的后几行。	tail -5 file
```

### 4、tree

```shell
tree	按结构树的形状显示目录和文件
```

### 5、du、df

```shell
du -h   查看每个文件的大小
df -h   查看磁盘的占用大小
```

### 6、ln

链接有两种，一种被称为硬链接，另一种被称为软连接（符号链接）。

**硬链接**：链接文件和被链接文件必须位于同一个**文件系统**中，并且不能建立指向目录的硬链接。

*特征*：修改任意的链接或被链接文件，所有文件内容都会修改。

```shell
ln hello word_h
```

```shell
stat file.h
	硬链接原理：使用Inode/唯一编号
	删除硬链接的时候：操作的是硬链接基数-1
```

**软连接**：

```shell
ln -s hello word_s
```

# 四、文件属性和用户用户组

## 1、whoami

```shell
whoami 	查看当前登录用户
```

## 2、chmod

***1）文字设定法***


	chmod [who] [+|-|=] [mode] 文件名

		操作对象who可是下述字母中的任一个或它们的组合：	
			u表示“用户（user）”，即文件或目录的所有者	
			g表示“同组（group）用户”，即与文件属主有相同组ID的所有用户
			o表示“其他（others）用户”
			a表示“所有（all）用户”，它表示系统默认值
		操作符号
			+添加某个权限
			-取消某个权限
			=赋予某个权限
		mode表示权限可用下述字母的任意组合
			r可读
			w可写
			x可执行

***2）数字设定法***


	chmod [mode] 文件名

		数字表示的属性：
			0表示没有权限
			1表示可执行权限
			2表示可写权限
			4表示可读权限

## 3、chown、chgrp

```shell
chown [OPTION]... [OWNER:GROUP] FILE... 
chown [OPTION]... -reference=RFILE FILE...
	-R 递归式地改变指定目录及其下的所有子目录和文件的拥有者。
	-v 显示chown命令所做的工作。
```

## 4、adduser/passwd/deluser

在`/etc`目录下的`passwd`文件中有用户和用户组信息：

![passwd](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/linux1.png)

```shell
sudo adduser username  	添加用户
	
sudo deluser username 	删除用户
	
sudo chown username filename 	sudo chown 新用户名 待修改文件
```

```shell
sudo addgroup g88 	添加用户组

sudo delgroup g88 	删除用户组

sudo chgrp g88 a.c	sudo chgrp 新用户组名 待修改文件
```

### 示例：把一个文件改为`nobody`用户和`nogroup`用户组所有

```shell
sudo chown nobody:nogroup fiel1
```

# 五、查找与检索

## 1、find（找文件）

```shell
find ./ -type 'l'  	通过文件类型搜索文件
find ./ -name '*.jpg'	通过文件名字搜索文件
find ./ -maxdepth 2 -name '*.jpg'	-maxdepth 2 指find的目录层级
find ./ -size +20M -size -50M 		通过文件大小查找文件（大于20M，小于50M）
-atime # access 	最近访问时间
-mtime # modify 	最近更改时间
-ctime # change 	最近改动时间，按天
	find ./ -ctime 1

find /usr/ -name "*tmp*" -exec ls -l {} \; 	如果执行 rm -r，不询问
find ./ -name "*tmp" -ok rm {} \; 		如果执行 rm -r，询问
	-xargs：将find搜索的结果集执行某一指定命令。当结果集数量过大时，可以分片映射，提高效率；
	find /usr/ -name '*tmp*' | xargs ls -ld

-xargs 和 -exec 的区别：
	（1）-xargs 与 | 同时使用
	（2）-xargs 当结果集数量过大时，可以分片映射，提高效率；
	（3）-xargs 以“空格”作为分割依据
	find ./ -maxdepth 1 -type f -print0 | xargs -print0 ls -l #以“null”作为拆分依据
```

## 2、stat

 ***查看Inode节点***

```shell
stat 文件名
```

![stat命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/linux2.png)

## 3、grep

***根据文件内容检索***

```shell
grep -r 'copy' ./ -n 	'copy'：文件内容 -n：会显示出行号
```

## 4、ps

ps命令用于监控后台进程的工作情况，因为后台进程是不合屏幕键盘等输出设备进行通信，所以需要检测其情况；

```shell
ps [选项] # 显示当前跟用户交互的进程
	-e # 显示所有进程
	-f # 全格式
	-h # 不显示标题
	-l # 长格式
	-w # 宽输出
	-r # 只显示正在运行的进程
	-a # 即all，查看当前系统所有用户的所有进程
	-u # 查看进程所有者及其他一些详细信息
	-x # 显示没有控制终端的进程
ps aux | grep 'cupsd' # 检索进程结果集
```

## 5、locate

查找符合条件的文件

## 6、manpage使用

	man -k keyword：搜索包含关键字的手册页。
	
	man -f command：显示命令的简短描述，相当于 whatis 命令。
	
	man --help：显示 man 命令的帮助信息。
	
	man -a command：显示所有匹配的手册页。

# 六、软件包安装

## 1、apt-get

![](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/linux3.png)

```shell
sudo apt-get update 		更新本地软件列表
sudo apt-get install 软件名 	安装软件
sudo apt-get remove 软件名 	卸载软件
```

**aptitude**与apt-get类似

```shell
sudo aptitude show tree 	查看tree是否已经安装，这是apt-get没有的
```

## 2、deb包安装

```shell
sudo dpkg -i xxx.deb 		安装deb软件包命令
sudo dpkg -r xxx.deb 		删除软件包命令
sudo dpkg -r --purge xxx.deb 	连同配置文件一起删除命令
sudo dpkg -info xxx.deb 	查看软件包信息命令
sudo dpkg -L xxx.deb 		查看文件拷贝详情命令
sudo dpkg -l 			查看系统中已安装软件包信息命令
sudo dpkg-reconfigure xxx 	重新配置软件包命令
```

## 3、源码包安装

1. 解压缩源码包
2. `cd dir`
3. `./configure` 检测文件是否缺失，创建Makefile，检测编译环境
4. `make` 编译源码，生成库和可执行程序
5. `sudo make install` 把库和可执行程序，安装到系统路径下
6. `sudo make distclean` 删除和卸载软件 

# 七、压缩包管理

## 1、tar

tar [主选项+辅选项] 文件或目录  ***打包***

tar可以为文件和目录创建档案。利用tar命令用户可以为某一特定文件创建档案，也可以在档案中改变文件，或者向档案中加入新的文件。使用该命令时，主选项是必须要有的，辅选项是辅助使用的，可以选用。

```shell
tar -zcvf 要生成的压缩包名（带.tar.gz后缀） 压缩文件
```

**主选项：**

```shell
c # 创建新的档案文件。如果用户想备份一个目录或一些文件，就要选择这个选项，create（常用）
r # 把要存档的文件追加到档案文件的末尾
t # 列出档案文件的内容，查看已经备份了哪些文件
u # 更新文件。用新增的文件取代原备份文件，如果在备份文件中找不到要更新的文件，则把它追加到备份文件的最后。
x # 从档案文件中释放文件（常用）
```

**辅选项：**

```shell
z # 指gzip来压缩/解压缩文件，加上该选项后可以将档案文件进行压缩，但还原时也一定要使用该选项进行解压缩（常用）
v # 指压缩说明；详细报告tar处理的文件信息（常用）
f # 指file，文件；使用档案文件或设备这个选项通常是必选的（常用）
k # 保存已经存在的文件
m # 在还原文件时，把所有文件的修改时间设定为现在
M # 创建多卷的档案文件，以便在几个磁盘中存放
W # 每一步都要求确认
j # 用bzip2来压缩/解压文件，加上该选项后可以将档案文件进行压缩，但还原时也一定要使用该选项进行解压缩（常用）
```

## 2、rar

打包：把dir压缩成newdir.rar

```shell
rar a -r newdir dir
```

解包：把newdir.rar解压缩到当前目录

```shell
unrar x newdir.rar
```

## 3、zip

打包：

```shell
zip -r dir.zip dir
```

解包：

```shell
unzip dir.zip
```

## 其它

	linux创建终端：快捷键

		新开终端：Ctrl+Shift+n

		创建终端标签：Ctrl+Shift+t

		切换标签：Alt+n（n=1）





