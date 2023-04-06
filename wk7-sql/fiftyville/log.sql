-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Describe why you’re running the query and/or what information you’re hoping to get out of it

-- To see how many crime scene reports there are and what the structure is to see what I'm dealing with
SELECT COUNT(id) FROM crime_scene_reports;
SELECT * FROM crime_scene_reports LIMIT 5;

-- The crime: July 28, 2021 @ Humphrey St.
-- Query crime scene reports that match the date of the crime, looking for information on Humphrey St.
SELECT * FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28;
-- RESULT:
--      (id-295), Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--      Interviews were conducted today with three witnesses who were present at the time –
--      each of their interview transcripts mentions the bakery.


-- Query the interviews, looking at ones from day of the crime & that mention the bakery
SELECT * FROM interviews 
WHERE year = 2021 AND month = 7 AND day = 28 
AND transcript LIKE "%bakery%";
-- RESULT:
--      (161)Ruth -- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery
--          parking lot and drive away. If you have security footage from the bakery parking lot, you might
--          want to look for cars that left the parking lot in that time frame.
--      (162)Eugene --  I don't know the thief's name, but it was someone I recognized. Earlier this morning,
--          before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--      (163)Raymond -- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--          I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked
--          the person on the other end of the phone to purchase the flight ticket


-- Query bakery security logs looking for license plate # of vehicle who left (exited) within 10 minutes of the theft (10:15 - 10:25)
SELECT license_plate FROM bakery_security_logs 
WHERE year = 2021 AND month = 7 AND day = 28 
AND hour = 10 AND minute BETWEEN 15 AND 25 
AND activity = 'exit';


-- Query people table to find info on people who have matching license plate numbers to the bakery security logs during time of theft
SELECT * FROM people 
WHERE license_plate IN(
    SELECT license_plate FROM bakery_security_logs 
    WHERE year = 2021 AND month = 7 AND day = 28 
    AND hour = 10 AND minute BETWEEN 15 AND 25 
    AND activity = 'exit');


-- Query phone calls to see what calls were made during time near theft. Duration should be < 60 secs, on 7/28/2021, and caller should have same phone # from people of previous query
SELECT * FROM phone_calls 
WHERE year = 2021 AND month = 7 AND day = 28 
AND duration < 60 AND caller IN(
    SELECT phone_number FROM people 
    WHERE license_plate IN(
        SELECT license_plate FROM bakery_security_logs 
        WHERE year = 2021 AND month = 7 AND day = 28 
        AND hour = 10 AND minute BETWEEN 15 AND 25 
        AND activity = 'exit'));


-- Select people that have the same phone number as those who have license plate number that matches the descriptions, and have same phone number as callers who made the call as described
SELECT id, name, passport_number FROM people 
WHERE license_plate IN(
    SELECT license_plate FROM bakery_security_logs 
    WHERE year = 2021 AND month = 7 AND day = 28 
    AND hour = 10 AND minute BETWEEN 15 AND 25 
    AND activity = 'exit') 
    AND phone_number IN(
        SELECT caller FROM phone_calls 
        WHERE year = 2021 AND month = 7 AND day = 28 
        AND duration < 60);



-- Select info of the people who were the receivers to the calls
SELECT * FROM people WHERE phone_number IN(
    SELECT receiver FROM phone_calls 
    WHERE year = 2021 AND month = 7 AND day = 28 
    AND duration < 60 AND caller IN(
        SELECT phone_number FROM people 
        WHERE license_plate IN(
            SELECT license_plate FROM bakery_security_logs 
            WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 
            AND minute BETWEEN 15 AND 25 
            AND activity = 'exit')));


-- Look at atm_transactions within described parameters of thief; want to find account #
SELECT * FROM atm_transactions 
WHERE year = 2021 AND month = 7 AND day = 28 
AND transaction_type = 'withdraw' 
AND atm_location = "Leggett Street";


-- Get person_id from those above account numbers so I can see which ones line up to my previous names
SELECT person_id FROM bank_accounts 
WHERE account_number IN(
    SELECT account_number FROM atm_transactions 
    WHERE year = 2021 AND month = 7 AND day = 28 
    AND transaction_type = 'withdraw' 
    AND atm_location = "Leggett Street");


-- Get names of those above people. These people are those who have account #s matching those that had transactions during described time of thief
SELECT name FROM people WHERE id IN(
    SELECT person_id FROM bank_accounts 
    WHERE account_number IN(
        SELECT account_number FROM atm_transactions 
        WHERE year = 2021 AND month = 7 AND day = 28 
        AND transaction_type = 'withdraw' 
        AND atm_locatio = "Leggett Street"));
-- DIANA & BRUCE ARE MATCHES


-- Get passenger info that matches the passport # of the 2 suspects
SELECT * FROM passengers 
WHERE passport_number = 3592750733 
OR passport_number = 5773159633;


-- Get flight IDs that leave from fiftyville and are on 7/29/2021 (day after theft)
SELECT flights.id FROM flights 
JOIN airports ON airports.id = flights.origin_airport_id 
WHERE airports.city = "Fiftyville" 
AND flights.year = 2021 
AND flights.month = 7 
AND flights.day = 29;


-- Get airport IDs for the given flights
SELECT origin_airport_id, destination_airport_id FROM flights 
WHERE id = 18 OR id = 36;


-- Get full airport info to match ids to previous queries, and names to ids
SELECT * FROM airports 
WHERE id = 8 OR id = 6 OR id = 4;


-- Get all flight info of the flights in suspect
SELECT * FROM flights 
WHERE id = 18 OR id = 36;


-- The interview said the suspect took the first flight out, which would be at the hour 8, so flight 36.
-- The passport # from the passenger on this flight (seen by previous query) is 5773159633
-- What's that persons name?
SELECT people.name FROM people 
WHERE passport_number = 5773159633;
-- Bruce
-- he was going to New York City
-- He was on the phone with Robin