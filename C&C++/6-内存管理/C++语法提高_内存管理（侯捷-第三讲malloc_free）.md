# 第三讲：malloc/free

## 1.VC6和VC10的malloc对比

![VC6和VC10的malloc对比](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/VC6%E5%92%8CVC10%E7%9A%84malloc%E5%AF%B9%E6%AF%94.png)

## 2.VC6_malloc内存分配代码分析

![VC6_malloc内存分配](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/VC6%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D.png)

### 3.VC6_malloc内存分配过程分析（分配-释放-合并-归还）

![VC6_malloc内存分配过程分析](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/VC6malloc%E5%86%85%E5%AD%98%E5%88%86%E9%85%8D%E8%BF%87%E7%A8%8B%E5%88%86%E6%9E%90.png)

### 4.VC6_malloc全回收和延缓

![VC6_malloc全回收和延缓](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/VC6_malloc%E5%85%A8%E5%9B%9E%E6%94%B6%E5%92%8C%E5%BB%B6%E7%BC%93.png)

### 5.其它

![VC6提供的其它函数](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/VC6%E6%8F%90%E4%BE%9B%E7%9A%84%E5%85%B6%E5%AE%83%E5%87%BD%E6%95%B0.png)
