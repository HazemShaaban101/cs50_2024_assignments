--In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
--      Your query should output a table with a single column for the title of each movie.
--      You may assume that there is only one person in the database with the name Chadwick Boseman.

select title from movies
join ratings on movies.id = ratings.movie_id where movie_id in
(select movie_id from stars where person_id in
(select id from people where name = 'Chadwick Boseman')) order by rating desc limit 5;