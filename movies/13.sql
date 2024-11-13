--In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
--      Your query should output a table with a single column for the name of each person.
--      There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--      Kevin Bacon himself should not be included in the resulting list.

select name from people where id in
(select distinct person_id from stars where movie_id in (
select movie_id from stars where person_id =
(select id from people where name = 'Kevin Bacon' and birth = 1958))) and not id = (select id from people where name = 'Kevin Bacon' and birth = 1958);