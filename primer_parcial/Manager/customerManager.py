import sqlite3
from Pedidos.pedido import *
from app.aplication import *


class PedidoManager:
    def __init__(self):
        self._connection = sqlite3.connect("db1.db")
        self._cursor = self._connection.cursor()
        self._create_table()    
    
    def _create_table(self):
        # Solo va a crear la tabla customers si no existe. 
        # Es mejor no permitir valores nulos
        self._cursor.execute("""          
            CREATE TABLE IF NOT EXISTS pedidos (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL, 
                surname TEXT NOT NULL,
                address TEXT NOT NULL,
                monto REAL );
        """)
        # Solo va a insertar el valor 99 de id atoincremental
        # para empezar cn código en valor igual a 100 si no 
        # existe la columna name con el valor 'customers',
        # esto significa que solo se insertará la primera
        # vez que se crea la tabla customers.
        self._cursor.execute("""
            INSERT INTO sqlite_sequence (name, seq)
            SELECT 'pedidos', 99
            WHERE NOT EXISTS (SELECT 1 FROM sqlite_sequence WHERE name = 'pedidos')
        """)   
        self._connection.commit()
        
    def insert_pedido(self, pedidos):
        self._cursor.execute("""
            INSERT INTO pedidos (name, surname, address, monto)
            VALUES (?, ?, ?, ?)
        """, (pedidos.name, pedidos.surname, pedidos.address, pedidos.monto))
        self._connection.commit()
        print("Pedido agregado correctamente.")

    def delete_pedido(self, id):
        self._cursor.execute("DELETE FROM pedidos WHERE id=?", (id,))
        self._connection.commit()
        print("Pedido eliminado correctamente.")

    def update_pedido(self, pedidos):
        self._cursor.execute("""
            UPDATE pedidos
            SET name=?, surname=?, address=?, monto=?
            WHERE id=?
        """, (pedidos.name, pedidos.surname, pedidos.address, pedidos.monto, pedidos.id))
        self._connection.commit()
        print("Pedido actualizado correctamente.")

    def get_pedido(self, id):
        self._cursor.execute("SELECT * FROM pedidos WHERE id=?", (id,))
        pedido_data = self._cursor.fetchone()
        if pedido_data:
            id, name, surname, address, monto = pedido_data
            return pedido(id, name, surname, address, monto)
        else:
            print("Pedido no encontrado.")
            return None

    def get_all_pedidos(self):
        self._cursor.execute("SELECT * FROM pedidos")
        pedidos_data = self._cursor.fetchall()
        pedidos = []
        for pedido_data in pedidos_data:
            id, name, surname, address, monto = pedido_data
            datos = pedido(id, name, surname, address,monto)
            pedidos.append(datos)
        return pedidos

    def close_connection(self):
        self._cursor.close()
        self._connection.close()