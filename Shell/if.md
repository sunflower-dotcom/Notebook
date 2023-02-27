---
title: Do not edit
Date: 2023-02-27 10:30:34
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2023-02-27 10:31:07
FilePath: \Notebook\Shell\if.md
Categories: Do not edit
---
# SHELL IF 语法

if [ -f file ]; then
   echo "yes yes yes"
elif [ -z file ]; then
   echo "yes yes"
else
   echo "nonono"
fi