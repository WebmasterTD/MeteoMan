# MeteoMan Server

Docker php mysql tutorial:

https://doc4dev.com/en/create-a-web-site-php-apache-mysql-in-5-minutes-with-docker/



## SQL

```sql
CREATE TABLE meteoman.MeasuredData (
	`timestamp` DATETIME NULL,
	temperature FLOAT DEFAULT 0.0 NULL,
	humidity FLOAT DEFAULT 0.0 NULL,
	rainfall FLOAT DEFAULT 0.0 NULL
)
```



## API

```json
{"timestamp":"2024-01-14 15:49:20","temperature":207.0,"humidity":"0.0","rainfall":"0"}
```

