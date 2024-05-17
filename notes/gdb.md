# Notes of Lession 2
> [应用视角的操作系统](https://www.bilibili.com/video/BV1dj421S7yK/?spm_id_from=333.788&vd_source=5c6a29b4695df3aedc57e4fca2da9605)


## 目标
- gdb 常用功能与操作方法
- strace 的使用
- objdump 的使用
- 上述工具在 c 编译 汇编 连接 中的使用场景。

## 从.c到可执行文件

- hello.c(源程序) 
- **预处理器(cpp)** 
- hello.i(修改后源程序) 
- **编译器(ccl)** 
- hello.s(汇编程序,文本) 
- **汇编器(as)** 
- hello.o(目标程序,二进制) 
- **链接器(ld)** 
- hello(可执行文件,二进制)

## objdump

反汇编器： 反汇编二进制目标程序，回到汇编语言。

```
$ tldr objdump

  objdump

  View information about object files.
  More information: https://manned.org/objdump.

  - Display the file header information:
    objdump -f binary

  - Display all header information:
    objdump -x binary

  - Display the disassembled output of executable sections:
    objdump -d binary

  - Display the disassembled executable sections in intel syntax:
    objdump -M intel -d binary

  - Display a complete binary hex dump of all sections:
    objdump -s binary

```
其中 -s 的选项就是jyy视频中，将binary变成16进制的样子。
```
$ objdump -s minimal.o

minimal.o:     file format elf64-x86-64

Contents of section .text:
 0000 48c7c001 00000048 c7c70100 000048c7  H......H......H.
 0010 c6000000 0048c7c2 1c000000 0f0548c7  .....H........H.
 0020 c03c0000 0048c7c7 01000000 48c7c600  .<...H......H...
 0030 00000048 c7c20000 00000f05 1b5b3031  ...H.........[01
 0040 3b33316d 48656c6c 6f2c204f 5320576f  ;31mHello, OS Wo
 0050 726c641b 5b306d0a                    rld.[0m.
Contents of section .note.gnu.property:
 0000 04000000 20000000 05000000 474e5500  .... .......GNU.
 0010 020001c0 04000000 01000000 00000000  ................
 0020 010001c0 04000000 01000000 00000000  ................
```

## strace
under `minimal/`

`strace ./minimal`

`strace -f gcc -o hello hello.c` 

`strace -f gcc -o hello hello.c &| vim -`: 放入nvim中读。

在nvim中使用grep过滤： `:%!grep`

`strace ls &| grep -e read -e write`

## 常用技巧vim

1. 在vim中调用grep来过滤

## Stack 栈帧

- 栈底在上，地址最大；
- 栈顶在下，地址最小；
- 新栈帧插入到已有栈帧之下。

## gdb debug

### 运行
- run r: 运行至断电；
- continue c: 继续执行，直至断点或结束；
- next n: 单步，不进入函数体；
- step s: 单步，并进入函数；
- until: 运行，直到退出循环体；
- until + <line_num>: 运行至某行；
- finish: 运行，直到当前函数完成并返回，并打印栈堆参数返回值等信息；
- call: 调用函数；
- quit q: 退出gdb。

### 设置断点
- break n (b n): 在第n行设置断点；
- break func: 在函数入口处设置断点；
- break <file_name: line_num>:
- info breakpoints(info b): 显示当前程序断点；
- delete <num>: 删除断点；
- disable <num>: 暂停断点；
- enable : 恢复断点；
- clear <line_num>: 清除断点；
- clear <file_name: line_num>: 清除断点；

### 条件断点
- b <location> if <cond expression>: b main.c:8 if x == 10
- condition <break_num>:
- condition <break_num> <expression>: 修改新条件

### 查看源代码
- list (l): 列出源代码；
- list line_num: 行号前后10行源码；
- list func_name: 函数所在代码；
- list: 接着上次的，显示10行。

### 查询运行信息
- where/bt: 当前运行的堆栈列表；
- set args: 指定运行参数；
- show args: 查看设置好的参数；
- info program: 查看程序是否在运行，进程号，暂停原因；
- info frame <frame_num>: 进入指定栈帧。

### 窗口
- layout: 分割窗口；
- layout asm: 反汇编窗口；
- layout src: 源码窗口；
- layout regs: 源码、反汇编、寄存器窗口；
- layout split： 显示源代码和反汇编窗口；
- Ctrl+L: 刷新。

### 打印表达式
- print <expression> p: 打印表达式；
- 常用格式：
    - x: 16
    - d: 10 
    - u: 16 without sign
    - o: 8
    - t: 2
    - a: address
    - c: char(ASCII)
    - f: float
    - s: string
    - i: 汇编
- x: 显示内存地址中的内容，也可以用上述格式。
    - x/10i $pc: 显示程序当前位置开始往后的10条汇编指令