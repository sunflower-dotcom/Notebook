---
title: Hash
Date: 2023-03-06 19:39:00
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2023-03-07 18:52:07
FilePath: \Notebook\Redis\Hash.md
categories: Redis
---
# Hash

## Hash算法

Redis4.0之前使用的Hash算法是MurmurHash, 即使输入的键是有规律的, 该算法计算的结果依然有很好的离散性, 并且计算速度非常快. Redis4.0开始更换为SipHash算法, 应该是出于安全的考虑, 该算法能有效防止Hash表碰撞
攻击, 并提供不错的性能

> ### SipHash
>
> 大部分非加密哈希算法的改良，都集中在让哈希速度更快更好上。SipHash 则是个异类，它的提出是为了[解决一类安全问题](http://emboss.github.io/blog/2012/12/14/breaking-murmur-hash-flooding-dos-reloaded/)：hash flooding。通过让> 输出随机化，SipHash 能够有效减缓 hash flooding 攻击。凭借这一点，它逐渐成为 Ruby、Python、Rust 等语言默认的 hash 表实现的一部分。  
> 如果你愿意尝试下新技术，可以看看 2016 新出的 [HighwayHash](https://github.com/google/highwayhash)。它宣称可以达到 SipHash 一样的效果，并且凭借 SIMD 的加持，在运算速度上它是 SipHash 的 5.2 倍（参考来源：[https://arxiv.>  org/abs/1612.06257](https://arxiv.org/abs/1612.06257) ）。

## 扩容

把ht[0]上的数据迁移到ht[1]shang

size调整为2的n次幂, 为了ht[1]Hash表数据长度是ht[0]Hash表数据长度的倍数, 有利于ht[0]的数据均匀地迁移到ht[1]

**Hash&ht.sizemask, sizemask=size-1, idx=hash%(ht.size)**, 因此, 假如ht[0].size为0, ht[1].size=2*n, 对于ht[0]上的元素, ht[0].table[k]的数据, 要不迁移到ht[1].table[k], 要不迁移到ht[1].table[k+n]

## 缩容

执行删除操作后, Redis会检查字典是否需要缩容, 当Hash表长度大于4且负载因子小于0.1时, 会执行缩容操作, 以节省内存

## 总结

Redis字典使用SipHash算法计算Hash值, 并使用链表法处理Hash冲突  
Redis字段使用渐进式扩容方法, 在每次数据操作中都执行一次扩容单步操作, 直到扩容完成  
散列类型的编码格式可以为OBJ_ENCODING_HT, OBJ_ENCODING_ZIPLIST  