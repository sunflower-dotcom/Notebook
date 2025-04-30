# record

rec + rec_len(变长列的长度控制信息1 or 2) + 2(记录长度) + ctl_bitsize(四列一字节, 每一列两bit) + (根据描述信息类型, 判断加什么 事务id(6) , rowid(6), rol_addr(7))


1. max_rec_len:

    (page_size - PAGE4_OF_INDEX_SIZE(82) - PAGE_HEADER(20) - PAGE_TAIL_SIZE) / 2

    max_data_len:

    tmp_len = (page_size - PAGE4_OF_INDEX_SIZE(82) - 2 * (1 + 2 + SIZEOF(DDWORD)) - (SIZEOF(USINT)) * 50) / 2
    max_data_len = tmp_len - (tmp_len % 100)

    page_tail_size:

    8 + hash_size + page_size / slice_size * extend_size

