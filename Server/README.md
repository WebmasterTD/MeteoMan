# MeteoMan Server

Docker php mysql tutorial:

https://doc4dev.com/en/create-a-web-site-php-apache-mysql-in-5-minutes-with-docker/

https://github.com/jcarlosroldan/oink/tree/main



## SQL

```sql
CREATE TABLE `MeasuredData` (
  `timestamp` datetime DEFAULT CURRENT_TIMESTAMP,
  `temperature` float DEFAULT '0',
  `humidity` float DEFAULT '0',
  `rainfall` float DEFAULT '0'
)
```



## API

```json
{"timestamp":"2024-01-14 15:49:20","temperature":207.0,"humidity":"0.0","rainfall":"0"}
```

