"""
Grafico dei tempi degli algoritmi di ordinamento (esercitazione 5).
Carica i dati prodotti da measure_sort2 e produce un grafico log-y.
"""
 
import numpy as np
import matplotlib.pyplot as plt
 
INPUT_FILE = "build_debug/measure_sort2.txt"

 
# Carico i dati saltando la riga di intestazione
data = np.loadtxt(INPUT_FILE, skiprows=1)
 
n          = data[:, 0]
t_bubble   = data[:, 1]
t_insert   = data[:, 2]
t_select   = data[:, 3]
t_merge    = data[:, 4]
t_quick    = data[:, 5]
t_std      = data[:, 6]
t_hybrid   = data[:, 7]
 

plt.figure()
 
plt.plot(n, t_bubble, 'o-',  label="bubble sort",     color="tab:red")
plt.plot(n, t_insert, 's-',  label="insertion sort",  color="tab:orange")
plt.plot(n, t_select, '^-',  label="selection sort",  color="tab:olive")
plt.plot(n, t_merge,  'd-',  label="merge sort",      color="tab:green")
plt.plot(n, t_quick,  'v-',  label="quick sort",      color="tab:blue")
plt.plot(n, t_hybrid, 'P-',  label="quick sort ibrido", color="tab:purple")
plt.plot(n, t_std,    'x--', label="std::sort",       color="black")
 
# Linea verticale alla soglia trovata 
n0_debug = 35
plt.axvline(n0_debug, color="gray", linestyle=":",
            label=f"soglia n0 = {n0_debug}")
 
plt.yscale("log")  # scala log sull'asse y: rende leggibili tempi su 2 ordini di grandezza
plt.xlabel('Dimensione del vettore (n)')
plt.ylabel("tempo medio per ordinamento [s]")
plt.title("Confronto algoritmi di ordinamento - Debug")
plt.grid(True, which="both", linestyle=":", alpha=0.6)
plt.legend(loc="best", fontsize=9)
plt.tight_layout()
plt.savefig('plot_sorts_debug.png', dpi=150)
plt.show()
 
