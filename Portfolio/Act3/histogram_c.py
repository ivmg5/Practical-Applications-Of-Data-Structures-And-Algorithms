import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Read the CSV file
data = pd.read_csv("output.csv")

# Set Seaborn style
sns.set_style("whitegrid")

# Create a histogram using Seaborn
plt.figure(figsize=(20, 10))
chart = sns.barplot(data=data, x="IP", y="Frequency")
chart.set_xticklabels(chart.get_xticklabels(), rotation=90)  # Rotate x-axis labels for better readability
plt.title("Frequency of All IPs")
plt.tight_layout()
plt.show()
