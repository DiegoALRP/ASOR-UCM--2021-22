renice 12 -p 17179

sudo chrt -f -p 12 17179

#La prioridad en el programa es de 12
#Si se heredan los atributos de planificacion

# También se puede escribir de la siguente manera
# que está mejor hecho

sudo chrt -f -p 12 $$
# $$ es el proceso actual

./ejercicio2