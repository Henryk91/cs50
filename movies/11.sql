-- SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT title
FROM movies
WHERE id IN (SELECT DISTINCT stars.movie_id
            FROM stars
                 JOIN ratings
                   ON stars.movie_id = ratings.movie_id
            WHERE person_id = (SELECT id
                               FROM people
                               WHERE name='Chadwick Boseman')
            ORDER BY rating DESC
            Limit 5)
