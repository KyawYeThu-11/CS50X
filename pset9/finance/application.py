import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_mail import Mail, Message
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

#configuring email
app.config["MAIL_DEFAULT_SENDER"] = os.environ.get("MAIL_DEFAULT_SENDER")
app.config["MAIL_PASSWORD"] = os.environ.get("MAIL_PASSWORD")
app.config["MAIL_PORT"] = 587
app.config["MAIL_SERVER"] = "smtp.gmail.com"
app.config["MAIL_USE_TLS"] = True
app.config["MAIL_USERNAME"] = os.getenv("MAIL_USERNAME")
mail = Mail(app)



# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

#*****************************Interesting********************************************

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/forgot_password", methods=["GET", "POST"])
def forgot_password():
    if request.method == "POST":
        email = request.form.get("email")
        if not email:
            return apology("must provide email")

        message = Message("You are registered!", recipients=[email])
        mail.send(message)
        return redirect("/login")

    else:
        return render_template("forgot_password.html")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
    last_row = db.execute("SELECT * FROM purchase WHERE id=(SELECT MAX(id) FROM purchase WHERE username=?)", username[0]['username'])
    #GET
    #If the user first log in to the index page
    if not last_row:
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        return render_template('index.html', plugin_remaining = cash, plugin_money = float(cash[0]['cash']))

    #If the user visit index page again without buying anything
    if int(last_row[0]['condition']) == 0:
        rows = db.execute("SELECT * FROM render WHERE username=?", username[0]['username'])
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

        summation = 0;
        for row in rows:
            summation += row['total']
        money = summation + cash[0]['cash']

        return render_template ("index.html", plugin_rows = rows, plugin_remaining= cash, plugin_money = float(money))

    #Buy
    existing_symbols = db.execute("SELECT symbol FROM render WHERE username=?", username[0]['username'])
    #If the user hasn't bought anything
    if not last_row:
        db.execute("INSERT INTO render (symbol, company_name, shares, price, total, username) VALUES (?, ?, ?, ?, ?, ?)", last_row[0]['symbol'], last_row[0]['company_name'], last_row[0]['shares'], last_row[0]['price'], last_row[0]['total'], username[0]['username'])

    symbol_list=[]
    for item in existing_symbols:
        symbol_list.append(item['symbol'])

    #If the symbol is already there
    if last_row[0]['symbol'] in symbol_list:
        db.execute("UPDATE render SET shares=shares+(?) WHERE symbol=?", last_row[0]['shares'], last_row[0]['symbol'])
        db.execute("UPDATE purchase SET condition=0 WHERE id=(SELECT MAX(id) FROM purchase WHERE username=?)", username[0]['username'])
    else:
        db.execute("INSERT INTO render (symbol, company_name, shares, price, total, username) VALUES (?, ?, ?, ?, ?, ?)", last_row[0]['symbol'], last_row[0]['company_name'], last_row[0]['shares'], last_row[0]['price'], last_row[0]['total'], username[0]['username'])
        db.execute("UPDATE purchase SET condition=0 WHERE id=(SELECT MAX(id) FROM purchase WHERE username=?)", username[0]['username'])
