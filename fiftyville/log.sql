-- Keep a log of any SQL queries you execute as you solve the mystery.

-- finds the ID of the crime and more information about time and witnesses
select * from crime_scene_reports where month = 7 and day = 28 and street = 'Humphrey Street';

-- three witnesses saw the thief and were interviewed the same day,
-- i gotta find out more info from their interviews.


-- look through interviews that happened that day, you will find useful information on the thief
select * from interviews where year = 2023 and month = 7 and day = 28;

-- after looking i found out the thief took his car within 10 minutes from the theft
-- the thief also withdrew some money from the atm on Leggett Street earlier that morning
-- while the thief was leaving, he called his accomplice and told him to buy plane tickets for the next day


-- find out information of people spotted leaving the bakery after the crime within the timeframe
-- who also withdrew money from the atm on Leggett Street earlier that day

select * from people where license_plate in
	(select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25)
and id in
	(select person_id from bank_accounts where account_number in
		(select account_number from atm_transactions where year = 2023 and month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw'));

-- i now have four suspects
--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--+--------+-------+----------------+-----------------+---------------+

-- now to find the thief, i need to crosscheck the list of suspects with the people with flights leaving fiftyville the next day, and for ease of use i will save them into a new TABLE
create table suspects_with_flights as
select * from people where passport_number in
	(select passport_number from passengers where flight_id in
		(select id from flights where year = 2023 and month = 7 and day = 29 and origin_airport_id in
			(select id from airports where city = 'Fiftyville')))
and passport_number in
	(select passport_number from people where license_plate in
		(select license_plate from bakery_security_logs where year = 2023 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute < 25)
	and id in
		(select person_id from bank_accounts where account_number in
			(select account_number from atm_transactions where year = 2023 and month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw')));
			
-- so now i can use select * from suspects_with_flights to find out current suspects_with_flights
select * from suspects_with_flights;

-- the last search yields 3 suspects
-- +--------+-------+----------------+-----------------+---------------+
-- |   id   | name  |  phone_number  | passport_number | license_plate |
-- +--------+-------+----------------+-----------------+---------------+
-- | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+-------+----------------+-----------------+---------------+

-- the witness mentioned something crucial, the thief told their friend in the call to book the earliest flight leaving from fiftyville the next day,
-- so if i list flights leaving fiftyville on the next day that have passengers from the list of suspects, and order it by time of flight, i will get the flight of the suspect
select * from flights where year = 2023 and month = 7 and day = 29 and id in
	(select flight_id from passengers where passport_number in
		(select passport_number from people where passport_number in
			(select passport_number from suspects_with_flights)
		and phone_number in
			(select caller from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60))) order by hour;

-- from this query we get the earliest flight with a passenger from our suspect list that made a phone call on the day of the theft that lasted less than a minute is this :
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |


-- this means that whoever is on that flight is our suspect so we search for the one on the flight from suspect list who made a short phone call on the day of the crime
select name from suspects_with_flights where passport_number in
	(select passport_number from passengers where flight_id = 36)
and phone_number in
	(select phone_number from suspects_with_flights where phone_number in
		(select caller from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60));
		
-- and voila, the thief is Bruce

-- now we get the city he travelled to and the accomplice he called
select (select city from airports where id = 4) as city, name from people where phone_number in
	(select receiver from phone_calls where id in
		(select id from phone_calls where year = 2023 and month = 7 and day = 28 and duration < 60 and caller in
			(select phone_number from suspects_with_flights where name = 'Bruce')));
			
-- this yields the desired info
-- +---------------+-------+
-- |     city      | name  |
-- +---------------+-------+
-- | New York City | Robin |
-- +---------------+-------+

