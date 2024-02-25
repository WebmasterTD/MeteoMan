<?php

require_once 'oink.php';

Oink\serve('api/endpoints.php', base_path: '/api', debug: 'true');

include("meteo_page.html");

?>