---
title: Do not edit
Date: 2023-03-01 15:08:18
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2024-06-02 15:57:12
FilePath: \Notebook\Bison\bison.md
Categories: Do not edit
---
# Bison

1. bison编译参数
    -p增加前缀
    也可以用%name-prefix="prefix"来实现
2. 调试
    enter state
    read next token
    查找是否存在shift, 如果有, go to state; 如果没有尝试, 直接goto, 在没有尝试reducing, 找到上层表达式, 在从当前堆栈找到对应的表达式所go to的state