# read

linux shell从键盘获取输入

**代码1：**

#!/bin/bash  
  
#提示“Input your choice:”，把用户的输入保存入变量choice\_user中  
read -p "Input your choice:" choice\_user  
echo "your choice:${choice\_user}"

  
#提示“请输入姓名”并等待30秒，把用户的输入保存入变量name中  
read -t 30 -p "请输入用户名称:" name  
echo -e "\\n"  
echo "用户名为:$name"  
  
#提示“请输入密码”并等待30秒，把用户的输入保存入变量age中，输入内容隐藏  
read -t 30 -s -p "请输入用户密码:" age  
echo -e "\\n"  
echo "用户密码为:$age"  
  
#提示“请输入性别”并等待30秒，把用户的输入保存入变量sex中，只接受一个字符输入  
read -t 30 -n 1 -p "请输入用户性别:" sex  
echo -e "\\n"  
echo "性别为$sex"

**read命令说明：**

  
read \[选项\]\[变量名\]  
选项：  
  
Read的一些选项  
Read可以带有-a, -d, -e, -n, -p, -r, -t, 和 -s八个选项。

\-a ：将内容读入到数值中  
echo -n "Input muliple values into an array:"  
read -a array  
echo "get ${#array\[@\]} values in array"  
\-d ：表示delimiter，即定界符，一般情况下是以IFS为参数的间隔，但是通过-d，我们可以定义一直读到出现执行的字符位置。例如read –d madfds value，读到有m的字符的时候就不在继续向后读，例如输入为 hello m，有效值为“hello”，请注意m前面的空格等会被删除。这种方式可以输入多个字符串，例如定义“.”作为结符号等等。  
\-e ：只用于互相交互的脚本，它将readline用于收集输入行。 
\-n ：用于限定最多可以有多少字符可以作为有效读入。例如echo –n 4 value1 value2，如果我们试图输入12 34，则只有前面有效的12 3，作为输入，实际上在你输入第4个字符‘3’后，就自动结束输入。这里结果是value为12，value2为3。  
\-p ：用于给出提示符，在前面的例子中我们使用了echo –n “…“来给出提示符，可以使用read –p ‘… my promt?’value的方式只需一个语句来表示。  
\-r ：在参数输入中，我们可以使用’/’表示没有输入完，换行继续输入，如果我们需要行最后的’/’作为有效的字符，可以通过-r来进行。此外在输入字符中，我们希望/n这类特殊字符生效，也应采用-r选项。  
\-s ：对于一些特殊的符号，例如箭头号，不将他们在terminal上打印，例如read –s key，我们按光标，在回车之后，如果我们要求显示，即echo，光标向上，如果不使用-s，在输入的时候，输入处显示^\[\[A，即在terminal上打印，之后如果要求echo，光标会上移。  
\-t ：用于表示等待输入的时间，单位为秒，等待时间超过，将继续执行后面的脚本，注意不作为null输入，参数将保留原有的值。