#!/usr/bin/env php
<?php
// Establecer encabezados para una respuesta HTTP válida
header("Content-Type: text/plain");

// Leer el cuerpo de la solicitud desde la entrada estándar
$postData = file_get_contents("php://stdin");

echo $postData;
?>
