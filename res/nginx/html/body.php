<?php
// Set headers for plain text response
header("Content-Type: text/plain");

// Get the request body
$requestBody = file_get_contents('php://input');

// Print the request body
echo $requestBody;
?>


