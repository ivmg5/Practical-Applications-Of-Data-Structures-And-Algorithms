import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Leer el archivo CSV
data = pd.read_csv("output.csv")

# Para visualizar mejor el histograma, tomaremos una muestra de las IPs con mayor frecuencia
top_ips = data.sort_values(by="Frecuencia", ascending=False).head(50)

# Configurar el estilo de Seaborn
sns.set_style("whitegrid")

# Crear un histograma usando Seaborn
plt.figure(figsize=(15, 10))
chart = sns.barplot(data=top_ips, x="IP", y="Frecuencia")
chart.set_xticklabels(chart.get_xticklabels(), rotation=90)  # Rotar las etiquetas del eje x para mejor visualización
plt.title("Top 50 IPs con Mayor Frecuencia")
plt.tight_layout()
plt.show()
