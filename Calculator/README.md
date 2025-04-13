# Simple C Calculator

Ένας απλός υπολογιστής γραμμένος σε C που εκτελεί τις βασικές αριθμητικές πράξεις με εύχρηστο περιβάλλον διεπαφής χρήστη.

## Χαρακτηριστικά 

✅ **Βασικές λειτουργίες**
  - Πρόσθεση (+)
  - Αφαίρεση (-)
  - Πολλαπλασιασμός (*)
  - Διαίρεση (/)

✅ **Φιλικό προς το χρήστη**
  - Διαδραστικό μενού επιλογών
  - Καθαρή παρουσίαση αποτελεσμάτων
  - Δυνατότητα συνεχόμενων υπολογισμών

✅ **Αξιοπιστία**
  - Ολοκληρωμένος χειρισμός σφαλμάτων
  - Προστασία από διαίρεση με μηδέν
  - Έλεγχος εγκυρότητας εισόδου

## Εγκατάσταση και Χρήση

### Προαπαιτούμενα
- GCC Compiler
- Git (προαιρετικά)

### Οδηγίες εγκατάστασης

1. **Κλωνοποίηση του repository**
```bash
git clone https://github.com/Ramantan21/C_projects.git
```

2. **Μετάβαση στον κατάλογο του project**
```bash
cd Calculator
```
3. **Μεταγλώττιση του προγράμματος**
```bash
make
```
Εναλλακτικά, μπορείτε να χρησιμοποιήσετε απευθείας τον GCC:
```
gcc -Wall -Wextra -o calculator calculator.c
```

4. **Εκτέλεση του προγράμματος**
```bash
./calculator
```

## Παράδειγμα χρήσης

```bash
Calculator started. Press CTRL+C to get menu at any time.

Simple C Calculator
------------------
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Exit
Choose an operation (1-5): 1
Enter first number: 10
Enter second number: 5

Result: 10.00 + 5.00 = 15.00

Simple C Calculator
------------------
1. Addition
2. Subtraction
3. Multiplication
4. Division
5. Exit
Choose an operation (1-5): 5

Calculator exited.
```

## Συνεισφορά

Οι συνεισφορές είναι ευπρόσδεκτες! Ακολουθήστε τα παρακάτω βήματα:

1. Fork το repository
2. Δημιουργήστε ένα νέο branch (`git checkout -b feature/amazing-feature`)
3. Κάντε commit τις αλλαγές σας (`git commit -m 'Add some amazing feature'`)
4. Push στο branch (`git push origin feature/amazing-feature`)
5. Ανοίξτε ένα Pull Request

Για μεγαλύτερα θέματα, παρακαλούμε ανοίξτε πρώτα ένα issue για συζήτηση.
=======
Οι συνεισφορές είναι ευπρόσδεκτες!
Ανοίξτε ένα issue ή ένα pull request για οποιαδήποτε βελτίωση

