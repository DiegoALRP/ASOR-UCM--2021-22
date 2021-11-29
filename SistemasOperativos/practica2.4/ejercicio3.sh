
# mkfifo tuberia3
# crea un fichero de tipo tuberia

# proceso escribe: echo 12345 > tuberia3
# (se congela hasta que otro proceso lea)

# proceso que lee: cat tuberia3
# (sale 12345)

# Al usar ls -l
# se puede ver que se crea el fichero
# de tipo especial tuberia, que comienza 
# con una "p" de pipe