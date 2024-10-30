import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Read the CSV file
data = pd.read_csv("output.csv")

# To better visualize the histogram, take a sample of the IPs with the highest frequency
top_ips = data.sort_values(by="Frequency", ascending=False).head(50)

# Set Seaborn style
sns.set_style("whitegrid")

# Create a histogram using Seaborn
plt.figure(figsize=(15, 10))
chart = sns.barplot(data=top_ips, x="IP", y="Frequency")
chart.set_xticklabels(chart.get_xticklabels(), rotation=90)  # Rotate x-axis labels for better readability
plt.title("Top 50 IPs with Highest Frequency")
plt.tight_layout()
plt.show()
