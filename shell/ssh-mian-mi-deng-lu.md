# ssh 免密登录

## Windows

1. 生成rsa密钥对

ssh-keygen -t rsa

2. 复制公钥要需要登录的机器

type id\_rsa.pub | ssh User@Host "cat >> .ssh/authorized\_keys

chmod 600 .ssh/authorized\_keys"

3. 修改本地.ssh/config文件, 增加配置项

Host Server1

&#x20;   HostName 192.168.100.123

&#x20;   User test

&#x20;   Identityfile "e:\id\_rsa"

4. 修改本地私钥文件id\_rsa的权限, 仅允许管理员和当前用户访问

## Linux

1. ssh-keygen
2. ssh-copy-id User@Host

(ssh-copy-id \[-i \[identity\_file]] User@Host)

3. linux下新增.ssh/config文件时, 需要调整权限chmod 600 config

