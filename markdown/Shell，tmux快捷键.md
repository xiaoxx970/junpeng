# shell 快捷键

`Ctrl+A`=HOME

`Ctrl+E`=END

`Esc+B` 移动到当前单词的开头

`Esc+F` 移动到当前单词的结尾

`Esc+T` 颠倒相邻两个单词

`Ctrl+T` 颠倒相邻两个**字符**

`Ctrl+XU|Ctrl+7` 撤销

`Ctrl+L` 刷新屏幕

`Ctrl+K` 剪切光标至行尾的内容

`Ctrl+W` 剪切光标到词首的内容

`Ctrl+Y` 粘贴


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
