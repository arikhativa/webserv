<?php
// Set headers for chunked response and plain text content type
header("Transfer-Encoding: chunked");
header("Content-Type: text/plain");

// Generate and send chunked response
for ($i = 0; $i < 1000; $i++) {
	$chunk = "This is chunk $i, ";
    echo $chunk ; // Send the chunk data
	// flush();
}
sleep(100);
echo "\n\nsleepepepe\n\n" ; // Send the chunk data
// flush();
for ($i = 0; $i < 10000; $i++) {
	$chunk = "aaaa $i, ";
	echo $chunk ; // Send the chunk data
	// flush();
}

// Finalize response
?>
