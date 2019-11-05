# shell 快捷键

## 光标移动

|   快捷键    |        描述        |
| :---------: | :----------------: |
| `Ctrl + a`  |     移动到行首     |
| `Ctrl + e`  |     移动到行尾     |
|  `Alt + b`  |     按单词左移     |
|  `Alt + f`  |     按单词右移     |
| `Ctrl + xx` | 行首与当前位置切换 |

## 剪切粘贴

|   快捷键   |         描述         |
| :--------: | :------------------: |
| `Ctrl + k` |      删除至行尾      |
| `Ctrl + u` |      删除至行首      |
| `Ctrl + w` |    删除前一个单词    |
| `Alt + d`  |    删除后一个单词    |
| `Alt + t`  |   颠倒相邻两个单词   |
| `Ctrl + t` |   颠倒相邻两个字母   |
| `Ctrl + y` | 粘贴上一次删除的文本 |

## 大小写转换

|  快捷键   |               描述               |
| :-------: | :------------------------------: |
| `Alt + c` | 大写当前字母，并移动光标到单词尾 |
| `Alt + u` |       大写从当光标到单词尾       |
| `Alt + l` |       小写从当光标到单词尾       |

## 历史命令

|   快捷键   |           描述           |
| :--------: | :----------------------: |
| `Ctrl + r` |     向后搜索历史命令     |
| `Ctrl + g` |         退出搜索         |
| `Ctrl + p` |     历史中上一个命令     |
| `Ctrl + n` |     历史中下一个命令     |
| `Alt + .`  | 上一个命令的最后一个单词 |

## 终端指令

|   快捷键   |                 描述                  |
| :--------: | :-----------------------------------: |
| `Ctrl + l` |                 清屏                  |
| `Ctrl + s` | 停止输出（在Zsh中为向前搜索历史命令） |
| `Ctrl + q` |               继续输出                |
| `Ctrl + c` |             终止当前命令              |
| `Ctrl + z` |             挂起当前命令              |
| `Ctrl + d` |        结束输入（产生一个EOF）        |

# tmux 快捷键:

配置文件：
```bash
unbind %
bind | split-window -h -c "#{pane_current_path}"      # 使用|竖屏，方便分屏 使用当前路径
unbind '"'
bind - split-window -v -c "#{pane_current_path}"      # 使用-横屏，方便分屏
set-window-option -g mouse on
unbind %
bind | split-window -h -c "#{pane_current_path}"      # 使用|竖屏，方便分屏 使>    用当前路径
unbind '"'
bind - split-window -v -c "#{pane_current_path}"      # 使用-横屏，方便分屏
set -g status-bg black
set -g status-fg white
set-option -g status-left '#[fg=cyan][#{session_name}]'
set-option -g status-left-length 25
set-option -g status-right '#[fg=white,bg=default]%H:%M #[default] #[fg=cyan]%Y    -%m-%d%a'
set-window-option -g window-status-fg default
set-window-option -g window-status-bg default
set-window-option -g clock-mode-colour black
set-window-option -g clock-mode-style 12
```
- 窗格操作:

    `%` 左右平分出两个窗格

    `"` 上下平分出两个窗格

    `x` 关闭当前窗格

    `{` 当前窗格前移

    `}` 当前窗格后移

    `;` 选择上次使用的窗格

    `o` 选择下一个窗格，也可以使用上下左右方向键来选择

    `space` 切换窗格布局，tmux 内置了五种窗格布局，也可以通过 ⌥1 至 ⌥5来切换

    `z` 最大化当前窗格，再次执行可恢复原来大小

    `q` 显示所有窗格的序号，在序号出现期间按下对应的数字，即可跳转至对应的窗格

- tmux 的窗口操作：

    `c` 新建窗口，此时当前窗口会切换至新窗口，不影响原有窗口的状态

    `p` 切换至上一窗口

    `n` 切换至下一窗口

    `w` 窗口列表选择

    `&` 关闭当前窗口

    `,` 重命名窗口，可以使用中文，重命名后能在 tmux 状态栏更快速的识别窗口 id

    `0` 切换至 0 号窗口，使用其他数字 id 切换至对应窗口

    `f` 根据窗口名搜索选择窗口，可模糊匹配
