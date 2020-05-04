# 快速配置DHCP客户端

通过`eth0`获取DHCP地址

```sh
sudo dhclient -v eth0
```

释放`eth0`的DHCP地址

```sh
sudo dhclient -v -r eth0
```

`-v`为显示详细信息


# 替换配置文件内容

```sh
sed -i "s/mirrors.cloud.tencent.com/mirrors.tencentyun.com/g" /etc/yum.repos.d/epel.repo
```

# Tcpdump 实例

- 只抓 SYN 包

    ```sh
    tcpdump -i eth1 'tcp[tcpflags] = tcp-syn'
    ```

- 抓 SYN, ACK

    ```sh
    tcpdump -i eth1 'tcp[tcpflags] & tcp-syn != 0 and tcp [tcpflags] & tcp-ack != 0'
    ```

- 抓 SMTP 数据

    ```sh
    tcpdump -i eth1 '((port 25) and (tcp[(tcp[12]>>2):4] = 0x4d41494c))'
    ```

    > 抓取数据区开始为"MAIL"的包，"MAIL"的十六进制为 0x4d41494c。

- 抓 HTTP GET 数据

    ```sh
    tcpdump -i eth1 'tcp[(tcp[12]>>2):4] = 0x47455420'
    ```

    > "GET "的十六进制是 47455420

- 抓 SSH 返回

    ```sh
    tcpdump -i eth1 'tcp[(tcp[12]>>2):4] = 0x5353482D'
    ```

    > "SSH-"的十六进制是 0x5353482D

> 参考：https://blog.csdn.net/nanyun2010/article/details/23445223

# ssh快速开启密钥登录

先看本地`~/.ssh`有没有生成好的密钥，没有的话生成一个
```sh
ssh-keygen -t rsa -C "xiaoxx97@outlook.com"
```

然后复制`id_rsa.pub`内容到服务器`~/.ssh/authorized_keys`里面

可以用工具快速复制

```sh
ssh-copy-id username@203.0.113.0
```

如果没有工具安装就使用管道复制

```sh
cat ~/.ssh/id_rsa.pub | \
ssh username@203.0.113.0 "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys"
```

在服务器修改`sshd`配置文件，重启`sshd`

```sh
sudo sed -i 's/#PubkeyAuthentication yes/PubkeyAuthentication yes/g' etc/ssh/sshd_config
sudo systemctl restart sshd
```

# Git

## 强制拉取使用线上版本

```sh
git fetch -all
git reset --hard origin/master
git pull
```

## 设置代理

```sh
git config --global http.proxy 'socks5://127.0.0.1:1080'
git config --global https.proxy 'socks5://127.0.0.1:1080'

git config --global --unset http.proxy
git config --global --unset https.proxy
```

## git remote

- 查看当前远程链接

    ```sh
    git remote -v
    ```

- 修改远程链接

  ```shell
  git remote set-url origin https://github.com/USERNAME/REPOSITORY.git
  ```

# 通过文件内容搜索文件

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

安装：

```sh
yum install gcc -y
wget -O- https://gist.githubusercontent.com/ifduyue/dea03b4e139c5758ca114770027cf65c/raw/install-proxychains-ng.sh | sudo bash -s
```

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

后面加 `pip,git,curl,wget` 都可以，加了就这条命令走代理

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
