-- Keep a log of any SQL queries you execute as you solve the mystery.

-- first step: check crime log to find out more information on what happened
SELECT * FROM crime_Scene_reports
WHERE year = 2023
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- now i know some basic info about the crime, there are 3 witnesses, all interviewed the same day, and they all mentioned something about the bakery

-- second step: figure out what the whitnesses said about the thief
SELECT * FROM interviews
WHERE year = 2023
AND month = 7
AND day = 28;

-- from that we figure out some key notes to solving this mystery
	-- 1- thief left within 10 minutes of the time of theft, this means between 10:15 and 10:25
	-- 2- he withdrew cash from the ATM on Leggett Street earlier that day
	-- 3- he made a phone call that lasted less than a minute
	-- 4- his accomplice booked the earliest flight leaving Fiftyville the next day


-- third step: built a query to find the thief based on the witness info
SELECT * FROM people
WHERE license_plate IN
	(SELECT license_plate FROM bakery_security_logs
	WHERE year = 2023
	AND month = 7
	AND day = 28
	AND hour = 10
	AND minute > 15
	AND minute < 25
	AND activity = 'exit')

AND id IN
	(SELECT person_id FROM bank_accounts
	WHERE account_number IN
		(SELECT account_number FROM atm_transactions
		WHERE year = 2023
		AND month = 7
		AND day = 28
		AND atm_location = 'Leggett Street'
		AND transaction_type = 'withdraw'))

AND phone_number IN
	(SELECT caller FROM phone_calls
	WHERE year = 2023
	AND month = 7
	AND day = 28
	AND duration < 60)

AND passport_number IN
	(SELECT passport_number FROM passengers
	WHERE flight_id IN
		(SELECT id FROM flights
		WHERE year = 2023
		AND month = 7
		AND day = 29
		AND origin_airport_id IN
			(SELECT id FROM airports
			WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1));

-- this gives us the thief info
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- now lets use this to build the final answer table

-- fourth step: find the city the thief escaped to, and his accomplice, and put them all IN a nice neat table
SELECT (SELECT name FROM people WHERE id = 686048) as thief, (SELECT city FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND id IN
(SELECT flight_id FROM passengers WHERE passport_number = 5773159633))) as escape_city, name as accomplice FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND caller = '(367) 555-5533' AND duration < 60);

-- and finally we get the answers we seek
-- +-------+---------------+------------+
-- | thief |  escape_city  | accomplice |
-- +-------+---------------+------------+
-- | Bruce | New York City | Robin      |
-- +-------+---------------+------------+