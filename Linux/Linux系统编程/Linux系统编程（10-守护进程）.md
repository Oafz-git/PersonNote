# �ػ�����

## һ��������ͻỰ

* **������ͻỰ**
![������ͻỰ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E7%BB%84%E5%92%8C%E4%BC%9A%E8%AF%9D.png)

* **���������**
![���������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E7%BB%84%E6%A6%82%E5%BF%B5.png)

* `ps ajx`**�鿴����ID**

	* `a`��ʾ�����е�ǰ�û��Ľ��̣�Ҳ�г����������û��Ľ���
	* `j`��ʾ�������п����ն˵Ľ��̣�Ҳ�г������޿����ն˵Ľ���
	* `x`��ʾ�г�����ҵ������ص���Ϣ
	
![ps ajx](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ps_ajx.png)

* `cat | cat | cat | wc -l`**����**

![cat | cat | cat | wc -l](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/cat_wc_l.png)

* **�Ự��** ���������Ľ�ϣ�**������bash����**

* **�����Ự**
![�����Ự](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%9B%E5%BB%BA%E4%BC%9A%E8%AF%9D.png)

## ����getsid����

![getsid����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getsid%E5%87%BD%E6%95%B0.png)

## ����setsid����

![setsid����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/setsid%E5%87%BD%E6%95%B0.png)

## �ġ��ػ�����

![�ػ����̸���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%88%E6%8A%A4%E8%BF%9B%E7%A8%8B%E6%A6%82%E5%BF%B5.png)

## �塢�����ػ�����

![�����ػ�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%9B%E5%BB%BA%E5%AE%88%E6%8A%A4%E8%BF%9B%E7%A8%8B.png)

**����`kill`����ɱ������ʹ�ýű��������**

### ʾ���������ػ�����

```C
//daemon.c
int main(int argc, char *argv[])
{
    pid_t pid;
    int ret, fd;

    pid = fork();
    if (pid > 0)                // ��������ֹ
        exit(0);

    pid = setsid();           //�����»Ự
    if (pid == -1)
        sys_err("setsid error");

    ret = chdir("/home/itcast/28_Linux");       // �ı乤��Ŀ¼λ��
    if (ret == -1)
        sys_err("chdir error");

    umask(0022);            // �ı��ļ�����Ȩ������

    close(STDIN_FILENO);    // �ر��ļ������� 0

    fd = open("/dev/null", O_RDWR);  //  fd --> 0
    if (fd == -1)
        sys_err("open error");

    dup2(fd, STDOUT_FILENO); // �ض��� stdout��stderr
    dup2(fd, STDERR_FILENO);

    while (1);              // ģ�� �ػ�����ҵ��.

	return 0;
}
```
