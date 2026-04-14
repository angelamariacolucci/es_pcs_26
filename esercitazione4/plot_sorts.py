import matplotlib.pyplot as plt
 
n         = [4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
bubble    = [1.708e-06, 1.041e-06, 2.75e-06,  1.0417e-05, 3.4083e-05, 0.000138208, 0.000572333, 0.00214946, 0.00778521, 0.0210225, 0.0558984, 0.215996]
insertion = [5.83e-07,  7.5e-07,   1.25e-06,  4.209e-06,  1.0292e-05, 3.8667e-05,  0.000196291, 0.00054625, 0.00167092, 0.00410108, 0.0111361, 0.0461699]
selection = [4.58e-07,  7.5e-07,   2.166e-06, 7e-06,      2.2875e-05, 0.000153875, 0.000300583, 0.00102875, 0.00288704, 0.00709504, 0.0206419, 0.0830395]
stdsort   = [1.916e-06, 1.542e-06, 2.042e-06, 6.166e-06,  1.2416e-05, 2.1917e-05,  5.6541e-05,  0.000144917, 0.0002205, 0.00032025, 0.000490583, 0.00111092]
 
plt.figure()
plt.loglog(n, bubble,    '-o', linewidth=1.5, label='Bubble sort')
plt.loglog(n, insertion, '-o', linewidth=1.5, label='Insertion sort')
plt.loglog(n, selection, '-o', linewidth=1.5, label='Selection sort')
plt.loglog(n, stdsort,   '-o', linewidth=1.5, label='std::sort')
 
plt.xlabel('Dimensione del vettore (n)')
plt.ylabel('Tempo (s)')
plt.title('Confronto algoritmi di ordinamento')
plt.legend(loc='upper left')
plt.grid(True, which='both')
plt.tight_layout()
plt.savefig('plot_sorts.png', dpi=150)
plt.show()
 
