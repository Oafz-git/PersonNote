# �ڶ�����std::allocator����׼���еķ�������

## һ���ٴ���ʶmalloc�ڴ����

![�ٴ���ʶmalloc](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%86%8D%E6%AC%A1%E8%AE%A4%E8%AF%86malloc.png)

## �������ֱ�׼��������std::allocator����ʵ��

![4�б�׼��������ʵ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/4%E4%B8%AD%E6%A0%87%E5%87%86%E5%88%86%E9%85%8D%E5%99%A8%E7%9A%84%E5%AE%9E%E7%8E%B0.png)

## ����G2.9std_allocԴ�����

**G2.9�汾��std::alloc��G4.9�汾��__pool_alloc��ͬһ�֣�ֻ�����ֲ�һ��������ʵ����ȥ��cookie**

### 1. G4.9�汾��pool allocator��ʹ�ð���

![G4.9�汾��pool_allocator��ʹ�ð���](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/G4.9%E7%89%88%E6%9C%AC%E7%9A%84pool_allocator%E7%9A%84%E4%BD%BF%E7%94%A8%E6%A1%88%E4%BE%8B.png)

### 2. G2.9�汾��std::alloc������ģʽ

#### a.std_alloc����ģʽ����

![std_alloc����ģʽ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/std_alloc%E8%BF%90%E8%A1%8C%E6%A8%A1%E5%BC%8F%E6%80%BB.png)

#### b.std_alloc����ģʽ����

![std_alloc����ģʽ����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/std_alloc%E8%BF%90%E8%A1%8C%E6%A8%A1%E5%BC%8F%E6%AD%A5%E9%AA%A4.png)

### 3. G2.9�汾��std::allocԴ�����

![std_allocԴ�����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/std_alloc%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90.png)

### 4. std::alloc��˼ά����

![std_alloc��˼ά����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/std_alloc%E7%9A%84%E6%80%9D%E7%BB%B4%E6%95%B4%E7%90%86.png)

### 5. std_alloc������Ҫ����ĵ�

![std_alloc������Ҫ����ĵ�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/std_alloc%E5%85%B6%E5%AE%83%E9%9C%80%E8%A6%81%E8%A1%A5%E5%85%85%E7%9A%84%E7%82%B9.png)

### 6. G4.9�汾��pool_allocator���������

![pool_allocator���������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/pool_allocator%E7%9A%84%E8%BF%90%E8%A1%8C%E6%83%85%E5%86%B5.png)

## �ġ�std_alloc��ֲ��C����

![std_alloc��ֲ��C����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/std_alloc%E7%A7%BB%E6%A4%8D%E8%87%B3C%E8%AF%AD%E8%A8%80.png)