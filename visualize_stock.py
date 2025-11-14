import pandas as pd
import matplotlib.pyplot as plt

# lets load the cleaned CSV file
filename = input("Enter the CSV filename to visualize: ")
df = pd.read_csv(filename)

# Lets convert 'Date' to datetime and sort
df['Date'] = pd.to_datetime(df['Date'])
df = df.sort_values('Date')

# Lets plot the closing price over time
plt.figure(figsize=(10, 5))
plt.plot(df['Date'], df['Close'], color='blue', linewidth=1.5)
plt.title("Stock Closing Price Over Time")
plt.xlabel("Date")
plt.ylabel("Closing Price ($)")
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()

# Lets plot daily returns histogram
plt.figure(figsize=(8, 5))
plt.hist(df['DailyReturn'].dropna(), bins=40, color='purple', alpha=0.7)
plt.title("Distribution of Daily Returns")
plt.xlabel("Daily Return (%)")
plt.ylabel("Frequency")
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.show()