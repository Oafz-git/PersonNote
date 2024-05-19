# 文件存储
 
![stat命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/stat%E5%91%BD%E4%BB%A4.png)
![inode和目录项](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9.png)
![inode和目录项（2）](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9%EF%BC%882%EF%BC%89.png)

#	文件系统函数

### 一、stat/lstat函数（获取文件属性，从inode中获取）

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

### 二、access函数

![access函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/access%E5%87%BD%E6%95%B0.png)

### 三、chomd函数

![chmod函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chmod%E5%87%BD%E6%95%B0.png)

### 四、truncate函数

![truncate函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/truncate%E5%87%BD%E6%95%B0.png)

### 五、link/unlink函数（硬链接）

![link函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/link%E5%87%BD%E6%95%B0.png)

![unlink函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/unlink%E5%87%BD%E6%95%B0.png)

* 隐式回收：当进程结束运行时，所有该进程打开的文件会被关闭，申请的内存空间会系统被释放。

### 六、symlink函数/readlink函数（符号链接）
![symlink函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/symlink%E5%87%BD%E6%95%B0.png)

![readlink函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%87%BD%E6%95%B0.png)

![readlink命令](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%91%BD%E4%BB%A4.png)

### 七、rename函数

![rename函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/rename%E5%87%BD%E6%95%B0.png)

# 目录操作函数

### 一、getcwd函数

![getcwd函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getcwd%E5%87%BD%E6%95%B0.png)

### 二、chdir函数

![chdir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chdir%E5%87%BD%E6%95%B0.png)


### 三、文件和目录权限

![文件和目录权限](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E3%80%81%E7%9B%AE%E5%BD%95%E6%9D%83%E9%99%90.png)

### 四、opendir函数

![opendir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/opendir%E5%87%BD%E6%95%B0.png)

### 五、closedir函数

![closedir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/closedir%E5%87%BD%E6%95%B0.png)

### 六、readdir函数

![readdir函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readdir%E5%87%BD%E6%95%B0.png)
![struct_dirent](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_dirent.png)

### 七、示例

#### 1、实现ls命令

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

#### 2、实现ls -R命令（递归遍历目录，同时显示文件大小）

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


### 八、dup和dup2函数（重定向）

	int dup(int oldfd);		文件描述符复制。

		oldfd: 已有文件描述符

		返回：新文件描述符。

	int dup2(int oldfd, int newfd); 文件描述符复制。重定向。

