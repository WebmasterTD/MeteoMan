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