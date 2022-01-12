#VM1
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add fd00:1:1:a::1/64 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:17:d3:b6 brd ff:ff:ff:ff:ff:ff
    inet6 fd00:1:1:a::1/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe17:d3b6/64 scope link 
       valid_lft forever preferred_lft forever



#VM2
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip a add fd00:1:1:b::2/64 dev eth0
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:0b:f4:5b brd ff:ff:ff:ff:ff:ff
    inet6 fd00:1:1:b::2/64 scope global tentative 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fe0b:f45b/64 scope link 
       valid_lft forever preferred_lft forever

ip -6 route add default via fd00:1:1:b::3

#VM3
[root@localhost ~]# ip link set eth0 up
[root@localhost ~]# ip link set eth1 up
[root@localhost ~]# ip a add fd00:1:1:a::3/64 dev eth0
[root@localhost ~]# ip a add fd00:1:1:b::3/64 dev eth1
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:ab:b8:28 brd ff:ff:ff:ff:ff:ff
    inet6 fd00:1:1:a::3/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:feab:b828/64 scope link 
       valid_lft forever preferred_lft forever
3: eth1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 08:00:27:c6:19:bd brd ff:ff:ff:ff:ff:ff
    inet6 fd00:1:1:b::3/64 scope global 
       valid_lft forever preferred_lft forever
    inet6 fe80::a00:27ff:fec6:19bd/64 scope link 
       valid_lft forever preferred_lft forever

[root@localhost ~]# vim /etc/quagga/zebra.conf 
[root@localhost ~]# cat /etc/quagga/zebra.conf 
interface eth0
	no ipv6 nd suppress-ra
	ipv6 nd prefix fd00:1:1:a::/64

[root@localhost ~]# service zebra start
Redirecting to /bin/systemctl start zebra.service
[root@localhost ~]# service zebra status
Redirecting to /bin/systemctl status zebra.service
● zebra.service - GNU Zebra routing manager
   Loaded: loaded (/usr/lib/systemd/system/zebra.service; disabled; vendor preset: disabled)
   Active: active (running) since Tue 2022-01-04 17:53:46 CET; 3s ago
  Process: 2061 ExecStart=/usr/sbin/zebra -d $ZEBRA_OPTS -f /etc/quagga/zebra.conf (code=exited, status=0/SUCCESS)
  Process: 2060 ExecStartPre=/sbin/ip route flush proto zebra (code=exited, status=0/SUCCESS)
 Main PID: 2063 (zebra)
   CGroup: /system.slice/zebra.service
           └─2063 /usr/sbin/zebra -d -A 127.0.0.1 -f /etc/quagga/zebra.conf

Jan 04 17:53:46 localhost.localdomain systemd[1]: Starting GNU Zebra routing ...
Jan 04 17:53:46 localhost.localdomain systemd[1]: PID file /run/quagga/zebra....
Jan 04 17:53:46 localhost.localdomain systemd[1]: Started GNU Zebra routing m...
Hint: Some lines were ellipsized, use -l to show in full.

[root@localhost ~]# sysctl -w net.ipv6.conf.all.forwarding=1
net.ipv6.conf.all.forwarding = 1
