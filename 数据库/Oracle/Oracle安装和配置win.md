# Oracle安装和配置

## 一、需要的软件

<img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle1.jpg" style="zoom: 67%;" />

[下载地址](https://www.oracle.com/database/technologies/oracle-database-software-downloads.html)

## 二、可能出现的错误

==Oracle11g 安装过程出现提示：未找到文件 D:\app\Administrator\product\11.2.0\dbhome_2\owb\external\oc4j_applications\applications\WFMLRSVCApp.ear==

**解决方法：**

将win64_11gR2_database_2of2中的\win64_11gR2_database_2of2\database\stage\Components\*（Components目录下所有文件）拷到\win64_11gR2_database_1of2\database\stage\Components目录下即可。

***最好在安装前就复制过去，一次成功***

## 三、Oracle数据库的安装

### 步骤（一）

只需打开“win64_11gR2_database_1of2”文件夹中的setup.exe即可。如果提示系统不满足最低要求，不用管它直接点是。这时候会让你填写电子邮箱，点击下一步，弹出下图，点击“是”。

<img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle2.jpg" style="zoom:67%;" />

 <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle3.jpg" style="zoom:67%;" />

### 步骤（二）

选择创建并配置数据库，点击下一步。

​    <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle4.jpg" style="zoom:50%;" />

### 步骤（三）

如果是在个人电脑中安装，就选择桌面类；如果是在服务器里安装就选择服务器类，然后一直点击下一步。

​    <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle5.jpg" style="zoom:50%"/>

### 步骤（四）

口令是Oracle123；

​      <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle6.jpg" style="zoom:50%"/>

### 步骤（五）

点击“完成”

​      <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle7.jpg" style="zoom:50%"/>

### 步骤（六）

口令管理：

最好直接设置，否则后期容易出错。

将sys和system直接设置新口令，将SCOTT和sh取消锁定账户，设置新口令。

​      <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle8.jpg" style="zoom:50%"/>

安装完成。

​      <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle9.jpg" style="zoom:50%"/>

## 四、Oracle客户端的安装

点击setup.exe即可。如果提示系统不满足最低要求，不用管它直接点是。选择管理员，点击下一步，其他的都是默认和下一步。

​    <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle10.jpg" style="zoom:50%"/>

## 五、Oracle客户端和数据库同时安装换出现错误（冲突）

   <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle11.jpg" style="zoom:50%"/>

解决方案：

应该是环境变量中自动调用的oracle客户端的可执行程序，而我们想调用的是oracle服务端的，当我们安装顺序为：服务端——客户端，这个时候环境变量将客户端的放到了前面，而我们要做的是将服务端的置前。

​      <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle12.jpg" style="zoom:50%"/>

## 六、安装PL/SQL

### 步骤（一）

点击直接安装

​     <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle13.jpg" style="zoom:50%"/>

### 步骤（二）

修改路径，选择Enter license information

​      <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle14.jpg" style="zoom:50%"/>

### 步骤（三）

然后在注册信息页面，填写相应的注册信息 

product code： 4vkjwhfeh3ufnqnmpr9brvcuyujrx3n3le

serial Number：226959

password： xs374ca

​    <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle15.jpg" style="zoom:50%"/>

### 步骤（四）

然后选择自定义安装，如下图然后点击下一步进行安装

  <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle16.jpg" style="zoom:50%"/>

   <img src="https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Oracle17.jpg" style="zoom:50%"/>