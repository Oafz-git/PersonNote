# 第三讲：良好使用C++标准库

## 一、算法

### 1.算法的形式

![算法的形式](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%AE%97%E6%B3%95%E7%9A%84%E5%BD%A2%E5%BC%8F.png)

### 2.迭代器分类（iterator_category）

![迭代器分类](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%AD%E4%BB%A3%E5%99%A8%E5%88%86%E7%B1%BB.png)

### 3.迭代器分类对算法的影响

### 4. 仿函数functors

![仿函数functors](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E4%BB%BF%E5%87%BD%E6%95%B0functors.png)

### 5.适配器Adapter（换肤工程）

#### a.认识各种适配器

![各种适配器](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%90%84%E7%A7%8D%E9%80%82%E9%85%8D%E5%99%A8.png)

#### b.容器适配器

![容器适配器](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8%E9%80%82%E9%85%8D%E5%99%A8.png)

#### c.函数适配器binder2nd

![函数适配器binder2nd](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%87%BD%E6%95%B0%E9%80%82%E9%85%8D%E5%99%A8binder2nd.png)

#### d.函数适配器not1（和分析binder2nd相同）

![函数适配器not1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%87%BD%E6%95%B0%E9%80%82%E9%85%8D%E5%99%A8not1.png)

#### e.函数适配器bind

![函数适配器bind](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%96%B0%E5%9E%8B%E9%80%82%E9%85%8D%E5%99%A8bind.png)

#### f.迭代器适配器（reverse_iterator）

![迭代器适配器（reverse_iterator）](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%AD%E4%BB%A3%E5%99%A8%E9%80%82%E9%85%8D%E5%99%A8reverse_iterator.png)

#### e.迭代器适配器（inserter）

![迭代器适配器（inserter）](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E8%BF%AD%E4%BB%A3%E5%99%A8%E9%80%82%E9%85%8D%E5%99%A8inserter.png)

#### f.其它适配器ostream_iterator

![其它适配器ostream_iterator](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%85%B6%E5%AE%83%E9%80%82%E9%85%8D%E5%99%A8ostream_iterator.png)

#### g.其它适配器istream_iterator

![其它适配器istream_iterator](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%85%B6%E5%AE%83%E9%80%82%E9%85%8D%E5%99%A8istream_iterator.png)