SELECT * FROM (SELECT name FROM movies JOIN stars JOIN people ON movies.id = stars.movie_id
AND stars.person_id = people.id WHERE title IN (SELECT title FROM movies JOIN stars JOIN people ON movies.id = stars.movie_id
AND stars.person_id = people.id WHERE name = "Kevin Bacon" AND birth = "1958")) WHERE NOT name = "Kevin Bacon";