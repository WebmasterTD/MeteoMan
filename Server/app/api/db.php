<?php

namespace DB;



$_conn = null;
function conn() {
	global $_conn;
	$host = "mysql";
	$dbname = "meteoman";
	$charset = "utf8";
	$port = "3306";
	if ($_conn === null) {
		$_conn = new \PDO(
			dsn: "mysql:host=$host;dbname=$dbname;charset=$charset;port=$port",
			username: "root",
			password: "konicaminolta",
		);
	}
	return $_conn;
}

function post_data($timestamp, $temperature, $humidity, $rainfall) {
	$insert = conn() -> prepare("INSERT INTO MeasuredData (timestamp, temperature, humidity, rainfall) VALUES(:timestamp, :temperature, :humidity, :rainfall);");
	$insert -> execute([":timestamp" => $timestamp->format('Y-m-d H:i:s'), ":temperature" => $temperature, ":humidity" => $humidity, ":rainfall" => $rainfall]);
	return conn() -> lastInsertId();
}