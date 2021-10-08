import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        #Receiving ID if edit or delete button is pressed
        edit = request.form.get("medit")
        delete = request.form.get("pdelete")

        #If edit button is pressed
        if edit:
            name = request.form.get("mname")
            if not name:
                row = db.execute("SELECT * FROM birthdays")
                return render_template("index.html", plugin_condition="1", plugin_row = row)

            month = request.form.get("mmonth")
            if not month or int(month) not in range(1, 13, 1):
                row = db.execute("SELECT * FROM birthdays")
                return render_template("index.html", plugin_condition="2", plugin_row = row)

            day = request.form.get("mday")
            if not day or int(day) not in range(1, 32, 1):
                row = db.execute("SELECT * FROM birthdays")
                return render_template("index.html", plugin_condition="3", plugin_row = row)

            #If all the inputs are valid
            db.execute("UPDATE birthdays SET name=? WHERE id=?", name, edit)
            db.execute("UPDATE birthdays SET month=? WHERE id=?", month, edit)
            db.execute("UPDATE birthdays SET day=? WHERE id=?", day, edit)

            row = db.execute("SELECT * FROM birthdays")
            return render_template("index.html", plugin_row = row)

        #if delete button is pressed
        elif delete:
            db.execute("DELETE FROM birthdays WHERE id = ?", delete)
            row = db.execute("SELECT * FROM birthdays")
            return render_template("index.html", plugin_row = row)

        #if neither of the two button is pressed
        else:
            #Add the user's entry into the database
            name = request.form.get("pname")
            if not name:
                row = db.execute("SELECT * FROM birthdays")
                return render_template("index.html", plugin_condition="1", plugin_row = row)

            month = request.form.get("pmonth")
            if not month or int(month) not in range(1, 13, 1):
                row = db.execute("SELECT * FROM birthdays")
                return render_template("index.html", plugin_condition="2", plugin_row = row)

            day = request.form.get("pday")
            if not day or int(day) not in range(1, 32, 1):
                row = db.execute("SELECT * FROM birthdays")
                return render_template("index.html", plugin_condition="3", plugin_row = row)

            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            return redirect("/")

    #If the page is accessed by GET
    else:

        #Display the entries in the database on index.html
        row = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", plugin_row = row)
