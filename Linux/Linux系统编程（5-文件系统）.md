# �ļ��洢
 
![stat����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/stat%E5%91%BD%E4%BB%A4.png)
![inode��Ŀ¼��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9.png)
![inode��Ŀ¼�2��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9%EF%BC%882%EF%BC%89.png)

#	�ļ�ϵͳ����

### һ��stat/lstat��������ȡ�ļ����ԣ���inode�л�ȡ��

	int stat(const char *path, struct stat *buf);

	������
		path�� �ļ�·��

		buf�������������� ����ļ����ԡ�

	����ֵ��

		�ɹ��� 0

		ʧ�ܣ� -1 errno

	�������Ӵ�͸��stat�ᡣlstat���ᡣ

![struct_stat](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_stat.png)
![�ļ�����-λͼ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E7%B1%BB%E5%9E%8B-%E4%BD%8D%E5%9B%BE.png)

### ����access����

![access����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/access%E5%87%BD%E6%95%B0.png)

### ����chomd����

![chmod����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chmod%E5%87%BD%E6%95%B0.png)

### �ġ�truncate����

![truncate����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/truncate%E5%87%BD%E6%95%B0.png)

### �塢link/unlink������Ӳ���ӣ�

![link����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/link%E5%87%BD%E6%95%B0.png)

![unlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/unlink%E5%87%BD%E6%95%B0.png)

* ��ʽ���գ������̽�������ʱ�����иý��̴򿪵��ļ��ᱻ�رգ�������ڴ�ռ��ϵͳ���ͷš�

### ����symlink����/readlink�������������ӣ�
![symlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/symlink%E5%87%BD%E6%95%B0.png)

![readlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%87%BD%E6%95%B0.png)

![readlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%91%BD%E4%BB%A4.png)

### �ߡ�rename����

![rename����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/rename%E5%87%BD%E6%95%B0.png)

# Ŀ¼��������

### һ��getcwd����

![getcwd����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getcwd%E5%87%BD%E6%95%B0.png)

### ����chdir����

![chdir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chdir%E5%87%BD%E6%95%B0.png)


### �����ļ���Ŀ¼Ȩ��

![�ļ���Ŀ¼Ȩ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E3%80%81%E7%9B%AE%E5%BD%95%E6%9D%83%E9%99%90.png)

### �ġ�opendir����

![opendir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/opendir%E5%87%BD%E6%95%B0.png)

### �塢closedir����

![closedir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/closedir%E5%87%BD%E6%95%B0.png)

### ����readdir����

![readdir����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readdir%E5%87%BD%E6%95%B0.png)
![struct_dirent](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/struct_dirent.png)

### �ߡ�ʾ��

#### 1��ʵ��ls����

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

#### 2��ʵ��ls -R����ݹ����Ŀ¼��ͬʱ��ʾ�ļ���С��

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


### �ˡ�dup��dup2�������ض���

	int dup(int oldfd);		�ļ����������ơ�

		oldfd: �����ļ�������

		���أ����ļ���������

	int dup2(int oldfd, int newfd); �ļ����������ơ��ض���

