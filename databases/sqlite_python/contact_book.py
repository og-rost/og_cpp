from tkinter import *
import sqlite3


class ContactBook:

    def __init__(self):
        try:
            self.data_base = sqlite3.connect("contact_book.db")
            self.cursor = self.data_base.cursor()
            self.cursor.execute("""CREATE TABLE contacts (
                                name text,
                                surname text,
                                address text,
                                phone_number text
                                )""")
            self.root = Tk()
            self.contact_rows = []
            self.initGUI()
            self.root.mainloop()
        finally:
            self.data_base.close()

    def __exit__(self):
        self.data_base.close()

    def initGUI(self):
        self.root.title("OG")
        self.root.geometry("400x600")

        self.name = Entry(self.root, width=30)
        self.name.grid(row=0, column=1, padx=20, pady=(10, 0))
        name_label = Label(self.root, text="Name")
        name_label.grid(row=0, column=0, pady=(10, 0))

        self.surname = Entry(self.root, width=30)
        self.surname.grid(row=1, column=1)
        surname_label = Label(self.root, text="Surname")
        surname_label.grid(row=1, column=0)

        self.address = Entry(self.root, width=30)
        self.address.grid(row=2, column=1)
        address_label = Label(self.root, text="Address")
        address_label.grid(row=2, column=0)

        self.phone_number = Entry(self.root, width=30)
        self.phone_number.grid(row=3, column=1)
        phone_number_label = Label(self.root, text="Phone Number")
        phone_number_label.grid(row=3, column=0)

        self.select = Entry(self.root, width=30)
        self.select.grid(row=6, column=1, pady=5)
        select_label = Label(self.root, text="Select ID")
        select_label.grid(row=6, column=0, pady=5)

        submit_btn = Button(self.root, text="Add Record", command=self.submit)
        submit_btn.grid(row=4, column=0, padx=10, columnspan=2, pady=10, ipadx=100)

        query_btn = Button(self.root, text="Show Records", command=self.query)
        query_btn.grid(row=5, column=0, padx=10, columnspan=2, pady=10, ipadx=137)

        remove_btn = Button(self.root, text="Delete Record", command=self.remove)
        remove_btn.grid(row=7, column=0, padx=10, columnspan=2, pady=10, ipadx=136)

        edit_btn = Button(self.root, text="Edit Record", command=self.edit)
        edit_btn.grid(row=8, column=0, padx=10, columnspan=2, pady=10, ipadx=143)

    def initEditorGUI(self):
        self.root.withdraw()
        self.editor = Tk()
        self.editor.title("Edit contact")
        self.editor.geometry("400x300")

        self._name = Entry(self.editor, width=30)
        self._name.grid(row=0, column=1, padx=20, pady=(10, 0))
        _name_label = Label(self.editor, text="Name")
        _name_label.grid(row=0, column=0, pady=(10, 0))

        self._surname = Entry(self.editor, width=30)
        self._surname.grid(row=1, column=1)
        _surname_label = Label(self.editor, text="Surname")
        _surname_label.grid(row=1, column=0)

        self._address = Entry(self.editor, width=30)
        self._address.grid(row=2, column=1)
        _address_label = Label(self.editor, text="Address")
        _address_label.grid(row=2, column=0)

        self._phone_number = Entry(self.editor, width=30)
        self._phone_number.grid(row=3, column=1)
        _phone_number_label = Label(self.editor, text="Phone Number")
        _phone_number_label.grid(row=3, column=0)

        _save_btn = Button(self.editor, text="Save Contact", command=self.update)
        _save_btn.grid(row=4, column=0, padx=10, pady=10, columnspan=2, ipadx=145)

    def submit(self):
        try:
            self.cursor.execute("INSERT INTO contacts VALUES (:name, :surname, :add, :num)",
                                {
                                   'name': self.name.get(),
                                   'surname': self.surname.get(),
                                   'add': self.address.get(),
                                   'num': self.phone_number.get()
                                })
        except sqlite3.OperationalError:
            return

        self.data_base.commit()
        self.name.delete(0, END)
        self.surname.delete(0, END)
        self.address.delete(0, END)
        self.phone_number.delete(0, END)

    def query(self):
        for label in self.contact_rows:
            label.destroy()

        try:
            self.cursor.execute("SELECT *, oid FROM contacts")
        except sqlite3.OperationalError:
            return

        records = self.cursor.fetchall()
        r = 12
        for item in records:
            my_str = str(item[4]) + ". " + item[0] + " " + item[1] + " " + item[2] + " " + item[3]
            my_label = Label(self.root, text=my_str)
            my_label.grid(row=r, column=0, columnspan=2)
            self.contact_rows.append(my_label)
            r += 1

    def update(self):
        selected_id = self.select.get()
        try:
            self.cursor.execute("""UPDATE contacts SET
                              name = :first,
                              surname = :last,
                              address = :add,
                              phone_number = :num
                              WHERE oid = :oid""",

                                {
                                 'first': self._name.get(),
                                 'last': self._surname.get(),
                                 'add': self._address.get(),
                                 'num': self._phone_number.get(),
                                 'oid': selected_id
                                })
        except sqlite3.OperationalError:
            return

        self.data_base.commit()
        self.select.delete(0, END)
        self.editor.destroy()
        self.root.deiconify()

    def edit(self):
        selected_id = self.select.get()
        try:
            self.cursor.execute("SELECT * FROM contacts WHERE oid = " + selected_id)
            records = self.cursor.fetchall()
        except sqlite3.OperationalError:
            return

        self.initEditorGUI()
        self._name.insert(0, records[0][0])
        self._surname.insert(0, records[0][1])
        self._address.insert(0, records[0][2])
        self._phone_number.insert(0, records[0][3])

    def remove(self):
        try:
            self.cursor.execute("DELETE from contacts WHERE oid = " + self.select.get())
        except sqlite3.OperationalError:
            return
        self.select.delete(0, END)
        self.data_base.commit()


if __name__ == "__main__":
    cb = ContactBook()

