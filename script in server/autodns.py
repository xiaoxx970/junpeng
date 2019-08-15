#!/usr/bin/env python
# coding=utf-8
from godaddypy import Client, Account
import urllib
import urllib.request
PUBLIC_KEY = 'Your_public_key_from_godaddy'
SECRET_KEY = 'Your_sercet_key_from_godaddy'
my_acct = Account(api_key=PUBLIC_KEY, api_secret=SECRET_KEY)
client = Client(my_acct)
domain = client.get_domains()[0]
name = input("sub domain name:")
record = client.get_records(domain, record_type='A')
i = 0
for x in record:
    if x['name'] == name:
        break
    i += 1
try:
    ecord_ip = record[i]['data']
except IndexError:
    print("new record")
    record_ip = "empty"
IP = urllib.request.urlopen('http://ip.42.pl/raw').read()
# print(name,domain, record_ip,IP)
# exit()
if IP != record_ip:
    if (client.update_record_ip(IP, domain, name, 'A')):
        print("success!")
    else:
        print("something wrong")
else:
    print("IP Record up to date")
