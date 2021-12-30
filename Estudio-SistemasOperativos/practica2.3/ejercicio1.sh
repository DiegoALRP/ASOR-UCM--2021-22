#Consular prioridad
nice

#Cambiar prioridad shell
renice -n -10 $$
# $$ es la shell

sudo chrt -f -p 12 $$

chrt -p $$
#Para preguntar por la planificacion y prioridad de un proceso