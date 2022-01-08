#VM1 (Router 1)

[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 08:00:27:a9:ae:21 brd ff:ff:ff:ff:ff:ff
[root@localhost ~]# ip link set eth0
[root@localhost ~]# ip a add 2001:db8:200:1::1/64 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST> mtu 1500 qdisc noop state DOWN group default qlen 1000
    link/ether 08:00:27:a9:ae:21 brd ff:ff:ff:ff:ff:ff
    inet6 2001:db8:200:1::1/64 scope global tentative 
       valid_lft forever preferred_lft forever



#VM2 (Router 2)
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip link set eth1 up
[root@localhost ~]# ip a add 2001:db8:200:1::2/64 dev eth0
[root@localhost ~]# ip a add 2001:db8:200:2::2/64 dev eth1
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:f3:d2:5f brd ff:ff:ff:ff:ff:ff
    inet6 2001:db8:200:1::2/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fef3:d25f/64 scope link 
       valid_lft forever preferred_lft forever
3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:f6:39:48 brd ff:ff:ff:ff:ff:ff
    inet6 2001:db8:200:2::2/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fef6:3948/64 scope link 
       valid_lft forever preferred_lft forever


#VM3 (Router 3)
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 2001:db8:200:2::3/64 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:66:d1:e1 brd ff:ff:ff:ff:ff:ff
    inet6 2001:db8:200:2::3/64 scope global tentative 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe66:d1e1/64 scope link 
       valid_lft forever preferred_lft forever

