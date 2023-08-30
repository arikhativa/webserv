<?php
// Set headers for plain text response
header("Content-Type: text/plain");

// $fileName = "/tmp/new_file.txt";
// $fileContent = "aaa";

// // Create the file
// if (file_put_contents($fileName, $fileContent) !== false) {
//     echo "File '$fileName' created successfully!";
// } else {
//     echo "Failed to create the file '$fileName'.";
// }

// Print request headers
foreach (getallheaders() as $name => $value) {
    echo "$name: $value\n";
}
echo "\n";

// Print request body (if present)
$requestBody = file_get_contents('php://input');
echo $requestBody;
?>
