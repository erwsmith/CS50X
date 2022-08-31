SELECT title, rating FROM movies JOIN ratings
ON movies.id = ratings.movie_id
WHERE movies.year = 2010
ORDER BY rating DESC, title;

-- This does the same, abbreviating table names as shorter variables:
SELECT title, rating FROM movies m JOIN ratings r
ON m.id = r.movie_id
WHERE m.year = 2010
ORDER BY rating DESC, title;