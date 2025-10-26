import mysql.connector as mariadb

# Connect to MariaDB Platform

mariadb_connection = mariadb.connect(host = 'localhost', user = 'root', password = '', database = 'testdb_1')
cursor = mariadb_connection.cursor()

# INSERT
cursor.execute("INSERT INTO table1(name) values('takahashi')")
mariadb_connection.commit()
