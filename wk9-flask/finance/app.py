# export API_KEY=pk_9e7bbea6befb4d10abd0b7141b2a3075

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, convert_to_int

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_stocks = db.execute("""SELECT SUM(number_shares) AS total_shares, stock_symbol, name 
                              FROM transactions WHERE user_id = ?
                              GROUP BY stock_symbol;""", session["user_id"])


    cash_amount = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    user_cash = cash_amount[0]["cash"]

    stocks = []
    total_value = user_cash
    for i in range(len(user_stocks)):
        stock_return = lookup(user_stocks[i]["stock_symbol"])
        stocks.append({"stock_symbol": user_stocks[i]["stock_symbol"],
                        "name": user_stocks[i]["name"],
                        "number_shares": user_stocks[i]["total_shares"],
                        "price": usd(stock_return["price"]),
                        "value": usd(stock_return["price"] * user_stocks[i]["total_shares"])
                    })
        total_value += stock_return["price"] * user_stocks[i]["total_shares"]
        print(total_value)
    return render_template("homepage.html", stocks=stocks, cash=user_cash, total_value = total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get info provided by user in form
        stock_symbol = request.form.get("symbol")
        amount_to_buy = convert_to_int(request.form.get("shares"))

        if not (stock_symbol and amount_to_buy):
            return apology("Provide a stock symbol and a valid amount of stock to buy", 400)

        # Lookup stock info
        stock_return = lookup(stock_symbol)
        if not stock_return:
            return apology("Stock not found for the given symbol", 400)

        # Return error if user doesn't have enough money
        price = stock_return["price"] * amount_to_buy
        user_cash_rows = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        if user_cash_rows[0]["cash"] < price:
            return apology("You don't have enough money to buy the specified amount of shares for this stock", 400)

        # Record transaction
        db.execute("""INSERT INTO transactions (user_id, stock_symbol, number_shares, price_per_share, name, transaction_type, datetime)
                    VALUES(?, ?, ?, ?, ?, ?, strftime('%s','now'));""", session["user_id"], stock_symbol, amount_to_buy, stock_return["price"], stock_return["name"], 'purchase')


        updated_cash = user_cash_rows[0]["cash"] - price

        # Change users cash amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", updated_cash, session["user_id"])

        return redirect("/")

    # For GET request, return the buy page
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("""SELECT stock_symbol, number_shares, price_per_share, transaction_type, datetime(datetime,'unixepoch') AS datetime, name 
                              FROM transactions WHERE user_id = ?;""", session["user_id"])
    for transaction in transactions:
        transaction["price_per_share"] = usd( transaction["price_per_share"] )
        transaction["datetime"] = str(transaction["datetime"])

    cash_amount = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    user_cash = usd(cash_amount[0]["cash"])

    return render_template("history.html", transactions = transactions, cash = user_cash)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?;", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("No stock found with provided symbol", 400)
        price = usd(quote["price"])
        return render_template("quoted.html", quote = quote, price = price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Must provide username", 400)

        elif (not password) or (not confirmation):
            return apology("Must provide password & confirm it", 400)

        elif password != confirmation:
            return apology("Password & confirmation must match", 400)

        # Query database for the username to ensure it doesn't exist
        rows = db.execute("SELECT * FROM users WHERE username = ?;", username)
        if len(rows) > 0:
            return apology("Username already exists", 400)

        hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        rows = db.execute("INSERT INTO users (username, hash) VALUES(?);", [username, hash])
        return redirect("/")
    # For GET request
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # get the symbol & # of shares of the stock that the user wants to sell
        stock_symbol = request.form.get("symbol")
        amount_to_sell = convert_to_int(request.form.get("shares"))

        # If user didn't provide correct info, return an error
        if not (stock_symbol and amount_to_sell):
            return apology("Provide a stock symbol and a valid amount of stock to sell", 400)

        # Return error if the specified stock symbol doesnt exist
        stock_return = lookup(stock_symbol)

        if not stock_return:
            return apology("Stock not found for the given symbol", 400)

        # Get the stocks that the user owns that match the given stock_symbol
        user_stocks = db.execute("""SELECT SUM(number_shares) AS total_shares
                                    FROM transactions WHERE user_id = ? AND stock_symbol = ?
                                    GROUP BY stock_symbol;""", session["user_id"], stock_symbol)

        if len(user_stocks) > 0:
            current_shares = user_stocks[0]["total_shares"]
            # If they don't own as many as they are trying to sell
            if amount_to_sell > current_shares:
                return apology("You don't own enough shares to sell the specified amount")
          
        else:
            return apology("You don't own any shares of this stock", 400)

        # Record transaction
        db.execute("""INSERT INTO transactions (user_id, stock_symbol, number_shares, price_per_share, name, transaction_type, datetime)
                                VALUES (?, ?, ?, ?, ?, ?, strftime('%s','now'));""", session["user_id"], stock_symbol,
                                -(amount_to_sell), stock_return["price"], stock_return["name"], 'sell')

        # Update user cash amount
        user_cash_rows = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
        new_amount = user_cash_rows[0]["cash"] + (amount_to_sell * stock_return["price"])
        db.execute("UPDATE users SET cash = ? WHERE id = ?;", new_amount, session["user_id"])

        return redirect("/")

    # GET request (visiting the sell page)
    else:
        owned_stocks = db.execute("""SELECT stock_symbol
                                    FROM transactions WHERE user_id = ?
                                    GROUP BY stock_symbol;""", session["user_id"])

        symbols = []

        for i in range(len(owned_stocks)):
            symbols.append(owned_stocks[i]["stock_symbol"])
        return render_template("sell.html", symbols = symbols)
