#!/usr/bin/env php
<?php
header("Content-Type: text/plain");

$postData = file_get_contents("php://stdin");

echo $postData;
?>
