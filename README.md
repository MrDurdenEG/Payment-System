# Payment-System

## Overview

This project is a simple C-based transaction system that simulates the process of handling card transactions, validating card details, and managing account balances. The system reads account data from a file, processes transactions, and updates the account database accordingly.

## Features

- **Card Data Validation**: The system checks the validity of cardholder names, expiration dates, and PANs (Primary Account Numbers).
- **Transaction Processing**: The system processes transactions by checking card expiration, comparing transaction amounts with maximum allowed amounts, and verifying account balances.
- **Account Status**: The system can detect blocked accounts and handle them appropriately.
- **File I/O Operations**: Account data is read from and written to files, ensuring data persistence.

## Project Structure

- **Headers/**: Contains header files with function prototypes and type definitions.
- **Source/**: Contains the source code for the application.
- **Data/**: Contains account and transaction data files used by the application.
- **main.c**: The entry point of the application.
- **app.c**: Contains the core application logic.

## How to Build and Run

1. **Compile the code**: Use a C compiler to compile the code.

   ```bash
   gcc -o transaction_system main.c app.c ...
   ```

   Replace `...` with any other source files in the project.

2. **Run the executable**:

   ```bash
   ./transaction_system
   ```

3. **Account Data File**: Ensure that your account data file is present in the specified directory (e.g., `Data/Accounts.txt`) and is formatted correctly. The format should include the account balance, account status (RUNNING/BLOCKED), and PAN.

4. **Transaction Data File**: The transaction data is stored in a file (e.g., `Data/TransInfo.txt`). Make sure this file is accessible and writable.

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

WELCOME TO THE TRANSACTION SYSTEM
====================================
Initializing the application...
Reading Accounts Data Base
====================================
Successfully loaded Accounts Data Base

Please enter cardholder name: John Doe \n
Please enter card expiration date (MM/YY): 12/25\n
Please enter card PAN: 1234567890123456\n
Validate card PAN\n
Please enter card transaction date(DD/MM/YYYY):01/12/2023\n
Check if the card is expired\n
Please enter maximum transaction amount : 5000\n
Please enter transaction amount: 1000\n
Check if the transaction amount is below the maximum allowed\n
Process the transaction\n
Transaction approved!\n
Updating Accounts in Data Base...\n

Thank you for using our system!\n
====================================
