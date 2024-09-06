# ϵͳ����

C��׼������ϵͳ���õĹ�ϵ��
![ϵͳ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8.png)

# �ļ�IO

* **open����/close����**
* ��������errno
* **read����/write�����������ͷ�������**
* strace����
* **fcntl����**
* **lseek����**
* **truncate����**

## һ��open����/close����

	int open(char *pathname, int flags)			#include <unistd.h>

	������
		pathname: ���򿪵��ļ�·����

		flags���ļ��򿪷�ʽ��									#include <fcntl.h>

			O_RDONLY|O_WRONLY|O_RDWR	O_CREAT|O_APPEND|O_TRUNC���ضϣ�|O_EXCL���ж��Ƿ���ڣ�|O_NONBLOCK���������� ....

	����ֵ��
		�ɹ��� ���ļ����õ���Ӧ�� �ļ���������������

		ʧ�ܣ� -1�� ����errno	



	int open(char *pathname, int flags�� mode_t mode)		123  775	

	������
		pathname: ���򿪵��ļ�·����

		flags���ļ��򿪷�ʽ��	O_RDONLY|O_WRONLY|O_RDWR	O_CREAT|O_APPEND|O_TRUNC|O_EXCL|O_NONBLOCK ....

		mode: ����3ʹ�õ�ǰ�ᣬ ��2ָ���� O_CREAT���������ļ�ʱʹ�ã���	ȡֵ8�����������������ļ��� ����Ȩ�ޡ� rwx    0664

			�����ļ�����Ȩ�� = mode & ~umask

	����ֵ��
		�ɹ��� ���ļ����õ���Ӧ�� �ļ���������������

		ʧ�ܣ� -1�� ����errno	
		
	��������
		1.���ļ�������
		2.��д��ʽ��ֻ���ļ������ļ�û�ж�ӦȨ�ޣ�
		3.��ֻд��ʽ��Ŀ¼

	int close(int fd);


## ������������errno��

	errno��ʾ����ϵͳ��ȫ�ֱ�������ֱ��ʹ��   #include<errno.h>
	
	char *strerror(int errnum); //����errno #include<string.h>
		printf("xxx error: %s\n", strerror(errno));
		
	void perror(const char *s); //�൱strerror(errno)��printf�Ľ�� #include<stdio.h>
	exit(1); #include<stdlib.h>

## ����read����/write����

	ssize_t read(int fd, void *buf, size_t count);

	������
		fd���ļ�������

		buf�������ݵĻ�����

		count����������С

	����ֵ��

		= 0�������ļ�ĩβ��socket�У���ʾ�Զ˹رա�close����

		> 0 �������ֽ�����

		-1 ���� errno
			
			��� errno == EINTR   ���쳣�նˡ� ��Ҫ����������ϵͳ���ñ��жϡ�

			��� errno == EAGIN �� EWOULDBLOCK ˵������readʧ�ܣ�����read���Է�������ʽ��һ���豸�ļ��������ļ����������ļ������ݡ�

			��� errno == ECONNRESET  ˵�����ӱ� ���á� ��Ҫ close�������Ƴ��������С�

	ssize_t write(int fd, const void *buf, size_t count);

	������
		fd���ļ�������

		buf����д�����ݵĻ�����

		count�����ݴ�С

	����ֵ��

		�ɹ���	д����ֽ�����

		ʧ�ܣ�	-1�� ���� errno

* strace������ٺ�������
	
* ��������read��write������������ΪUnbuffered I/O��ָ�������û�����������������֤��ʹ���ں˻�����
	
* Ԥ���뻺������ƣ�ϵͳ���úͿ⺯���Ƚϣ�
![Ԥ���뻺���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E9%A2%84%E8%AF%BB%E5%85%A5%E7%BC%93%E8%BE%93%E5%87%BA%E6%9C%BA%E5%88%B6.png)

### ʾ����ģ��cp����

