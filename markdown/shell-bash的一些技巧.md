# 搜索文件内容

搜索当前目录下所有文件内容，把含有字符串"Advanced Bracket"的文件列出并显示所在行号

```bash
find .| xargs grep -rni "Advanced Bracket"
```

> -r 是递归查找
>
> -n 是显示行号
>
> -R 查找所有文件包含子目录
>
> -i 忽略大小写

# 解压tar.gz和tar.bz2的命令

1. 解压tar.gz文件

```bash
tar -zxvf ×××.tar.gz1
```

2. 解压tar.bz2文件

```bash
tar -jxvf ×××.tar.bz2
```

# proxychains代理

装好后编辑配置文件：
```
vim /etc/proxychains.conf
```
最后一行改成
```
socks5 127.0.0.1 1080
```
就可以用了:
```
proxychains wget http://xxx.com/xxx.zip
```
后面加pip,git好像都可以，加了就这条命令走代理

# 添加系统服务的新方法
1. 创建`.service`文件在`/etc/systemd/system/`下
```
[Unit]
Description=Frp Client Service
After=network.target

[Service]
Type=simple
User=nobody
Restart=on-failure
RestartSec=5s
ExecStart=/usr/bin/frpc -c /etc/frp/frpc.ini
ExecReload=/usr/bin/frpc reload -c /etc/frp/frpc.ini

[Install]
WantedBy=multi-user.target
```
2. 开启默认启动
```
systemctl enable frpc
```
3. 启动服务
```
systemctl start frpc
```