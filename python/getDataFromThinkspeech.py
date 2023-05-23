# import requests
# response = requests.get("https://api.thingspeak.com/channels/2160109/feeds.json?api_key=7NENWMEIZ8L1I6EF")
# response.content() # Return the raw bytes of the data payload
# response.text() # Return a string representation of the data payload

# print(response.json())
import xlwt
import requests

response = requests.get("https://api.thingspeak.com/channels/2160109/feeds.json?api_key=7NENWMEIZ8L1I6EF")

datalist = response.json()["feeds"]

book = xlwt.Workbook(encoding="utf-8")

sheet1 = book.add_sheet("Sheet 1")

sheet1.write(0, 0, "ID")
sheet1.write(0, 1, "Timestamp")
sheet1.write(0, 2, "Temperature")

i=0

for item in datalist:
    i = i + 1
    sheet1.write(i, 0, i)
    sheet1.write(i, 1, item['created_at'])
    sheet1.write(i, 2, item['field1'])

book.save("trial.xls")