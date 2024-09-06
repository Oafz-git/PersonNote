
* getcwd����
* **chdir����**
* **opendir����**
* **closedir����**
* **readdir����**
* **dup����/dup2����**


# Ŀ¼��������

## һ��getcwd����

![getcwd����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getcwd%E5%87%BD%E6%95%B0.png)

## ����chdir����

![chdir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chdir%E5%87%BD%E6%95%B0.png)


## �����ļ���Ŀ¼Ȩ��

![�ļ���Ŀ¼Ȩ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E3%80%81%E7%9B%AE%E5%BD%95%E6%9D%83%E9%99%90.png)

## �ġ�opendir����

![opendir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/opendir%E5%87%BD%E6%95%B0.png)

## �塢closedir����

![closedir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/closedir%E5%87%BD%E6%95%B0.png)

## ����readdir����

![readdir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readdir%E5%87%BD%E6%95%B0.png)
![struct_dirent](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_dirent.png)

### ʾ��1��ʵ��ls����

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

### ʾ��2��ʵ��ls -R����ݹ����Ŀ¼��ͬʱ��ʾ�ļ���С��

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

void fetchdir(const char *dir, void (*fcn)(char *)) //�ú���������,���ѱ��ж�ΪĿ¼
{
    char name[PATH_LEN];
    struct dirent *sdp;
    DIR *dp;

    if ((dp = opendir(dir)) == NULL) {     //��Ŀ¼ʧ��
        //perror("fetchdir can't open");
        fprintf(stderr, "fetchdir: can't open %s\n", dir);
        return;
    }

    while ((sdp = readdir(dp)) != NULL) {
        if (strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0) {    //��ֹ�������޵ݹ�
            continue; 
        }

        if (strlen(dir)+strlen(sdp->d_name)+2 > sizeof(name)) 
            fprintf(stderr, "fetchdir: name %s %s too long\n", dir, sdp->d_name);
        } else {
            sprintf(name, "%s/%s", dir, sdp->d_name);
            (*fcn)(name);                     //����һ��ʲô??  
        }
    }

    closedir(dp);
}

void isfile(char *name)          //����Ŀ¼/�ļ�
{
    struct stat sbuf;

   if (stat(name, &sbuf) == -1) {   //�ļ�����Ч
        fprintf(stderr, "isfile: can't access %s\n", name);
        exit(1);
    }
    if ((sbuf.st_mode & S_IFMT) == S_IFDIR) {  //�ж��Ƿ�ΪĿ¼
        fetchdir(name, isfile);                //�ص�����,˭�ǻص�������?
    }

    printf("%8ld %s\n", sbuf.st_size, name);   //����Ŀ¼,������ͨ�ļ�,ֱ�Ӵ�ӡ�ļ���
}
//./ls_R ~/1110_linux
int main(int argc, char *argv[])
{
    if (argc == 1) 
        isfile(".");
    else
        while (--argc > 0)          //��һ�β�ѯ���Ŀ¼ 
            isfile(*++argv);        //ѭ�����øú���������������д����Ŀ¼

    return 0;
}
```


## �ߡ�dup��dup2�������ض���

	int dup(int oldfd);		�ļ����������ơ�

		oldfd: �����ļ�������

		���أ����ļ���������

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

	int dup2(int oldfd, int newfd); �ļ����������ơ��ض��򣨽�newfd�ض����oldfd������newfdָ��oldfd��ָ����ļ���

```C
int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_RDWR); //3
	int fd2 = open(argv[2], O_RDWR); //4
	
	int fdret = dup2(fd1, fd2);//�������ļ�������fd2����fd2ָ��fd1��ָ����ļ�
	printf("fdret = %d\n", fdret);
	
	int ret = write(fd2, "1234567", 7);//��д�뵽fd1��ָ����ļ���
	printf("ret = %d\n", ret);
	
	dup2(fd1, STDOUT_FILENO);//����Ļ���룬�ض����fd1��ָ����ļ���
	printf("----------1234");//����Ļ��������ݽ�д�뵽fd1��ָ����ļ���
}
```

### ʾ����ʹ��fcntlʵ��dup������

	int fcntl(int fd, int cmd, ....)

	cmd: F_DUPFD

```C
int main(int argc, char* argv[])
{
	int fd1 = open(argv[1], O_REWR);
	printf("fd1 = %d\n", fd1);
	
	int newfd = fcntl(fd1, F_DUPFD, 0);//0��ռ�ã�fcntlʹ���ļ����������п��õ���С�ļ�����������
	printf("newfd = %d\n", newfd);
	
	int newfd2 = fcntl(fd1, F_DUPFD, 7);//7δ��ռ�ã����� >=7 ���ļ�������
	printf("newfd2 = %d\n", newfd2);
	
	int ret = write(newfd2, "YYYYYYY", 7);//��д�뵽fd1��ָ����ļ���
	printf("ret = %d\n", ret);
	
	return 0;
}
```