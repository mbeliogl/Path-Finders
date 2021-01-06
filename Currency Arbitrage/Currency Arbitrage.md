#### Currency Arbitrage

---

You can find more information on the Currency Arbitrage problem [here](https://stackoverflow.com/questions/2282427/interesting-problem-currency-arbitrage)

**---currency---**
To compile: make currency 
To run: currency.exe exchangerates.txt <output file> <source vertex> <destination vertex> <transaction cost> 
Ex: currency.exe exchangerates.txt currency_path.txt GBP EUR 0.003065

Description: The program checks the list of currency exchange rates and makes use of the Bellman Ford algorithm to detect a negative cycle. A negative cycle in this circumstance means that there is a way to perform a series of exchanges such that we end up with more currency X than what we started with. 
A sample output can be found in currency_path.txt 