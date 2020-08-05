#!/bin/bash
if [ ! -n "$1" ] ;then
    echo "Input an address"
else
    echo "Add $1 to list"
    echo "ipset=/$1/gfwlist
server=/$1/127.0.0.1#5353" >> /etc/dnsmasq.d/custom_forward.conf
    /etc/init.d/dnsmasq restart
fi