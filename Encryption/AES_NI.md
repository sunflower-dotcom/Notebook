---
title: AES_NI
Date: 2023-04-03 14:23:01
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2023-04-03 18:45:59
FilePath: \Notebook\Encryption\AES_NI.md
categories: Encryption
---

# AES_NI

## How to find out AES-NI (Advanced Encryption) Enabled on Linux System
One can find out that the processor has the AES/AES-NI instruction set using the lscpu command:
> lscpu

Type the following grep command to make sure that the processor has the AES instruction set and enabled in the BIOS:
> grep -o aes /proc/cpuinfo

OR
> grep -m1 -o aes /proc/cpuinfo