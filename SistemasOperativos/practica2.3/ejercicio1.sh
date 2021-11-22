sudo renice -n -10 -p $$ 
#el $$ es el proceso actual
#-p es la prioridad

nice

sudo chrt -f -p 12 $$
# recordar que el $$ es para el proceso actual
# -f es para indicar que es FIFO

chrt -p $$
# para preguntar la prioridad actual
