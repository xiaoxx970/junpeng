#!/usr/bin/python
# -*- coding: utf-8 -*-
import json
import base64
import os
import sys
import getopt
import random
import string


config_path = "/etc/shadowsocks-python/config.json"    #配置文件路径
#config_path = "config.json"
Hostname = "yourdomain.com"                            #主机域名

class bcolors:                                          #给字染色
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def main(argv):
    global conf,Method                                  #把配置文件的内容和加密方式作为全局变量
    conf = load_conf()
    Method = conf['method']
    print("[{}qr{}]     {}Print config of one port via qrcode in terminal{}".format(bcolors.HEADER,bcolors.ENDC,bcolors.OKBLUE,bcolors.ENDC))
    print("[{}add{}]    {}Add a port and generte a password{}".format(bcolors.HEADER,bcolors.ENDC,bcolors.OKBLUE,bcolors.ENDC))
    print("[{}list{}]   {}List all used port and password{}".format(bcolors.HEADER,bcolors.ENDC,bcolors.OKBLUE,bcolors.ENDC))
    print("[{}del{}]    {}Delete one port you want{}".format(bcolors.HEADER,bcolors.ENDC,bcolors.OKBLUE,bcolors.ENDC))
    print("(Press `Enter` to quit)")
    choice = raw_input('Choice one:')
    print(choice)
    if choice == "qr":
        port_list()
        port = raw_input('Port to print QR:')
        qrprint(port)
        exit()
    elif choice == "add":
        add()
    elif choice == "list":
        port_list()
    elif choice == "del":
        port_list()
        port = raw_input('Port you want to remove:')
        port_del(port)
    else:
        print("usage: addss.py <qr|add|list|del>")
        exit()


def load_conf():                                        # 读配置文件并返回dict对象
    read_data = []
    with open(config_path) as load_f:
        read_data = json.load(load_f)
    return read_data

def write_conf():
    with open(config_path, 'w') as dump_f:
        json.dump(conf, dump_f, indent=4)
    os.system("/etc/init.d/shadowsocks-python restart")
    print(bcolors.OKGREEN+"Done!"+bcolors.ENDC)

def port_list():                                        # 遍历所有端口并打印端口：密码
    for x in conf['port_password']:
        print(x+" : "+conf['port_password'][x])


def qrprint(port):                                      # 终端打印指定端口二维码
    if port in conf['port_password']:
        Password = conf['port_password'][port]
        ss = ("{}:{}@{}:{}".format(Method, Password, Hostname, port))
        qr = ("ss://"+str(base64.b64encode(ss)))        #把配置字符串转换成base64格式并添加前缀
        print(qr)
        os.system("qr {}".format(qr))                   #通过终端命令qr打印二维码
    else:
        print("Did nothing!")
        exit()

def add():                                              # 添加端口
    port = raw_input('Enter port:')
    if port:                                #端口有输入
        if port in conf['port_password']:   #输入的端口已经存在
            print("port already exit")
            print("Did nothing!")
            exit()
        else:
            password = ''.join(random.sample(string.ascii_letters + string.digits, 8))  #生成8位密码
            print('Genrated a password: '+password)
            conf['port_password'].update(   #新端口和密码并入dict
                {'{0}'.format(port): '{0}'.format(password)})
    else:
        print("Did nothing!")               #输入为空就退出
        exit()
    write_conf()
    #port_list()
    qrprint(port)

def port_del(port):                                     # 删除端口
    if port in conf['port_password']:
        del conf['port_password'][port]
    else:
        print("port not exit")
        print("Did nothing!")
        exit()
    write_conf()
    port_list()

if __name__ == "__main__":
    main(sys.argv[1:])
