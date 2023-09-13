<?php
header("Transfer-Encoding: chunked");
header("Content-Encoding: none");

// Send chunk to browser
function send_chunk($chunk)
{
    // The chunk must fill the output buffer or php won't send it
    $chunk = str_pad($chunk, 4096);

    printf("%x\r\n%s\r\n", strlen($chunk), $chunk);
    flush();
}

// Send your content in chunks
for($i=0; $i<10; $i++)
{
    send_chunk("This is Chunk #$i.<br>\r\n");
    usleep(1000000);
}

// note that if you send an empty chunk
// the browser won't display additional output
echo "0\r\n\r\n";
flush();
