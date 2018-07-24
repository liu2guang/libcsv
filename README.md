# libcsv pkg #
---

## 1、介绍

### 1.1、CSV格式
CSV文件(Comma-separated values), 就是逗号分隔的数据文件, 常用于数据集成的数据交换部分标准部分. CSV没有正式标准，但是国际互联网工程任务组(IETF)给推荐标准RFC 4180描述了CSV文件的结构. 

### 1.2、libcsv介绍
libcsv是用纯ANSI C89编写的小型、简单、快速的CSV库，可以读写CSV数据。它提供了一个简单的接口，使用回调函数来处理解析的字段和行，并且可以解析不正确格式化的CSV文件. 

### 1.3、常见CSV格式配置

~~~
MS-DOS-style lines that end with (CR/LF) characters (optional for the last line)
Jiger: {使用回车换行（两个字符）作为行分隔符，最后一行数据可以没有这两个字符。}

An optional header record (there is no sure way to detect whether it is present, so care is required when importing).
Jiger:{标题行是否需要，要双方显示约定}.

Each record "should" contain the same number of comma-separated fields.
Jiger:{每行记录的字段数要相同，使用逗号分隔。} 逗号是默认使用的值，双方可以约定别的。
Any field may be quoted (with double quotes).

Jiger:{任何字段的值都可以使用双引号括起来}. 为简单期间，可以要求都使用双引号。
Fields containing a line-break, double-quote, and/or commas should be quoted. (If they are not, the file will likely be impossible to process correctly).
Jiger:{字段值中如果有换行符，双引号，逗号的，必须要使用双引号括起来。这是必须的。}

A (double) quote character in a field must be represented by two (double) quote characters.
Jiger:{如果值中有双引号，使用一对双引号来表示原来的一个双引号}
~~~

### 1.4、依赖

- 依赖 [libc](https://github.com/RT-Thread/rt-thread/tree/master/components/libc) 组件. 
- 依赖 [dfs](https://www.rt-thread.org/document/site/rtthread-development-guide/rtthread-manual-doc/zh/1chapters/12-chapter_filesystem/) 文件系统. 
- 依赖 [env](https://www.rt-thread.org/document/site/rtthread-development-guide/rtthread-tool-manual/env/env-user-manual/) 工具. 
- RT-Thread 3.0+，对 bsp 无依赖
- demo程序依赖 [optpaser](https://github.com/liu2guang/optparse) (getopt-like for rtt)在线包. 

> 注: 该仓库基于libcsv-3.0.3 【[源仓库地址](https://sourceforge.net/projects/libcsv/ "点击跳转")】版本进行移植人. 

### 1.5、demo程序
libcsv目前提供了一个验证csv文件是否合法的例程. 

## 2、获取方式

请使用 ENV 工具辅助下载：

包的路径为：`RT-Thread online package` -> `miscellaneous packages` -> `libcsv`

```
  RT-Thread online packages --->
      miscellaneous packages --->
          [*] libcsv: a small, simple and fast CSV library written in pure ANSI C89. ---> 
                libcsv version(v1.0.0) ---> 
          [*]   libcsv demo example
```
保存 menuconfig 配置后使用 `pkgs --update` 命令下载软件包

> 注：demo是测试例程, 帮助理解库的使用. 

## 3、使用说明 

> 注意: 使用说明见源码下的`libcsv_development_manual.pdf`手册. 后期会整理翻译成中文文档. 

## 4、注意事项

> libcsv库移植到RT-Thread过程中只对代码格式和目录格式做调整.

## 5、许可方式

GNU Library or Lesser General Public License version 2.0 (LGPLv2). 
更多关于许可信息请浏览`COPYING.LESSER`文件和源作者仓库的许可声明, 或者直接联系原作者本人. 

## 6、联系方式 & 感谢
* 感谢：[rgamble](https://sourceforge.net/u/rgamble/profile/) 编写了libcsv库. 
* 维护：[liu2guang](https://github.com/liu2guang).
* 主页：https://github.com/liu2guang/libcsv. 
