-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find a crime scene report matching the date and location of crime
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month == 07 AND day = 28 AND street = 'Humphrey Street';

-- Retrieve info about a person based on their name
SELECT * FROM people WHERE name = 'person_name';

-- Search for interviews with potential suspects
SELECT * FROM interviews WHERE year = 2021 AND month == 07 AND day = 28 AND transcript LIKE '%bakery%';

-- Investigate ATM transactions near crime location
SELECT * FROM atm_transactions WHERE atm_location = 'atm_location';


SELECT * FROM bakery_security_logs WHERE activity LIKE '%suspicious%';




-- Analyze bakey security logs for suspicious activity
SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name
FROM bakery_security_logs
JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 07
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25;


-- Gather flight information for potential escape routes
SELECT * FROM flights WHERE origin_airport_id = 'departure_airport_id' OR destination_airport_id = 'arrival_airport_id';

-- Identify passengers on specific flights
SELECT id, hour, minute, origin_airport_id, destination_airport_id
FROM flights
WHERE year = 2021
AND month = 07
AND day = 29
ORDER BY hour ASC
LIMIT 1;

UPDATE flights
SET origin_airport_id = airports.city
FROM airports
WHERE flights.origin_airport_id = airports.id;

UPDATE flights
SET destination_airport_id = airports.city
FROM airports
WHERE flights.destination_airport_id = airports.id;


-- Investigate bank account transactions of a suspect
SELECT people.name, atm_transactions.transaction_type
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.day = 28
AND atm_location = "Leggett Street"
AND atm_transactions.transaction_type = 'withdraw';

-- Check phone calls made by a specific person
SELECT caller, receiver FROM phone_calls
WHERE year = 2021
AND month = 07
AND day = 28
AND duration < 60;

UPDATE phone_calls
SET caller_name = people.name
FROM people
WHERE phone_calls.caller = people.phone_number;

UPDATE phone_calls
SET receiver_name = people.name
FROM people
WHERE phone_calls.receiver = people.phone_number;






-- any additional queries