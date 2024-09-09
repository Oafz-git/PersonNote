# ����ͨ�ţ�IPC��

## һ��IPC����

![IPC����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/IPC%E6%A6%82%E5%BF%B5.png)

## �������÷�ʽ������

�ڽ��̼�������ݴ�����Ҫ��������ϵͳ�ṩ����ķ������磺�ļ����ܵ����źš������ڴ桢��Ϣ���С��׽��֡������ܵ��ȡ����ż���������չ��һЩ������������ȱ�ݱ���̭�����ã����ڳ��õĽ��̼�ͨ�ŷ�ʽ�У�

1. �ܵ���ʹ����򵥣�

2. �źţ�������С��

3. ����ӳ��������ѪԵ��ϵ��

4. �����׽��֣����ȶ���

# �ܵ�

## һ���ܵ�����

�ܵ���һ���������IPC���ƣ���������ѪԵ��ϵ�Ľ��̼䣬������ݴ��ݡ�����**pipeϵͳ����**���ɴ���һ���ܵ���

**���ʣ�**

1. �䱾����һ��**α�ļ���ʵΪ�ں˻�������**

2. ��**�����ļ�����������**��һ����ʾ���ˣ�һ����ʾд��

3. �涨���ݴӹܵ���д������ܵ����Ӷ�������

**ԭ��**�ܵ�ʵΪ�ں�ʹ��**���ζ���**���ƣ�����**�ں˻�������4k��ʵ��**

**�����ԣ�**

1. ����**���ܽ����Լ�д���Լ���**

2. �ܵ�������**���ɷ�����ȡ**��һ�����ߣ��ܵ��в��ٴ���

3. ����**��˫��ͨ�ŷ�ʽ**������ֻ���ڵ�����������

4. ֻ������**��������**�Ľ��̼�ʹ�ùܵ�

![�ܵ�ԭ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AE%A1%E9%81%93%E5%8E%9F%E7%90%86.png)

## ����pipe���������������򿪹ܵ���

	int pipe(int fd[2]);

	������	fd[0]: ���ˡ�

		fd[1]: д�ˡ�

	����ֵ�� �ɹ��� 0

		 ʧ�ܣ� -1 errno

![�ܵ�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AE%A1%E9%81%93%E5%88%9B%E5%BB%BA.png)

## �����ܵ��Ķ�д��Ϊ��

	���ܵ���
		1. �ܵ������ݣ�read����ʵ�ʶ������ֽ�����

		2. �ܵ������ݣ�	1����д�ˣ�read����0 �����ƶ����ļ�β��

				2����д�ˣ�read�����ȴ���

	д�ܵ���
		1. �޶��ˣ� �쳣��ֹ�� ��SIGPIPE���µģ�

		2. �ж��ˣ�	1�� �ܵ������� �����ȴ�

				2�� �ܵ�δ���� ����д�����ֽڸ�����

### ʾ�����ܵ��Ķ�д
```C
int main(void)
{
    pid_t pid;
    char buf[1024];
    int fd[2];
    char *p = "test for pipe\n";
    
   if (pipe(fd) == -1) 
       sys_err("pipe");

   pid = fork();
   if (pid < 0) {
       sys_err("fork err");
   } else if (pid == 0) {
        close(fd[1]);//�ر�д��
        int len = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);
   } else {
       close(fd[0]);//�رն���
       write(fd[1], p, strlen(p));
       wait(NULL);
       close(fd[1]);
   }
    return 0;
}
```

## �ġ�wc����

	�����ڼ����ļ����������������ֽ���
	
	-l , --lines : ��ʾ������

	-w , --words : ��ʾ������

	-m , --chars : ��ʾ�ַ�����

	-c , --bytes : ��ʾ�ֽ�����

	-L , --max-line-length : ��ʾ��еĳ��ȣ�

### ʾ����ʵ�� ls | wc -l������ͨ�š��ֵ�ͨ�ţ�

