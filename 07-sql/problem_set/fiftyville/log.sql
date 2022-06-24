-- Keep a log of any SQL queries you execute as you solve the mystery.
-- get description of theft which took place on July 28, 2021 and that it took place on Humphrey Street.
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

/*
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted
today with three witnesses who were present at the time – each of their interview transcripts mentions
the bakery.
*/

-- get all license plates numbers from cars that visited the bakery on 7/28
SELECT id, activity, minute, license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 12 AND minute < 27;
/*
| id  | activity | minute | license_plate |
+-----+----------+--------+---------------+
| 259 | entrance | 14     | 13FNH73       |
| 260 | exit     | 16     | 5P2BI95       |
| 261 | exit     | 18     | 94KL13X       |
| 262 | exit     | 18     | 6P58WS2       |
| 263 | exit     | 19     | 4328GD8       |
| 264 | exit     | 20     | G412CB7       |
| 265 | exit     | 21     | L93JTIZ       |
| 266 | exit     | 23     | 322W7JE       |
| 267 | exit     | 23     | 0NTHK55       |
*/
-- license plate is probably 5P2BI95, exited at 10:16, get all info from bakery security on that license plate:
SELECT * FROM bakery_security_logs WHERE license_plate = "5P2BI95";

-- get list of possible license plates
SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 12 AND minute < 27;

-- get interview transcripts from 7/28
SELECT transcript FROM interviews WHERE month = 7 AND day = 28;

/*
Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot
and drive away. If you have security footage from the bakery parking lot, you might want to look for
cars that left the parking lot in that time frame.
|
| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived
at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
|
| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In
the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville
tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- get data on all atm withdrawals at Leggett Street the day of the theft
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw";
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 and atm_location = "Leggett Street" and transaction_type = "withdraw";

-- get data on all phone calls made the day of the theft that lasted less than a minute
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 and duration < 61;
SELECT caller, receiver FROM phone_calls WHERE month = 7 AND day = 28 and duration < 61;

-- get names of people who made withdrawals at leggett street on day of theft
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE month = 7 AND day = 28
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"));

-- get airport and flight information, earliest flight out of Fiftyville
SELECT * from airports WHERE city = "Fiftyville";
SELECT * from flights WHERE day = 29 AND month = 7 AND origin_airport_id = 8 ORDER BY hour LIMIT 1;
-- the earliest flight was id = 36, went to destination_airport_id = 4, which is NYC

-- get passenger info for flight 36
SELECT * FROM passengers WHERE flight_id = 36;
SELECT passport_number FROM passengers WHERE flight_id = 36;
SELECT name from people
WHERE passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id = 36);


-- SUSPECTS
SELECT name FROM people
WHERE phone_number IN (
    SELECT caller FROM phone_calls
    WHERE month = 7 AND day = 28 AND duration < 60)
AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26)
AND id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE month = 7 AND day = 28
        AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"))
AND passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id = 36);


-- ACCOMPLICES
SELECT name FROM people
WHERE phone_number = (
    SELECT receiver FROM phone_calls
    WHERE caller = (
        SELECT phone_number FROM people
        WHERE name = "Bruce")
        AND month = 7 AND day = 28 AND duration < 61);