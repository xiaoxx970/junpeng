#!/usr/bin/python3
# -*- coding: utf-8 -*-
import json
import base64
import os
import sys
import getopt
import random
import string
import urllib
import urllib.request


IP = bytes.decode(urllib.request.urlopen('http://ip.42.pl/raw').read())
config_path = "/etc/shadowsocks-python/config.json"  # 配置文件路径
#config_path = "config.json"
Hostname = IP  # 主机域名


class bcolors:  # 给字染色
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def main(argv):
    global conf, Method  # 把配置文件的内容和加密方式作为全局变量
    conf = load_conf()
    Method = conf['method']
    if 'port_password' not in conf:  # 如果这是个新文件没有多端口化的
        print("intalizing configure file")
        port_origin = conf['server_port']
        password_origin = conf['password']
        conf['port_password'] = {}
        conf['port_password'][port_origin] = password_origin
        del conf['server_port']
        del conf['password']
    if os.geteuid() != 0:
        print ("{}Warning:{}In order to write config file and restart the ss server correctly, please run as root by using sudo.".format(
            bcolors.WARNING, bcolors.ENDC))
    else:
        try:
            import qrcode
        except ModuleNotFoundError:
            if (os.system("sudo pip3 install qrcode")):
                print("Insatll fault!\nInstall it yourself by `sudo pip3 install qrcode`")
    if argv == []:   #命令后面没跟东西
        print("[{}qr{}]     {}Print config of one port via qrcode in terminal{}".format(
            bcolors.HEADER, bcolors.ENDC, bcolors.OKBLUE, bcolors.ENDC))
        print("[{}add{}]    {}Add a port and generte a password{}".format(
            bcolors.HEADER, bcolors.ENDC, bcolors.OKBLUE, bcolors.ENDC))
        print("[{}list{}]   {}List all used port and password{}".format(
            bcolors.HEADER, bcolors.ENDC, bcolors.OKBLUE, bcolors.ENDC))
        print("[{}del{}]    {}Delete one port you want{}".format(
            bcolors.HEADER, bcolors.ENDC, bcolors.OKBLUE, bcolors.ENDC))
        print("(Press `Enter` to quit)")
        choice = input('Choice one:')
        print(choice)
        if choice == "qr":
            port_list()
            port = input('Port to print QR:')
            qrprint(port)
            exit()
        elif choice == "add":
            port = input('Enter port:')
            add(port)
        elif choice == "list":
            port_list()
        elif choice == "del":
            port_list()
            port = input('Port you want to remove:')
            port_del(port)
        else:
            print("choice nothing,quit")
            exit()
    else:   #命令后面有参数
        if argv[0] == "list" or argv[0] == "ls":
            port_list()
        elif argv[0] == "add":
            try:
                add(argv[1])
            except IndexError:
                print ("add what?")
        elif argv[0] == "qr":
            try:
                qrprint(argv[1])
            except IndexError:
                print ("qr which?")
        elif argv[0] == "del":
            try:
                port_del(argv[1])
            except IndexError:
                print ("del what?")
        else:
            print("usage: "+sys.argv[0]+" <qr|add|list|del>")
            

def load_conf():                                        # 读配置文件并返回dict对象
    read_data = []
    with open(config_path) as load_f:
        read_data = json.load(load_f)
    return read_data


def write_conf():
    with open(config_path, 'w') as dump_f:
        json.dump(conf, dump_f, indent=4)
    if os.geteuid() != 0:
        print(bcolors.FAIL + "Can't restart server since you're not running in root!\nConfig won't go into effect till you restart ss server manually." + bcolors.ENDC)
    else:
        os.system("/etc/init.d/shadowsocks-python restart")
        print(bcolors.OKGREEN + "Done!" + bcolors.ENDC)


def port_list():                                        # 遍历所有端口并打印端口：密码
    for x in conf['port_password']:
        print(str(x) + " : " + conf['port_password'][x])


def qrprint(port):                                      # 终端打印指定端口二维码
    #port = int(port)
    if port in conf['port_password']:
        Password = conf['port_password'][port]
        ss = ("{}:{}@{}:{}".format(Method, Password, Hostname, port)).encode('ascii')
        qr = ("ss://" + str(base64.b64encode(ss).decode('ascii')))  # 把配置字符串转换成base64格式并添加前缀
        print(qr)
        result = os.system("qr {}".format(qr))  # 通过终端命令qr打印二维码
        if (result == 32512):
            print("You have not insalled the package `qrcode`")
    else:
        print("Port not in there, did nothing!")
        exit()


def add(port):                                              # 添加端口
    
    if port:  # 端口有输入
        if port in conf['port_password']:  # 输入的端口已经存在
            print("port already exit")
            print("Did nothing!")
            exit()
        else:
            try:
                port = str(int(port))
            except ValueError:
                print("port must be number")
                exit()
            password = ''.join(
                random.sample(
                    string.ascii_letters +
                    string.digits,
                    8))  # 生成8位密码
            print('Genrated a password: ' + password)
            conf['port_password'].update(  # 新端口和密码并入dict
                {'{0}'.format(port): '{0}'.format(password)})
    else:
        print("Did nothing!")  # 输入为空就退出
        exit()
    write_conf()
    # port_list()
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
