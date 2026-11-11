# Hot Buns 🥐

A desktop application for handling sales and planning production in a small bakery.
University course project (2018/2019), written in **C++ / Qt 5** with an **SQLite** database.

## Features

- **Customers** – list, add and edit customers
- **Products** – product catalogue (weight, net price, VAT rate, gross price)
- **Sales** – issuing **WZ** (goods dispatch notes), **VAT invoices** and **receipts**, with automatic net/gross value calculation and document numbering
- **Sales overview** – browsing issued documents by date and type
- **Production** – a summary of how many units of each product need to be baked on a given day (totalled across all sales documents)

## Tech stack

- C++11, Qt 5 (Widgets, SQL)
- SQLite (`QSQLITE`)
- UI designed in Qt Designer (`.ui`)

## Building and running

1. Open `Projekt.pro` in Qt Creator (tested with Qt 5.12, MinGW).
2. Build the project.
3. Copy `baza.db` into the application's working directory (the build directory) – the application opens the database from a relative path.

`baza.db` contains sample test data. An empty database can be created from the schema:

```sh
sqlite3 baza.db < schema.sql
```

## Project structure

The user interface and source file names are in Polish.

| File | Description |
|------|-------------|
| `mainwindow.*` | Main window, module tabs, database connection |
| `odbiorcy_*` | Customer list and editing |
| `towary_*` | Product list and editing |
| `sprzedaz.*` | Issuing sales documents |
| `sprzedaz_przeglad.*` | Sales document overview |
| `produkcja.*` | Production planning |
| `schema.sql` | Database schema |