```C
//ls_wc_l.c
int main(void)
{
    int fd[2];
    pid_t  pid;
    int i;

    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error:");
        exit(1);
    }

    for (i = 0; i < 2; i++){
        pid = fork();
        if (pid == -1) {
            perror("pipe error:");  //ls | wc -l
            exit(1);
        }
        if (pid == 0)
            break;
    }

    if (i == 0) {  //��  ls 
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
    } else if (i == 1) { // �� wc -l 
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
    } else if (i == 2) {  //�� 
        close(fd[0]);
        close(fd[1]);
        for(i = 0; i < 2; i++)
            wait(NULL);
    }

    return 0;
}
```

## �塢�ܵ���������С

### 1.`ulimit -a`����
	
	�鿴��ǰϵͳ�йܵ��ļ�����Ӧ���ں˻�������С
	
![ulimit_a����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ulimit_a%E5%91%BD%E4%BB%A4.png)

### 2.fpathconf()����

	long fpathconf(int fd, int name);
	
	������
	
		fd���ļ���������name����
	
	����ֵ��
	
		�ɹ������عܵ���С��ʧ�ܣ�-1������errno 

## �����ܵ�����

* ���ŵ㡿�򵥣�����źţ��׽���ʵ�ֽ��̼�ͨ�ţ��򵥺ܶ�

* ��ȱ�㡿

	1. ֻ�ܵ���ͨ�ţ�˫��ͨ���轨�������ܵ���
	
	2. ֻ�����ڸ��ӡ��ֵܽ��̣��й�ͬ���ȣ���ͨ�š�

## �ߡ�fifo�ܵ��������ܵ���

* �ܵ�`pipe`ֻ������**��ѪԵ��ϵ**�Ľ��̼䣬��ͨ��**FIFO**������صĽ���Ҳ�ܽ������ݡ�

* `FIFO`��Linux�����ļ������е�һ�֣���FIFO�ļ��ڴ�����û�����ݿ飬����������ʶ�ں��е�һ��ͨ���������̿��Դ�����ļ�����`read/write`��ʵ�������ڶ�д**�ں�ͨ��**��������ʵ���˽��̼�ͨ�š�

### 2.`mkfifo`���mkfifo����
	
	���mkfifo �ܵ���
	
	�⺯����int mkfifo(const char* pathname, mode_t mode);

#### ʾ����ʵ����ѪԵ��ϵ���̼�ͨ�ţ�

	���ˣ�open fifo O_RDONLY
	д�ˣ�open fifo O_WRONLY

```C
//fifo_w.c
int main(int argc, char *argv[])
{
    int fd, i;
    char buf[4096];

    if (argc < 2) {
        printf("Enter like this: ./a.out fifoname\n");
        return -1;
    }
    fd = open(argv[1], O_WRONLY);       //�򿪹ܵ��ļ�
    if (fd < 0) 
        sys_err("open");

    i = 0;
    while (1) {
        sprintf(buf, "hello itcast %d\n", i++);

        write(fd, buf, strlen(buf));    // ��ܵ�д����
        sleep(1);
    }
    close(fd);

    return 0;
}
```

```C
//fifo_r.c
int main(int argc, char *argv[])
{
    int fd, len;
    char buf[4096];

    if (argc < 2) {
        printf("./a.out fifoname\n");
        return -1;
    }
    //int fd = mkfifo("testfifo", 644);
    //open(fd, ...);
    fd = open(argv[1], O_RDONLY);   // �򿪹ܵ��ļ�
    if (fd < 0) 
        sys_err("open");
    while (1) {
        len = read(fd, buf, sizeof(buf));   // �ӹܵ��Ķ��˻�ȡ����
        write(STDOUT_FILENO, buf, len);
        sleep(3);           //��������ʱӦ����˯������,�Ŵ�Ч��.
    }
    close(fd);

    return 0;
}
```


# �����ڴ�ӳ��:

