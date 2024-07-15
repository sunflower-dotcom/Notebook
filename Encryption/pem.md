---
title: Do not edit
Date: 2024-07-15 15:34:52
LastEditors: sunflower-dotcom 707339665@qq.com
LastEditTime: 2024-07-15 15:36:00
FilePath: \Notebook\Encryption\pem.md
categories: Do not edit
---
# [如何将.pem转换为.crt和.key](https://www.cnblogs.com/LiuYanYGZ/p/10375164.html "发布于 2019-02-14 16:09")

# [如何将.pem转换为.crt和.key？](https://vimsky.com/article/3608.html "如何将.pem转换为.crt和.key？")

摘自： https://vimsky.com/article/3608.html

貔貅 [技术问答](https://vimsky.com/category/%e6%8a%80%e6%9c%af%e9%97%ae%e7%ad%94) 2017-10-08 23:11 [certificate](https://vimsky.com/tags/certificate), [crt](https://vimsky.com/tags/crt), [private-key](https://vimsky.com/tags/private-key), [ssl](https://vimsky.com/tags/ssl) [去评论](https://vimsky.com/article/3608.html#respond)

## .pem转换的问题描述

从`.pem`文件中提取/转换证书`.crt`和私钥`.key`文件的正确方法或者命令是什么？我知道它们是可转换的，但是不清楚怎么做。

## 最佳解决方法

可以使用以下方式将pem转换为crt：

```csharp
openssl x509 -outform der -in your-cert.pem -out your-cert.crt 
```

## 可行的解决方法整理

使用OpenSSL进行转换

以下命令允许将证书和密钥转换为不同的格式，使其与特定类型的服务器或软件兼容。

- 将DER文件(.crt .cer .der)转换为PEM
    
    ```csharp
    openssl x509 -inform der -in certificate.cer -out certificate.pem 
    ```
    
- 将PEM文件转换为DER
    
    ```csharp
    openssl x509 -outform der -in certificate.pem -out certificate.der 
    ```
    
- 将包含私钥和证书的PKCS＃12文件(.pfx .p12)转换为PEM
    
    ```sql
    openssl pkcs12 -in keyStore.pfx -out keyStore.pem -nodes  You can add -nocerts to only output the private key or add -nokeys to only output the certificates. 
    ```
    
- 将PEM证书文件和私钥转换为PKCS＃12(.pfx .p12)
    
    ```objectivec
    openssl pkcs12 -export -out certificate.pfx -inkey privateKey.key -in certificate.crt -certfile CACert.crt 
    ```
    
- 将PEM转换为CRT(.CRT文件)
    
    ```csharp
    openssl x509 -outform der -in certificate.pem -out certificate.crt 
    ```
    

OpenSSL转换PEM

- 将PEM转换为DER
    
    ```csharp
    openssl x509 -outform der -in certificate.pem -out certificate.der 
    ```
    
- 将PEM转换为P7B
    
    ```objectivec
    openssl crl2pkcs7 -nocrl -certfile certificate.cer -out certificate.p7b -certfile CACert.cer 
    ```
    
- 将PEM转换为PFX
    
    ```objectivec
    openssl pkcs12 -export -out certificate.pfx -inkey privateKey.key -in certificate.crt -certfile CACert.crt 
    ```
    

OpenSSL转换DER

- 将DER转换为PEM
    
    ```csharp
    openssl x509 -inform der -in certificate.cer -out certificate.pem 
    ```
    

OpenSSL转换P7B

- 将P7B转换为PEM
    
    ```csharp
    openssl pkcs7 -print_certs -in certificate.p7b -out certificate.cer 
    ```
    
- 将P7B转换为PFX
    
    ```objectivec
    openssl pkcs7 -print_certs -in certificate.p7b -out certificate.cer  openssl pkcs12 -export -in certificate.cer -inkey privateKey.key -out certificate.pfx -certfile CACert.cer 
    ```
    

OpenSSL转换PFX

- 将PFX转换为PEM
    
    ```csharp
    openssl pkcs12 -in certificate.pfx -out certificate.cer -nodes 
    ```
    

通过OpenSSL生成rsa密钥

- 在命令行上使用OpenSSL，首先需要生成公钥和私钥，应该使用-passout参数密码保护此文件，该参数可以采用许多不同的形式，可以请参阅OpenSSL文档。
    
    ```csharp
    openssl genrsa -out private.pem 1024 
    ```
    
- 这将创建一个名为private.pem的密钥文件，该文件使用1024位(bits)。该文件实际上同时具有私钥和公钥，可以从该文件中提取公共密钥：
    
    ```csharp
    openssl rsa -in private.pem -out public.pem -outform PEM -pubout  or  openssl rsa -in private.pem -pubout > public.pem  or  openssl rsa -in private.pem -pubout -out public.pem 
    ```
    
    现在你的`public.pem`只包含公钥，可以和第三方自由地分享。可以通过使用公钥加密自己的东西然后使用私钥进行解密来测试，首先我们需要一些数据做加密：
    
- 示例文件：
    
    ```bash
    echo 'too many secrets' > file.txt 
    ```
    
- 现在在file.txt中有一些数据，可以使用OpenSSL和公钥进行加密：
    
    ```delphi
    openssl rsautl -encrypt -inkey public.pem -pubin -in file.txt -out file.ssl 
    ```
    
- 这将创建一个加密版本的file.txt，命令这个文件为file.ssl（如果直接打开这个文件查看那么它看起来只是二进制垃圾，人类无法看懂）。然后可以使用私钥解密它：
    
    ```delphi
    openssl rsautl -decrypt -inkey private.pem -in file.ssl -out decrypted.txt 
    ```
    
- 现在在decryptpted.txt中有一个未加密的文件：
    
    ```bash
    cat decrypted.txt |output -> too many secrets 
    ```
    

OpenSSL中的RSA工具选项

- 名称：
    
    ```undefined
    rsa  -  RSA密钥处理工具
    ```
    
- 概要：
    
    ```css
    openssl rsa [-help] [-inform PEM | NET | DER] [-outform PEM | NET | DER] [-in filename] [-passin arg] [-out filename] [-passout arg] [-aes128] [ -aes192] [-aes256] [-camellia128] [-camellia192] [-camellia256] [-des] [-des3] [-idea] [-text] [-noout] [-modulus] [-check] [-pubin ] [-pubout] [-RSAPublicKey_in] [-RSAPublicKey_out] [-engine id]
    ```
    
- 说明：   
    rsa命令处理RSA密钥。它们可以在各种形式之间进行转换，并将其组件打印出来。注意，此命令使用传统的SSLeay兼容格式进行私钥加密：较新的应用程序应使用pkcs8实用程序使用更安全的PKCS＃8格式。
    
- 命令选项:
    
    ```bash
    -help 
    ```
    
    打印出使用信息。
    
    ```diff
    -inform DER|NET|PEM 
    ```
    
    指定输入格式。 DER选项使用与`PKCS＃1 RSAPrivateKey`或`SubjectPublicKeyInfo`格式兼容的ASN1 DER编码格式。 PEM格式是默认格式：它由DER格式base64编码，带有附加的页眉和页脚行。在输入PKCS＃8格式的私钥也被接受。 NET格式是在NOTES部分中描述的格式。
    
    ```diff
    -outform DER|NET|PEM 
    ```
    
    指定输出格式，选项与-inform选项的含义相同。
    
    ```diff
    -in filename 
    ```
    
    如果未指定此选项，则指定从或从标准输入读取密钥的输入文件名。如果密钥加密，将提示输入密码。
    
    ```diff
    -passin arg 
    ```
    
    输入文件的密码来源。有关arg的格式的更多信息，参阅openssl中的`PASS PHRASE ARGUMENTS`部分。
    
    ```csharp
    -out filename 
    ```
    
    如果未指定此选项，则指定将密钥写入或输出的输出文件名。如果设置了任何加密选项，则会提示输入密码。输出文件名不能与输入文件名相同。
    
    ```diff
    -passout password 
    ```
    
    输出文件密码来源。有关arg的格式的更多信息，参阅openssl中的`PASS PHRASE ARGUMENTS`部分。
    
    ```diff
    -aes128|-aes192|-aes256|-camellia128|-camellia192|-camellia256|-des|-des3|-idea 
    ```
    
    这些选项在输出之前用指定的密码加密私钥。会有同通行提示信息。如果没有指定这些选项，则key以纯文本形式写入。这些选项只能用于PEM格式的输出文件。
    
    ```diff
    -text 
    ```
    
    除了编码版本之外，以纯文本形式打印各种公共或私人密钥组件。
    
    ```diff
    -noout 
    ```
    
    此选项可防止输出密钥的编码版本。
    
    ```diff
    -modulus 
    ```
    
    此选项打印出该键的取模数值。
    
    ```diff
    -check 
    ```
    
    此选项将检查RSA私钥的一致性。
    
    ```diff
    -pubin 
    ```
    
    默认情况下，从输入文件读取私钥：使用此选项读取公钥。
    
    ```diff
    -pubout 
    ```
    
    默认情况下会输出一个私钥：使用此选项将会输出一个公钥。如果输入是公钥，则会自动设置此选项。
    
    ```diff
    -RSAPublicKey_in, -RSAPublicKey_out 
    ```
    
    像-pubin和-pubout一样，除了使用RSAPublicKey格式的情形。
    
    ```bash
    -engine id 
    ```
    
    指定一个引擎(通过其获得唯一的id字符串)将导致rsa尝试获得对特定引擎功能的引用，从而在需要时进行初始化。然后，引擎将被设置为所有可用算法的默认值。
    
- 笔记
    
    PEM私钥格式使用以下页眉和页脚行：
    
    ```vbnet
    -----BEGIN RSA PRIVATE KEY-----  -----END RSA PRIVATE KEY----- 
    ```
    
    PEM公钥格式使用以下页眉和页脚行：
    
    ```vbnet
    -----BEGIN PUBLIC KEY-----  -----END PUBLIC KEY----- 
    ```
    
    PEM RSAPublicKey格式使用以下页眉和页脚线：
    
    ```vbnet
    -----BEGIN RSA PUBLIC KEY-----  -----END RSA PUBLIC KEY----- 
    ```
    
    NET格式是与旧的Netscape服务器和Microsoft IIS .key文件兼容的格式，它使用未加密的RC4进行加密。这种方法不是很安全，所以只能在必要时使用。一些较新版本的IIS在导出的.key文件中有其他额外的数据。要使用这些实用程序，请使用二进制编辑器查看文件，并查找字符串"private-key"，然后追溯到字节序列0x30，0x82(这是一个`ASN1 SEQUENCE`)。将所有数据从此点复制到另一个文件，并将其用作带有-inform NET选项的rsa实用程序的输入。
    
    例子
    
    要删除RSA私钥上的密码短语：
    
    ```csharp
     openssl rsa -in key.pem -out keyout.pem 
    ```
    
    使用三重DES加密私钥：
    
    ```csharp
     openssl rsa -in key.pem -des3 -out keyout.pem 
    ```
    
    将私钥从PEM转换为DER格式：
    
    ```csharp
      openssl rsa -in key.pem -outform DER -out keyout.der 
    ```
    
    将私钥的组件输出到标准输出：
    
    ```vbnet
      openssl rsa -in key.pem -text -noout 
    ```
    
    要输出私钥的公共部分：
    
    ```csharp
      openssl rsa -in key.pem -pubout -out pubkey.pem 
    ```
    
    以RSAPublicKey格式输出私钥的公共部分：
    
    ```csharp
      openssl rsa -in key.pem -RSAPublicKey_out -out pubkey.pem 
    ```


## 1.pem转crt格式

```powershell
openssl x509 -in fullchain.pem -out fullchain.crt
具体用法为:
cd ..
openssl
x509 -in /etc/letsencrypt/archive/domain/fullchain1.pem -out /etc/letsencrypt/archive/domain/fullchain1.crt
然后在这个路径找到转换好的证书/etc/letsencrypt/archive/domain
```

## 2.pem转key格式

```powershell
openssl rsa -in privkey.pem -out privkey.key
具体用法为:
cd ..
openssl
rsa -in /etc/letsencrypt/archive/domain/privkey1.pem -out /etc/letsencrypt/archive/domain/privkey1.key
然后在这个路径找到转换好的证书/etc/letsencrypt/archive/domain
```