import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Leer el archivo CSV
data = pd.read_csv("output.csv")

# Configurar el estilo de Seaborn
sns.set_style("whitegrid")

# Crear un histograma usando Seaborn
plt.figure(figsize=(20, 10))
chart = sns.barplot(data=data, x="IP", y="Frecuencia")
chart.set_xticklabels(chart.get_xticklabels(), rotation=90)  # Rotar las etiquetas del eje x para mejor visualización
plt.title("Frecuencia de Todas las IPs")
plt.tight_layout()
plt.show()
