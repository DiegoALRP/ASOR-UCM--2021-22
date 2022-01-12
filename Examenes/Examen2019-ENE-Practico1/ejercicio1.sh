

#####
#VM1#
#####
[root@localhost ~]# ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 08:00:27:17:d3:b6 brd ff:ff:ff:ff:ff:ff
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 192.168.0.1/24 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:17:d3:b6 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.1/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe17:d3b6/64 scope link 
       valid_lft forever preferred_lft forever

[root@localhost ~]# ip route add default via 192.168.0.3

[root@localhost ~]# nc -l 7777



#####
#VM2#
#####
[root@localhost ~]# ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 08:00:27:0b:f4:5b brd ff:ff:ff:ff:ff:ff
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 172.16.0.2/16 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:0b:f4:5b brd ff:ff:ff:ff:ff:ff
    inet 172.16.0.2/16 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe0b:f45b/64 scope link 
       valid_lft forever preferred_lft forever

[root@localhost ~]# ip route add default via 172.16.0.3

[root@localhost ~]# nc 172.16.0.3 80



##############
#VM3 (Router)#
##############
[root@localhost ~]# ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 08:00:27:ab:b8:28 brd ff:ff:ff:ff:ff:ff
3: eth1: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 08:00:27:c6:19:bd brd ff:ff:ff:ff:ff:ff
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip link set eth1 up
[root@localhost ~]# ip a add 192.168.0.3/24 dev eth0
[root@localhost ~]# ip a add 172.16.0.3/16 dev eth1
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:ab:b8:28 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.3/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:feab:b828/64 scope link 
       valid_lft forever preferred_lft forever
3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:c6:19:bd brd ff:ff:ff:ff:ff:ff
    inet 172.16.0.3/16 scope global eth1
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fec6:19bd/64 scope link 
       valid_lft forever preferred_lft forever

[root@localhost ~]# sysctl net.ipv4.ip_forward=1

[root@localhost ~]# iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -o eth1 -j MASQUERADE
[root@localhost ~]# iptables -t nat -A PREROUTING -d 172.16.0.0/16 -p tcp --dport 80 -j DNAT --to 192.168.0.1:7777

