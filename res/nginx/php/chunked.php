<?php
// Set headers for chunked response and plain text content type
header("Transfer-Encoding: chunked");
header("Content-Type: text/plain");

// Generate and send chunked response
for ($i = 0; $i < 3; $i++) {
    $chunk = "This is chunk $i\r\n";
    // echo dechex(strlen($chunk)) . "\r\n"; // Send chunk size in hexadecimal
    echo $chunk ; // Send the chunk data
    // echo $chunk . "\r\n"; // Send the chunk data
	flush();
    sleep(1); // Introduce a delay between chunks (optional)
}
// echo "0\r\n\r\n";

// Finalize response
?>
