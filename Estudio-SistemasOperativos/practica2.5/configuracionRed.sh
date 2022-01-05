#VM1 (Servidor)
[root@localhost ~]# ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 08:00:27:59:03:7e brd ff:ff:ff:ff:ff:ff
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 192.168.0.1/24 dev eth0
[root@localhost ~]# ip a add fd00::a:0:0:0:1/64 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:59:03:7e brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.1/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fd00:0:0:a::1/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe59:37e/64 scope link 
       valid_lft forever preferred_lft forever



#VM2 (Cliente)
[root@localhost ~]# ip link
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 08:00:27:4d:3a:80 brd ff:ff:ff:ff:ff:ff
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 192.168.0.100/24 dev eth0
[root@localhost ~]# ip a add fd00::a:0:0:0:100/64 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:4d:3a:80 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.100/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fd00:0:0:a::100/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe4d:3a80/64 scope link 
       valid_lft forever preferred_lft forever
