<?php
// Set headers for video content type
header("Content-Type: video/mp4");

// Specify the path to the video file
$videoFilePath = "vid.mp4"; // Replace with the actual video path

// Output the video file
readfile($videoFilePath);
?>
