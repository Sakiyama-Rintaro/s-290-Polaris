import mysql.connector as mariadb

mariadb_connection = mariadb.connect(host='localhost', user='root', password='', database='testdb_1') #database='your database name'
cursor = mariadb_connection.cursor()

# SELECT
cursor.execute("SELECT * FROM table1") # ("SELECT * FROM 'your table name'")
for id, name in cursor:
    print(id)
    print(name)