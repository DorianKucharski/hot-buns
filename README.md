# Hot Buns 🥐

Desktopowa aplikacja do obsługi sprzedaży i planowania produkcji w małej piekarni.
Projekt zaliczeniowy na studia (2018/2019), napisany w **C++ / Qt 5** z bazą **SQLite**.

## Funkcje

- **Odbiorcy** – lista, dodawanie i edycja kontrahentów
- **Towary** – kartoteka produktów (waga, cena netto, stawka VAT, cena brutto)
- **Sprzedaż** – wystawianie dokumentów **WZ**, **faktur VAT** i **paragonów** z automatycznym przeliczaniem wartości netto/brutto i numeracją dokumentów
- **Przegląd sprzedaży** – przeglądanie wystawionych dokumentów wg daty i typu
- **Produkcja** – zestawienie, ile sztuk każdego towaru trzeba wyprodukować na dany dzień (suma ze wszystkich dokumentów sprzedaży)

## Technologie

- C++11, Qt 5 (Widgets, SQL)
- SQLite (`QSQLITE`)
- Interfejs zaprojektowany w Qt Designer (`.ui`)

## Uruchomienie

1. Otwórz `Projekt.pro` w Qt Creatorze (testowane na Qt 5.12, MinGW).
2. Zbuduj projekt.
3. Skopiuj `baza.db` do katalogu roboczego aplikacji (katalogu builda) – aplikacja otwiera bazę ze ścieżki względnej.

Plik `baza.db` zawiera przykładowe dane testowe. Pustą bazę można utworzyć ze schematu:

```sh
sqlite3 baza.db < schema.sql
```

## Struktura

| Plik | Opis |
|------|------|
| `mainwindow.*` | Okno główne, zakładki modułów, połączenie z bazą |
| `odbiorcy_*` | Wykaz i edycja odbiorców |
| `towary_*` | Wykaz i edycja towarów |
| `sprzedaz.*` | Wystawianie dokumentów sprzedaży |
| `sprzedaz_przeglad.*` | Przegląd dokumentów |
| `produkcja.*` | Planowanie produkcji |
| `schema.sql` | Schemat bazy danych |
