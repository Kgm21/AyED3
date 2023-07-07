import tkinter as tk
from tkinter import ttk
from Pedidos.pedido import * 
from Manager.customerManager import *

class Aplication(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Gestion de Pedidos")
        self.geometry("500x500")

        self.pedidos_manager = PedidoManager()

        self.create_menu()
        self.create_table_view()

        # Cuando inicia la aplicación refresca la tabla clientes
        self.refresh_table()
        
    # Método que crea el menú:
    def create_menu(self):
        self.menu_bar = tk.Menu(self)

        # Opciones del menú
        pedido_menu = tk.Menu(self.menu_bar, tearoff=0)
        pedido_menu.add_command(
            label="Add pedido", command=self.add_pedido)
        pedido_menu.add_command(
            label="Modificar pedido", command=self.update_pedido)
        pedido_menu.add_command(
            label="Eliminar pedido", command=self.delete_pedido)
        pedido_menu.add_command(
            label="Listar todos", command=self.list_all_pedidos)

        self.menu_bar.add_cascade(label="Menú", menu=pedido_menu)
        self.config(menu=self.menu_bar)

    # Método que crea la vista en tabla para listar todos los clientes.
    def create_table_view(self):
        self.table_frame = tk.Frame(self)
        self.table_frame.pack(padx=10, pady=10)

        self.table = ttk.Treeview(self.table_frame, columns=(
            "id", "name", "surname", "address", "monto"))
        self.table.heading("id", text="Código")
        self.table.heading("name", text="Nombre")
        self.table.heading("surname", text="Apellido")
        self.table.heading("address", text="Dirección")
        self.table.heading("monto",text="monto")
        self.table.pack()

    # Método que refresca la tabla para mostrar los datos de los clientes guardados
    def refresh_table(self):
        self.table.delete(*self.table.get_children())
        pedidos = self.pedidos_manager.get_all_pedidos()
        if pedidos:
            for pedido in pedidos:
                self.table.insert("", "end", values=(
                    pedido.id, pedido.name, pedido.surname, pedido.address, pedido.monto))
        else:
            self.table.insert("", "end", values=(
                "No hay pedidos cargados.", "", "", "",""))
            
    # Método de vista para mostrar el formulario de inserción de un cliente
    def add_pedido(self):
        add_window = tk.Toplevel(self)
        add_window.title("Agregar un pedido")
        add_window.geometry("300x200")

        tk.Label(add_window, text="Nombre:").pack()
        name_entry = tk.Entry(add_window)
        name_entry.pack()

        tk.Label(add_window, text="Apellido:").pack()
        surname_entry = tk.Entry(add_window)
        surname_entry.pack()

        tk.Label(add_window, text="Dirección:").pack()
        address_entry = tk.Entry(add_window)
        address_entry.pack()

        tk.Label(add_window, text="Monto:").pack()
        monto_entry = tk.Entry(add_window)
        monto_entry.pack()

        def save_customer():
            name = name_entry.get()
            surname = surname_entry.get()
            address = address_entry.get()
            monto = monto_entry.get()

            pedidos = pedido(id, name, surname, address, monto)
            self.pedidos_manager.insert_pedido(pedidos)
            add_window.destroy()
            self.refresh_table()

        tk.Button(add_window, text="Guardar", command=save_customer).pack()

    # Método de vista para mostrar el formulario de borrado de un cliente
    def delete_pedido(self):
        delete_window = tk.Toplevel(self)
        delete_window.title("Eliminar un pedido")
        delete_window.geometry("200x100")

        tk.Label(delete_window, text="Código:").pack()
        id_entry = tk.Entry(delete_window)
        id_entry.pack()

        def delete():
            id = int(id_entry.get())
            self.pedidos_manager.delete_pedido(id)
            delete_window.destroy()
            self.refresh_table()

        tk.Button(delete_window, text="Eliminar", command=delete).pack()

    # Método de vista para mostrar el formulario de modificación de un cliente
    def update_pedido(self):
        update_window = tk.Toplevel(self)
        update_window.title("Modificar un Pedido")
        update_window.geometry("500x300")

        tk.Label(update_window, text="Código:").pack()
        id_entry = tk.Entry(update_window)
        id_entry.pack()

        tk.Label(update_window, text="Nombre:").pack()
        name_entry = tk.Entry(update_window)
        name_entry.pack()

        tk.Label(update_window, text="Apellido:").pack()
        surname_entry = tk.Entry(update_window)
        surname_entry.pack()

        tk.Label(update_window, text="Dirección:").pack()
        address_entry = tk.Entry(update_window)
        address_entry.pack()

        tk.Label(update_window, text="Monto:").pack()
        monto_entry = tk.Entry(update_window)
        monto_entry.pack()

        def update():
            id = int(id_entry.get())
            pedidos = self.pedidos_manager.get_pedido(id)
            if pedidos:
                pedidos.name = name_entry.get()
                pedidos.surname = surname_entry.get()
                pedidos.address = address_entry.get()
                pedidos.monto = monto_entry.get()
                self.pedidos_manager.update_pedido(pedidos)
                update_window.destroy()
                self.refresh_table()

        tk.Button(update_window, text="Modificar", command=update).pack()

    # Método de vista para mostrar los clientes en la tabla y por consola

    def list_all_pedidos(self):
        pedido = self.pedidos_manager.get_all_pedidos()

        # Crear una nueva ventana
        list_window = tk.Toplevel(self)
        list_window.title("List All pedidos")
        list_window.geometry("600x400")

        # Crear la tabla para mostrar los clientes
        table = ttk.Treeview(list_window, columns=("id", "name", "surname", "address", "monto"), show="headings")
        table.heading("id", text="ID")
        table.heading("name", text="Name")
        table.heading("surname", text="Surname")
        table.heading("address", text="Address")
        table.heading("monto", text="monto")

        # Agregar los clientes a la tabla
        if pedido:
            for pedido in pedido:
                table.insert("", "end", values=(pedido.id, pedido.name, pedido.surname, pedido.address, pedido.monto))

        # Empaquetar la tabla en la ventana
        table.pack()

        # Establecer el comportamiento de cierre de la ventana
        list_window.protocol("WM_DELETE_WINDOW", list_window.destroy)


    def quit(self):
        self.pedidos_manager.close_connection()
        self.destroy()
