#Crea fichero regular
touch ejercicio10.txt

#Crea directorio
mkdir ejercicio10

#Crea un fichero de enlace simbolico a ejercicio10.txt
ln -s ejercicio10.txt ejercicio10s.txt
# Se crea un nuevo fichero con un nuevo inodo, pero que tiene como 
# contendio un enlace al fichero original

#Crea un fichero de enlace simbolico a ejercicio10
ln -s ejercicio10 ejercicio10s
# Se crea un nuevo fichero con el mismo inodo que el fichero original.
# Y se incrementa en numero de enlaces que tiene el fichero original.

#Comprobar inodos y ficheros
ls -l

ls -i

ls -li

#Crear enlaces rigidos
ln ejercicio10.txt ejercicio10r.txt

ln ejercicio10 ejercicio10r
#ln: ‘ejercicio10’: hard link not allowed for directory
#No se permite hacer hard link de un directorio

#Quitar enlace rigido
rm ejercicio10r.txt
# Se elimina el fichero de enlace rigido y el fichero original 
# reduce el numero de enlaces que posee

#Quitar enlace simbolico
rm ejercicio10s.txt
# Se elimina el fichero de enlace simbolico, pero el fichero
# original se mantiene igual

#Quitar fichero original
rm ejercicio10.txt
# Se elimina el fichero original.
# El enlace rigido se reduce su numero de enlaces
#  y su contenido queda igual.
# El enlace simbolico se corrompe porque ya no existe 
#  el fichero al que apuntaba.
