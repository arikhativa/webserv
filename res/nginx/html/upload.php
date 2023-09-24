<?php
// Set the content type to indicate that the response will be binary data
header('Content-Type: application/octet-stream');

// Check if a file was uploaded
if(isset($_FILES['file']) && $_FILES['file']['error'] == UPLOAD_ERR_OK) {
    // Get the temporary file name
    $tmpFile = $_FILES['file']['tmp_name'];

    // Read the content of the uploaded file
    $fileContent = file_get_contents($tmpFile);

    // Output the file content
    echo $fileContent;
} else {
    // If no file was uploaded or an error occurred, return an error message
    echo "Error uploading file.";
}
?>