## һ���ļ�ʵ�ֽ��̼�ͨ�ţ����ѹ�ʱ��

	�򿪵��ļ����ں��е�һ�黺�����������ѪԵ��ϵ�Ľ��̣�����ͬʱ���ʸ��ļ���

## �����洢ӳ�����

![�洢ӳ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AD%98%E5%82%A8%E6%98%A0%E5%B0%84.png)

## ����mmap����

	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);	//���������ڴ�ӳ��

	������
		addr�� 	ָ��ӳ�������׵�ַ��ͨ����NULL����ʾ��ϵͳ�Զ�����

		length�������ڴ�ӳ�����Ĵ�С����<= �ļ���ʵ�ʴ�С��

		prot��	�����ڴ�ӳ�����Ķ�д���ԡ�PROT_READ��PROT_WRITE��PROT_READ|PROT_WRITE

		flags��	��ע�����ڴ�Ĺ������ԡ�MAP_SHARED��ֱ�ӷ�Ӧ��������̣���MAP_PRIVATE������Ӧ��������̣�

		fd:	���ڴ��������ڴ�ӳ�������Ǹ��ļ��� �ļ���������

		offset��Ĭ��0����ʾӳ���ļ�ȫ����ƫ��λ�á����� 4k ����������

	����ֵ��

		�ɹ���ӳ�������׵�ַ��

		ʧ�ܣ�MAP_FAILED (void*(-1))�� errno

## �ġ�munmap����

	int munmap(void *addr, size_t length);		�ͷ�ӳ������

	addr��mmap �ķ���ֵ

	length����С


### ʹ��ע�����

![mmapע������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/mmap%E6%B3%A8%E6%84%8F%E4%BA%8B%E9%A1%B9.png)

	1. ���ڴ���ӳ�������ļ���СΪ 0��ʵ��ָ����0��С����ӳ�������� �����ߴ��󡱣�7 SIGBUS����

	2. ���ڴ���ӳ�������ļ���СΪ 0��ʵ���ƶ�0��С����ӳ������ �� ����Ч��������

	3. ���ڴ���ӳ�������ļ���д����Ϊ��ֻ����ӳ��������Ϊ ����д�� �� ����Ч��������

	4. ����ӳ��������ҪreadȨ�ޡ�������Ȩ��ָ��Ϊ ������MAP_SHARED�ǣ� mmap�Ķ�дȨ�ޣ�Ӧ�� <=�ļ���openȨ�ޡ�	ֻд���С�

	5. �ļ�������fd����mmap����ӳ������ɼ��ɹرա����������ļ����� ��ַ���ʡ�

	6. offset ������ 4096������������MMU ӳ�����С��λ 4k ��

	7. �������ӳ�����ڴ棬����Խ����ʡ� 

	8. munmap�����ͷŵ� ��ַ��������mmap���뷵�صĵ�ַ��

	9. ӳ��������Ȩ��Ϊ ��˽�С�MAP_PRIVATE, ���ڴ������������޸ģ�ֻ���ڴ���Ч�����ᷴӦ����������ϡ�

	10.ӳ��������Ȩ��Ϊ ��˽�С�MAP_PRIVATE, ֻ��Ҫopen�ļ�ʱ���ж�Ȩ�ޣ����ڴ���ӳ�������ɡ�


### mmap�����ı��յ��÷�ʽ��

	1. fd = open��"�ļ���"�� O_RDWR��;

	2. mmap(NULL, ��Ч�ļ���С�� PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);


### ʾ��1�����ӽ���ʹ�� mmap ���̼�ͨ�ţ�

	������ �� ����ӳ������ open��O_RDWR�� mmap(MAP_SHARED);

	ָ�� MAP_SHARED Ȩ��

	fork() �����ӽ��̡�

	һ�����̶��� ����һ������д��

