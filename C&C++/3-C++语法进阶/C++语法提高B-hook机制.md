# Hook ����

**Hook ����** ��һ���������غʹ���ϵͳ�¼��������õķ�����ͨ�� Hook ���ƣ�����������ض����¼�����ʱ��������֮ǰ��֮������Զ��������Hook ���ƹ㷺Ӧ���ڵ��ԡ����ܼ�ء���ȫ��ơ�������չ������

## Hook ���Ƶ����ͼ�ʵ�ַ���

### 1. ��Ϣ Hook

* ��Ҫ�������غʹ������ϵͳ����Ϣ���¼������磬�� Windows ����ϵͳ�У�Ӧ�ó������ͨ��������Ϣ Hook ���ػ񴰿���Ϣ����ʵ���Զ������Ϣ�����߼���

* ��Windows ����ϵͳ�У�����ʹ�� SetWindowsHookEx ����������Ϣ Hook��������һ���򵥵�ʾ����

```c
#include <windows.h>

HHOOK hHook;

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // ����ס����Ϣ
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;
            printf("Key pressed: %d\n", kbd->vkCode);
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookProc, NULL, 0);
    if (!hHook) {
        printf("Failed to install hook!\n");
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}
```

### 2. API Hook���������ӣ�

* ͨ�����غ��滻�ض��� API ���ã�ʵ���Զ���Ĺ��ܡ����磬�����ļ����� API��ʵ���ļ�������غͿ��ơ�

* ������һ��ʹ�� `dlsym` �� `dlfcn.h` ��ʵ�ֵ�ʾ������������ `open` ϵͳ���ã�

```C
#include <dlfcn.h>	//���ڶ�̬���ӿ⺯����dlsym��
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

//����һ������ָ�����͡�open_pfn_t������ʾָ��open��������ָ��
typedef int (*open_pfn_t)(const char *pathname, int flags);

//����һ��ȫ�ֱ����洢ϵͳ����ָ��
open_pfn_t g_sys_open_func = NULL;

//��������ڶ�̬��ȡϵͳ�����ĵ�ַ�����洢����Ӧ��ȫ�ֱ�����
#define HOOK_SYS_FUNC(name) \
if( !g_sys_##name##_func ) { \
    g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT, #name); \
}

//ʹ�ú깳ȡ open �����ĵ�ַ
void hook_open_func() {
    HOOK_SYS_FUNC(open)

    if (g_sys_open_func) {
        printf("Successfully hooked open function.\n");
    } else {
        printf("Failed to hook open function.\n");
    }
}

int main() {
    hook_open_func();//����hook_open_func����ȡopen����

    // ʹ�ù�ȡ�ĺ��������ļ�
    if (g_sys_open_func) {
        int fd = g_sys_open_func("test.txt", O_RDONLY);
        if (fd != -1) {
            printf("File descriptor: %d\n", fd);
            close(fd);
        } else {
            printf("Failed to open file.\n");
        }
    }
    return 0;
}
```

#### ��`HOOK_SYS_FUNC`����

```C
#define HOOK_SYS_FUNC(name) \		
if( !g_sys_##name##_func ) { \
    g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT, #name); \
}
```

1. **�����**`name`

	* �������ϵͳ���������ƣ���`open`��`read`��`write`��

2. **ȫ�ֱ���**`g_sys_##name##_func`

	* ����һ������ָ�����͵�ȫ�ֱ��������ڴ洢ϵͳ�����ĵ�ַ��

	* `##` ��Ԥ���������ӷ������ڽ� name �� g_sys_ ������һ���γɱ�������

3. **�����ж�**`if( !g_sys_##name##_func )`

	* �ⲿ�ִ�����ȫ�ֱ���` g_sys_##name##_func` �Ƿ�Ϊ `NULL`�����Ƿ��Ѿ���ȡ�˺�����ַ��
	
	* ���δ��ȡ��������Ϊ `NULL`���������ִ������Ĵ��롣
	
4. `dlsym(RTLD_NEXT, #name)`

	* `dlsym`�Ƕ�̬���ӿ�ĺ���������������ʱ��ȡ���ţ��纯����������ĵ�ַ��

	* `RTLD_NEXT` ��һ�������־����ʾ����һ����������в��ҷ��š�

	* `#name` ������� `name` ת��Ϊ�ַ����������������ơ�

5. **����ת��** `(name##_pfn_t)`

	* ����ȡ�ĵ�ַת��Ϊ���ʵĺ���ָ�����͡�����������Ƕ����� `name##_pfn_t` ��Ϊ����ָ�����͡�

### 3. �� Hook

* ͨ�����غ��滻��̬���ӿ⣨DLL���еĺ������ã�ʵ���ض����ܵ���չ�Ͷ��ơ�

* ������һ��ʹ�� LD_PRELOAD ��������ʵ�ֵ�ʾ�����������غ��滻 malloc ������

```c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void *(*original_malloc)(size_t size) = NULL;

void *malloc(size_t size) {
    if (!original_malloc) {
        original_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    printf("malloc called with size: %zu\n", size);
    return original_malloc(size);
}

__attribute__((constructor)) void init() {
    printf("Custom malloc hook initialized.\n");
}

__attribute__((destructor)) void cleanup() {
    printf("Custom malloc hook cleaned up.\n");
}
```

