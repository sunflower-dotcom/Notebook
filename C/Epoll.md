---
title: Epoll
Date: 2023-03-05 14:05:20
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2023-03-05 17:18:47
FilePath: \Notebook\C\Epoll.md
categories: C/C++
---

# Epoll

**`epoll`**是[Linux](https://zh.wikipedia.org/wiki/Linux "Linux")内核的可扩展I/O事件通知机制<sup id="cite_ref-1" class="reference"><a href="https://zh.wikipedia.org/wiki/Epoll#cite_note-1">[1]</a></sup>。于Linux 2.5.44首度登场，它设计目的旨在取代既有[POSIX](https://zh.wikipedia.org/wiki/POSIX "POSIX") [`select(2)`](https://zh.wikipedia.org/wiki/Select_(Unix) "Select (Unix)")与`poll(2)`[系统函数](https://zh.wikipedia.org/wiki/%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8 "系统调用")，让需要大量操作[文件描述符](https://zh.wikipedia.org/wiki/%E6%AA%94%E6%A1%88%E6%8F%8F%E8%BF%B0%E5%AD%90 "文件描述符")的程序得以发挥更优异的性能（举例来说：旧有的系统函数所花费的时间复杂度为O(n)，`epoll`的时间复杂度O(log n)）。epoll 实现的功能与 poll 类似，都是监听多个文件描述符上的事件

## 程序接口

int epoll\_create(int size);

在内核中创建`epoll`实例并返回一个`epoll`文件描述符。 在最初的实现中，调用者通过 `size` 参数告知内核需要监听的文件描述符数量。如果监听的文件描述符数量超过 size, 则内核会自动扩容。而现在 size 已经没有这种语义了，但是调用者调用时 size 依然必须大于 0，以保证后向兼容性。

int epoll\_ctl(int epfd, int op, int fd, struct epoll\_event \*event);

向 epfd 对应的内核`epoll` 实例添加、修改或删除对 fd 上事件 event 的监听。op 可以为 `EPOLL_CTL_ADD`, `EPOLL_CTL_MOD`, `EPOLL_CTL_DEL` 分别对应的是添加新的事件，修改文件描述符上监听的事件类型，从实例上删除一个事件。如果 event 的 events 属性设置了 `EPOLLET` flag，那么监听该事件的方式是边缘触发。

int epoll\_wait(int epfd, struct epoll\_event \*events, int maxevents, int timeout);

当 timeout 为 0 时，epoll\_wait 永远会立即返回。而 timeout 为 -1 时，epoll\_wait 会一直阻塞直到任一已注册的事件变为就绪。当 timeout 为一正整数时，epoll 会阻塞直到计时 timeout 毫秒终了或已注册的事件变为就绪。因为内核调度延迟，阻塞的时间可能会略微超过 timeout 毫秒。

## 触发模式\[[编辑](https://zh.wikipedia.org/w/index.php?title=Epoll&action=edit&section=2 "编辑章节：触发模式")\]

`epoll`提供[边沿触发](https://zh.wikipedia.org/wiki/%E4%B8%AD%E6%96%AD#%E8%BE%B9%E6%B2%BF%E8%A7%A6%E5%8F%91 "中断")及[状态触发](https://zh.wikipedia.org/wiki/%E4%B8%AD%E6%96%AD#%E7%8A%B6%E6%80%81%E8%A7%A6%E5%8F%91 "中断")模式。在边沿触发模式中，`epoll_wait`仅会在新的事件首次被加入`epoll`队列时返回；于level-triggered模式下，`epoll_wait`在事件状态未变更前将不断被触发。状态触发模式是默认的模式。

状态触发模式与边沿触发模式有读和写两种情况，我们先来考虑读的情况。假设我们注册了一个读事件到`epoll`实例上，`epoll`实例会通过`epoll_wait`返回值的形式通知我们哪些读事件已经就绪。简单地来说，在状态触发模式下，如果读事件未被处理，该事件对应的内核读缓冲器非空，则每次调用 `epoll_wait` 时返回的事件列表都会包含该事件。直到该事件对应的内核读缓冲器为空为止。而在边沿触发模式下，读事件就绪后只会通知一次，不会反复通知。

然后我们再考虑写的情况。水平触发模式下，只要文件描述符对应的内核写缓冲器未满，就会一直通知可写事件。而在边沿触发模式下，内核写缓冲器由满变为未满后，只会通知一次可写事件。

举例来说，倘若有一个已经于`epoll`注册之[流水线](https://zh.wikipedia.org/wiki/Anonymous_pipe "Anonymous pipe")接获资料，`epoll_wait`将返回，并发出资料读取的信号。现假设缓冲器的资料仅有部分被读取并处理，在level-triggered模式下，任何对`epoll_wait`之调用都将即刻返回，直到缓冲器中的资料全部被读取；然而，在edge-triggered的情境下，`epoll_wait`仅会于再次接收到新资料(亦即，新资料被写入流水线)时返回。

### 边沿触发模式\[[编辑](https://zh.wikipedia.org/w/index.php?title=Epoll&action=edit&section=3 "编辑章节：边沿触发模式")\]

边沿触发模式使得程序有可能在用户态缓存 IO 状态。nginx 使用的是边沿触发模式。

文件描述符有两种情况是推荐使用边沿触发模式的。

1. read 或者 write 系统调用返回了 EAGAIN。
2. 非阻塞的文件描述符。

可能的缺陷：

1. 如果 IO 空间很大，你要花很多时间才能把它一次读完，这可能会导致饥饿。举个例子，假设你在监听一个文件描述符列表，而某个文件描述符上有大量的输入（不间断的输入流），那么你在读完它的过程中就没空处理其他就绪的文件描述符。（因为边沿触发模式只会通知一次可读事件，所以你往往会想一次把它读完。）一种解决方案是，程序维护一个就绪队列，当 `epoll` 实例通知某文件描述符就绪时将它在就绪队列数据结构中标记为就绪，这样程序就会记得哪些文件描述符等待处理。Round-Robin 循环处理就绪队列中就绪的文件描述符即可。
2. 如果你缓存了所有事件，那么一种可能的情况是 A 事件的发生让程序关闭了另一个文件描述符 B。但是内核的 `epoll` 实例并不知道这件事，需要你从 `epoll` 删除掉。