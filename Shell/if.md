---
title: Shell IF语法
Date: 2023-02-27T10:30:34.000Z
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2023-02-27T20:45:23.000Z
FilePath: \Notebook\Shell\if.md
Categories: SHELL
---

# SHELL IF 语法

if \[ -f file ]; then\
echo "yes yes yes"\
elif \[ -z file ]; then\
echo "yes yes"\
else\
echo "nonono"\
fi
