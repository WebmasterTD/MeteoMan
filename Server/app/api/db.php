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
	$table = "MeasuredData";
	$insert = conn() -> prepare("INSERT INTO $table (timestamp, temperature, humidity, rainfall) VALUES(:timestamp, :temperature, :humidity, :rainfall);");
	$insert -> execute([":timestamp" => $timestamp->format('Y-m-d H:i:s'), ":temperature" => $temperature, ":humidity" => $humidity, ":rainfall" => $rainfall]);
	return conn() -> lastInsertId();
}

function get_data($start, $end) {
	$table = "MeasuredData";
	$select = conn() -> prepare("SELECT * FROM $table WHERE `timestamp` > :start  and `timestamp` < :end ;");
	$select -> execute([":start" => $start->format('Y-m-d H:i:s'), ":end" => $end->format('Y-m-d H:i:s')]);
	return $select -> fetchAll(\PDO::FETCH_ASSOC);
}