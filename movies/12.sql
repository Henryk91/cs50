-- SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred
SELECT title
FROM   movies
WHERE  id IN (SELECT movie_id
              FROM   stars
              WHERE  movie_id IN (SELECT movie_id
                                  FROM   stars
                                  WHERE  person_id = (SELECT id
                                                      FROM   people
                                                      WHERE  NAME =
                                                     'Johnny Depp'))
                     AND person_id = (SELECT id
                                      FROM   people
                                      WHERE  NAME = 'Helena Bonham Carter'))