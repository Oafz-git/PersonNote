# 文件存储
 
![stat命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/stat%E5%91%BD%E4%BB%A4.png)
![inode和目录项](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9.png)
![inode和目录项（2）](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9%EF%BC%882%EF%BC%89.png)

#	文件系统函数

* **stat/lstat函数**
* access函数
* chomd函数/fchmod函数
* **truncate函数/ftruncate函数**
* **link/unlink函数**
* symlink函数/readlink函数
* rename函数

## 一、stat/lstat函数（获取文件属性，从inode中获取）

	int stat(const char *path, struct stat *buf);

	参数：
		path： 文件路径

		buf：（传出参数） 存放文件属性。

	返回值：

		成功： 0

		失败： -1 errno

	符号链接穿透：stat会。lstat不会。

![struct_stat](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_stat.png)
![文件类型-位图](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E7%B1%BB%E5%9E%8B-%E4%BD%8D%E5%9B%BE.png)

### 示例：获取文件属性

```C
//stat.c
int main(int argc, char* argv[])
{
        int ret=0;
        struct stat st;
        lstat(argv[1], &st);
        printf("st_ino=%d\n",st.st_ino);
        printf("st_size=%ld\n",st.st_size);
        printf("st_mode=%x\n",st.st_mode);
        printf("st_uid=%d\n",st.st_uid);
        printf("st_gid=%d\n",st.st_gid);
        printf("st_nlink=%d\n",st.st_nlink);

        if(S_ISREG(st.st_mode))				//使用宏函数
                printf("It's a regular file\n");
        if(S_ISDIR(st.st_mode))
                printf("It's a dir file\n");
        //if(S_ISFIFO(st.st_mode))
        if((st.st_mode & S_IFMT) == S_IFIFO)		//使用宏-位图
                printf("It's a fifo file\n");     
        if(S_ISLNK(st.st_mode))
                printf("It's a link file\n");
        return 0;
}
```

## 二、mkfifo命令
`mkfifo f1`：创建管道文件

## 三、access函数

![access函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/access%E5%87%BD%E6%95%B0.png)

## 四、chomd函数

![chmod函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chmod%E5%87%BD%E6%95%B0.png)

## 五、truncate函数

![truncate函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/truncate%E5%87%BD%E6%95%B0.png)

## 六、link/unlink函数（硬链接）

![link函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/link%E5%87%BD%E6%95%B0.png)

![unlink函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/unlink%E5%87%BD%E6%95%B0.png)

* 隐式回收：当进程结束运行时，所有该进程打开的文件会被关闭，申请的内存空间会系统被释放。

### 示例1：实现mv命令

```C
//mymv.c
int main(int argc, char* argv[])
{
        int ret=0;
        ret = link(argv[1],argv[2]);
        if(ret == -1)
        {
                perror("link error");
                exit(1);
        }
        ret = unlink(argv[1]);
        if(ret == -1)
        {
                perror("unlink error");
                exit(1);
        }
        return 0;
}
```

### 示例2：实现rm命令

```C
myrm.c
int main(int argc, char* argv[])
{
        int ret=0;
        ret = unlink(argv[1]);
        if(ret == -1)
        {
                perror("unlink error");
                exit(1);
        }
        return 0;
}

```
### 示例3：临时文件的使用

```C
//unlink.c
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	int fd, ret;
	char *p = "test of unlink\n";
	char *p2 = "after write something.\n";

	fd = open("temp.txt", O_RDWR|O_CREAT|O_TRUNC, 0644);
	if(fd < 0){
		perror("open temp error");
		exit(1);
	}

	ret = unlink("temp.txt");		 //应用：将unlink提前，即时程序崩了，也能够删除文件（临时文件）
	if(ret < 0){
		perror("unlink error");
		exit(1);
	}

	ret = write(fd, p, strlen(p));
    if (ret == -1) {
        perror("-----write error");
    }

	printf("hi! I'm printf\n");
	ret = write(fd, p2, strlen(p2));//是将内容写入到缓存中，cat命令是查看磁盘上的文件内容
    if (ret == -1) {
        perror("-----write error");
    }

    printf("Enter anykey continue\n");
    getchar();

    p[3] = 'H';//段错误

	close(fd);//fd没有被回收，会被隐式回收，程序需要退出

	return 0;
}
```

## 七、symlink函数/readlink函数（符号链接）
![symlink函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/symlink%E5%87%BD%E6%95%B0.png)

![readlink函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%87%BD%E6%95%B0.png)

![readlink命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%91%BD%E4%BB%A4.png)

## 八、rename函数

![rename函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/rename%E5%87%BD%E6%95%B0.png)
