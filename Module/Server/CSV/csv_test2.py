import csv

# CSVファイルの読み込み
with open('test_1.csv','r') as csv_file:
    reader = csv.DictReader(csv_file)
    for row in reader:
        print(row['Name'], row['Score'])
