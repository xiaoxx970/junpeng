#!/bin/bash

sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak
sudo cp /etc/apt/sources.list.d/raspi.list /etc/apt/sources.list.d/raspi.list.bak
sudo sed -i 's#://raspbian.raspberrypi.org#s://mirrors.tuna.tsinghua.edu.cn/raspbian#g' /etc/apt/sources.list
sudo sed -i 's#://archive.raspberrypi.org/debian#s://mirrors.tuna.tsinghua.edu.cn/raspberrypi#g' /etc/apt/sources.list.d/raspi.list
sudo apt-get update
sudo apt-get install samba -y
sudo echo "
# 分享名称
[Media]
# 说明信息
comment = NAS Storage
# 可以访问的用户
valid users = ljp,root
# 共享文件的路径。
path = /media/ljp/Media/
# 可被其他人看到资源名称（非内容）
browseable = yes
# 可写
writable = yes
# 新建文件的权限为 664
create mask = 0664
# 新建目录的权限为 775
directory mask = 0775
"  >> /etc/samba/smb.conf
echo '\n' | testparm
echo "samba服务配置完成，请设定密码："
sudo smbpasswd -a ljp

FRP_VER=0.29.0
echo "开始安装frp"
cd ~
wget https://github.com/fatedier/frp/releases/download/v${FRP_VER}/frp_${FRP_VER}_linux_amd64.tar.gz
tar -xvf frp_{$FRP_VER}_linux_amd64.tar.gz && \
rm -f frp_{$FRP_VER}_linux_amd64.tar.gz
sudo mkdir /etc/frp/ /usr/local/bin/frp/
sudo mv frp_${FRP_VER}_linux_amd64/frpc /usr/local/bin/frp/
sudo tee /etc/frp/frpc.ini <<-'EOF'
[common]
server_addr = ali.mcyo.pw
server_port = 7000

[ssh_njupt]
type = tcp
local_ip = 127.0.0.1
local_port = 22
remote_port = 6422

[web-lab]
type = http
local_ip = 127.0.0.1
local_port = 8888
custom_domains = lab.mcyo.pw
EOF
sudo tee /etc/systemd/system/frpc.service <<-'EOF'
[Unit]
Description=frpc daemon
After=syslog.target  network.target
Wants=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/frp/frpc -c /etc/frp/frpc.ini
Restart= always
RestartSec=1min
ExecStop=/usr/bin/killall frpc

[Install]
WantedBy=multi-user.target
EOF
sudo systemctl daemon-reload
sudo systemctl enable frpc
sudo systemctl start frpc
