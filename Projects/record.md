# record

rec + rec\_len(变长列的长度控制信息1 or 2) + 2(记录长度) + ctl\_bitsize(四列一字节, 每一列两bit) + (根据描述信息类型, 判断加什么 事务id(6) , rowid(6), rol\_addr(7))

1.  max\_rec\_len:

    (page\_size - PAGE4\_OF\_INDEX\_SIZE(82) - PAGE\_HEADER(20) - PAGE\_TAIL\_SIZE) / 2

    max\_data\_len:

    tmp\_len = (page\_size - PAGE4\_OF\_INDEX\_SIZE(82) - 2 \* (1 + 2 + SIZEOF(DDWORD)) - (SIZEOF(USINT)) \* 50) / 2\
    max\_data\_len = tmp\_len - (tmp\_len % 100)

    page\_tail\_size:

    8 + hash\_size + page\_size / slice\_size \* extend\_size