#Sell


    #Updating price & total
    render_rows = db.execute("SELECT * FROM render WHERE username=?", username[0]['username'])
    for row in render_rows:
        symbol = row['symbol']
        shares = float(row['shares'])

        dictionary = lookup(symbol)
        price = float(dictionary['price'])
        total = shares * price

        db.execute("UPDATE render SET price=?, total=? WHERE symbol=?", price, total, symbol)

    rows = db.execute("SELECT * FROM render WHERE username=?", username[0]['username'])
    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

    summation = 0;
    for row in rows:
        summation += row['total']
    money = summation + cash[0]['cash']

    return render_template ("index.html", plugin_rows = rows, plugin_remaining= cash, plugin_money = float(money))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")



        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])

        if not symbol:
            return apology("how do you buy without specifying symbol")
        if not shares:
            return apology("are u gonna buy nothing?")

        try:
            shares = int(shares)
        except:
            return apology("the number of shares must be integer")

        if int(shares) <= 0:
            return apology("never have i seen that amount of shares")

        if float(shares) != int(shares):
            return apology("never have i seen that amount of shares")

        #If user input is OK
        dictionary = lookup(symbol)
        if dictionary == None:
            return apology("there is no such symbol")

        #If lookup successful
        company_name = dictionary['name']
        price = float(dictionary['price'])
        total = price * int(shares)

        if total > cash[0]['cash']:
            return apology("Don't buy unless you have enough money")

        #if purchase succssful
        db.execute("INSERT INTO purchase (symbol, company_name, shares, price, total, username, condition) VALUES (?, ?, ?, ?, ?, ?, 1)", symbol, company_name, shares, price, total, username[0]['username'])
        db.execute("UPDATE users SET cash = cash-(?) WHERE id = ?", total, session["user_id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])

    purchase_rows = db.execute("SELECT * FROM purchase WHERE username=?", username[0]['username'])
    for row in purchase_rows:
        db.execute("INSERT INTO history (transactions, symbol, company_name, shares, price, timestamp) VALUES ('buy', ?, ?, ?, ?, ?)", row['symbol'], row['company_name'], row['shares'], row['price'], row['timestamp'])

    sell_rows = db.execute("SELECT * FROM sell WHERE username=?", username[0]['username'])
    for row in sell_rows:
        db.execute("INSERT INTO history (transactions, symbol, company_name, shares, price, timestamp) VALUES ('sell', ?, ?, ?, ?, ?)", row['symbol'], row['company_name'], row['shares'], row['price'], row['timestamp'])

    rows = db.execute("SELECT * FROM history ORDER BY timestamp")
    db.execute("DELETE FROM history WHERE transactions='buy' OR transactions='sell'")
    return render_template("history.html", plugin_rows = rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("how do i find without specifying symbol?")

        dictionary = lookup(symbol)
        if dictionary == None:
            return apology("there is no such symbol")

        return render_template("quoted.html", company_name=dictionary['name'] , symbol=dictionary['symbol'], price=dictionary['price'])

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username_register = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        usernames_list = db.execute("SELECT username FROM users")

        if not username_register:
            return apology("must provide username")

        elif not password:
            return apology("must provide password")

        elif not confirm_password:
            return apology("must confirm passsword")

        elif password != confirm_password:
            return apology("password confirmation does not match")

        elif len(usernames_list) >= 1:
            for dictionary in usernames_list:
                if username_register == dictionary['username']:
                    return apology("username is taken")

        hash_password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username_register, hash_password)
        return redirect("/login")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')

        if not symbol:
            return apology("how do you sell without specifying symbol")
        if not shares:
            return apology("are u gonna sell nothing?")
        if int(shares) <= 0:
            return apology("never have i seen that amount of shares")

        username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
        shares_own = db.execute("SELECT shares FROM render WHERE username=? AND symbol=?", username[0]['username'], symbol)

        if int(shares_own[0]['shares']) < int(shares):
            return apology("you don't even have that amount of shares")

        dictionary = lookup(symbol)
        price = float(dictionary['price'])
        company_name = dictionary['name']

        total = price * int(shares)
        db.execute("UPDATE users SET cash=cash+(?) WHERE username=?", total, username[0]['username'])
        db.execute("UPDATE render SET shares=shares-(?) WHERE username=? AND symbol=?", shares, username[0]['username'], symbol)
        db.execute("INSERT INTO sell (symbol, company_name, shares, price, total, username) VALUES (?, ?, ?, ?, ?, ?)", symbol, company_name, shares, price, total, username[0]['username'])

        #copy-paste from '/' route
        render_rows = db.execute("SELECT * FROM render WHERE username=?", username[0]['username'])
        for row in render_rows:
            symbol = row['symbol']
            shares = float(row['shares'])

            dictionary = lookup(symbol)
            price = float(dictionary['price'])
            total = shares * price

            db.execute("UPDATE render SET price=?, total=? WHERE symbol=?", price, total, symbol)

        rows = db.execute("SELECT * FROM render WHERE username=?", username[0]['username'])
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

        summation = 0;
        for row in rows:
            summation += row['total']
        money = summation + cash[0]['cash']

        return render_template ("index.html", plugin_rows = rows, plugin_remaining= cash, plugin_money = float(money))

    else:
        username = db.execute("SELECT username FROM users WHERE id=?", session["user_id"])
        rows = db.execute("SELECT symbol FROM render WHERE username=?", username[0]['username'])
        return render_template('sell.html', plugin_rows=rows)

#**************** End of Interest ********************
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
