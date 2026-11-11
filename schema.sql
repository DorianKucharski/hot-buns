-- Schemat bazy danych Hot Buns (SQLite)

CREATE TABLE "odbiorcy" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`nazwa`	TEXT NOT NULL,
	`adres`	TEXT NOT NULL
);

CREATE TABLE "towary" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`nazwa`	TEXT NOT NULL,
	`waga`	REAL NOT NULL,
	`cena_netto`	REAL,
	`stawkavat`	REAL,
	`cena_brutto`	REAL
);

CREATE TABLE "numery_dokumentow" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`faktury`	INTEGER,
	`wz`	INTEGER,
	`paragony`	INTEGER
);

CREATE TABLE "faktury" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`numer_dokumentu`	TEXT NOT NULL,
	`id_odbiorcy`	INTEGER,
	`data`	TEXT,
	`wartosc_netto`	REAL,
	`wartosc_brutto`	REAL
);

CREATE TABLE "faktury_pozycje" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`numer_dokumentu`	TEXT NOT NULL,
	`indeks_towaru`	INTEGER,
	`nazwa_towaru`	TEXT,
	`ilosc`	REAL,
	`cena_netto`	REAL,
	`stawka_vat`	REAL,
	`cena_brutto`	REAL,
	`wartosc_netto`	REAL,
	`wartosc_brutto`	REAL
);

CREATE TABLE "wz" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`numer_dokumentu`	TEXT NOT NULL,
	`id_odbiorcy`	INTEGER,
	`data`	TEXT,
	`wartosc_netto`	REAL,
	`wartosc_brutto`	REAL
);

CREATE TABLE "wz_pozycje" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`numer_dokumentu`	TEXT NOT NULL,
	`indeks_towaru`	INTEGER,
	`nazwa_towaru`	TEXT,
	`ilosc`	REAL,
	`cena_netto`	REAL,
	`stawka_vat`	REAL,
	`cena_brutto`	REAL,
	`wartosc_netto`	REAL,
	`wartosc_brutto`	REAL
);

CREATE TABLE "paragony" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`numer_dokumentu`	TEXT NOT NULL,
	`data`	TEXT,
	`wartosc_netto`	REAL,
	`wartosc_brutto`	REAL
);

CREATE TABLE "paragony_pozycje" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`numer_dokumentu`	TEXT NOT NULL,
	`indeks_towaru`	INTEGER,
	`nazwa_towaru`	TEXT,
	`ilosc`	REAL,
	`cena_netto`	REAL,
	`stawka_vat`	REAL,
	`cena_brutto`	REAL,
	`wartosc_netto`	REAL,
	`wartosc_brutto`	REAL
);

INSERT INTO numery_dokumentow VALUES (0, 0, 0, 0);
