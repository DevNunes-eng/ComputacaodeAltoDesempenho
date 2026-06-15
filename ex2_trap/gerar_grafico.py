import numpy as np
import matplotlib.pyplot as plt

# 1. Inserir os dados da tabela do relatório
n_valores = np.array([64, 256, 1024, 4096, 16384])
h_valores = np.pi / n_valores
erros = np.array([4.0161e-4, 2.5099e-5, 1.5687e-6, 9.8045e-8, 6.1278e-9])

# 2. Calcular a inclinação (m) usando regressão linear no espaço logarítmico
log_h = np.log10(h_valores)
log_e = np.log10(erros)
m, b = np.polyfit(log_h, log_e, 1)

print(f"Inclinação medida (m): {m:.2f}")

# 3. Configurar o gráfico em escala Log-Log
plt.figure(figsize=(7, 5))
plt.loglog(h_valores, erros, 'ro-', label=f'Dados Empíricos (Inclinação $m$ = {m:.2f})')

# Linha teórica ideal O(h^2) para comparação gráfica
plt.loglog(h_valores, 10**b * (h_valores**2), 'b--', alpha=0.7, label='Tendência Teórica $O(h^2)$')

# Customização do Layout para manter a sobriedade acadêmica
plt.title('Análise de Convergência Teórica — Regra do Trapézio', fontsize=12, fontweight='bold')
plt.xlabel('Tamanho do Espaçamento Geométrico ($h = \\pi / n$)', fontsize=10)
plt.ylabel('Erro Absoluto ($E$)', fontsize=10)
plt.grid(True, which="both", ls="--", color='gray', alpha=0.5)
plt.legend(loc='lower right', fontsize=10)

plt.savefig('convergencia_trap.png', dpi=300, bbox_inches='tight')
plt.close()
print("Gráfico 'convergencia_trap.png' gerado com sucesso!")