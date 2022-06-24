SELECT DISTINCT name FROM people, directors, ratings
WHERE directors.person_id = people.id
AND ratings.movie_id = directors.movie_id
AND ratings.rating >= 9.0;