# 守护进程

## 一、进程组和会话

![进程组和会话](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E7%BB%84%E5%92%8C%E4%BC%9A%E8%AF%9D.png)

* **【进程组】** 也称之为 **作业**，代表一个或多个进程的集合。每个进程都属于一个进程组；

	* 当父进程创建子进程的时候，默认子进程与父进程属于同一进程组。进程组ID==第一个进程ID【组长进程】；
	
	* 可以使用`kill -SIGKILL -进程组ID（负的）`来将整个进程组内的进程全部杀死；
	
	* 组长进程可以创建一个进程组，创建该进程组中的进程，然后终止。只要进程组中有一个进程存在，进程组就存在，与组长进程是否终止无关；

	* 进程组生存期：进程组创建到最后一个进程离开（终止或转移到另一个进程组）；

	* 一个进程可以为自己或子进程设置进程组ID；

* `ps ajx`**查看进程ID**

	* `a`表示不仅列当前用户的进程，也列出所以其它用户的进程
	* `j`表示不仅列有控制终端的进程，也列出所有无控制终端的进程
	* `x`表示列出与作业控制相关的信息
	
![ps ajx](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ps_ajx.png)

* `cat | cat | cat | wc -l`**命令**

![cat | cat | cat | wc -l](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/cat_wc_l.png)

* **会话：** 多个进程组的结合，**依附于bash创建**

* **创建会话**

![创建会话](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%9B%E5%BB%BA%E4%BC%9A%E8%AF%9D.png)

## 二、getsid函数

![getsid函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getsid%E5%87%BD%E6%95%B0.png)

## 三、setsid函数

![setsid函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/setsid%E5%87%BD%E6%95%B0.png)

## 四、守护进程

![守护进程概念](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%88%E6%8A%A4%E8%BF%9B%E7%A8%8B%E6%A6%82%E5%BF%B5.png)

## 五、创建守护进程

![创建守护进程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%9B%E5%BB%BA%E5%AE%88%E6%8A%A4%E8%BF%9B%E7%A8%8B.png)

**需用`kill`命令杀死，可使用脚本程序管理**

### 示例：创建守护进程

```C
//daemon.c
int main(int argc, char *argv[])
{
    pid_t pid;
    int ret, fd;

    pid = fork();
    if (pid > 0)                // 父进程终止
        exit(0);

    pid = setsid();           //创建新会话
    if (pid == -1)
        sys_err("setsid error");

    ret = chdir("/home/itcast/28_Linux");       // 改变工作目录位置
    if (ret == -1)
        sys_err("chdir error");

    umask(0022);            // 改变文件访问权限掩码

    close(STDIN_FILENO);    // 关闭文件描述符 0

    fd = open("/dev/null", O_RDWR);  //  fd --> 0
    if (fd == -1)
        sys_err("open error");

    dup2(fd, STDOUT_FILENO); // 重定向 stdout和stderr
    dup2(fd, STDERR_FILENO);

    while (1);              // 模拟 守护进程业务.

	return 0;
}
```
