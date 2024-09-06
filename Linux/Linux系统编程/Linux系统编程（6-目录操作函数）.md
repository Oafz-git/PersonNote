
* getcwd函数
* **chdir函数**
* **opendir函数**
* **closedir函数**
* **readdir函数**
* **dup函数/dup2函数**


# 目录操作函数

## 一、getcwd函数

![getcwd函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getcwd%E5%87%BD%E6%95%B0.png)

## 二、chdir函数

![chdir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chdir%E5%87%BD%E6%95%B0.png)


## 三、文件和目录权限

![文件和目录权限](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E3%80%81%E7%9B%AE%E5%BD%95%E6%9D%83%E9%99%90.png)

## 四、opendir函数

![opendir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/opendir%E5%87%BD%E6%95%B0.png)

## 五、closedir函数

![closedir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/closedir%E5%87%BD%E6%95%B0.png)

## 六、readdir函数

![readdir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readdir%E5%87%BD%E6%95%B0.png)
![struct_dirent](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_dirent.png)

### 示例1：实现ls命令

```C
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
        DIR *dp;
        struct dirent *sdp;
        dp = opendir(argv[1]);
        if(dp == NULL)
        {
                perror("opendir error");
                exit(1);
        }
        while((sdp = readdir(dp)) != NULL)
        {
                printf("%s\t",sdp->d_name);
        }
        printf("\n");
        closedir(dp);
        return 0;
}
```

### 示例2：实现ls -R命令（递归遍历目录，同时显示文件大小）

```C
//ls_R.c
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PATH_LEN 256
//dir=/home/itcast/1110_linux    fcn=isfile

void fetchdir(const char *dir, void (*fcn)(char *)) //该函数被调用,既已被判定为目录
{
    char name[PATH_LEN];
    struct dirent *sdp;
    DIR *dp;

    if ((dp = opendir(dir)) == NULL) {     //打开目录失败
        //perror("fetchdir can't open");
        fprintf(stderr, "fetchdir: can't open %s\n", dir);
        return;
    }

    while ((sdp = readdir(dp)) != NULL) {
        if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0) {    //防止出现无限递归
            continue; 
        }

        if (strlen(dir)+strlen(sdp->d_name)+2 > sizeof(name)) 
            fprintf(stderr, "fetchdir: name %s %s too long\n", dir, sdp->d_name);
        } else {
            sprintf(name, "%s/%s", dir, sdp->d_name);
            (*fcn)(name);                     //这是一个什么??  
        }
    }

    closedir(dp);
}

void isfile(char *name)          //处理目录/文件
{
    struct stat sbuf;

   if (stat(name, &sbuf) == -1) {   //文件名无效
        fprintf(stderr, "isfile: can't access %s\n", name);
        exit(1);
    }
    if ((sbuf.st_mode & S_IFMT) == S_IFDIR) {  //判定是否为目录
        fetchdir(name, isfile);                //回调函数,谁是回调函数呢?
    }

    printf("%8ld %s\n", sbuf.st_size, name);   //不是目录,则是普通文件,直接打印文件名
}
//./ls_R ~/1110_linux
int main(int argc, char *argv[])
{
    if (argc == 1) 
        isfile(".");
    else
        while (--argc > 0)          //可一次查询多个目录 
            isfile(*++argv);        //循环调用该函数处理各个命令行传入的目录

    return 0;
}
```


## 七、dup和dup2函数（重定向）

	int dup(int oldfd);		文件描述符复制。

		oldfd: 已有文件描述符

		返回：新文件描述符。

```C
int main(int argc, char* argv[])
{
        int fd = open("temp.txt", O_RDWR);
        if(fd == -1)
        {
                perror("open error");
                exit(1);
        }
        int fd2 = dup(fd);
        write(fd2, "aaaaaaaa", 7);
        close(fd);
        close(fd2);

        return 0;
}
```

	int dup2(int oldfd, int newfd); 文件描述符复制。重定向（将newfd重定向给oldfd，即将newfd指向oldfd所指向的文件）

```C
int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_RDWR); //3
	int fd2 = open(argv[2], O_RDWR); //4
	
	int fdret = dup2(fd1, fd2);//返回新文件描述符fd2，将fd2指向fd1所指向的文件
	printf("fdret = %d\n", fdret);
	
	int ret = write(fd2, "1234567", 7);//将写入到fd1所指向的文件中
	printf("ret = %d\n", ret);
	
	dup2(fd1, STDOUT_FILENO);//将屏幕输入，重定向给fd1所指向的文件；
	printf("----------1234");//向屏幕输出的内容将写入到fd1所指向的文件中
}
```

### 示例：使用fcntl实现dup描述符

	int fcntl(int fd, int cmd, ....)

	cmd: F_DUPFD

```C
int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_REWR);
	printf("fd1 = %d\n", fd1);
	
	int newfd = fcntl(fd1, F_DUPFD, 0);//0被占用，fcntl使用文件描述符表中可用的最小文件描述符返回
	printf("newfd = %d\n", newfd);
	
	int newfd2 = fcntl(fd1, F_DUPFD, 7);//7未被占用，返回 >=7 的文件描述符
	printf("newfd2 = %d\n", newfd2);
	
	int ret = write(newfd2, "YYYYYYY", 7);//将写入到fd1所指向的文件中
	printf("ret = %d\n", ret);
	
	return 0;
}
```