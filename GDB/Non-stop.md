---
title: No-stop
Date: 2024-07-10T09:59:30.000Z
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2024-07-10T10:04:29.000Z
FilePath: \Notebook\GDB\Non-stop.md
categories: GDB
---

# Non-stop

1. 前提\
   gdb -v 查看版本信息\
   7.0以前不支持non-stop模式
2. 把以下三行放在\~/.gdbinit中(或在启动进程前输入gdb命令)\
   set target-async 1\
   set pagination off\
   set non-stop on
3. 启动gdb(gdb启动进程)\
   gdb
