<?php
// Set content type to HTML
header("Content-Type: text/html");

// Check if the request is a POST request
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Initialize an associative array to hold key-value pairs
    $formData = $_POST;

    // Append uploaded files to the form data
    foreach ($_FILES as $key => $file) {
        $formData[$key] = $file['name'];
    }

    // Display the form data in HTML format
    echo "<html><body><h1>Form Data</h1><ul>";
    foreach ($formData as $key => $value) {
        echo "<li>$key: $value</li>";
    }
    echo "</ul></body></html>";
} else {
    echo "<html><body><h1>Error</h1><p>Invalid request</p></body></html>";
}
?>
