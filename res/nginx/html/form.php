<?php
// Set headers for plain text response
header("Content-Type: text/plain");

// Get the raw HTTP request
$rawRequest = file_get_contents("php://input");

// Print the raw request
echo $rawRequest;
?>
