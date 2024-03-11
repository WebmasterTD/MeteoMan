<?php

require_once 'db.php';
use function Oink\{datetime, number, check};

function post_data() {
	$timestamp = datetime("timestamp");
	$temperature = number("temperature");
	$humidity = number("humidity");
	$rainfall = number("rainfall");
	DB\post_data($timestamp, $temperature, $humidity, $rainfall);
}

function data_get() {
	$timestamp = datetime("timestamp");
	$temperature = number("temperature");
	$humidity = number("humidity");
	$rainfall = number("rainfall");

	$start = = datetime("start", default: "0000-01-01 00:00:00");
	$end= datetime("end", default: date('Y-m-d H:i:s'));
	DB\post_data($timestamp, $temperature, $humidity, $rainfall);
}