```C
// myCp.c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
        char buf[1024];
        int n = 0;
        int fd1 = open(argv[1], O_RDONLY);
        if(fd1 == -1)
        {
                perror("open argv1 error");
                exit(1);
        }
        int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC ,0777);
        if(fd2 == -1)
        {
                perror("open argv2 error");
                exit(1);
        }


        while(n = read(fd1, buf, 1024) != 0)
        {
                if(n == -1)
                {
                        perror("read error");
                        break;
                }

                write(fd2, buf, n);
        }

        close(fd1);
        close(fd2);
        return 0;
}
```
		

## �ġ��ļ���������

![�ļ�������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%87%E4%BB%B6%E6%8F%8F%E8%BF%B0%E7%AC%A6.png)

	PCB���̿��ƿ飺���� �ṹ�塣

	��Ա���ļ���������

	�ļ���������0/1/2/3/4��������/1023     ����1024���ļ������п��õ���С�ġ�

	0 - STDIN_FILENO

	1 - STDOUT_FILENO

	2 - STDERR_FILENO

## �塢���������������豸�ļ��������ļ������ԣ�
	
	���������ĳ����� ���豸�ļ����������ļ������������ļ������������

	/dev/tty -- �ն��ļ���

### ʾ������������ʽ��ȡ�ն��ļ�

˵����ѭ����ʱ10s��ÿ2����з�������ȡ�������try again����10s���ն�δ��������Ϊ��ʱ�������time out��

```C
//nonblock_timeout.c
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MSG_TRY "try again\n"
#define MSG_TIMEOUT "time out\n"

int main(void)
{
    char buf[10];
    int fd, n, i;

    fd = open("/dev/tty", O_RDONLY|O_NONBLOCK);//�Է�������ʽ���ն��ļ���Ĭ��Ϊ������ʽ
    if(fd < 0){
        perror("open /dev/tty");
        exit(1);
    }
    printf("open /dev/tty ok... %d\n", fd);

    for (i = 0; i < 5; i++){						//���ó�ʱ
        n = read(fd, buf, 10);
        if (n > 0) {                    //˵�������˶���
            break;
        }
        if (errno != EAGAIN) {          //EWOULDBLOCK�����Է�������ʽ��һ���豸�ļ��������ļ����������ļ�������ʱ
            perror("read /dev/tty");
            exit(1);
        } else {
            write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
            sleep(2);
        }
    }

    if (i == 5) {
        write(STDOUT_FILENO, MSG_TIMEOUT, strlen(MSG_TIMEOUT));
    } else {
        write(STDOUT_FILENO, buf, n);
    }

    close(fd);

    return 0;
}
```

## ����fcntl�������ı�һ��[�Ѿ���]���ļ��ķ�������

	int fcntl(int fd, int cmd, ...); //�ı�һ��[�Ѿ���]���ļ��ķ������ԣ�

	Ӧ�ã�
		int flgs = fcntl(fd,  F_GETFL);//��ȡ�ļ�����

		flgs |= O_NONBLOCK//�������

		fcntl(fd,  F_SETFL, flgs);//��������

	��ȡ�ļ�״̬�� F_GETFL

	�����ļ�״̬�� F_SETFL
	
![λͼ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BD%8D%E5%9B%BE.png)

### ʾ����Ϊstdin���������Ϣ

˵����ͨ��fcntl���O_NONBLOCK����

```C
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(void)
{
	char buf[10];
	int flags, n;

	flags = fcntl(STDIN_FILENO, F_GETFL); //��ȡstdin������Ϣ
	if(flags == -1){
		perror("fcntl error");
		exit(1);
	}
	flags |= O_NONBLOCK;
	int ret = fcntl(STDIN_FILENO, F_SETFL, flags);//Ϊstdin���������Ϣ
	if(ret == -1){
		perror("fcntl error");
		exit(1);
	}

tryagain:
	n = read(STDIN_FILENO, buf, 10);
	if(n < 0){
		if(errno != EAGAIN){		
			perror("read /dev/tty");
			exit(1);
		}
		sleep(3);
		write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
		goto tryagain;
	}
	write(STDOUT_FILENO, buf, n);

	return 0;
}
```