```C
//fork_mmap.c
int var = 100;
int main(void)
{
    int *p;
    pid_t pid;

    int fd;
    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    ftruncate(fd, 4);

    //p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    p = (int *)mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(p == MAP_FAILED){		//ע��:����p == NULL
        perror("mmap error");
        exit(1);
    }
    close(fd);					//ӳ�����������,���ɹر��ļ�

    pid = fork();				//�����ӽ���
    if(pid == 0){
       *p = 7000;               // д�����ڴ�
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    } else {
        sleep(1);
        printf("parent, *p = %d, var = %d\n", *p, var);     // �������ڴ�
        wait(NULL);

        int ret = munmap(p, 4);				//�ͷ�ӳ����
        if (ret == -1) {
            perror("munmap error");
            exit(1);
        }
    }

    return 0;
}
```


### ʾ��2����ѪԵ��ϵ���̼� mmap ͨ�ţ�  				����д��

	�������� ��ͬһ���ļ�������ӳ������

	ָ��flags Ϊ MAP_SHARED��

	һ������д�룬����һ�����̶�����

	��ע�⡿����ѪԵ��ϵ���̼�ͨ�š�mmap�����ݿ����ظ���ȡ��

					fifo������ֻ��һ�ζ�ȡ��


```C
//mmap_r.c
struct STU {
    int id;
    char name[20];
    char sex;
};

int main(int argc, char *argv[])
{
    int fd;
    struct STU student;
    struct STU *mm;

    if (argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        sys_err("open error");
    mm = mmap(NULL, sizeof(student), PROT_READ, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap error");
    close(fd);//ע�⣺�����ļ���������Ϳ��Թر��ļ���
    while (1) {
        printf("id=%d\tname=%s\t%c\n", mm->id, mm->name, mm->sex);
        sleep(2);
    }
    munmap(mm, sizeof(student));

    return 0;
}
```
```C
//mmap_w.c
struct STU {
    int id;
    char name[20];
    char sex;
};
int main(int argc, char *argv[])
{
    int fd;
    struct STU student = {10, "xiaoming", 'm'};
    char *mm;

    if (argc < 2) {
        printf("./a.out file_shared\n");
        exit(-1);
    }
    fd = open(argv[1], O_RDWR | O_CREAT, 0664);
    ftruncate(fd, sizeof(student));

    mm = mmap(NULL, sizeof(student), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (mm == MAP_FAILED)
        sys_err("mmap");
    close(fd);
    while (1) {
        memcpy(mm, &student, sizeof(student));
        student.id++;
        sleep(1);
    }
    munmap(mm, sizeof(student));

    return 0;
}

```

## �塢mmap����ӳ��

**ֻ������ѪԵ��ϵ���̼�ͨ��**
	
	p = (int *)mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);
		
		len��С����
	
* `/dev/zero`�հ��ļ����᲻�ϲ������ֽڣ����޵Ŀ��ֽ���

* `/dev/null`�ڶ��ļ���������
	
### ʾ��1��ʹ��MAP_ANONYMOUS��MAP_ANON��

```C
int main(void)
{
	int *p;
	pid_t pid;
	
	p = mmap(NULL, 4, PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);  //MAP_ANONYMOUS
	if(p == MAP_FAILED){		//ע��:����p == NULL
		perror("mmap error");
		exit(1);
	}

	pid = fork();				//�����ӽ���
	if(pid == 0){
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	munmap(p, 4);				//�ͷ�ӳ����

	return 0;
}
```

### ʾ��2��û�к�����

```C
int main(void)
{
	int *p;
	pid_t pid;
	
	int fd;
	fd = open("/dev/zero", O_RDWR);

	p = mmap(NULL, 400, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

	if(p == MAP_FAILED){		//ע��:����p == NULL
		perror("mmap error");
		exit(1);
	}

	pid = fork();				//�����ӽ���
	if(pid == 0){
		*p = 2000;
		printf("child, *p = %d\n", *p);
	} else {
		sleep(1);
		printf("parent, *p = %d\n", *p);
	}

	munmap(p, 4);				//�ͷ�ӳ����

	return 0;
}
```


















	
	

	

	



	