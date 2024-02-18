<?php

require_once 'oink.php';

Oink\serve('endpoints.php', base_path: '/api', debug: 'true');