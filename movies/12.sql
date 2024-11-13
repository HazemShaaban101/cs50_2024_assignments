--In 12.sql, write a SQL query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.
--      Your query should output a table with a single column for the title of each movie.
--      You may assume that there is only one person in the database with the name Bradley Cooper.
--      You may assume that there is only one person in the database with the name Jennifer Lawrence.

select title from movies where id in (select movie_id from stars where person_id in (select id from people where name = 'Bradley Cooper')) 
                        and id in (select movie_id from stars where person_id in (select id from people where name = 'Jennifer Lawrence'));
