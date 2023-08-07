<?php
header("Content-Type: text/html; charset=utf-8");
header("Transfer-Encoding: chunked");

// Function to send a chunk of data
function send_chunk($data) {
    echo dechex(strlen($data)) . "\r\n"; // Send the chunk size in hexadecimal
    echo $data . "\r\n"; // Send the chunk data followed by CRLF
    ob_flush();
    flush(); // Flush the output buffer to send the chunk immediately
}

// Start output buffering
ob_start();

// HTML content to be sent in chunks
$html = '
<!DOCTYPE html>
<html>
<head>
    <title>Chunked Transfer Encoding</title>
</head>
<body>
    <h1>Hello, Chunked Transfer Encoding!</h1>
    <p>This is an example of an HTML page generated using chunked transfer encoding in PHP.</p>
</body>
</html>
';

// Generate the response in chunks
send_chunk($html);

// Send the last zero-size chunk to signal the end of the response
echo "0\r\n\r\n";

ob_end_flush(); // End output buffering and send any remaining data
