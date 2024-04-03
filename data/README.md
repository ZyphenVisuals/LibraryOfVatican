# Structure

## Accounts

Contains the account data for each user. Each file contains 3 lines:

1. Surname
2. Name
3. Password (Hashed)

## Inventory

Contains the books owned by the library. Each file contains 5 lines:

1. Title
2. Author
3. Publisher
4. Year
5. Quantity

When the quantity reaches 0, the file gets removed.

## Loans

Contains the books loaned out to each user, grouped in directories named SurnameName. The structure of the files is the same as in Inventory.
