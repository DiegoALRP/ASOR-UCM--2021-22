man kill
man pkill

kill [pid] # Envía la señal de KILL a un proceso PID.
kill -l # Lista todas las señales.
kill -9 -1 # Mata a todos los procesos que puede matar
kill [pid] -s [signal] # Envia la señal especificada

# Ejemplos
kill -SIGSTOP 2652  # Ctrl + Z
kill -SIGCONT 2652  # foreground
kill -SIGQUIT 2652  # Ctrl + C (quit)