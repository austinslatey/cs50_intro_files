import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Ensure database tables are created
db.execute(
    """
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL,
        hash TEXT NOT NULL
    )
"""
)
db.execute(
    """
    CREATE TABLE IF NOT EXISTS purchase (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        price NUMERIC NOT NULL,
        transacted TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (user_id) REFERENCES users (id)
    )
"""
)
db.execute(
    """
    CREATE TABLE IF NOT EXISTS sale (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        price NUMERIC NOT NULL,
        transacted TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (user_id) REFERENCES users (id)
    )
"""
)


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
    # Retrieve user stocks and their quantities from the database
    rows = db.execute(
        """
        SELECT symbol, SUM(shares) AS total_shares
        FROM purchase
        WHERE user_id = :user_id
        GROUP BY symbol
        HAVING total_shares > 0
    """,
        user_id=session["user_id"],
    )

    # Calculate the current price and total value for each stock holding
    stocks = []
    total_value = 0

    # Iterate through each stock holding
    for row in rows:
        stock = lookup(row["symbol"])
        total_shares = row["total_shares"]
        price = stock["price"]
        total_stock_value = total_shares * price

        # Create a dictionary to store the stock details
        stock_details = {
            "symbol": stock["symbol"],
            "name": stock["name"],
            "shares": total_shares,
            "price": price,
            "total": total_stock_value,
        }

        stocks.append(stock_details)
        total_value += total_stock_value

    # Retrieve the user's current cash balance from the users table
    cash = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]

    # Render the template with the portfolio data
    return render_template(
        "layout.html", stocks=stocks, cash=cash, total_value=total_value
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure a symbol is provided
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure a valid symbol is provided
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol", 400)

        # Ensure a number of shares is provided
        if not request.form.get("shares").isdigit():
            return apology("must provide valid number of shares", 400)

        shares = int(request.form.get("shares"))

        # Ensure a positive number of shares is provided
        if shares <= 0:
            return apology("must provide positive number of shares", 400)

        # Calculate the total cost of the shares
        price = stock["price"]
        total_cost = shares * price

        # Retrieve the user's current cash balance
        cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]

        # Ensure the user has enough cash to make the purchase
        if total_cost > cash:
            return apology("not enough cash", 400)

        # Deduct the cost of the shares from the user's cash balance
        db.execute(
            "UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
            total_cost=total_cost,
            user_id=session["user_id"],
        )

        # Insert the purchase transaction into the purchase table
        db.execute(
            """
            INSERT INTO purchase (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)
        """,
            user_id=session["user_id"],
            symbol=stock["symbol"],
            shares=shares,
            price=price,
        )

        # Redirect to the index page
        return redirect(url_for("index"))

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Retrieve all the user's transactions from the purchase and sale tables
    purchases = db.execute(
        """
        SELECT symbol, shares, price, transacted
        FROM purchase
        WHERE user_id = :user_id
    """,
        user_id=session["user_id"],
    )

    sales = db.execute(
        """
        SELECT symbol, shares, price, transacted
        FROM sale
        WHERE user_id = :user_id
    """,
        user_id=session["user_id"],
    )

    # Render the template with the transaction history data
    return render_template("history.html", purchases=purchases, sales=sales)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = :username",
            username=request.form.get("username"),
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect(url_for("index"))

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect(url_for("login"))


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure a symbol is provided
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Lookup the stock symbol
        stock = lookup(request.form.get("symbol"))

        # Ensure a valid symbol is provided
        if not stock:
            return apology("invalid symbol", 400)

        # Render the template with the stock quote data
        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        # Generate password hash
        hash = generate_password_hash(request.form.get("password"))

        # Insert the new user into users table
        result = db.execute(
            "INSERT INTO users (username, hash) VALUES (:username, :hash)",
            username=request.form.get("username"),
            hash=hash,
        )

        # Check if the username is already taken
        if not result:
            return apology("username already taken", 400)

        # Remember which user has registered
        session["user_id"] = result

        # Redirect user to home page
        return redirect(url_for("index"))

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Ensure a symbol is provided
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure a valid symbol is provided
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol", 400)

        # Ensure a number of shares is provided
        if not request.form.get("shares").isdigit():
            return apology("must provide valid number of shares", 400)

        shares = int(request.form.get("shares"))

        # Ensure a positive number of shares is provided
        if shares <= 0:
            return apology("must provide positive number of shares", 400)

        # Retrieve the user's current shares of the stock
        user_shares = db.execute(
            """
            SELECT SUM(shares) AS total_shares
            FROM purchase
            WHERE user_id = :user_id AND symbol = :symbol
            GROUP BY symbol
        """,
            user_id=session["user_id"],
            symbol=stock["symbol"],
        )

        # Ensure the user has enough shares to sell
        if not user_shares or user_shares[0]["total_shares"] < shares:
            return apology("not enough shares", 400)

        # Calculate the total value of the shares
        price = stock["price"]
        total_value = shares * price

        # Deduct the sold shares from the user's purchase table
        db.execute(
            """
            INSERT INTO sale (user_id, symbol, shares, price)
            VALUES (:user_id, :symbol, :shares, :price)
        """,
            user_id=session["user_id"],
            symbol=stock["symbol"],
            shares=shares,
            price=price,
        )

        # Update the user's cash balance
        db.execute(
            "UPDATE users SET cash = cash + :total_value WHERE id = :user_id",
            total_value=total_value,
            user_id=session["user_id"],
        )

        # Redirect to the index page
        return redirect(url_for("index"))

    else:
        # Retrieve the symbols of stocks the user owns
        stocks = db.execute(
            """
            SELECT symbol
            FROM purchase
            WHERE user_id = :user_id
            GROUP BY symbol
            HAVING SUM(shares) > 0
        """,
            user_id=session["user_id"],
        )

        return render_template("sell.html", stocks=stocks)


if __name__ == "__main__":
    app.run(debug=True)

