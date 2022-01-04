#VM1
ip link set eth0 up
ip a add 192.168.0.129/25 dev eth0

#VM2 (Router A)
ip link set eth0 up
ip link set eth1 up
ip a add 192.168.0.130/25 dev eth0
ip a add 10.0.0.2/24 dev eth1
vim /etc/quagga/ripd.conf
    # Activar el encaminamiento por RIP
    router rip
        # Definir la versión del protocolo que se usará
        version 2
        # Habilitar información de encaminamiento en redes asociadas a los interfaces
        network eth0
        network eth1
service ripd start
service zebra start
sysctl net.ipv4.ip_forward=1

#VM3 (Router B)
ip link set eth0 up
ip link set eth1 up
ip a add 10.0.0.3/24 dev eth1
ip a add 172.16.0.3/24 dev eth0
vim /etc/quagga/ripd.conf
    # Activar el encaminamiento por RIP
    router rip
        # Definir la versión del protocolo que se usará
        version 2
        # Habilitar información de encaminamiento en redes asociadas a los interfaces
        network eth0
        network eth1
service ripd start
service zebra start
sysctl net.ipv4.ip_forward=1