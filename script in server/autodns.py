#!/usr/bin/env python
# coding=utf-8
from godaddypy import Client, Account
import urllib
PUBLIC_KEY = 'dLiaUHdmPzmA_Wfoeuyk3sjkvVd5g4LNKra'
SECRET_KEY = 'WfoiRDEkHQtaCyZkbyNAX4'
my_acct = Account(api_key=PUBLIC_KEY, api_secret=SECRET_KEY)
client = Client(my_acct)
domain = client.get_domains()[0]
name = "us"
record = client.get_records(domain, record_type='A')
i = 0
for x in record:
    if x['name'] == name:
        break
    i += 1
record_ip = record[i]['data']
IP = urllib.urlopen('http://ip.42.pl/raw').read()
# print(name,domain, record_ip,IP)
# exit()
if IP != record_ip:
    if (client.update_record_ip(IP, domain, name, 'A')):
        print("success!")
    else:
        print("something wrong")
else:
    print("IP Record up to date")
