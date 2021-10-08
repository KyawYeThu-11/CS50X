--1
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2020 AND street = "Chamberlin Street";

--2 - finding interviewees who mentioned 'courthouse'
SELECT name FROM interviews WHERE transcript LIKE "%courthouse%";

--3 - filtering the interviewees after the crime who mentioned 'courthouse'
SELECT name FROM interviews WHERE month >= 7 AND transcript LIKE "%courthouse%";

--4 - reading transcript from those three witnesses
SELECT transcript FROM interviews WHERE name = "Raymond" OR  name ="Ruth" OR name = "Eugene";

--5 - reading account_number & amount from ATM
SELECT account_number, amount FROM atm_transactions WHERE year = 2020 AND month = 7 AND  day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street";

--6 - reading license_plate within time frame
SELECT license_plate, hour, minute FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour >= 10 AND hour <= 11 AND minute >= 15 AND minute <=25 AND activity = "exit";

--7 - looking at the airport name in Fiftyville
SELECT id, abbreviation, full_name  FROM airports WHERE city = "Fiftyville";

--8 - finding for flight.id based on the earliest flight
SELECT id, hour, minute FROM flights WHERE origin_airport_id = 8 AND year = 2020 AND month = 7 AND day=29;

--9 - finding passport numbers and seats of the possible flight
SELECT passport_number, seat FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE id = 36;

--10 - finding name, phone_number, passport_number by using license_plate from query 6
SELECT name, phone_number, passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE
year = 2020 AND month = 7 AND day = 28 AND hour >= 10 AND hour <= 11 AND minute >= 15 AND minute <=25 AND activity = "exit");

--11 - finding name, phone_number, passport_number by using account_number from query 5
SELECT name, phone_number, passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7
AND  day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street");

--12 - Just taking out the same names from the ouput of query 10(license_plate) and query 11(account_number)
SELECT name, phone_number, passport_number FROM (SELECT name, phone_number, passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE
year = 2020 AND month = 7 AND day = 28 AND hour >= 10 AND hour <= 11 AND minute >= 15 AND minute <=25 AND activity = "exit"))
WHERE name IN (SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7
AND  day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"));

--13 - Just taking out the same names from the output of query 12(license_plate+account_number) and query9
SELECT name, phone_number FROM (SELECT name, phone_number, passport_number FROM (SELECT name, phone_number, passport_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE
year = 2020 AND month = 7 AND day = 28 AND hour >= 10 AND hour <= 11 AND minute >= 15 AND minute <=25 AND activity = "exit"))
WHERE name IN (SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7
AND  day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"))) WHERE passport_number IN (SELECT passport_number FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE id = 36);

--14 - phone calls last than 1 minute on that day
SELECT caller, receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;

--15 - Let's say there are two people left after query13, Ernest & Danielle
--When compared with phone calls, Ernest call is there

--16 - The one Ernest call is Berthold
SELECT name FROM people WHERE phone_number = (375) 555-8161;

--17 - figuring out which city does flight_id = 36 flies to
SELECT city FROM airports JOIN flights ON airports.id = flights.destination_airport_id WHERE
destination_airport_id = (SELECT destination_airport_id FROM flights WHERE id = 36);