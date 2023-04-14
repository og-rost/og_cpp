from tkinter import *
import sqlite3


query_results = []


def initMain():
    global conn
    global cursor

    conn = sqlite3.connect('contact_book.db')
    cursor = conn.cursor()


def initGUI():
    global f_name
    global l_name
    global city
    global number
    global select_box

    global root
    root = Tk()
    root.title('OG')
    # root.iconbitmap('path to icon')
    root.geometry("400x600")

    f_name = Entry(root, width=30)
    f_name.grid(row=0, column=1, padx=20, pady=(10, 0))
    l_name = Entry(root, width=30)
    l_name.grid(row=1, column=1)
    city = Entry(root, width=30)
    city.grid(row=2, column=1)
    number = Entry(root, width=30)
    number.grid(row=3, column=1)

    select_box = Entry(root, width=30)
    select_box.grid(row=9, column=1, pady=5)

    f_name_label = Label(root, text="First Name")
    f_name_label.grid(row=0, column=0, pady=(10, 0))
    l_name_label = Label(root, text="Last Name")
    l_name_label.grid(row=1, column=0)
    city_label = Label(root, text="City")
    city_label.grid(row=2, column=0)
    number_label = Label(root, text="Phone Number")
    number_label.grid(row=3, column=0)

    select_box_label = Label(root, text="Select ID")
    select_box_label.grid(row=9, column=0, pady=5)


def initButtons():
    submit_btn = Button(root, text="Add Record To Database", command=submit)
    submit_btn.grid(row=6, column=0, columnspan=2, pady=10, padx=10, ipadx=100)

    query_btn = Button(root, text="Show Records", command=query)
    query_btn.grid(row=7, column=0, columnspan=2, pady=10, padx=10, ipadx=137)

    delete_btn = Button(root, text="Delete Record", command=delete)
    delete_btn.grid(row=10, column=0, columnspan=2, pady=10, padx=10, ipadx=136)

    edit_btn = Button(root, text="Edit Record", command=edit)
    edit_btn.grid(row=11, column=0, columnspan=2, pady=10, padx=10, ipadx=143)


def initEditorGUI():
    root.withdraw()
    global editor
    editor = Tk()
    editor.title('Update A Record')
    editor.geometry("400x300")

    global f_name_editor
    global l_name_editor
    global city_editor
    global number_editor

    f_name_editor = Entry(editor, width=30)
    f_name_editor.grid(row=0, column=1, padx=20, pady=(10, 0))
    l_name_editor = Entry(editor, width=30)
    l_name_editor.grid(row=1, column=1)
    city_editor = Entry(editor, width=30)
    city_editor.grid(row=2, column=1)
    number_editor = Entry(editor, width=30)
    number_editor.grid(row=3, column=1)

    f_name_label = Label(editor, text="First Name")
    f_name_label.grid(row=0, column=0, pady=(10, 0))
    l_name_label = Label(editor, text="Last Name")
    l_name_label.grid(row=1, column=0)
    city_label = Label(editor, text="City")
    city_label.grid(row=2, column=0)
    number_label = Label(editor, text="Phone Number")
    number_label.grid(row=3, column=0)


def update(record_id: int):
    try:
        cursor.execute("""UPDATE contacts SET
            first_name = :first,
            last_name = :last,
            city = :city,
            number = :number

            WHERE oid = :oid""",
                       {
                        'first': f_name_editor.get(),
                        'last': l_name_editor.get(),
                        'city': city_editor.get(),
                        'number': number_editor.get(),
                        'oid': record_id
                       })
    except sqlite3.OperationalError:
        return

    conn.commit()

    editor.destroy()
    root.deiconify()


def edit():
    record_id = select_box.get()
    select_box.delete(0, END)
    try:
        cursor.execute("SELECT * FROM contacts WHERE oid = " + record_id)
        records = cursor.fetchall()
    except sqlite3.OperationalError:
        return

    initEditorGUI()

    for record in records:
        f_name_editor.insert(0, record[0])
        l_name_editor.insert(0, record[1])
        city_editor.insert(0, record[2])
        number_editor.insert(0, record[3])

    edit_btn = Button(editor, text="Save Record", command=lambda: update(record_id))
    edit_btn.grid(row=6, column=0, columnspan=2, pady=10, padx=10, ipadx=145)


def delete():
    try:
        cursor.execute("DELETE from contacts WHERE oid = " + select_box.get())
    except sqlite3.OperationalError:
        return

    conn.commit()

    select_box.delete(0, END)


def submit():
    try:
        cursor.execute("INSERT INTO contacts VALUES (:f_name, :l_name, :city, :number)",
                       {
                        'f_name': f_name.get(),
                        'l_name': l_name.get(),
                        'city': city.get(),
                        'number': number.get()
                       })
    except sqlite3.OperationalError:
        return

    conn.commit()

    f_name.delete(0, END)
    l_name.delete(0, END)
    city.delete(0, END)
    number.delete(0, END)


def query():
    for q in query_results:
        q.destroy()
    try:
        cursor.execute("SELECT *, oid FROM contacts")
    except sqlite3.OperationalError:
        return

    records = cursor.fetchall()

    i = 0
    for record in records:
        print_records = str(record[4]) + ": " + str(record[0]) + " " + str(record[1]) + " " + "\t\t" + str(record[2]) + "\t" + str(record[3])

        query_label = Label(root, text=print_records)
        query_label.grid(row=12 + i, column=0, columnspan=2)
        query_results.append(query_label)
        i += 1

    conn.commit()


'''
conn = sqlite3.connect('contact_book.db')
c = conn.cursor()

c.execute("""CREATE TABLE contacts (
        first_name text,
        last_name text,
        city text,
        number text
        )""")

'''

try:
    initMain()
    initGUI()
    initButtons()
    root.mainloop()
finally:
    conn.close()
