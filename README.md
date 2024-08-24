# Payment-System

## Overview

This project is a simple C-based transaction system that simulates the process of handling card transactions, validating card details, and managing account balances. The system reads account data from a file, processes transactions, and updates the account database accordingly. The project leverages a linked list data structure to efficiently manage account data in memory.

(there is some file and folders i didnt use them, don't care about 'em ,thanks )

(there is some file and folders i didnt use them, don't care about 'em ,thanks )

## Features

- **Card Data Validation**: The system checks the validity of cardholder names, expiration dates, and PANs (Primary Account Numbers).
- **Transaction Processing**: The system processes transactions by checking card expiration, comparing transaction amounts with maximum allowed amounts, and verifying account balances.
- **Account Status**: The system can detect blocked accounts and handle them appropriately.
- **File I/O Operations**: Account data is read from and written to files, ensuring data persistence.
- **Linked List Management**: Account data is stored and managed using a linked list, which allows for efficient dynamic memory management and easier data manipulation.

## Project Structure

- **Headers/**: Contains header files with function prototypes and type definitions.
- **Source/**: Contains the source code for the application.
- **Data/**: Contains account and transaction data files used by the application.
- **main.c**: The entry point of the application.
- **app.c**: Contains the core application logic, including linked list operations.

## How to Build and Run

1. **Compile the code**: Use a C compiler to compile the code.

   ```bash
   gcc -o transaction_system main.c app.c ...

   ```

2. **Account Data File**: Ensure that your account data file is present in the specified directory (e.g., `Data/Accounts.txt`) and is formatted correctly. The format should include the account balance, account status (RUNNING/BLOCKED), and PAN.

3. **Transaction Data File**: The transaction data is stored in a file (e.g., `Data/TransInfo.txt`). Make sure this file is accessible and writable.

## Usage

- The program will prompt you to enter card details such as the cardholder name, expiration date, and PAN.
- The system will then process the transaction by validating the card details and checking if the transaction can be approved.
- The result of the transaction will be displayed, and the transaction data will be saved.

## Customization

You can customize the application by modifying the source code. Key areas for customization include:

- **Account Database**: Modify the account data file to add or update accounts.
- **Transaction Logic**: Customize the transaction processing logic in `app.c`.

## Example

Upon running the program, you might see the following output:

# WELCOME TO THE TRANSACTION SYSTEM

Initializing the application...

# Reading Accounts Data Base

Successfully loaded Accounts Data Base

Please enter cardholder name: John Doe

Please enter card expiration date (MM/YY): 12/25

Please enter card PAN: 1234567890123456

Validate card PAN

Please enter card transaction date(DD/MM/YYYY):01/12/2023

Check if the card is expired

Please enter maximum transaction amount : 5000

Please enter transaction amount: 1000

Check if the transaction amount is below the maximum allowed

Process the transaction

Transaction approved!

Updating Accounts in Data Base...

Transaction Data info saved in AccountDB.txt

# Thank you for using our system!

====================================
