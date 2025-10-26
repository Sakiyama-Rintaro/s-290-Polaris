import mysql.connector as mariadb

mariadb_connection = mariadb.connect(host='localhost',user='root',password='',database='testdb_1')
cursor =mariadb_connection.cursor()

# UPDATE
id = 2
name = 'new_suzuki'
cursor.execute("UPDATE table1 SET name=%s WHERE id=%s", (name, id))
mariadb_connection.commit()
