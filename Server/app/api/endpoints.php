<?php

require_once 'db.php';
use function Oink\{datetime, number, check};

function data_post() {
	$timestamp = datetime("timestamp");
	$temperature = number("temperature");
	$humidity = number("humidity");
	$rainfall = number("rainfall");
	DB\post_data($timestamp, $temperature, $humidity, $rainfall);
}

function data_getrange() {
	$start = datetime("start", format: "Y-m-d H:i:s", default: date_create('0000-01-01'), optional: true);
	$end = datetime("end", format: "Y-m-d H:i:s", default: date_create(), optional: true);
	return DB\get_data($start, $end);
}