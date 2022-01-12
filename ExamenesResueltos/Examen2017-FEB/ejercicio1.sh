####
#VM1
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 192.168.0.129/25 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:17:d3:b6 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.129/25 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe17:d3b6/64 scope link 
       valid_lft forever preferred_lft forever


####
#VM2
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add 10.0.2.2/24 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:0b:f4:5b brd ff:ff:ff:ff:ff:ff
    inet 10.0.2.2/24 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe0b:f45b/64 scope link 
       valid_lft forever preferred_lft forever

[root@localhost ~]# dhclient eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:0b:f4:5b brd ff:ff:ff:ff:ff:ff
    inet 10.0.2.30/24 brd 10.0.2.255 scope global dynamic eth0
       valid_lft 43198sec preferred_lft 43198sec
    inet6 fe80::a00:27ff:fe0b:f45b/64 scope link 
       valid_lft forever preferred_lft forever

####
#VM3
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip link set eth1 up
[root@localhost ~]# ip a add 192.168.0.130/25 dev eth0
[root@localhost ~]# ip a add 10.0.2.3/24 dev eth1
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:ab:b8:28 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.130/25 scope global eth0
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:feab:b828/64 scope link 
       valid_lft forever preferred_lft forever
3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:c6:19:bd brd ff:ff:ff:ff:ff:ff
    inet 10.0.2.3/24 scope global eth1
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fec6:19bd/64 scope link 
       valid_lft forever preferred_lft forever

[root@localhost ~]# vim /etc/dhcp/dhcpd.conf
[root@localhost ~]# cat /etc/dhcp/dhcpd.conf 
#
# DHCP Server Configuration file.
#   see /usr/share/doc/dhcp*/dhcpd.conf.example
#   see dhcpd.conf(5) man page
#
subnet 10.0.2.0 netmask 255.255.255.0 {
	range 10.0.2.30 10.0.2.50;
	option routers 10.0.2.3;
	option broadcast-address 10.0.2.255;
}
[root@localhost ~]# service dhcpd start
[root@localhost ~]# service dhcpd status