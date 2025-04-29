# dd

## 用途

[dd命令](https://so.csdn.net/so/search?q=dd%E5%91%BD%E4%BB%A4&spm=1001.2101.3001.7020),主要功能为转换和复制文件。  
在Linux中，硬件的设备驱动和特殊设备文件 也是文件；dd也可以直接读取或写入到这些文件。  
dd：用指定大小的块拷贝一个文件，并在拷贝的同时进行指定的转换。

块是衡量一次读取、写入和转换字节的单位。命令行选项可以为输入/读取（ibs）和输出/写入（[obs](https://so.csdn.net/so/search?q=obs&spm=1001.2101.3001.7020)）指定一个不同的块大小，尽管块大小（bs）选项会覆盖ibs和obs选项。输入和输出的默认块大小为512字节（传统的磁盘块及POSIX规定的“块”大小）复制的count选项。

## 参数详解

- if=文件名：输入文件名，缺省为标准输入。即指定源文件。< if=input file >
- of=文件名：输出文件名，缺省为标准输出。即指定目的文件。< of=output file >
- ibs=bytes：一次读入bytes个字节，即指定一个块大小为bytes个字节。
- obs=bytes：一次输出bytes个字节，即指定一个块大小为bytes个字节。
- bs=bytes：同时设置读入/输出的块大小为bytes个字节。
- cbs=bytes：一次转换bytes个字节，即指定转换缓冲区大小。
- skip=blocks：从输入文件开头跳过blocks个块后再开始复制。
- seek=blocks：从输出文件开头跳过blocks个块后再开始复制。  
    注意：通常只用当输出文件是磁盘或磁带时才有效，即备份到磁盘或磁带时才有效。
- count=blocks：仅拷贝blocks个块，块大小等于ibs指定的字节数。
- conv=conversion：用指定的参数转换文件。
- ascii：转换ebcdic为ascii
- ebcdic：转换ascii为ebcdic
- ibm：转换ascii为alternate ebcdic
- block：把每一行转换为长度为cbs，不足部分用空格填充
- unblock：使每一行的长度都为cbs，不足部分用空格填充
- lcase：把大写字符转换为小写字符
- ucase：把小写字符转换为大写字符
- swab：交换输入的每对字节
- noerror：出错时不停止
- notrunc：不截短输出文件
- sync：将每个输入块填充到ibs个字节，不足部分用空（NUL）字符补齐。

## dd 示例

1.将本地的/dev/hdb整盘备份到/dev/hdd

```bash
dd if=/dev/hdb of=/dev/hdd
```

2.将/dev/hdb全盘数据备份到指定路径的image文件

```bash
dd if=/dev/hdb of=/root/image
```

3.将备份文件恢复到指定盘

```bash
dd if=/root/image of=/dev/hdb
```

4.备份/dev/hdb全盘数据，并利用gzip工具进行压缩，保存到指定路径

```bash
dd if=/dev/hdb | gzip > /root/image.gz
```

5.将压缩的备份文件恢复到指定盘

```bash
gzip -dc /root/image.gz | dd of=/dev/hdb
```

6.备份与恢复MBR  
备份磁盘开始的512个字节大小的MBR信息到指定文件：

```bash
dd if=/dev/hda of=/root/image count=1 bs=512
count=1指仅拷贝一个块；bs=512指块大小为512个字节。
```

恢复：

```bash
dd if=/root/image of=/dev/had
将备份的MBR信息写到磁盘开始部分
```

7.备份软盘

```bash
dd if=/dev/fd0 of=disk.img count=1 bs=1440k (即块大小为1.44M)
```

8.拷贝内存内容到硬盘

```bash
dd if=/dev/mem of=/root/mem.bin bs=1024 (指定块大小为1k)
```

9.拷贝光盘内容到指定文件夹，并保存为cd.iso文件

```bash
dd if=/dev/cdrom(hdc) of=/root/cd.iso
```

10.增加swap分区文件大小

```bash
第一步：创建一个大小为256M的文件：
dd if=/dev/zero of=/swapfile bs=1024 count=262144
第二步：把这个文件变成swap文件：
mkswap /swapfile
第三步：启用这个swap文件：
swapon /swapfile
第四步：编辑/etc/fstab文件，使在每次开机时自动加载swap文件：
/swapfile swap swap default 0 0
```

11.销毁磁盘数据

```bash
dd if=/dev/urandom of=/dev/hda1
```

注意：利用随机的数据填充硬盘，在某些必要的场合可以用来销毁数据。

12.测试硬盘的读写速度

```bash
dd if=/dev/zero bs=1024 count=1000000 of=/root/1Gb.file
dd if=/root/1Gb.file bs=64k | dd of=/dev/null
```

通过以上两个命令输出的命令执行时间，可以计算出硬盘的读、写速度。

13.确定硬盘的最佳块大小：

```bash
dd if=/dev/zero bs=1024 count=1000000 of=/root/1Gb.file
dd if=/dev/zero bs=2048 count=500000 of=/root/1Gb.file
dd if=/dev/zero bs=4096 count=250000 of=/root/1Gb.file
dd if=/dev/zero bs=8192 count=125000 of=/root/1Gb.file
```

通过比较以上命令输出中所显示的命令执行时间，即可确定系统最佳的块大小。

14.修复硬盘：

```bash
dd if=/dev/sda of=/dev/sda 或dd if=/dev/hda of=/dev/hda
```

当硬盘较长时间(一年以上)放置不使用后，磁盘上会产生magnetic flux point，当磁头读到这些区域时会遇到困难，并可能导致I/O错误。当这种情况影响到硬盘的第一个扇区时，可能导致硬盘报废。上边的命令有可能使这些数 据起死回生。并且这个过程是安全、高效的。

15.将一个很大的视频文件中的第i个字节的值改成0x41（也就是大写字母A的ASCII值）

```bash
echo A | dd of=bigfile seek=$i bs=1 count=1 conv=notrunc
```