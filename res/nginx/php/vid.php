<?php
$videoFilePath = 'vid.mp4';

header('Content-Type: video/mp4');
header('Transfer-Encoding: chunked');
header('Content-Disposition: inline');


$handle = fopen($videoFilePath, 'rb');
if ($handle) {
    while (!feof($handle)) {
        $chunk = fread($handle, 1024 * 1024); // Read 1MB chunk from the file
        echo dechex(strlen($chunk)) . "\r\n"; // Send the chunk size in hexadecimal
        echo $chunk . "\r\n"; // Send the chunk data
        echo "\r\n"; // Send an additional CRLF to separate chunks

        // Delay for a short period to simulate streaming behavior
        usleep(100000); // Sleep for 100 milliseconds (adjust as needed)
    }
    fclose($handle);
}
