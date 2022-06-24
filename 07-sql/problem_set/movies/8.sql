SELECT name FROM people, stars, movies
WHERE stars.person_id = people.id
AND stars.movie_id = movies.id
AND title = "Toy Story";