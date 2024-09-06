# �ļ��洢
 
![stat����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/stat%E5%91%BD%E4%BB%A4.png)
![inode��Ŀ¼��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9.png)
![inode��Ŀ¼�2��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/inode%E5%92%8C%E7%9B%AE%E5%BD%95%E9%A1%B9%EF%BC%882%EF%BC%89.png)

#	�ļ�ϵͳ����

* **stat/lstat����**
* access����
* chomd����/fchmod����
* **truncate����/ftruncate����**
* **link/unlink����**
* symlink����/readlink����
* rename����

## һ��stat/lstat��������ȡ�ļ����ԣ���inode�л�ȡ��

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

### ʾ������ȡ�ļ�����

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

        if(S_ISREG(st.st_mode))				//ʹ�ú꺯��
                printf("It's a regular file\n");
        if(S_ISDIR(st.st_mode))
                printf("It's a dir file\n");
        //if(S_ISFIFO(st.st_mode))
        if((st.st_mode & S_IFMT) == S_IFIFO)		//ʹ�ú�-λͼ
                printf("It's a fifo file\n");     
        if(S_ISLNK(st.st_mode))
                printf("It's a link file\n");
        return 0;
}
```

## ����mkfifo����
`mkfifo f1`�������ܵ��ļ�

## ����access����

![access����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/access%E5%87%BD%E6%95%B0.png)

## �ġ�chomd����

![chmod����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/chmod%E5%87%BD%E6%95%B0.png)

## �塢truncate����

![truncate����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/truncate%E5%87%BD%E6%95%B0.png)

## ����link/unlink������Ӳ���ӣ�

![link����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/link%E5%87%BD%E6%95%B0.png)

![unlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/unlink%E5%87%BD%E6%95%B0.png)

* ��ʽ���գ������̽�������ʱ�����иý��̴򿪵��ļ��ᱻ�رգ�������ڴ�ռ��ϵͳ���ͷš�

### ʾ��1��ʵ��mv����

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

### ʾ��2��ʵ��rm����

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
### ʾ��3����ʱ�ļ���ʹ��

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

	ret = unlink("temp.txt");		 //Ӧ�ã���unlink��ǰ����ʱ������ˣ�Ҳ�ܹ�ɾ���ļ�����ʱ�ļ���
	if(ret < 0){
		perror("unlink error");
		exit(1);
	}

	ret = write(fd, p, strlen(p));
    if (ret == -1) {
        perror("-----write error");
    }

	printf("hi! I'm printf\n");
	ret = write(fd, p2, strlen(p2));//�ǽ�����д�뵽�����У�cat�����ǲ鿴�����ϵ��ļ�����
    if (ret == -1) {
        perror("-----write error");
    }

    printf("Enter anykey continue\n");
    getchar();

    p[3] = 'H';//�δ���

	close(fd);//fdû�б����գ��ᱻ��ʽ���գ�������Ҫ�˳�

	return 0;
}
```

## �ߡ�symlink����/readlink�������������ӣ�
![symlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/symlink%E5%87%BD%E6%95%B0.png)

![readlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%87%BD%E6%95%B0.png)

![readlink����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/readlink%E5%91%BD%E4%BB%A4.png)

## �ˡ�rename����

![rename����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/rename%E5%87%BD%E6%95%B0.png)