## Hook ���Ƶ�Ӧ�ó�����ʾ��

### 1. ���Ժ����

* **�����޸�Դ���룺** �����ڲ��޸�ԭʼ�������������ز���¼�������ã�������Ժ�������⡣

* **����ԣ�** ����������ʱ��ӵ�����Ϣ���鿴�������õĲ����ͷ���ֵ���˽���������״����

```C
//�����ļ�ϵͳ�������������жԡ�open�������ĵ���
#include <dlfcn.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

typedef int (*open_pfn_t)(const char *pathname, int flags);
open_pfn_t g_sys_open_func = NULL;

#define HOOK_SYS_FUNC(name) \
if( !g_sys_##name##_func ) { \
    g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT, #name); \
}

int open(const char *pathname, int flags) {
    HOOK_SYS_FUNC(open)
    printf("Open called with pathname: %s\n", pathname);
    return g_sys_open_func(pathname, flags);
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd != -1) {
        printf("File descriptor: %d\n", fd);
        close(fd);
    } else {
        printf("Failed to open file.\n");
    }
    return 0;
}
```

### 2. ���ܼ��

* **��ϸ����أ�** ���Լ���ض�������ִ��ʱ�䣬�ҵ�����ƿ����

* **����ʱ������** ���������������м��Ӧ�õ����ܣ�������ͣ�������±��롣

```C
//��غ���ִ��ʱ��
#include <dlfcn.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

typedef int (*open_pfn_t)(const char *pathname, int flags);
open_pfn_t g_sys_open_func = NULL;

#define HOOK_SYS_FUNC(name) \
if( !g_sys_##name##_func ) { \
    g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT, #name); \
}

int open(const char *pathname, int flags) {
    HOOK_SYS_FUNC(open)
    clock_t start = clock();
    int result = g_sys_open_func(pathname, flags);
    clock_t end = clock();
    printf("Open called with pathname: %s, duration: %ld\n", pathname, end - start);
    return result;
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd != -1) {
        printf("File descriptor: %d\n", fd);
        close(fd);
    } else {
        printf("Failed to open file.\n");
    }
    return 0;
}
```

### 3. ��ȫ���

* **��ȫ��ƣ�** ���������в��������ļ�����������ͨ�ţ�ǰ����Ӱ�ȫ��飬��¼�ͷ�ֹ�Ƿ����ʡ�

* **��ǿ��ȫ�ԣ�** ����������ʱ��̬���غ��޸Ĳ���ȫ�ĺ������ã���ǿӦ�õİ�ȫ�ԡ�

```C
//���ļ�����ǰ����Ӱ�ȫ���
#include <dlfcn.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef int (*open_pfn_t)(const char *pathname, int flags);
open_pfn_t g_sys_open_func = NULL;

#define HOOK_SYS_FUNC(name) \
if( !g_sys_##name##_func ) { \
    g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT, #name); \
}

int open(const char *pathname, int flags) {
    HOOK_SYS_FUNC(open)
    if (strcmp(pathname, "restricted.txt") == 0) {
        printf("Access to restricted file denied: %s\n", pathname);
        return -1;
    }
    return g_sys_open_func(pathname, flags);
}

int main() {
    int fd = open("restricted.txt", O_RDONLY);
    if (fd != -1) {
        printf("File descriptor: %d\n", fd);
        close(fd);
    } else {
        printf("Failed to open file.\n");
    }
    return 0;
}
```

### 4. ��̬��Ϊ����

* **�Ȳ�ι��ܣ�** �����ڲ�ֹͣӦ�õ��������ӻ��޸Ĺ��ܡ����磬��̬���ز����ʵ�ֿ���չ��Ӧ�ó���

* **���滻��** ����������ʱ�滻�ײ�⣬��Ӧ��ͬ��ʵ������

### 5. ��ƽ̨����

* **ƽ̨�����ԣ�** ����������ʱ����ƽ̨��̬���������ϵͳ�������򻯿�ƽ̨������

* **�汾�����ԣ�** �������°汾������ṩ�ɰ汾�����ļ���ʵ�֣�ȷ���ɰ�����������С�

### 6. ���ϵͳ

* **ģ�黯������** ���Խ����ܻ���Ϊ���ģ�飬������ʱ��̬���غ͵��ã�ʵ��ģ�黯������

* **�����չ��** ����ͨ�����ϵͳ��չӦ�ù��ܣ��ṩ�����Ľ��������

### 7. ����ָ�

* **��׳�ԣ�** �����ں�������ʧ��ʱִ�б��ò�������߳���Ľ�׳�Ժ��ݴ�������

## �ŵ��ȱ��

### �ŵ㣺

����ԣ�����������ʱ��̬���غ��޸ĺ������ã�ʵ�����Ĺ�����չ�Ͷ��ơ�

�������ԣ������޸�Դ���룬�������޸����д���ķ��ա�

���Ժ���ϣ������ڵ��Ժ���ϸ������⣬�����������������С�

### ȱ�㣺

�����ԣ�ʵ�� Hook ������Ҫ�ϸߵı�̼��ɺ���⡣

���ܿ��������ܻ������������ܿ������������ڸ�Ƶ�ʵ��õĺ����ϡ�

���������⣺�ڲ�ͬƽ̨��ͬ�汾��ϵͳ���Ͽ��ܻ��м��������⡣
