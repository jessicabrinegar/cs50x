-- list the names of all songs in the database
SELECT name FROM songs;

-- list the names of all songs in increasing order of tempo
-- output a table with a single column for the name of each song
SELECT name FROM songs 
ORDER BY tempo ASC;

-- list the names of the top 5 longest songs, in descending order of length
-- output a table with a single column for the name of each song
SELECT name FROM songs 
ORDER BY duration_ms DESC LIMIT 5;

-- lists the names of any songs that have danceability, energy, and valence
-- greater than 0.75. Output a table with a single column for the name of each song
SELECT name FROM songs 
WHERE danceability > 0.75 
AND energy > 0.75 
AND valence > 0.75;

-- returns the average energy of all the songs
-- output a table with a single column and a single row containing the average energy
SELECT AVG(energy) FROM songs;

-- lists the names of songs that are by Post Malone.
-- output a table with a single column for the name of each song
SELECT songs.name FROM songs, artists 
WHERE songs.artist_id = artists.id 
AND artists.name = 'Post Malone';

-- returns the average energy of songs that are by Drake
SELECT AVG(energy) FROM songs 
JOIN artists ON songs.artist_id = artists.id 
WHERE artists.name = 'Drake';

-- lists the names of the songs that feature other artists.
SELECT name FROM songs WHERE name LIKE "%feat.%";