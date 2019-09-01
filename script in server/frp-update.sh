#!/bin/bash
wget -O frp_0.29.0_linux_amd64.tar.gz https://github.com/fatedier/frp/releases/download/v0.29.0/frp_0.29.0_linux_amd64.tar.gz
tar -xzvf frp_*_linux_amd64.tar.gz && rm frp_*_linux_amd64.tar.gz
systemctl stop frp
mv frp_*_linux_amd64/frps /usr/local/bin/frps
systemctl start frp
rm -rf frp_*_linux_amd64