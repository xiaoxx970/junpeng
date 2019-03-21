# 在Normal模式下：

`dw`:删除到下一个空格前的单词

`d`表示删除命令，后面紧跟参数：

    w:删除到下一个空格前的单词，包括字符后的空格

    e:删除到下一个空格前的单词，不包括字符后的空格

    $:删除到行尾

`w`:Jump to next word

> `2w`:Jump to next two word

`e`:Jump to the end of next word

> `3e`:Jump to the end of next 3 word

`0`:=HOME

`$`:=END

`d2w`:删除下2个单词

`dd`:删除一整行

`p`:把删除的插入到光标后

`r`:替换光标所在的字符，按r后输入要替换的字符

`ce|cw`:替换光标后所在的单词，按ce后输入要替换的内容（通过`w`移到单词首比较方便）

> `c2w`:替换光标后的两个单词

`>>`:缩进当前行

> `<<`:取消缩进当前行
>
> `<`:visual模式下选择后缩进

`u`:**撤销**

`U`:还原一整行

`Ctrl+R`:重做

# 定位相关：

`Ctrl+G`:显示光标在文件的位置

`gg`:跳到文件开头

`G`:跳到文件末尾

> `500G`:跳到500行

`/`:文本搜索，输入后回车，`n`跳到下一个结果，`N`跳到上一个结果  

> `?`:向上搜索

`Ctrl+O`:光标跳到前一个位置

`Ctrl+I`:光标跳到后一个位置

`%`:匹配括号（(,[,{）

# 查找并替换单词：

> `:s/thee/the`:替换行中第一个thee为the
>
> `:s/thee/the/g`:替换行中所有thee为the
>
> `:#,#s/old/new/g`:替换行#,#,区间内所有的old为new
>
> `:%s/old/new/g`:替换文件中所有old为new
>
> `:%s/old/new/gc`:查找文件中每一个old并询问是否替换为new
>
`:!`:后面跟shell命令，可以执行

`:w [filename]`:以filename保存当前文件在当前目录下

`v`:选区

`:r [filename]`:读取filename内容插入到当前位置

> `:r !ls`:把shell命令ls的返回值插入到当前位置

`o`:在当前行下方插入一行并且进入Insert模式

> `O`:在当前行上方插入一行并且进入Insert模式

`R`:替换，覆盖当前已有字符

`y`:复制

> `p`:粘贴
>
> `yw`:复制一个单词（光标在单词首时）

`a`:在光标后开始插入

`A`:在行末开始插入

`Ctrl-W,Ctrl-W`:切换vim中的窗口

# 让tmux和vim更好的配合工作：

1. In your .vimrc add:
    ```bash
    set ttymouse=xterm2
    set mouse=a
    ```
2. In your tmux.conf add:
    ```bash
    set -g mouse on
    ```
You will then be able to use the mouse to select blocks of text, resize splitted windows, ...