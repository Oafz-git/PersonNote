# 守护进程

## 一、进程组和会话

* **进程组和会话**
![进程组和会话](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E7%BB%84%E5%92%8C%E4%BC%9A%E8%AF%9D.png)

* **进程组概念**
![进程组概念](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%9B%E7%A8%8B%E7%BB%84%E6%A6%82%E5%BF%B5.png)

* `ps ajx`**查看进程ID**

	* `a`表示不仅列当前用户的进程，也列出所以其它用户的进程
	* `j`表示不仅列有控制终端的进程，也列出所有无控制终端的进程
	* `x`表示列出与作业控制相关的信息
	
![ps ajx](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/ps_ajx.png)
* `cat | cat | cat | wc -l`**命令**
![cat | cat | cat | wc -l](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/cat_wc_l.png)

* **会话：** 多个进程组的结合，**依附于bash创建**

* **创建会话**
![创建会话](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%9B%E5%BB%BA%E4%BC%9A%E8%AF%9D.png)

## 二、getsid函数

![getsid函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/getsid%E5%87%BD%E6%95%B0.png)

## 三、setsid函数

![setsid函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/setsid%E5%87%BD%E6%95%B0.png)

## 四、守护进程

![守护进程概念](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%88%E6%8A%A4%E8%BF%9B%E7%A8%8B%E6%A6%82%E5%BF%B5.png)

## 五、创建守护进程

![创建守护进程](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%88%9B%E5%BB%BA%E5%AE%88%E6%8A%A4%E8%BF%9B%E7%A8%8B.png)

**需用`kill`命令杀死，可使用脚本程序管理**

### 示例：创建守护进程