## �ߡ�lseek�������޸��ļ�ƫ��������дλ�ã�

	off_t lseek(int fd, off_t offset, int whence);//�޸��ļ�ƫ��������дλ�ã�

	������
		fd���ļ�������

		offset�� ƫ����

		whence����ʼƫ��λ�ã� SEEK_SET/SEEK_CUR/SEEK_END

	����ֵ��

		�ɹ�������ʼλ��ƫ�������ļ�ͷ��λ�ã�

		ʧ�ܣ�-1 errno

### ʾ����

#### 1. �ļ��ġ���������д��ʹ��ͬһƫ��λ�á�

```C
int main(int argc, char* argv[])
{
        char msg[] = "It's a for lseek.txt";
        int fd, n;
        char buf;
        fd = open("lseek.txt", O_RDWR|O_CREAT|O_TRUNC, 0664);
        if(fd < 0)
        {
                perror("open error");
                exit(1);
        }
        n = write(fd,msg,strlen(msg));

        lseek(fd, 0, SEEK_SET);//���ù�굽�ļ���ʼλ��
        while(n = read(fd, &buf, 1))
        {
                if(n == -1)
                {
                        perror("read error");
                        exit(1);
                }
                write(STDOUT_FILENO, &buf, n);
        }

        close(fd);
        return 0;
}
```

#### 2. ʹ��lseek��ȡ�ļ���С������ֵ����С

```C
int main(void)
{
	int fd;

	fd = open("lseek.txt", O_RDONLY | O_CREAT, 0664);
	if(fd < 0){
		perror("open lseek.txt error");
		exit(1);
	}

	int len = lseek(fd, 0, SEEK_END);
	if(len == -1){
		perror("lseek error");
		exit(1);
	}
	printf("len of msg = %d\n", len);//�����ļ���С

	off_t cur = lseek(fd, -10, SEEK_SET);//��Ч����
	printf("--------| %ld\n", cur);
	if(cur == -1){
		perror("lseek error");
		exit(1);
	}
}
```

#### 3. ʹ��lseek��չ�ļ���С��Ҫ��ʹ�ļ���С������չ����������IO������û������ַ��Ļ��С��ļ��ն���

```C
len = lseek(fd, 999, SEEK_SET);//��չ�ļ���С
if(len == -1){
	perror("lseek seek_set error");
	exit(1);
}
  int ret = write(fd, "a", 1);
if(ret == -1){
	perror("write error");
	exit(1);
}
```

#### 4.ʹ�� truncate ������ֱ����չ�ļ���	int ret = truncate("dict.cp", 250);

```C
int ret = truncate("lseek.txt", 1500);//��չ�ļ���С
//int ret = ftruncate(fd, 1000);
if(ret == -1){
	perror("ftrun error");
	exit(1);
}
printf("len of file = %d\n", ret);

close(fd);
return 0;
}
```

## �ˡ�od����

	od -tcx filename //�鿴�ļ���16���Ʊ�ʾ��ʽ
	od -tcd filename //�鿴�ļ���10���Ʊ�ʾ��ʽ

![od����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/od.png)

## �š����봫������

	���������

		1. ָ����Ϊ����������

		2. ͬ����const�ؼ������Ρ�

		3. ָ��ָ����Ч���� �ں����ڲ�����������

	����������

		1. ָ����Ϊ����������

		2. �ں�������֮ǰ��ָ��ָ��Ŀռ���������壬��������Ч��

		3. �ں����ڲ�����д������

		4���������ý����󣬳䵱��������ֵ��

	���봫��������

		1. ָ����Ϊ����������

		2. �ں�������֮ǰ��ָ��ָ��Ŀռ���ʵ�����塣

		3. �ں����ڲ�������������������д������

		4. �������ý����󣬳䵱��������ֵ��





	




























