import requests
import time
import datetime
from bs4 import BeautifulSoup

# Connect to MONGODB
from pymongo import MongoClient
client = MongoClient('localhost', 27017)
db = client.Stocks


# Get HTML
url = 'https://finance.yahoo.com/gainers'


def getStocks(url):
    response = requests.get(url)
    html = response.text
    soup = BeautifulSoup(html, 'html.parser')
    table = soup.find('table', {'class': 'W(100%)'})
    trs = table.find_all('tr')
    for tr in trs:
        tds = tr.find_all('td')
        if len(tds) > 0:
            symbol = tds[0].text
            name = tds[1].text
            price = tds[2].text
            change = tds[3].text
            volume = tds[5].text
            doc = {
                'Symbol': symbol,
                'Name': name,
                'Price': price,
                'Change': change,
                'Volume': volume,
            }
            # Check if the document already exists
            if db.stocks.find_one({'Symbol': symbol}) is None:
                db.stocks.insert_one(doc)
                print('Added', symbol)
            else:
                db.stocks.update_one
                print('Updated', symbol)


while (True):
    getStocks(url)
    print('Updated at', datetime.datetime.now())
    time.sleep(180)
    # Kills the program after 15 minutes
    if datetime.datetime.now().minute == 15:
        break
