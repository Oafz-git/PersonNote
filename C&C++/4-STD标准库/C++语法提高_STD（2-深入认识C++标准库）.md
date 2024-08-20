# �ڶ�����������ʶC++��׼��

## һ��Դ�����

### 1.����������

![����������](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%93%8D%E4%BD%9C%E7%AC%A6%E9%87%8D%E8%BD%BD.png)

### 2.ģ��

#### a.��ģ�塢����ģ�塢��Աģ��

![ģ��](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E6%A8%A1%E7%89%88.png)

#### b.�������ػ���ƫ�ػ�

![�ػ�-����-ƫ�ػ�](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%89%B9%E5%8C%96-%E6%B3%9B%E5%8C%96-%E5%81%8F%E7%89%B9%E5%8C%96.png)

## ��������������һ���ֿ��ڴ����

## ����˳��ʽ����

### 1.����֮��Ĺ�ϵ

![����֮��Ĺ�ϵ](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8%E4%B9%8B%E9%97%B4%E7%9A%84%E5%85%B3%E7%B3%BB.png)

### 2.����list��G2.9vs.G4.9��

![����list](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8list.png)

### 3.Iterator�����ԭ���Iterator Traits����ȡ���������������

![Iterator��Trait](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/Iterator%E5%92%8CTrait.png)

### 4.����Vector��G2.9vs.G4.9��

![����VectorG2.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8vector.png)

---

![����VectorG4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8vectorG4.9.png)

### 5.����Array��TR1vs.G4.9��

![����array-TR1](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8array-TR1.png)

---

![����array-G4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8array-G4.9.png)

### 6.����forward_list��û����ϸ���⣩

![����forward_list](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8forward_list.png)

### 7.����deque

![����deque-G2.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8deque.png)

---

![����deque-G4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8deque-G4.9.png)

### 8.����queue��stack��Ĭ��ʹ��dequeΪ�ײ�֧�ţ�

![����queue������stack](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8queue%E5%92%8C%E5%AE%B9%E5%99%A8stack.png)

## �ġ�����ʽ����

### 1.����rb_tree��G2.9 vs. G4.9��

* Red-Black tree�����������ƽ������������г��õ�һ�֡����������й���������`search`��`insert`����**�����ʶ�ƽ�⡪�����κνڵ����**��

* re_tree�ṩ**����**������Iterator������������++ite�����������ܻ��**����**״̬��

* ����**��Ӧ**ʹ��re_tree��iterator**�ı�**Ԫ��ֵ����ΪԪ�������Ͻ����й��򣩡�����̲���**��δ�������**���������Ƿ�����ȷ�ģ���Ϊrb_tree����Ϊset��map������Ϊ�ײ�֧�ţ�����map����Ԫ�ص�`data`���ı䣬ֻ��Ԫ�ص�`key`���ǲ����Ա��ı�ġ�

* rb_tree�ṩ����insertion������`insert_unique()`��`insert_equal()`��ǰ�߱�ʾ�ڵ��keyһ��������tree�ж�һ�޶������򰲲�ʧ�ܣ����߱�ʾ�ڵ��key���ظ���

#### a. rb_tree G2.9��

![�����G2.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%A2%E9%BB%91%E6%A0%91G2.9.png)

#### b. rb_tree G4.9��

![�����G4.9](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E7%BA%A2%E9%BB%91%E6%A0%91G4.9.png)

### 2.����set��multiset

* set/multiset��rb_treeΪ�ײ�ṹ�������**Ԫ���Զ�����**���ԡ���������ݾ���key����**set/multisetԪ�ص�value��key��һ��value����key��**

* set/multiset�ṩ**����**������Iterator������������++ite�����������ܻ������״̬��sorted����

* ����**����**ʹ��set/multiset��Iterator�ı�Ԫ��ֵ����Ϊkey�����Ͻ������й��򣩡�set/multiset��Iterator����ײ���rb_tree��const_iterator������Ϊ��**��ֹ**user��Ԫ�ظ�ֵ��

* setԪ�ص�key�����һ�޶��������`insert()`�õ���rb_tree��`insert_unique()`��

* multisetԪ�ص�key�����ظ��������`insert()`�õ���rb_tree��`insert_equal()`��

![����set](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8set.png)

### 3.����map��multimap

* map/multimap��rb_treeΪ�ײ�ṹ�������**Ԫ���Զ�����**���ԡ���������ݾ���key��

* map/multimap�ṩ**����**������Iterator������������++ite�����������ܻ������״̬��sorted����

* ����**�޷�**ʹ��map/multimap��Iterator�ı�key����Ϊkey�����Ͻ������й��򣩣��������������ı�Ԫ�ص�data�����map/multimap�ڲ��Զ���**userָ����key type**��Ϊ**const**����˱���**��ֹ**user��**Ԫ�ص�key**��ֵ��

* mapԪ�ص�key�����һ�޶��������`insert()`�õ���rb_tree��`insert_unique()`��

* multimapԪ�ص�key�����ظ��������`insert()`�õ���rb_tree��`insert_equal()`��

![����map](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8map.png)

## �塢����������

### 1.����hashtable

![����hashtable](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/%E5%AE%B9%E5%99%A8hashtable.png)

### 2.unorder����

![unorder����](https://oafz-draw-bed.oss-cn-beijing.aliyuncs.com/img/unorder%E5%AE%B9%E5%99%A8.png)








