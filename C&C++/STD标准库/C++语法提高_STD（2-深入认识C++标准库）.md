# 第二讲：深入认识C++标准库

## 一、源码基础

### 1.操作符重载

![操作符重载](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%93%8D%E4%BD%9C%E7%AC%A6%E9%87%8D%E8%BD%BD.png)

### 2.模板

#### a.类模板、函数模板、成员模版

![模版](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%A8%A1%E7%89%88.png)

#### b.泛化、特化、偏特化

![特化-泛化-偏特化](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%89%B9%E5%8C%96-%E6%B3%9B%E5%8C%96-%E5%81%8F%E7%89%B9%E5%8C%96.png)

## 二、分配器（这一部分看内存管理）

## 三、顺序式容器

### 1.容器之间的关系

![容器之间的关系](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB.png)

### 2.容器list（G2.9vs.G4.9）

![容器list](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8list.png)

### 3.Iterator的设计原则和Iterator Traits（萃取机）的作用与设计

![Iterator和Trait](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Iterator%E5%92%8CTrait.png)

### 4.容器Vector（G2.9vs.G4.9）

![容器VectorG2.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8vector.png)

---

![容器VectorG4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8vectorG4.9.png)

### 5.容器Array（TR1vs.G4.9）

![容器array-TR1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8array-TR1.png)

---

![容器array-G4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8array-G4.9.png)

### 6.容器forward_list（没有详细讲解）

![容器forward_list](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8forward_list.png)

### 7.容器deque

![容器deque-G2.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8deque.png)

---

![容器deque-G4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8deque-G4.9.png)

### 8.容器queue和stack（默认使用deque为底部支撑）

![容器queue和容器stack](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8queue%E5%92%8C%E5%AE%B9%E5%99%A8stack.png)

## 四、关联式容器

### 1.容器rb_tree（G2.9 vs. G4.9）

* Red-Black tree（红黑树）是平衡二叉搜索树中常用的一种。特征：排列规则有利于`search`和`insert`，并**保持适度平衡——无任何节点过深**。

* re_tree提供**遍历**操作及Iterator，按正常规则（++ite）遍历，便能获得**排序**状态。

* 我们**不应**使用re_tree的iterator**改变**元素值（因为元素有其严谨排列规则）。但编程层面**并未阻绝此事**。如此设计是否是正确的，因为rb_tree即将为set和map服务（作为底部支撑），而map允许元素的`data`被改变，只有元素的`key`才是不可以被改变的。

* rb_tree提供两种insertion操作：`insert_unique()`和`insert_equal()`。前者表示节点的key一定在整个tree中独一无二，否则安插失败；后者表示节点的key可重复。

#### a. rb_tree G2.9版

![红黑树G2.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%A2%E9%BB%91%E6%A0%91G2.9.png)

#### b. rb_tree G4.9版

![红黑树G4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%A2%E9%BB%91%E6%A0%91G4.9.png)

### 2.容器set、multiset

* set/multiset以rb_tree为底层结构，因此有**元素自动排序**特性。排序的依据就是key，而**set/multiset元素的value和key合一：value就是key。**

* set/multiset提供**遍历**操作及Iterator。按正常规则（++ite）遍历，便能获得排序状态（sorted）。

* 我们**不能**使用set/multiset的Iterator改变元素值（因为key有其严谨的排列规则）。set/multiset的Iterator是其底部的rb_tree的const_iterator，就是为了**禁止**user对元素赋值。

* set元素的key必须独一无二，因此其`insert()`用的是rb_tree的`insert_unique()`。

* multiset元素的key可以重复，因此其`insert()`用的是rb_tree的`insert_equal()`。

![容器set](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8set.png)

### 3.容器map、multimap

* map/multimap以rb_tree为底层结构，因此有**元素自动排序**特性。排序的依据就是key。

* map/multimap提供**遍历**操作及Iterator。按正常规则（++ite）遍历，便能获得排序状态（sorted）。

* 我们**无法**使用map/multimap的Iterator改变key（因为key有其严谨的排列规则），但可以用它来改变元素的data。因此map/multimap内部自动将**user指定的key type**设为**const**，如此便能**禁止**user对**元素的key**赋值。

* map元素的key必须独一无二，因此其`insert()`用的是rb_tree的`insert_unique()`。

* multimap元素的key可以重复，因此其`insert()`用的是rb_tree的`insert_equal()`。

![容器map](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8map.png)

## 五、不定序容器

### 1.容器hashtable

![容器hashtable](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8hashtable.png)

### 2.unorder容器

![unorder容器](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/unorder%E5%AE%B9%E5%99%A8.png)








